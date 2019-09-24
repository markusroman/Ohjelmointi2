#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
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
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
