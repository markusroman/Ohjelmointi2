#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int amount = 0;
    std::cin >> amount;
    int current = 1;
    while (current < amount + 1) {
        std::cout << current << std::endl;
        current++;
    }
}
