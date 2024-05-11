#include "LexicalAnalyzer.h"
#include "LexicalAnalyzer.cpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int main() {
    LexicalAnalyzer la;
    // read fpin to string 
    ifstream sourceFile("LA_TEST.txt");

    stringstream buffer;
    buffer << sourceFile.rdbuf();
    string sourceCode = buffer.str();
    // cout << "Source code: " << sourceCode << endl;
    
    // Tokenize the source code
    cout << sourceCode << endl;
    cout << "Tokenizing..." << endl;
    vector<LexicalAnalyzer::Token> tokens = la.analyse(sourceCode);
    for (LexicalAnalyzer::Token &token : tokens) {
        // la.printToken(token);
        cout << "Type: " << token.type << ", Value: " << token.value << endl;
    }
    
    return 0;
}