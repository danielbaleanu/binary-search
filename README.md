# Binary Search on Large Data Sets
A proof of concept for performing binary search on a dataset containing 100 million phone numbers using C++.

## Description
This project demonstrates the efficient implementation of binary search on a large dataset of 100 million phone numbers, each within the range of '0700000000' to '0799999999'. It also includes a name list generator where, by default, all names are labeled as 'Unknown'. The data is stored in two separate text files, and a Makefile is included for compilation.

## Getting Started
To use this project, follow these steps:

1. **Generate Data**: Run the generator programs to create the required text files. The order in which you run these generators doesn't matter, as they operate independently.

2. **Data Size**: Keep in mind that with the default `dbSize` value, each text file will occupy approximately 1GB of disk memory.

3. **Associate Names**: After generating the data, you can run the 'name-associator' program as many times as needed to associate names with specific phone numbers.

4. **Perform Binary Search**: Use the 'binary-search' program to retrieve the index and owner name of any phone number within the specified range.

For detailed instructions, please refer to the video tutorial provided in the repository.

## Repository Structure
- `name-list-generator/`: Contains name list generator program.
- `phone-numbers-generator/`: Contains phone numbers generator program.
- `name-associator/`: Code for associating names with phone numbers.
- `binary-search/`: Implementation of binary search.
- `Makefile`: Used to compile the programs.

## Video Tutorial
For step-by-step instructions and demonstrations, please check the video tutorial provided in the repository.

## License
This project is open-source.

## Author
- Băleanu Ștefan-Daniel (https://github.com/danielbaleanu)

Feel free to contribute or report issues by creating pull requests or opening issues on this repository.
