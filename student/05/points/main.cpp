#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

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
    std::string input_file_name;
    getline(std::cin, input_file_name);
    std::ifstream input_file(input_file_name);

    if ( ! input_file ) {
        std::cout << "Error! The file " << input_file_name << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Final scores:" << std::endl;
    std::string row = "";
    std::map <std::string, int> playerpoints = {};
    std::string name = "";
    int points = 0;
    while ( getline(input_file, row) ) {
        std::vector< std::string > parts  = split(row, ':');
        name = parts.at(0);
        points = stoi(parts.at(1));
        if ( playerpoints.find(name) != playerpoints.end() ) {
            playerpoints.at(name) += points;
        } else {
            playerpoints.insert({ name, points });
        }
    }
    input_file.close();

    for ( auto intelpair : playerpoints ) {
        std::cout << intelpair.first << ": " << intelpair.second << std::endl;
    }


    return EXIT_SUCCESS;
}
