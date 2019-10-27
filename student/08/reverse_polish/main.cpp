#include <iostream>
#include <vector>

using namespace std;

vector<char> split(const string& s, const char delimiter,
                     bool ignore_empty = false){
    vector<char> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        char new_char = atol(new_part);
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_char.empty()))
        {
            result.push_back(new_char);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        char new_char = tmp;
        result.push_back(new_char);
    }
    return result;
}

int main()
{
    cout << "Input an expression in reverse Polish notation (end with #):\nEXPR> ";
    string input;
    getline(cin, input);
    vector<char> input_parts = split(input, ' ', true);

}
