#include <fstream>
#include <iostream>
#include <limits>
#include <string>

// Function to move to a specific line in a file
std::fstream& GotoLine(std::fstream& file, unsigned int num);

// Function to clear the console screen
void clearConsole();

// Function to validate target phone number
bool isValidPhoneNumber(const std::string& target, unsigned long startPoint,
                        unsigned long dbSize);

// Function to update and display progress bar
void updateProgressBar(unsigned int percentage);

// Function to perform binary search
unsigned int binarySearchPhoneNumber(const std::string& target,
                                     std::fstream& file, unsigned long dbSize);

// Function to retrieve and print the associated name
void printAssociatedName(std::fstream& file, int index);

// Function for target number input and validation
std::string inputAndValidatePhoneNumber(unsigned long startPoint,
                                        unsigned long dbSize);

int main() {
    using namespace std;

    // Variables declaration
    string target;
    unsigned long startPoint = 700000000, dbSize = 100000000;

    clearConsole();

    cout << "Binary search program:\n"
         << " - This program will search for the target phone number and "
            "return its index and associated name;\n"
         << " - Note that due to the high volume of phone numbers contained in "
            "the database, this might take a while;\n"
         << " - Press enter to continue.\n";
    cin.get();

    clearConsole();

    // Target number input and validation
    target = inputAndValidatePhoneNumber(startPoint, dbSize);

    // Binary search in file1
    fstream file1("numbers.txt");
    int index = binarySearchPhoneNumber(target, file1, dbSize);

    if (index != -1) {
        clearConsole();
        cout << "Index: " << index << "\n";
        fstream file2("name-list.txt");
        printAssociatedName(file2, index);
        file2.close();
    } else {
        clearConsole();
        cout << "Phone number not found.\n";
    }

    file1.close();
    return 0;
}

// Function to move to a specific line in a file
std::fstream& GotoLine(std::fstream& file, unsigned int num) {
    file.seekg(std::ios::beg);
    for (unsigned int i = 0; i < num - 1; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return file;
}

// Function to clear the console screen
void clearConsole() { std::cout << "\033[2J\033[1;1H"; }

// Function to validate target phone number
bool isValidPhoneNumber(const std::string& target, unsigned long startPoint,
                        unsigned long dbSize) {
    return (stoul(target) >= startPoint && stoul(target) < startPoint + dbSize);
}

// Function to update and display progress bar
void updateProgressBar(unsigned int percentage) {
    const unsigned int progressBarWidth = 20;
    unsigned int completed = progressBarWidth * percentage / 100;
    for (unsigned int i = 0; i < progressBarWidth; ++i) {
        if (i < completed) {
            std::cout << "■";
        } else {
            std::cout << "▢";
        }
    }
    std::cout << " " << percentage << "%\n";
}

// Function to perform binary search
unsigned int binarySearchPhoneNumber(const std::string& target,
                                     std::fstream& file, unsigned long dbSize) {
    unsigned long left = 1, right = dbSize;
    unsigned int steps = 0;
    unsigned int count = 0;
    unsigned int j = 0;

    while (dbSize != 1) {
        dbSize /= 2;
        steps++;
    }

    while (left <= right) {
        unsigned int percentage = count * 100 / steps;
        if (percentage >= (j + 1) * 5) {
            updateProgressBar(percentage);
            j++;
        }

        unsigned int mid = (left + right) / 2;
        GotoLine(file, mid);
        std::string line;
        file >> line;

        if (stoul(line) > stoul(target)) {
            right = mid - 1;
        } else if (stoul(line) < stoul(target)) {
            left = mid + 1;
        } else {
            return mid;
        }

        count++;
        clearConsole();
    }

    return -1;  // Not found
}

// Function to retrieve and print the associated name
void printAssociatedName(std::fstream& file, int index) {
    GotoLine(file, index);
    std::string line;
    getline(file, line);
    std::cout << "The requested phone number is associated with: " << line
              << "\n";
}

// Function for target number input and validation
std::string inputAndValidatePhoneNumber(unsigned long startPoint,
                                        unsigned long dbSize) {
    std::string target;
    while (true) {
        std::cout << "Input target phone number: ";
        std::cin >> target;
        if (isValidPhoneNumber(target, startPoint, dbSize)) {
            return target;
        } else {
            clearConsole();
            std::cout << "Please insert a valid phone number!\n";
        }
    }
}
