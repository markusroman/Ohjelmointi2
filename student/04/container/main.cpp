#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        ints.push_back(new_integer);
    }
}

// TODO: Implement your solution here

bool same_values(std::vector< int >& integers) {
    for (int number: integers) {
        if (number != integers.at(0)) {
            return false;
        }
    }
    return true;
}

bool is_ordered_non_strict_ascending(std::vector< int >& integers) {
    std::vector< int >::size_type size = integers.size();
    if (size < 2){
        return true;
    }

    int length = size;
    for (int i = 1; i < length; i++) {
        if (integers.at(i - 1) > integers.at(i)) {
            return false;
        }
    }
    return true;
}
bool is_arithmetic_series(std::vector< int >& integers) {
    std::vector< int >::size_type size = integers.size();
    if (size < 3){
        return true;
    }
    int diff = integers.at(1) - integers.at(0);
    int length = size;

    for (int i = 2; i < length; i++) {
        if (integers.at(i) - integers.at(i - 1) != diff) {
            return false;
        }
    }

    return true;
}
bool is_geometric_series(std::vector< int >& integers) {
    std::vector< int >::size_type size = integers.size();
    if (size < 3){
        return true;
    }
    double div = integers.at(1) / integers.at(0);
    int length = size;

    for (int i = 2; i < length; i++) {
        if (integers.at(i) / integers.at(i - 1) != div) {
            return false;
        }
    }

    return true;
}


int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
