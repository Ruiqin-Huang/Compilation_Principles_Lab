#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <string>
#include <cstdio>
#include <vector>

using namespace std;

class LexicalAnalyzer {
private:
    bool IsKeyword(string word);
    bool IsFunction(string word);
    bool IsOperator(char ch);
    bool IsDelimiter(char ch);
    bool IsFilter(char ch);
    bool IsLetterOrUnderscore(char ch);
    bool IsDigit(char ch);
    template <class T>
    int value(T *a, int n, T str);
    string KEYWORD[3];
    char OPERATOR[12];
    char DELIMITER[6];
    char FILTER[4];
    string FUNCTION[1];
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