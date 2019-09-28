#include <iostream>
#include <string>
#include <fstream>


int main()
{
    std::cout << "Input file: ";
    std::string input_file_name;
    std::cin >> input_file_name;
    std::cout << "Output file: ";
    std::string output_file_name;
    std::cin >> output_file_name;

    std::ifstream input_file(input_file_name);
    if ( ! input_file ){
        std::cout << "Error! The file " << input_file_name << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }

    int row_number = 1;
    std::string row = "";
    std::ofstream output_file(output_file_name);
    while ( getline(input_file, row) ) {
        output_file << row_number << " " << row << std::endl;
        row_number++;
    }
    input_file.close();
    output_file.close();

    return EXIT_SUCCESS;
}
