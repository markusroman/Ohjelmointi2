#include <iostream>
#include <string>
#include <cctype>

bool faulty_key(std::string key);

int main()
{
    std::cout << "Enter the encryption key: ";
    std::string key = "";
    std::cin >> key;

    if (faulty_key(key)) {
        return EXIT_FAILURE;
    }

    std::cout << "Enter the text to be encrypted: ";
    std::string message = "";
    std::cin >> message;
    std::string::size_type msg_length = message.length();

    std::string alphabets = "abcdefghijklmnopqrstuvwxyz";
    std::string encryption = "";
    char current = 'a';
    int current_id = 0;
    for (unsigned int x = 0; x < msg_length; ++x) {
        current_id = alphabets.find(message.at(x));
        current = key.at(current_id);
        encryption += current;
    }

    std::cout << "Encrypted text: " << encryption << std::endl;

    return EXIT_SUCCESS;
}

bool faulty_key(std::string key) {
    std::string::size_type key_length = key.length();
    if (key_length != 26) {
        std::cout << "Error! The encryption key must contain 26 characters." << std::endl;
        return true;
    }
    std::string help_string = "abcdefghijklmnopqrstuvwxyz";
    for (int x = 0; x < 26; ++x) {

        std::string::size_type location = key.find(help_string.at(x));

        if (! islower(key.at(x))) {
            std::cout << "Error! The encryption key must contain only lower case characters." << std::endl;
            return true;
        }
        if (location == std::string::npos) {
            std::cout << "Error! The encryption key must contain all alphabets a-z." << std::endl;
            return true;
        }
    }

    return false;
}
