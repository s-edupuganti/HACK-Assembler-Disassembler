#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <bitset>
#include <vector>
#include <sstream>

using namespace std;

void clean(string &str) {

    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());

    if (str.find("//") != string::npos) {
        str.erase(str.find("//"));
    }

}



bool isLabel(string &str) {


    if (str[0] == '(' && str.back() == ')') {
        // cout << "true" << endl;
        int i = 0;

        while (i < str.size()) {
            if (str[i] == '(' || str[i] == ')') {
                str.erase(i, 1);
            } else {
                i++;
            }
        }
        return true;
    }

    return false;

}

bool keyPresent(unordered_map<string, string> table, string key) {

    if (table.find(key) == table.end()) {
        return false;
    }

    return true;

}

bool isInstruction(string &str) {

    if (str.empty()) {
        return false;
    }

    return true;


}

bool isValidAInstruction(string &str) {

    if (str[0] == '@') {
        int i = 0;
        while (i < str.size()) {
            if (str[i] == '@') {
                str.erase(i, 1);
            } else {
                i++;
            }
        }
        return true;
    }

    return false;
}

bool isAlphabet(string &str) {

    for (int i = 0; i < str.size(); i++) {
        if (isalpha(str[i]) == false) {
            return false;
        }
    }

    return true;
}

bool validSymbolChars(string &str) {

    if (isAlphabet(str) || (str.find('.' != string::npos)) || (str.find(':' != string::npos)) || (str.find('$' != string::npos)) || (str.find('_' != string::npos))) {
        return true;
    }

    return false;

}



bool isNumber(string &str) {

    for (int i = 0; i < str.size(); i++) {
        if (isdigit(str[i]) == false) {
            return false;
        }
    }

    return true;
}

bool isAInstruction(string &str) {

    if (str[0] != '@') {
        return false;
    }

    int i = 0;
    while (i < str.size()) {
        if (str[i] == '@') {
            str.erase(i, 1);
        } else {
            i++;
        }
    
    }

    if (isNumber(str)) {
        if (stoi(str) >= 0) {
            return true;
        }
    }

    // if (isAlphabet(str)) {
    //     return true; 
    // }

    if (isdigit(str[0])) {
        return false;
    }


    if (validSymbolChars(str)) {
        return true; 
    }

    return false;


}

string aInstruction(string &str, unordered_map<string, string> table) {

    string bin;
    string address;

    if (isNumber(str)) {
        if (stoi(str) >= 0) {
            bitset<15> toBinary(stoi(str));
            bin = toBinary.to_string();
            return("0" + bin);
        }
    }

    address = ((table.find(str))->second);
    bitset<15> toBinary(stoi(address));
    bin = toBinary.to_string();
    return("0" + bin);

}

bool isCInstruction(string &str, unordered_map<string, string> destTable, unordered_map<string, string> compTable, unordered_map<string, string> jumpTable) {

    int numEQ = count(str.begin(), str.end(), '=');
    int numSC = count(str.begin(), str.end(), ';');
    string temp;
    string tempString = str;

    // cout << "hello" << endl;
    // cout << numEQ << endl;
    // cout << numSC << endl;

    if (!(numEQ == 1 || numSC == 1)) {
        return false;
    }

    // cout << "hello" << endl;

    vector<string> tokens;

    // int i = 0;
    // while (i < str.size()) {
    //     if ((str[i] == '=') || str[i] == ';') {
    //         str.erase(i, 1);
    //     } else {
    //         i++;
    //     }
    // }

    // replace_if(str.begin(), str.end(), ' ');

    replace(str.begin(), str.end(), '=', ' ');
    replace(str.begin(), str.end(), ';', ' ');

    stringstream ss(str);

    while (getline(ss, temp, ' ')) {
        tokens.push_back(temp);
    }

    // cout << tokens[0] << endl;

    if (tokens.size() != 2 && tokens.size() != 3) {
        return false;
    }

    if (tokens.size() == 2) {
        int numTempEQ = count(tempString.begin(), tempString.end(), '=');
        if (numTempEQ == 1) {
            if (!keyPresent(destTable, tokens[0])) {
                return false;
            }
            if (!keyPresent(compTable, tokens[1])) {
                return false;
            }
        } else {
            if (!keyPresent(compTable, tokens[0])) {
                return false;
            }
            if (!keyPresent(jumpTable, tokens[1])) {
                return false;
            }
        }
    } else if (tokens.size() == 3) {
        if (!keyPresent(destTable, tokens[0])) {
            return false;
        }
        if (!keyPresent(compTable, tokens[1])) {
            return false;
        }
        if (!keyPresent(jumpTable, tokens[2])) {
            return false;
        }
    }

    return true;

}

