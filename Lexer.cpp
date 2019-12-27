#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include "Lexer.h"

using namespace std;

list<string> split(string input, char delimiter) {
    list<string> res;
    if (input[1] == '"') {
        res.push_back(input);
        return res;
    }
    string token;
    size_t pos = 0;
    input = input + delimiter;
    unsigned int delimiterOffset = 1;
    while ((pos = input.find(delimiter)) != string::npos) {
        token = input.substr(0, pos);
        if (!token.empty()) {
            res.push_back(token);
        }
        input.erase(0, pos + delimiterOffset);
    }
    if (res.empty()) {
        res.push_back(input);
    }
    return res;
}

list<string> splitByParen(string input) {
    list<string> res;
    if (input[1] == '"') {
        res.push_back(input);
        return res;
    }
    string token;
    size_t pos = 0;
    input = input + '(';
    unsigned int delimiterOffset = 1;
    while ((pos = input.find('(')) != string::npos || (pos = input.find(')')) != string::npos) {
        if (input[pos-1] == ')') {
            token = input.substr(0, pos - 1);
        } else {
            token = input.substr(0, pos);
        }
        if (!token.empty()) {
            res.push_back(token);
        }
        input.erase(0, pos + delimiterOffset);
    }
    if (res.empty()) {
        res.push_back(input);
    }
    return res;
}

list<string> splitByQuotes(string input) {
    list<string> res;
    string token;
    size_t pos = 0;
    bool inQuotes = false;
    input = input + '"';
    //cout << input << endl;
    while ((pos = input.find('"')) != string::npos && (pos = input.find('"')) != 0) {
        token = input.substr(0, pos);
        if (inQuotes) {
            token = '"' + token + '"';
        }
        res.push_back(token);
        inQuotes = !inQuotes;
        pos++;
        input.erase(0, pos);
    }
    return res;
}

vector<string> Lexer::lexer(string filename) {
    ifstream lexerInput;
    lexerInput.open(filename);
    string line;
    vector<string> commands;
    /*unsigned int m;
    m = 0;*/

    while (getline(lexerInput, line)) {
        //m++;
        //cout << line << endl;
        list<string> byQuotes = splitByQuotes(line);

        list<string> byParen;
        //cout << "byQuotes: " << endl;
        for (auto const& i : byQuotes) {
            //cout << i << endl;
            byParen.splice(byParen.end(), splitByParen(i));
        }

        list<string> byComma;
        //cout << "byParen: " << endl;
        for (auto const& i : byParen) {
            //cout << i << endl;
            byComma.splice(byComma.end(), split(i, ','));
        }

        list<string> bySpace;
        //cout << "bySpace: " << endl;
        for (auto const& i : byComma) {
            //cout << i << endl;
            bySpace.splice(bySpace.end(), split(i, ' '));
        }

        //cout << "printing bySpace: " << endl;
        while (!bySpace.empty()) {
            commands.push_back(bySpace.front());
            bySpace.pop_front();
        }
    }
    lexerInput.close();
    for (unsigned int i = 0; i < commands.size(); i++) {
        cout << commands[i] << ",";
    }
    return commands;
}