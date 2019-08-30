#include <iostream>


int main()
{
    std::cout << "Enter the total number of lottery balls: ";
    int total;
    std::cin >> total;
    std::cout << "Enter the number of drawn balls: ";
    int drawn;
    std::cin >> drawn;

    if (total < 0 or drawn < 0) {
        std::cout << "The number of balls must be a positive number." << std::endl;
        return EXIT_FAILURE;
    }
    if (total < drawn) {
        std::cout << "The maximum number of drawn balls is the total amount of balls." << std::endl;
        return EXIT_FAILURE;
    }


    return 0;
}
