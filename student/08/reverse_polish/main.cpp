#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<char> char_vec;
    cout << "Input an expression in reverse Polish notation (end with #):\nEXPR> ";
    char input = '';

    while ( cin >> input ) {
        if ( input == '#' ) {
            break;
        } else if ( input - '0' >= 0 and input - '0' <= '9' ) {
            char_vec.push_back(input);
        } else if ( input == ('*', '+', '-', '/') ) {

        } else {
            cout << "Error: Unknown character" << endl;
            return EXIT_FAILURE;
        }

    }

}