string cInstruction(string &str, unordered_map<string, string> destTable, unordered_map<string, string> compTable, unordered_map<string, string> jumpTable) {

    // cout << "got to c instruction function" << endl;

    int numEQ = count(str.begin(), str.end(), '=');
    int numSC = count(str.begin(), str.end(), ';');
    string temp;
    string tempString = str;

    vector<string> tokens;

    // cout << "got to c instruction function1" << endl;

    // int i = 0;
    // while (i < str.size()) {
    //     if ((str[i] == '=') || str[i] == ';') {
    //         str.erase(i, 1);
    //     } else {
    //         i++;
    //     }
    // }

    replace(str.begin(), str.end(), '=', ' ');
    replace(str.begin(), str.end(), ';', ' ');

    // cout << "got to c instruction function2" << endl;
    
    stringstream ss(str);

    while (getline(ss, temp, ' ')) {
        tokens.push_back(temp);
    }

    // cout << "got to c instruction function3" << endl;

    string prefix = "111";
    string dest = "";
    string comp = "";
    string jump = "";

    // cout << "got to c instruction function4" << endl;

    if (tokens.size() == 2) {
        int numTempEQ = count(tempString.begin(), tempString.end(), '=');
        // cout << "got to c instruction function5" << endl;
        // cout << "numTempEQ = " << numTempEQ << endl;

        if (numTempEQ == 1) {
            // cout << "got to c instruction function6" << endl;
            dest = destTable.find(tokens[0])->second;
            comp = compTable.find(tokens[1])->second;
            jump = "000";

            // cout << "got to c instruction function6" << endl;

            // if (dest.empty() || comp.empty()) {
            //     throw invalid_argument("Dest and Comp are NULL");
            // }
        } else {
            dest = "000";
            comp = compTable.find(tokens[0])->second;
            jump = jumpTable.find(tokens[1])->second;

            // if (comp.empty() || jump.empty()) {
            //     throw invalid_argument("Comp and Jump are NULL");
            // }
        }
    } else {
        dest = destTable.find(tokens[0])->second;
        comp = compTable.find(tokens[1])->second;
        jump = jumpTable.find(tokens[2])->second;

        // if (dest.empty() || comp.empty() || jump.empty()) {
        //     throw invalid_argument("All THREE ARE NULL");
        // }
    }

    return (prefix + comp + dest + jump);


}



int main () {

    unordered_map<string, string> symbolTable;
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



    // SymbolTable

    symbolTable["SP"] = "0";
    symbolTable["LCL"] = "1";
    symbolTable["ARG"] = "2";
    symbolTable["THIS"] = "3";
    symbolTable["THAT"] = "4";

    for (int i = 0; i <= 15; i++) {
        symbolTable["R" + to_string(i)] = to_string(i);
    }

    symbolTable["SCREEN"] = "16384";
    symbolTable["KBD"] = "24576";

    int PC = 0;
    int nextAddress = 16;
    string bin;
    string prefix = "111";
    string comp = "000";
    string dest = "000";
    string jump = "000";
    
    // vector<string> tokens;

    // for (auto x : symbolTable) {
    //     cout << x.first << " " << x.second << endl;
    // }

    for (string line; getline(cin, line);) {

        clean(line);


        // if (keyPresent(symbolTable, line)) {
        //     cout << (symbolTable.find(line))->second << endl;
        // }


        if (keyPresent(compTable, line)) {
            cout << prefix + (compTable.find(line))->second + dest + jump << endl;
        } else if (keyPresent(destTable, line)) {
            cout << prefix + comp + (destTable.find(line))->second + jump << endl;
        } else if (keyPresent(jumpTable, line)) {
            cout << prefix + comp + dest + (jumpTable.find(line))->second << endl;
        }

        if (isLabel(line)) {
            // cout << "is label" << endl;
            if (!keyPresent(symbolTable, line)) {
                symbolTable[line] = to_string(PC);
                // cout << (symbolTable.find(line))->second << endl;
            }
        }

        if (isAInstruction(line)) {

            // cout << "is a construction" << endl;
            if (!isNumber(line) && !keyPresent(symbolTable, line)) {
                symbolTable[line] = to_string(nextAddress);
                nextAddress++;
                // cout << (symbolTable.find(line))->second << endl;
            }

            bin = aInstruction(line, symbolTable);
            cout << bin << endl;
        }

        string tempString = line;

        if (isCInstruction(line, destTable, compTable, jumpTable)) {
            bin = cInstruction(tempString, destTable, compTable, jumpTable);
            cout << bin << endl;

        }

        // if (isAInstruction(line)) {
            // bin = aInstruction(line, symbolTable);
            // cout << bin << endl;
        // }

        if (isInstruction(line)) {
            PC++;
            // cout << "is instruction lol" << endl;
        }

        // cout << line << endl;

    }

    return 0;


}

