#include <fstream>
#include <iostream>
#include <limits>

std::fstream& GotoLine(std::fstream& file, unsigned int num);

void clear_console();

bool is_valid_target(const std::string& target, unsigned long start_point,
                     unsigned long db_size);

void display_progress_bar(unsigned int percentage, unsigned int j);

void associate_name_with_number(const std::string& target,
                                unsigned long start_point,
                                unsigned long db_size);

int main() {
    using namespace std;

    unsigned long db_size = 100000000, start_point = 700000000;
    string target;

    clear_console();

    cout << "Name association program:\n"
         << " - this program will associate one phone number with one name at "
            "a time;\n"
         << " - note that in order to modify the names contained in this "
            "database, it has to be rewritten via a temporary file, so this "
            "might take a while;\n"
         << " - press enter to continue.\n";
    cin.get();

    clear_console();

    while (true) {
        cout << "Input target phone number: ";
        cin >> target;
        if (is_valid_target(target, start_point, db_size)) {
            clear_console();
            associate_name_with_number(target, start_point, db_size);
            break;
        } else {
            clear_console();
            cout << "Please insert a valid phone number!\n";
        }
    }

    return 0;
}

std::fstream& GotoLine(std::fstream& file, unsigned int num) {
    file.seekg(std::ios::beg);
    for (unsigned int i = 0; i < num - 1; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return file;
}

void clear_console() { std::cout << "\033[2J\033[1;1H"; }

bool is_valid_target(const std::string& target, unsigned long start_point,
                     unsigned long db_size) {
    return (stoul(target) >= start_point &&
            stoul(target) < start_point + db_size);
}

void display_progress_bar(unsigned int percentage, unsigned int j) {
    std::string progress_bar[20];
    for (unsigned int i = 0; i < 20; i++) {
        progress_bar[i] = (i <= j) ? "■" : "▢";
    }

    clear_console();

    for (unsigned int i = 0; i < 20; i++) {
        std::cout << progress_bar[i];
    }
    std::cout << " " << percentage << "%\n";
}

void associate_name_with_number(const std::string& target,
                                unsigned long start_point,
                                unsigned long db_size) {
    std::ofstream file1("name-list-temp.txt");
    std::fstream file2("name-list.txt");

    std::string name, line;
    unsigned int percentage = 0, j = 0;

    clear_console();

    std::cout << "Insert a name for " << target << ": ";
    getline(std::cin >> std::ws, name);

    clear_console();

    for (unsigned long count = 0; count < db_size; count++) {
        if (count % (db_size / 100) == 0) {
            if (count % (db_size / 20) == 0 && count > 0) {
                j++;
            }
            percentage += 1;
            display_progress_bar(percentage, j);
        }

        if (count == stoul(target) - start_point) {
            file1 << name << "\n";
            getline(file2, line);
        } else {
            getline(file2, line);
            file1 << line << "\n";
        }
    }

    clear_console();

    std::cout << "The contact name has been successfully associated with the "
                 "number!\n";

    char oldname[] = "name-list-temp.txt";
    char newname[] = "name-list.txt";

    if (rename(oldname, newname) != 0)
        perror("Error renaming file");
    else
        std::cout << "Temporary file has been successfully removed!\n";

    file1.close();
    file2.close();
}