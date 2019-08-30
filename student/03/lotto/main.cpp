#include <iostream>

unsigned long int kertoma(int n);

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
        return EXIT_SUCCESS;
    }
    if (total < drawn) {
        std::cout << "The maximum number of drawn balls is the total amount of balls." << std::endl;
        return EXIT_SUCCESS;
    }

    unsigned long int n = kertoma(total);
    unsigned long int p = kertoma(drawn);
    unsigned long int np = kertoma(total - drawn);

    unsigned long int prob = n / (np * p);
    std::cout << "The probability of guessing all " << drawn << " balls correctly is 1/" << prob << std::endl;

    return EXIT_SUCCESS;
}

unsigned long int kertoma(int x) {
    unsigned long int total = 1;
    if (x == 0) {
        return total;
    }

    while (x > 1) {
        total *= x;
        --x;
    }

    return total;
}
