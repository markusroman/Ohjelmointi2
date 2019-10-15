#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

const std::string HELP_TEXT = "S = store id1 i2\n P = print id\n"
                              "C = count id\n D = depth id";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void print( std::map<std::string, std::vector<std::string>> datastructure,
           std::string id , int dotcount ) {
    std::string dots;
    for (int i = 0 ; i < dotcount ; ++i ) {
        dots += "..";
    }
    std::cout << dots << id << std::endl;
    if ( datastructure.find(id) != datastructure.end() ) {
        for ( std::string name : datastructure.at(id) ) {
            print(datastructure, name, dotcount + 1 );
        }
    }
}

int countSize( std::map<std::string, std::vector<std::string>> datastructure,
           std::string id , int sizecount = 0 ) {
    if ( datastructure.find(id) != datastructure.end() ) {
        for ( std::string name : datastructure.at(id) ) {
            sizecount = countSize(datastructure, name, sizecount + 1 );
        }
        return sizecount;
    }

    return sizecount;
}

int countDepth( std::map<std::string, std::vector<std::string>> datastructure,
             std::string id , int depthcount = 1 ) {
    if ( datastructure.find(id) != datastructure.end() ) {
        ++depthcount;
        for ( std::string name : datastructure.at(id) ) {
            countDepth(datastructure, name, depthcount);
        }
    }

    return depthcount;
}

int main()
{
    // TODO: Implement the datastructure here
    std::map<std::string, std::vector<std::string>> datastructure;

    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            if (datastructure.find(id1) == datastructure.end() ) {
                std::vector<std::string> friends;
                datastructure.insert({id1, friends});
            }
            datastructure.at(id1).push_back(id2);

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            print(datastructure, id, 0);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << countSize(datastructure, id) << std::endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << countDepth(datastructure, id) << std::endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
