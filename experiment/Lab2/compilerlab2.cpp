// Lab 1: compilerlab1
// Name: Huang Ruiqin
// ID: 1120211809

// The grammar that the primitive compiler can handle is as follows: 
// Keywords: int, return, main
// Identifier: C89(start with a letter or _, followed by letters or digits or _)
// Constants: Decimal integers, such as 1, 223, 10, etc
// Operators: =,+, -, *,/, %, <, <=, >, >=, ==, !=, &, |, ^
// Delimiter: ;, {, }, (, )
// Function: println_int()
// Statement: expression statement, assignment statement, 
//            where the expression statement contains parentheses 
//            and nested parentheses;

#include "LexicalAnalyzer.h"
#include "LexicalAnalyzer.cpp"
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
using namespace std;

// Classify token types
// string classifier(const string& token) {
//     if (token == "int" || token == "return" || token == "main") {
//         return "keyword";
//     } else if (token == "=" || token == "+" || token == "-" || token == "*" || token == "/" || token == "(" || token == ")") {
//         return "operator";
//     } else if (token == ";") {
//         return "delimiter";
//     } else if (token.length() == 1 && isalpha(token[0])) {
//         return "identifier";
//     } else if (isdigit(token[0])) {
//         bool isConstant = true;
//         for (char c : token) {
//             if (!isdigit(c)) {
//                 isConstant = false;
//                 break;
//             }
//         }
//         if (isConstant) {
//             return "constant";
//         }
//     } else {
//         return "unknown type";
//     }
// } 

// Function to split the input source code into tokens
// vector<Token> tokenize(const string& sourceCode) {
//     vector<Token> tokens;
//     string currentToken;
//     string type;
    
//     // Loop through each character in the source code
//     for (char c : sourceCode) {
//         // split the input source by space and newline
//         if (c == ' ' || c == '\n') {
//             // If the current token is not empty, add it to the list of tokens
//             if (!currentToken.empty()) {
//                 type = classifier(currentToken);
//                 if(type != "unknown type") {
//                     tokens.push_back({type, currentToken});
//                     currentToken.clear();
//                 } else {
//                     cout << "Error! An unknown type word was input: " << currentToken << endl;
//                     exit(1);
//                 }
//             }
//         } else {
//             // Append the character to the current token
//             currentToken += c;
//         }
//     }
    
//     // Add the last token to the list of tokens
//     if (!currentToken.empty()) {
//         type = classifier(currentToken);
//         if(type != "unknown type") {
//             tokens.push_back({type, currentToken});
//             currentToken.clear();
//         } else {
//             cout << "Error! An unknown type word was input: " << currentToken << endl;
//             exit(1);
//         }
//     }
    
//     return tokens;
// }


int priority(const string& op) {
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/")
        return 2;
    return 0;
}

// Convert the infix expression to a postfix expression
vector<Token> infixToPostfix(const vector<Token>& tokens, int ptr_expression) {
    // string RPN is the postfix expression
    vector<Token> RPN;
    stack<Token> ops;
    int ptr = ptr_expression; // Pointer to the first token of the expression

    while (tokens[ptr].type != "delimiter") {
        if (tokens[ptr].type == "operator" && tokens[ptr].value == "(") {
            // If the token is a left parenthesis
            ops.push(tokens[ptr]);
        } else if (tokens[ptr].type == "operator" && tokens[ptr].value == ")") {
            // If the token is a right parenthesis
            while (!ops.empty() && (ops.top()).value != "(") {
                RPN.push_back(ops.top());
                ops.pop();
            }
            ops.pop();  // Remove '('
        } else if (tokens[ptr].type == "operator" && (tokens[ptr].value == "+" || tokens[ptr].value == "-" || tokens[ptr].value == "*" || tokens[ptr].value == "/")) {
            // If the token is an operator
            while (!ops.empty() && priority((ops.top()).value) >= priority(tokens[ptr].value)) {
                RPN.push_back(ops.top());
                ops.pop();
            }
            ops.push(tokens[ptr]);
        } else {
            // If the token is an identifier or a constant
            RPN.push_back(tokens[ptr]);
        }
        ptr++;
    }

    // Add the remaining operators in stack to RPN
    while (!ops.empty()) {
        RPN.push_back(ops.top());
        ops.pop();
    }
    return RPN;
}

