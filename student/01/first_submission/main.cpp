#include <iostream>
#include <string>

int main()
{

    std::string name = "";
    std::cout << "Enter your name: ";
    getline(std::cin, name);

    int age = 0;
    std::cout << "Enter your age: ";
    std::cin >> age;

    return EXIT_SUCCESS;
}
