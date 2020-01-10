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
    input = input; // + delimiter;
    unsigned int delimiterOffset = 1;
    size_t counter = 0;
    //cout << "input is: " << input << " and the delimiter is: " << delimiter << endl;
    while ((pos = input.find(delimiter)) != string::npos && counter < splitLimit) {
        token = input.substr(0, pos);
        //cout << token << endl;
        if (token == "var") {
            splitLimit = 3;
        } else if (token == "while") {
            splitLimit = 1;
        }
        if (!token.empty()) {
            res.push_back(token);
        }
        input.erase(0, pos + delimiterOffset);
        counter++;
    }
    if (res.empty()) {
        res.push_back(input);
    } else if (!input.empty()) {
        res.push_back(input);
    }
    return res;
}

bool isknownCommand(string input) {
    CommandMap& commands = CommandMap::getInstance();
    string check;
    if (input[0] == ' ' || input[0] == ',' || input[0] == '\t') {
        check  = input.substr(1);

    } else {
        check = input;
    }
    return commands.getCommand(Lexer::split(check, ' ', 2).front()) != nullptr
    || commands.getCommand(Lexer::split(check, '(', 2).front()) != nullptr;
}

list<string> splitByParen(string input) {
    list<string> res;
    if (input == ")") {
        return res;
    }
    if (input.find('(') == string::npos && input.find(')') == string::npos) {
        res.push_back(input);
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
}

list<string> splitByQuotes(string input) {
    list<string> res;
    string token;
    if (input.find('"') == string::npos) {
        res.push_back(input);
        return res;
    }
    size_t pos = 0;
    bool inQuotes = false;
    input = input + '"';
    //cout << input << endl;
    while ((pos = input.find('"')) != string::npos && (pos = input.find('"')) != 0) {
        token = input.substr(0, pos);
        if (inQuotes) {
            if (token[0] == '/') {
                token = token.substr(1);
            }
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

list<string> splitByRightCurlyBracket(string input) {
    list<string> res;
    if (input.find('{') != string::npos) {
        size_t pos = input.find('{');
        string token1 = input.substr(0, pos);
        string token2 = input.substr(pos, 1);
        res.push_back(token1);
        res.push_back(token2);
    } else {
        res.push_back(input);
    }
    return res;
}

vector<string> Lexer::lexer(string filename) {
    ifstream lexerInput;
    lexerInput.open(filename);
    string line;
    vector<string> commands;

    while (getline(lexerInput, line)) {
        //cout << line << endl;
        list<string> byQuotes = splitByQuotes(line);
        // removing tabs
        for (string s : byQuotes) {
            if (s.find('\t') != string::npos) {
                int pos = s.find_last_of('\t');
                s = s.substr(pos + 1, s.size() - (pos + 1));
            }
        }

        list<string> byRightCurlyBracket;
        //cout << "byRightCurlyBracket: " << endl;
        for (auto const& i : byQuotes) {
            //cout << i << endl;
            byRightCurlyBracket.splice(byRightCurlyBracket.end(), splitByRightCurlyBracket(i));
        }

        list<string> byParen;
        for (auto const& i : byRightCurlyBracket) {
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
            string comm;
            comm = bySpace.front();
            if (comm.find('\t') != string::npos) {
                int pos = comm.find_last_of('\t');
                comm = comm.substr(pos+1, comm.size() - (pos+1));
            }
            commands.push_back(comm);
            bySpace.pop_front();
        }
        //commands.emplace_back("\n");
    }
    lexerInput.close();

/*
    //Print for testing: (Lexer includes newline characters.
    for (unsigned int i = 0; i < commands.size(); i++) {
        cout << commands[i] << "," << endl;
    }
    //end of test print
*/
    return commands;
}