// Calculate the postfix expression and output the calculation process in assembly language.
string calculatePostfix(const vector<Token>& RPN, map<string, int> identifierMap) {
    string expression_asm;
    stack<Token> oprands;

    for (const Token& token : RPN) {
        if (token.type == "constant") {
            oprands.push(token);
            expression_asm += "\n";
            expression_asm += "   mov eax, " + token.value + "\n";
            expression_asm += "   push eax\n";
        } else if (token.type == "identifier") {
            oprands.push(token);
            expression_asm += "\n";
            expression_asm += "   mov eax, DWORD PTR [ebp-" + to_string(identifierMap[token.value] * 4) + "]\n";
            expression_asm += "   push eax\n";
        } else if (token.type == "operator") {
            Token oprand2 = oprands.top();
            oprands.pop();
            Token oprand1 = oprands.top();
            oprands.pop();
            if (token.value == "+") {
                oprands.push({"Intermediate results", "x"});
                expression_asm += "\n";
                expression_asm += "   pop ebx\n";
                expression_asm += "   pop eax\n";
                expression_asm += "   add eax, ebx\n";
                expression_asm += "   push eax\n";
            } else if (token.value == "-") {
                oprands.push({"Intermediate results", "x"});
                expression_asm += "\n";
                expression_asm += "   pop ebx\n";
                expression_asm += "   pop eax\n";
                expression_asm += "   sub eax, ebx\n";
                expression_asm += "   push eax\n";
            } else if (token.value == "*") {
                oprands.push({"Intermediate results", "x"});
                expression_asm += "\n";
                expression_asm += "   pop ebx\n";
                expression_asm += "   pop eax\n";
                expression_asm += "   imul eax, ebx\n";
                expression_asm += "   push eax\n";
            } else if (token.value == "/") {
                oprands.push({"Intermediate results", "x"});
                expression_asm += "\n";
                expression_asm += "   pop ebx\n";
                expression_asm += "   pop eax\n";
                expression_asm += "   cdq\n";
                expression_asm += "   idiv ebx\n";
                expression_asm += "   push eax\n";
            }
        }

    }
    return expression_asm;
}

