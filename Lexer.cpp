#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include "Lexer.h"
#include "CommandMap.h"
#include <string>

using namespace std;

list<string> Lexer::split(string input, char delimiter, size_t splitLimit) {
    list<string> res;
    if (input[0] == '"') {
        res.push_back(input);
        return res;
    }
    string token;
    size_t pos = 0;
    input = input + delimiter;
    unsigned int delimiterOffset = 1;
    size_t counter = 0;
    while ((pos = input.find(delimiter)) != string::npos && counter < splitLimit) {
        token = input.substr(0, pos);
        if (token == "var") {
            splitLimit = 3;
        }
        if (!token.empty()) {
            res.push_back(token);
        }
        input.erase(0, pos + delimiterOffset);
        counter++;
    }
    if (!input.empty() || res.empty()) {
        res.push_back(input);
    }
    return res;
}

bool isknownCommand(string input) {
    return CommandMap::getInstance().getCommand(Lexer::split(input, ' ', 2).front()) != nullptr
        || CommandMap::getInstance().getCommand(Lexer::split(input, '(', 2).front()) != nullptr;
}

list<string> splitByParen(string input) {
    list<string> res;
    if (input == ")") {
        return res;
    }
    if (input[0] == '"' || !isknownCommand(input)) {
        if ((input.find('(') == string::npos) && (input.find(')') == input.size()-1)) {
            res.push_back(input.substr(0, input.size()-1));
        } else {
            res.push_back(input);
        }
        return res;
    } else {
        size_t openParenPos = input.find('(');
        string token1 = input.substr(0, openParenPos);
        string token2 = input.substr(openParenPos + 1, input.size() - openParenPos - 2);
        res.push_back(token1);
        if (!token2.empty()) {
            res.push_back(token2);
        }
    }
    if (res.empty() && !input.empty()) {
        res.push_back(input);
    }
    return res;
/*
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
    if (res.empty() && !input.empty()) {
        res.push_back(input);
    }
    return res;
    */
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
        if (!token.empty()) {
            res.push_back(token);
        }
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
            byComma.splice(byComma.end(), split(i, ',', i.size()));
        }

        list<string> bySpace;
        //cout << "bySpace: " << endl;
        for (auto const& i : byComma) {
            //cout << i << endl;
            bySpace.splice(bySpace.end(), split(i, ' ', 2));
        }

        //cout << "printing bySpace: " << endl;
        while (!bySpace.empty()) {
            commands.push_back(bySpace.front());
            bySpace.pop_front();
        }
        commands.emplace_back("\n");
    }
    lexerInput.close();
    // Print for testing: (Lexer includes newline characters.
    for (unsigned int i = 0; i < commands.size(); i++) {
        cout << commands[i] << ",";
        /*if (commands[i] != "\n") {
        }*/
    }
    // ends of test print
    return commands;
}