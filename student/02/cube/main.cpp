#include <iostream>
#include <cmath>


int main()
{
    std::cout << "Enter a number: ";
    int given_number = 0;
    std::cin >> given_number;

    int cube = pow(given_number, 3);



    std::cout << "The cube of " << given_number << " is " << cube << "." << std::endl;

    return 0;
}
