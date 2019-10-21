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
#include <set>

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
// Tiedoston luku
bool readFile( map<string, vector<string>>& datastructure ) {

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
        vector<string> row_parts = split(row, ';', true);
        if ( row_parts.size() != 2 ) {
            cout << "Error: Invalid format in file." << endl;
            return false;
        }
        string line = row_parts.at(0);
        string station = row_parts.at(1);
        if ( datastructure.find(line) == datastructure.end() ) {
            vector<string> stations = { station };
            datastructure.insert({line, stations});
        } else if ( find(datastructure.at(line).begin(), datastructure.at(line).end(),
                         station) == datastructure.at(line).end() ) {
            datastructure.at(line).push_back(station);
        } else {
            cout << "Error: Station/line already exists." << endl;
        }
    }
    input_file.close();
    return true;
}

// The most magnificent function in this whole program.
// Prints a RASSE
void printRasse()
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

void printLine(map<string,vector<string>>& datastructure, string line) {
    if ( datastructure.find(line) == datastructure.end() ) {
        cout << "Error: Line could not be found." << endl;
        return;
    }
    cout << "Line " << line
         << " goes through these stations in the order they are listed:"
         << endl;
    for ( string station_name : datastructure.at(line) ) {
        cout << "- " << station_name << endl;
    }
}

void printStation( map<string,vector<string>>& datastructure, string station ) {
    set<string> lines;
    for ( pair<string,vector<string>> line_stations_pair : datastructure ) {
        for ( string station_name : line_stations_pair.second ) {
            if ( station == station_name ) {
                lines.insert(line_stations_pair.first);
            }
        }
    }
    if ( lines.size() == 0 ) {
        cout << "Error: Station could not be found." << endl;
        return;
    }
    cout << "Station " << station << " can be found on the following lines:" << endl;
    for ( string line_name : lines ) {
        cout << "- " << line_name << endl;
    }
}

vector<string> combineInput ( vector<string>& string_parts ) {
    string line_or_station = string_parts.at(1);
    vector<string> input_vec;
    if ( string_parts.size() > 2 ) {
        size_t i = 1;
        while ( i < string_parts.size() ) {
            string current_string = string_parts.at(i);
            if (current_string.at(0) == '"') {
                line_or_station = current_string + " " + string_parts.at(i + 1);
                line_or_station = line_or_station.substr(1, line_or_station.length() - 2);
                input_vec.push_back(line_or_station);
                ++i;
            } else {
                input_vec.push_back(line_or_station);
            }
            ++i;
        }
    } else {
        input_vec.push_back(line_or_station);
    }
    return input_vec;
}

int main()
{
    // Alustetaan tietorakenne map <linja, vector <pysäkki>>
    map<string,vector<string>> datastructure;

    // Suoritetaan tiedostonluku ja lopetetaan ohjelman
    // suoritus, mikäli tiedosto on virheellinen.
    if ( ! readFile(datastructure) ) {
        return EXIT_FAILURE;
    }
    printRasse();

    // Käyttöliittymä

    for ( ;; ) {
        cout << "tramway> ";
        string input;
        getline(cin, input);
        vector<string> input_parts = split(input, ' ', true);
        string command = input_parts.at(0);

        if ( command == "QUIT" ) {
            return EXIT_SUCCESS;

        } else if ( command == "LINES" ) {
            cout << "All tramlines in alphabetical order:" << endl;
            for ( pair<string,vector<string>> line_stations_pair : datastructure ) {
                cout << line_stations_pair.first << endl;
            }

        } else if ( command == "LINE" ) {
            if ( input_parts.size() < 2 ) {
                cout << "Error: Invalid input." << endl;
                continue;
            }
            vector<string> lines = combineInput(input_parts);
            printLine(datastructure, lines.at(0));

        } else if ( command == "STATIONS" ) {
            cout << "All stations in alphabetical order:" << endl;
            set<string> all_stations;
            for ( pair<string,vector<string>> line_stations_pair : datastructure ) {
                for ( string station_name : line_stations_pair.second ) {
                    all_stations.insert(station_name);
                }
            }
            for ( string station_name : all_stations ) {
                cout << station_name << endl;
            }

        } else if ( command == "STATION" ) {
            if ( input_parts.size() < 2 ) {
                cout << "Error: Invalid input." << endl;
                continue;
            }
            vector<string> stations = combineInput(input_parts);
            printStation(datastructure, stations.at(0));

        } else if ( command == "ADDLINE" ) {
            if ( input_parts.size() < 2 ) {
                cout << "Error: Invalid input." << endl;
                continue;
            }
            vector<string> lines = combineInput(input_parts);
            if ( datastructure.find(lines.at(0)) == datastructure.end() ) {
                vector<string> stations;
                datastructure.insert({lines.at(0), stations});
                cout << "Line was added." << endl;
            } else {
                cout << "Error: Station/line already exists." << endl;
            }

        } else if ( command == "ADDSTATION" ) {

        } else if ( command == "REMOVE" ) {

        } else {
            cout << "Error: Invalid input." << endl;
        }
    }

    return EXIT_SUCCESS;
}
