#include "LexicalAnalyzer.h"
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
    la.analyse(sourceCode);
    return 0;
}