// Function to generate the tokens into assembly code
string generateAssembly(const vector<LexicalAnalyzer::Token>& tokens) {
    string assemblyCode;
    assemblyCode += "\n";
    int ptr = 0; // Pointer to the current token
    map<string, int> identifierMap; // Establish identifier-ID mapping

    // Loop through each token
    while (ptr < tokens.size()) {
        // If the first token is a keyword
        if (tokens[ptr].type == "keyword") {
            if (tokens[ptr].value == "int") {
                if (tokens[ptr + 1].type == "identifier") {
                    if (identifierMap.count(tokens[ptr + 1].value)) {
                        // if identifier has been defined before
                        cout << "Error! Identifier " << tokens[ptr + 1].value << " has been defined before." << endl;
                        exit(1);
                    } else {
                        // if identifier is defined for the first time
                        int size = identifierMap.size();
                        identifierMap[tokens[ptr + 1].value] = size + 1;
                        assemblyCode += "   mov DWORD PTR [ebp-" + to_string(identifierMap[tokens[ptr + 1].value] * 4) + "], 0\n";
                        ptr += 2;
                    }
                } else {
                    cout << "ERROR! Identifier expected after 'int'." << endl;
                    exit(1);
                }
            } else if (tokens[ptr].value == "return") {
                assemblyCode += "\n";
                if (tokens[ptr + 1].type == "identifier") {
                    if (identifierMap.count(tokens[ptr + 1].value)) {
                        assemblyCode += "   mov eax, DWORD PTR [ebp-" + to_string(identifierMap[tokens[ptr + 1].value] * 4) + "]\n";
                        ptr += 2;
                    } else {
                        cout << "ERROR! Identifier " << tokens[ptr + 1].value << " has not been defined." << endl;
                        exit(1);
                    }
                } else if (tokens[ptr + 1].type == "constant") {
                    assemblyCode += "   mov eax, " + tokens[ptr + 1].value + "\n";
                    ptr += 2;
                } else {
                    cout << "ERROR! Identifier or constant expected after 'return'." << endl;
                    exit(1);
                }
            }
            else {
                cout << "ERROR! Unknown keyword: " << tokens[ptr].value << endl;
                exit(1);
            }
        }
        // If the first token is an identifier
        else if (tokens[ptr].type == "identifier") {
            if (identifierMap.count(tokens[ptr].value)) {
                if (tokens[ptr + 1].type == "operator" && tokens[ptr + 1].value == "=") {
                    int ptr_expression = ptr + 2; // Now, tokens[ptr_expression] is the first token of the expression
                    if (tokens[ptr_expression + 1].type == "delimiter" && tokens[ptr_expression + 1].value == ";"){
                        // If the expression is a constant or a single identifier
                        if (tokens[ptr_expression].type == "constant") {
                            assemblyCode += "   mov DWORD PTR [ebp-" + to_string(identifierMap[tokens[ptr].value] * 4) + "], " + tokens[ptr_expression].value + "\n";
                            ptr += 3;
                        } else if (tokens[ptr_expression].type == "identifier") {
                            if (identifierMap.count(tokens[ptr_expression].value)) {
                                assemblyCode += "   mov eax, DWORD PTR [ebp-" + to_string(identifierMap[tokens[ptr_expression].value] * 4) + "]\n";
                                assemblyCode += "   mov DWORD PTR [ebp-" + to_string(identifierMap[tokens[ptr].value] * 4) + "], eax\n";
                                ptr += 3;
                            } else {
                                cout << "ERROR! Identifier " << tokens[ptr].value << " has not been defined." << endl;
                                exit(1);
                            }
                        } else {
                            cout << "ERROR! Constant or identifier expected after '='." << endl;
                            exit(1);
                        }
                    } else {
                        // If the expression is a complex expression
                        // Calculate using Reverse Polish Notation (RPN)

                        // Step 1: Convert the infix expression to a postfix expression. 
                        vector<Token> RPN = infixToPostfix(tokens, ptr_expression);

                        // Step 2: Calculate the postfix expression and output the calculation process in assembly language.
                        string expression_asm = calculatePostfix(RPN, identifierMap);
                        assemblyCode += expression_asm;

                        // Step 3: Store the result of the expression in the identifier
                        assemblyCode += "   pop eax\n";
                        assemblyCode += "   mov DWORD PTR [ebp-" + to_string(identifierMap[tokens[ptr].value] * 4) + "], eax\n";
                        
                        // Step 4: move the pointer to the end of the expression
                        // count the length of expression
                        int expression_length = 0;
                        while (tokens[ptr_expression + expression_length].type != "delimiter") {
                            expression_length++;
                        }
                        ptr += 2 + expression_length ;
                    } 
                } else {
                    cout << "ERROR! '=' expected after identifier." << endl;
                    exit(1);
                }
            } else {
                cout << "ERROR! Identifier " << tokens[ptr].value << " has not been defined." << endl;
                exit(1);
            }
        }
        // If the token is a delimiter
        else if (tokens[ptr].type == "delimiter" && tokens[ptr].value == ";") {
            ptr++;
        }
    }
    
    return assemblyCode;
}

int main(int argc, char* argv[]) {
    if(argc != 2 || argv[1] == nullptr) {
        cout << "ERROR! Usage: " << argv[0] << " <source file path>" << endl;
        exit(1);
    }

    // Read the source code from the file
    string filePath = argv[1];
    ifstream sourceFile(filePath);
    if (!sourceFile) {
        cout << "ERROR! Could not open source file at path: " << filePath << endl;
        exit(1);
    }

    stringstream buffer;
    buffer << sourceFile.rdbuf();
    string sourceCode = buffer.str();
    // cout << "Source code: " << sourceCode << endl;

    // create a string to store the assembly code
    string assemblyCode = "";
    
    // Tokenize the source code
    LexicalAnalyzer la;
    vector<LexicalAnalyzer::Token> tokens = la.analyse(sourceCode);
    
    // Print the tokens
    for (LexicalAnalyzer::Token &token : tokens) {
        // la.printToken(token);
        cout << "Type: " << token.type << ", Value: " << token.value << endl;
    }

    // Generate the assembly code
    // assemblyCode = generateAssembly(tokens);
    // cout << assemblyCode << endl;
    
    return 0;
}