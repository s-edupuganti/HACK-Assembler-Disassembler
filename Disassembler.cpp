#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <bitset>
#include <vector>
#include <sstream>

using namespace std;


void toDecimal(string &str) {

    int number;
    string num;

    bitset<16> binaryBitset(str);

    number = (int)(binaryBitset.to_ulong());

    num = to_string(number);

    cout << "@" + num << endl;

}

bool valuePresent(unordered_map<string, string> table, string &key, string &value) {

    bool isValPresent = false;

    auto i = table.begin();

    while (i != table.end()) {
        if (i->second == value) {
            isValPresent = true;
            key = i->first;
        }

        i++;
    }

    return isValPresent;

    
}

int main () {

    unordered_map<string, string> compTable;
    unordered_map<string, string> destTable;
    unordered_map<string, string> jumpTable;

    // Comp Table

    compTable["0"] = "0101010";
    compTable["1"] = "0111111";
    compTable["-1"] = "0111010";
    compTable["D"] = "0001100";
    compTable["A"] = "0110000";
    compTable["!D"] = "0001101";
    compTable["!A"] = "0110001";
    compTable["-D"] = "0001111";
    compTable["-A"] = "0110011";
    compTable["D+1"] = "0011111";
    compTable["A+1"] = "0110111";
    compTable["D-1"] = "0001110";
    compTable["A-1"] = "0110010";
    compTable["D+A"] = "0000010";
    compTable["D-A"] = "0010011";
    compTable["A-D"] = "0000111";
    compTable["D&A"] = "0000000";
    compTable["D|A"] = "0010101";
    compTable["M"] = "1110000";
    compTable["!M"] = "1110001";
    compTable["-M"] = "1110011";
    compTable["M+1"] = "1110111";
    compTable["M-1"] = "1110010";
    compTable["D+M"] = "1000010";
    compTable["D-M"] = "1010011";
    compTable["M-D"] = "1000111";
    compTable["D&M"] = "1000000";
    compTable["D|M"] = "1010101";

    // Dest Table

    destTable["M"] = "001";
    destTable["D"] = "010";
    destTable["MD"] = "011";
    destTable["A"] = "100";
    destTable["AM"] = "101";
    destTable["AD"] = "110";

    // Jump Table

    jumpTable["JGT"] = "001";
    jumpTable["JEQ"] = "010";
    jumpTable["JGE"] = "011";
    jumpTable["JLT"] = "100";
    jumpTable["JNE"] = "101";
    jumpTable["JLE"] = "110";
    jumpTable["JMP"] = "111"; 

    string key;
    string key2;
    string key3;
    string key4;

    for (string line; getline(cin, line);) {


        string ogLine = line;

        line.erase(0, 3);

        string comp = line.substr(0, 7);
        line.erase(0, 7);
        string dest = line.substr(0, 3);
        line.erase(0, 3);
        string jump = line.substr(0, 3);
        line.erase(0, 3);


        if (ogLine.at(0) == '0') {
            toDecimal(ogLine);
        } else {

            if (!(valuePresent(destTable, key, dest)) && !(valuePresent(compTable, key2, comp)) && (valuePresent(jumpTable, key3, jump))) {

                cout << key << endl;
            }

            if (!(valuePresent(destTable, key, dest)) && (valuePresent(compTable, key2, comp)) && (valuePresent(jumpTable, key3, jump))) {

                cout << key2 << ";" << key3 << endl;
            }

            if ((valuePresent(destTable, key, dest)) && (valuePresent(compTable, key2, comp)) && !(valuePresent(jumpTable, key3, jump))) {

                cout << key << "=" << key2 << endl;
            }

            if (!(valuePresent(destTable, key, dest)) && (valuePresent(compTable, key2, comp)) && !(valuePresent(jumpTable, key3, jump))) {

                cout << key2 << endl;
            }

            if ((valuePresent(destTable, key, dest)) && (valuePresent(compTable, key2, comp)) && (valuePresent(jumpTable, key3, jump))) {

                cout << key << "=" << key2 << ";" << key3 << endl;
            }


        }


        // cout << line << endl;
        // cout << comp << endl;
        // cout << dest << endl;
        // cout << jump << endl;
    }


    return 0;
}