#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

std::vector< std::string > split(std::string line, char separator, bool ignore = false) {
    std::vector< std::string > parts;

    while (line.find(separator) != std::string::npos) {
        std::string part = line.substr(0, line.find(separator));
        if (part.length() != 0) {
            parts.push_back(part);
        }
        if (ignore == false and part.length() == 0) {
            parts.push_back("");
        }

        line = line.substr(line.find(separator) + 1);

    }
    if (line.length() != 0) {
        parts.push_back(line);
    } else if (ignore == false and line.length() == 0){
        parts.push_back("");
    }

    return parts;
}

int main()
{
    std::cout << "Input file: ";
    std::string input_file_name = "";
    getline(std::cin, input_file_name);
    std::ifstream input_file(input_file_name);
    if ( ! input_file ) {
        std::cout << "Error! The file " << input_file_name << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }
    std::map <std::string, std::set<int>> wordmap;
    std::string row = "";
    int row_number = 1;
    while ( getline(input_file, row) ) {
        std::vector< std::string > parts  = split(row, ' ');
        for ( std::string word : parts ) {

            if ( wordmap.find(word) != wordmap.end() ) {
                wordmap.at(word).insert(row_number);
            } else {
                std::set <int> line_numbers;
                line_numbers.insert(row_number);
                wordmap.insert( {word, line_numbers} );
            }
        }
        ++row_number;
    }

    for ( auto intelpair : wordmap ) {
        std::string word = intelpair.first;
        std::set<int> lines = intelpair.second;
        std::cout << word << " " << lines.size() << ": ";
        int is_first_line = true;
        for ( int line_number : lines ) {
            if ( is_first_line ) {
                std::cout << line_number;
                is_first_line = false;
            } else {
                std::cout << ", " << line_number;
            }
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}
