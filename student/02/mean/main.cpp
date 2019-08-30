#include <iostream>

// Write here a function counting the mean value

int main()
{
    std::cout << "From how many integer numbers you want to count the mean value? ";
    int amount = 0;
    std::cin >> amount;

    double total_value = 0.0;
    int current = 1;

    if (amount < 1) {
        std::cout << "Cannot count mean value from " << amount << " numbers" << std::endl;
        return 0;
    }

    while (current < amount + 1) {
        std::cout << "Input " << current << ". number: ";
        int temp = 0;
        std::cin >> temp;

        total_value += temp;
        current++;
    }

    double final_mean = 0.0;
    final_mean = total_value / amount;
    std::cout << "Mean value of the given numbers is " << final_mean << std::endl;
}
