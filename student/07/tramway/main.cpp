/* RASSE-projekti (TIE-02201 Ohjelmointi 2: Perusteet)
 *
 * Ohjelma lukee tiedostosta linja-pysäkki -pareja ja tallentaa ne
 * tietorakenteeseen, josta käyttöliittymän avulla voidaan suorittaa
 * eri toimintoja.
 *
 * Program author
 * Name: Markus Röman
 * Student number: 281954
 * UserID: romanm
 * E-Mail: markus.roman@tuni.fi
 * */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;


vector<string> split(const string& s, const char delimiter, bool ignore_empty = false){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

bool readFile( map<string, vector<string>>& datastructure ) {
    // Tiedoston luku
    cout << "Give a name for input file: ";
    string input_file_name;
    getline(cin, input_file_name);
    ifstream input_file(input_file_name);
    if ( ! input_file ) {
        cout << "Error: File could not be read." << endl;
        return false;
    }
    string row = "";
    while ( getline(input_file, row) ) {
        vector<string> row_bits = split(row, ';', true);
        if ( row_bits.size() != 2 ) {
            cout << "Error: Invalid format in file." << endl;
            return false;
        }
        string line = row_bits.at(0);
        string station = row_bits.at(1);
        vector<string> stations = { station };
        if ( datastructure.find(line) == datastructure.end() ) {
            datastructure.insert({line, stations});
        } else if ( find(datastructure.at(line).begin(), datastructure.at(line).end(),
                         station) == datastructure.at(line).end() ) {
            datastructure.at(line).push_back(station);
        }
    }
    input_file.close();
    return true;
}

// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << endl;
}

// Short and sweet main.
int main()
{
    // Alustetaan tietorakenne map <linja, vector <pysäkki>>
    map<string,vector<string>> datastructure;

    if ( ! readFile(datastructure) ) {
        return EXIT_FAILURE;
    }

    for ( auto intel : datastructure ) {
        cout << intel.first << endl;
        for ( string station : intel.second ) {
            cout << "- " << station << endl;
        }
    }

    print_rasse();

    // Käyttöliittymä

    return EXIT_SUCCESS;
}
