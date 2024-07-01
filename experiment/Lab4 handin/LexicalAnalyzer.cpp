// The grammar that the primitive compiler can handle is as follows: 
// Keywords: int, return, main, void, if, else, while, continue, break 
// Identifier: C89(start with a letter or _, followed by letters or digits or _)
// Constants: Decimal integers, such as 1, 223, 10, etc
// Operators: =, -, !, ~, +, -, *, /, %, <, <=, >, >=, ==, !=, &, |, ^, &&, ||
// Delimiter: ;, {, }, (, )
// Lib_Function: println_int()
// Statement: expression statement, assignment statement, 
//            where the expression statement contains parentheses 
//            and nested parentheses;

#include "LexicalAnalyzer.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;

LexicalAnalyzer::LexicalAnalyzer() {
    KEYWORD[0] = "int", KEYWORD[1] = "return", KEYWORD[2] = "main", KEYWORD[3] = "void", KEYWORD[4] = "if", KEYWORD[5] = "else", KEYWORD[6] = "while", KEYWORD[7] = "continue", KEYWORD[8] = "break";
    OPERATOR[0] = '=', OPERATOR[1] = '+', OPERATOR[2] = '-', OPERATOR[3] = '*', OPERATOR[4] = '/', OPERATOR[5] = '%', OPERATOR[6] = '<', OPERATOR[7] = '>', OPERATOR[8] = '&', OPERATOR[9] = '|', OPERATOR[10] = '^', OPERATOR[11] = '!', OPERATOR[12] = '~';
    DELIMITER[0] = ';', DELIMITER[1] = '{', DELIMITER[2] = '}', DELIMITER[3] = '(', DELIMITER[4] = ')', DELIMITER[5] = ',';
    FILTER[0] = ' ', FILTER[1] = '\t', FILTER[2] = '\r', FILTER[3] = '\n';
    LIB_FUNCTION[0] = "println_int";
}

LexicalAnalyzer::~LexicalAnalyzer() {
}

// Define a struct to represent a token
struct Token {
    string type;
    string value;
};

bool LexicalAnalyzer::IsKeyword(string word) {
    for (string &i : KEYWORD) {
        if (i == word) {
            return true;
        }
    }
    return false;
}

bool LexicalAnalyzer::IsLibFunction(string word) {
    for (string &i : LIB_FUNCTION) {
        if (i == word) {
            return true;
        }
    }
    return false;
}

bool LexicalAnalyzer::IsOperator(char ch) {
    for (char &i : OPERATOR) {
        if (i == ch) {
            return true;
        }
    }
    return false;
}

bool LexicalAnalyzer::IsDelimiter(char ch) {
    for (char &i : DELIMITER) {
        if (i == ch) {
            return true;
        }
    }
    return false;
}

bool LexicalAnalyzer::IsFilter(char ch) {
    for (auto &i : FILTER) {
        if (i == ch) {
            return true;
        }
    }
    return false;
}

bool LexicalAnalyzer::IsLetterOrUnderscore(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

bool LexicalAnalyzer::IsDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

template <class T>
int LexicalAnalyzer::value(T *a, int n, T str) {
    for (int i = 0; i < n; i++) {
        if (a[i] == str) return i ;
    }
    return -1;
}

vector<LexicalAnalyzer::Token> LexicalAnalyzer::analyse(const string& input) {
    int i = 0; 
    // Define a vector to store tokens
    vector<Token> tokens;

    while(i < input.size()) {
        string currentToken = "";
        string type = "";
        // Check if it is a filter character
        if (IsFilter(input[i])) {i++;} 
        // Check if it is an identifier or keyword or lib_function
        else if (IsLetterOrUnderscore(input[i])) { 
            while (IsLetterOrUnderscore(input[i]) || IsDigit(input[i])) {
                currentToken += input[i];
                i++;
            }
            // Check if it is a keyword or identifier or lib_function
            if (IsKeyword(currentToken)) {
                type = "Keyword";
                tokens.push_back({type, currentToken});
            } else if (IsLibFunction(currentToken)) {
                type = "Lib_Function";
                tokens.push_back({type, currentToken});
            } else {
                // variable or function
                type = "Identifier";
                tokens.push_back({type, currentToken});
            }
            // cout << currentToken << "  " << type << endl;
        } else if (IsDigit(input[i])) { // Check if it is a constant
            while (IsDigit(input[i])) {
                currentToken += input[i];
                i++;
            }
            type = "Constant";
            tokens.push_back({type, currentToken});
            // cout << currentToken << "  " << type << endl;
        } else if (IsOperator(input[i])) { // Check if it is an operator
            // Operator includes - ! ~ + - * / % < <= > >= == != & | ^ && ||
            if ( input[i] == '<' || input[i] == '>' || input[i] == '!' || input[i] == '=') {
                currentToken += input[i];
                i++;
                // if the operator is a double character operator
                if (input[i] == '=') {
                    currentToken += input[i];
                    i++;
                }
            } else if (input[i] == '&' || input[i] == '|') {
                currentToken += input[i];
                i++;
                // if the operator is a double character operator
                if (input[i] == input[i-1]) {
                    currentToken += input[i];
                    i++;
                }
            } else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '%' || input[i] == '^' || input[i] == '~') {
                currentToken += input[i];
                i++;
            }
            type = "Operator";
            tokens.push_back({type, currentToken});
            // cout << currentToken << "  " << type << endl;
        } else if (IsDelimiter(input[i])) { // Check if it is a delimiter
            currentToken += input[i];
            i++;
            type = "Delimiter";
            tokens.push_back({type, currentToken});
            // cout << currentToken << "  " << type << endl;
        } else {
            cout << "ERROR! Unknown character : " << input[i] << endl;
            exit(1);
        }
    }

    return tokens;
}

void LexicalAnalyzer::printToken(const Token& token) {
    cout << "Type: " << token.type << ", Value: " << token.value << endl;
}