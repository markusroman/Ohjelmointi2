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

// Funktio jakaa komennot osiin ja palauttaa
// osat vectoriin lisättyinä merkkijonoina.
vector<string> split(const string& s, const char delimiter,
                     bool ignore_empty = false){
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

// Funktio lukee tiedostosta reitti-pysäkki -pareja ja lisää ne
// tietorakenteeseen. Paluuarvona on totuusarvo tiedostonluvun onnistumisesta.
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
            input_file.close();
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
            input_file.close();
            return false;
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

// Funktio tulostaa tietyn reitin pysäkit lisäysjärjestyksessä.
void printLine( const map<string,vector<string>>& datastructure,
                const string line) {
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

// Funktio tulostaa tietyn pysäkin sisältävät reitit aakkosjärjestyksessä.
void printStation( const map<string,vector<string>>& datastructure,
                   const string station ) {
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

// Funktio yhdistää käyttöliittymässä annetut syötteet (komentoa lukuunottamatta)
// kokonaisiksi merkkijonoiksi ja palauttaa ne vectorina.
vector<string> combineInput ( const vector<string>& string_parts ) {
    string line_or_station = string_parts.at(1);
    vector<string> input_vec;
    if ( string_parts.size() > 2 ) {
        size_t i = 1;
        while ( i < string_parts.size() ) {
            string current_string = string_parts.at(i);
            if (current_string.at(0) == '"') {
                line_or_station = current_string + " " + string_parts.at(i + 1);
                line_or_station = line_or_station.substr(
                            1, line_or_station.length() - 2);
                input_vec.push_back(line_or_station);
                ++i;
            } else {
                input_vec.push_back(string_parts.at(i));
            }
            ++i;
        }
    } else {
        input_vec.push_back(line_or_station);
    }
    return input_vec;
}

// Funktio lisää pysäkin tiettyyn kohtaan vectoria
// ja palauttaa yhtä alkiota pidemmän vektorin.
vector<string> addStation ( const vector<string>& station_vec,
                            const string station_to_add,
                            const string station_after_new ) {
    vector<string> help_vec = station_vec;
    help_vec.push_back("");
    size_t station_id = 0;
    for ( size_t i = 0 ; i < station_vec.size() ; ++i ) {
        if ( station_vec.at(i) == station_after_new ) {
            station_id = i;
        }
    }
    help_vec.at(station_id) = station_to_add;
    for ( size_t i = station_id ; i < station_vec.size() ; ++i ) {
        help_vec.at(i + 1) = station_vec.at(i);
    }
    return help_vec;
}

// Funktio suorittaa lisättävälle pysäkille virheentarkastelun
// ja kutsuu lisäysfumktiota, jos annetut syötteet ovat kelvollisia.
void checkStation ( map<string,vector<string>>& datastructure,
                    const vector<string>& combined_parts ) {
    // ADDSTATION linja pysäkki (seuraava_pysäkki)
    if ( combined_parts.size() < 2 ) {
        cout << "Error: Invalid input." << endl;
        return;
    }
    string line = combined_parts.at(0);
    string station_to_add = combined_parts.at(1);
    string station_after_new = "";
    bool station_found = false;
    if ( combined_parts.size() == 3 ) {
        station_after_new = combined_parts.at(2);
        for ( string station_name : datastructure.at(line) ) {
            if ( station_after_new == station_name ) {
                station_found = true;
            }
        }
    }
    if ( datastructure.find(line) == datastructure.end() ) {
        cout << "Error: Line could not be found." << endl;
        return;
    }
    for ( string station_name : datastructure.at(line) ) {
        if ( station_to_add == station_name ) {
            cout << "Error: Station/line already exists." << endl;
            return;
        }
    }
    if ( station_found ) {
        vector<string> station_vec = datastructure.at(line);
        datastructure.at(line) = addStation(station_vec, station_to_add, station_after_new);
    } else {
        datastructure.at(line).push_back(station_to_add);
    }
        cout << "Station was added." << endl;
}

// Funktio poistaa halutun pysäkin koko tietorakenteesta
void removeStation( map<string,vector<string>>& datastructure,
                    const string station_to_remove ) {
    bool remove_successful = false;
    for ( pair<string,vector<string>> line_stations_pair : datastructure ) {
        string line = line_stations_pair.first;
        size_t station_id = 0;
        for ( string station : line_stations_pair.second ) {
            if ( station == station_to_remove ) {
                datastructure.at(line).erase(datastructure.at(line).begin() + station_id);
                remove_successful = true;
            }
            ++station_id;
        }
    }
    if ( remove_successful ) {
        cout << "Station was removed from all lines." << endl;
    } else {
        cout << "Error: Station could not be found." << endl;
    }
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
            vector<string> combined_input = combineInput(input_parts);
            checkStation(datastructure, combined_input);

        } else if ( command == "REMOVE" ) {
            if ( input_parts.size() < 2 ) {
                cout << "Error: Invalid input." << endl;
                continue;
            }
            vector<string> combined_input = combineInput(input_parts);
            removeStation(datastructure, combined_input.at(0));

        } else {
            cout << "Error: Invalid input." << endl;
        }
    }

    return EXIT_SUCCESS;
}
