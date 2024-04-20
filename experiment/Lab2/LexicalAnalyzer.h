#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <string>
#include <cstdio>

using namespace std;

class LexicalAnalyzer {
public:
    LexicalAnalyzer();
    ~LexicalAnalyzer();
    void analyse(const string& input);
private:
    // Define a struct to represent a token
    struct Token {
        string type;
        string value;
    };
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
    char DELIMITER[5];
    char FILTER[4];
    string FUNCTION[1];
};

#endif // LEXICALANALYZER_H