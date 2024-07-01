#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

// The grammar that the primitive compiler can handle is as follows: 
// Keywords: int, return, main, void
// Identifier: C89(start with a letter or _, followed by letters or digits or _)
// Constants: Decimal integers, such as 1, 223, 10, etc
// Operators: =, -, !, ~, +, -, *, /, %, <, <=, >, >=, ==, !=, &, |, ^, &&, ||
// Delimiter: ;, {, }, (, )
// Lib_Function: println_int()
// Statement: expression statement, assignment statement, 
//            where the expression statement contains parentheses 
//            and nested parentheses;

#include <string>
#include <cstdio>
#include <vector>

using namespace std;

class LexicalAnalyzer {
private:
    bool IsKeyword(string word);
    bool IsLibFunction(string word);
    bool IsOperator(char ch);
    bool IsDelimiter(char ch);
    bool IsFilter(char ch);
    bool IsLetterOrUnderscore(char ch);
    bool IsDigit(char ch);
    template <class T>
    int value(T *a, int n, T str);
    string KEYWORD[9];
    char OPERATOR[13];
    char DELIMITER[6];
    char FILTER[4];
    string LIB_FUNCTION[1];
public:
    // Define a struct to represent a token
    struct Token {
        string type;
        string value;
    };
    LexicalAnalyzer();
    ~LexicalAnalyzer();
    vector<Token> analyse(const string& input);
    void printToken(const Token& token);
};

#endif // LEXICALANALYZER_H