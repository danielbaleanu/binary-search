#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to clear the console screen
void clearConsole();

// Function to display a progress bar
void displayProgressBar(unsigned int percentage, unsigned int progressBarSize);

// Function to display the percentage sequence
void displayPercentageSequence(unsigned long current, unsigned long total,
                               unsigned int progressBarSize);

// Function to generate a name list database
void generateNameList(unsigned long dbSize);

int main() {
    unsigned long dbSize = 100000000;  // Default database size

    generateNameList(dbSize);

    return 0;
}

// Function to clear the console screen
void clearConsole() { cout << "\033[2J\033[1;1H"; }

// Function to display a progress bar
void displayProgressBar(unsigned int percentage, unsigned int progressBarSize) {
    vector<string> progressBar(progressBarSize, "▢");

    unsigned int progressBarIndex = (percentage * progressBarSize) / 100;
    for (unsigned int i = 0; i < progressBarIndex; i++) {
        progressBar[i] = "■";
    }

    clearConsole();

    for (unsigned int i = 0; i < progressBarSize; i++) {
        cout << progressBar[i];
    }

    cout << " " << percentage << "%\n";
}

// Function to display the percentage sequence
void displayPercentageSequence(unsigned long current, unsigned long total,
                               unsigned int progressBarSize) {
    unsigned int percentage =
        static_cast<unsigned int>((current * 100) / total);
    displayProgressBar(percentage, progressBarSize);
}

// Function to generate a name list database
void generateNameList(unsigned long dbSize) {
    const unsigned int progressBarSize = 20;

    clearConsole();

    cout << "Name list generator:\n"
         << " - this program will generate " << dbSize
         << " contacts labeled as 'Unknown';\n"
         << " - press enter to continue.\n";
    cin.get();

    // Open the output file
    ofstream file("name-list.txt");

    for (unsigned int count = 0; count < dbSize; count++) {
        if (count % (dbSize / 100) == 0) {
            displayPercentageSequence(count, dbSize, progressBarSize);
        }
        file << "Unknown\n";
    }

    clearConsole();

    cout << "Name list database has been generated (Default - " << dbSize
         << " 'Unknown' contacts)\n";
    file.close();
}
