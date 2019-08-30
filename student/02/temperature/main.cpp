#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";
    int temp = 0;
    cin >> temp;

    double f = 0.0;
    double c = 0.0;

    f = temp * 1.8 + 32;
    c = (temp - 32) / 1.8;

    cout << temp << " degrees Celsius is " << f << " degrees Fahrenheit" << endl;
    cout << temp << " degrees Fahrenheit is " << c << " degrees Celsius" << endl;
    // Write your code here

    return 0;
}
