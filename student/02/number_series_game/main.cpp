#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int amount = 0;
    std::cin >> amount;
    int current = 1;
    while (current < amount + 1) {
        if (current % 3 == 0 and current % 7 == 0) {
            std::cout << "zip boing" << std::endl;
        } else if (current % 7 == 0) {
            std::cout << "boing" << std::endl;
        } else if (current % 3 == 0) {
            std::cout << "zip" << std::endl;
        } else {
            std::cout << current << std::endl;
        }

        current++;
    }
}
