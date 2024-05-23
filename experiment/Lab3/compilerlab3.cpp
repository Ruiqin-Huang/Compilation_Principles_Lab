// Lab 3: compilerlab3
// Name: Huang Ruiqin
// ID: 1120211809
// Class: 07112103

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

#include "LexicalAnalyzer.h"
// #include "LexicalAnalyzer.cpp"
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
using namespace std;

// Establish a return value map to indicate the return value types of each function
// map<string, string> returnValueMap;

// create VariableidentifierMapStack to store identifier in different scope
map<string, int> GlobalIdentifierMap;
map<string, int> UserDefinedFunctionMap;
map<string, string> FuctionReturnValueMap;

// all user defined function with int return type stores in GlobalIdentifierMap as "{function name}_return_value"

stack<string> inFuctionWhat;
stack<map<string, int>> VariableidentifierMapStack;
int scopeDepth = 0;
// scopeDepth = 1 represents global scope

int jump_label = 0;

// indicate one function has ended
int function_has_ended = 0;

// Establish a stack to indicate the current scope
// stack<int> scopeStack;

void enterScope() {
    map<string, int> newScopeMap;
    VariableidentifierMapStack.push(newScopeMap);
    scopeDepth++;
}

void leaveScope() {
    VariableidentifierMapStack.pop();
    scopeDepth--;
}

void addVariableidentifier(string identifier) {
    if (VariableidentifierMapStack.top().count(identifier) > 0) {
        throw runtime_error("Identifier already defined in current scope");
    }
    int value = VariableidentifierMapStack.top().size();
    VariableidentifierMapStack.top()[identifier] = value;
}

void addGlobalIdentifier(string identifier) {
    if (GlobalIdentifierMap.count(identifier) > 0) {
        throw runtime_error("Identifier already defined in global scope");
    }
    int value = GlobalIdentifierMap.size();
    GlobalIdentifierMap[identifier] = value;
}

void addFunctionidentifier(string identifier, string return_type) {
    if (UserDefinedFunctionMap.count(identifier) > 0) {
        throw runtime_error("Function already defined in global scope");
    }
    int value = UserDefinedFunctionMap.size();
    UserDefinedFunctionMap[identifier] = value;
    FuctionReturnValueMap[identifier] = return_type;
}

int priority(const string& op, bool isUnary = false) {
    if (op == "||")
        return 1;
    if (op == "&&")
        return 2;
    if (op == "|")
        return 3;
    if (op == "^")
        return 4;
    if (op == "&")
        return 5;
    if (op == "==" || op == "!=")
        return 6;
    if (op == "<" || op == ">" || op == "<=" || op == ">=")
        return 7;
    if (op == "+")
        return 8;
    if (op == "*" || op == "/" || op == "%")
        return 9;
    if (op == "!" || op == "~" )
        return 10;
    // "-" has two kinds of priority
    if (op == "-" || op == "unary_minus_sign" || op == "binary_minus_sign") {
        if (isUnary)
            return 10;
        else
            return 8;
    }
    return 0;
}

int caculate_expression(const vector<LexicalAnalyzer::Token>&, int, string&);

// Convert the infix expression to a postfix expression
vector<LexicalAnalyzer::Token> infixToPostfix(const vector<LexicalAnalyzer::Token>& tokens, int ptr_expression, int expression_length, string& assemblyCode) {
    // string RPN is the postfix expression
    vector<LexicalAnalyzer::Token> RPN;
    stack<pair<LexicalAnalyzer::Token, bool>> ops;
    int ptr = ptr_expression; // Pointer to the first token of the expression

    while (ptr < ptr_expression + expression_length) {
        if (tokens[ptr].type == "Delimiter" && tokens[ptr].value == "(") {
            // If the token is a left parenthesis
            ops.push(make_pair(tokens[ptr], false));
        } else if (tokens[ptr].type == "Delimiter" && tokens[ptr].value == ")") {
            // If the token is a right parenthesis
            while (!ops.empty() && ((ops.top()).first).value != "(") {
                RPN.push_back(ops.top().first);
                ops.pop();
            }
            ops.pop();  // Remove '('
        } else if (tokens[ptr].type == "Operator" && (tokens[ptr].value == "+" || tokens[ptr].value == "*" || tokens[ptr].value == "/" || tokens[ptr].value == "%" || tokens[ptr].value == "<" || tokens[ptr].value == "<=" || tokens[ptr].value == ">" || tokens[ptr].value == ">=" || tokens[ptr].value == "==" || tokens[ptr].value == "!=" || tokens[ptr].value == "&" || tokens[ptr].value == "|" || tokens[ptr].value == "^" || tokens[ptr].value == "&&" || tokens[ptr].value == "||")) {
            // If the token is binary Operator
            while (!ops.empty() && priority((ops.top()).first.value, (ops.top()).second) >= priority(tokens[ptr].value, false)) {
                RPN.push_back(ops.top().first);
                ops.pop();
            }
            ops.push(make_pair(tokens[ptr], false));
        } else if (tokens[ptr].type == "Operator" && (tokens[ptr].value == "!" || tokens[ptr].value == "~")) {
            // If the token is a unary Operator
            while (!ops.empty() && priority((ops.top()).first.value, (ops.top()).second) >= priority(tokens[ptr].value, true)) {
                RPN.push_back(ops.top().first);
                ops.pop();
            }
            ops.push(make_pair(tokens[ptr], true));
        } else if (tokens[ptr].type == "Operator" && (tokens[ptr].value == "-")) {
            // If the token is "-" Operator, which has two kinds of priority
            if (tokens[ptr-1].type == "Operator" || (tokens[ptr-1].type == "Delimiter" && (tokens[ptr-1].value == "(" || tokens[ptr-1].value == ",")) || tokens[ptr-1].type == "Keyword") {
                // If the token is a unary Operator
                while (!ops.empty() && priority((ops.top()).first.value, (ops.top()).second) >= priority(tokens[ptr].value, true)) {
                    RPN.push_back(ops.top().first);
                    ops.pop();
                }
                LexicalAnalyzer::Token unary_minus_sign = {"Operator", "unary_minus_sign"};
                ops.push(make_pair(unary_minus_sign, true));
            } else {
                // If the token is a binary Operator
                while (!ops.empty() && priority((ops.top()).first.value, (ops.top()).second) >= priority(tokens[ptr].value, false)) {
                    RPN.push_back(ops.top().first);
                    ops.pop();
                }
                LexicalAnalyzer::Token binary_minus_sign = {"Operator", "binary_minus_sign"};
                ops.push(make_pair(binary_minus_sign, false));
            } 
        } else if (tokens[ptr].type == "Constant") {
            // If the token is a Constant
            RPN.push_back(tokens[ptr]);
        } else if (tokens[ptr].type == "Identifier") {

            string identifier_name = tokens[ptr].value;

            // check if it is a Identifier
            if (UserDefinedFunctionMap.count(tokens[ptr].value) > 0) {
                // If the token is a function Identifier
                
                string function_name = tokens[ptr].value;

                ptr+=2; // ptr points to first parameter

                // start to push parameters into stack
                // if parameters is not empty
                if (tokens[ptr].value != ")") {
                    // count number of parameters
                    int parameter_num = 1;
                    
                    int ptr_first_parameter = ptr;

                    int open_brackets = 0;
                    while(true) {
                        if (tokens[ptr].value == "(") {
                            open_brackets++;
                        } else if (tokens[ptr].value == ")" && open_brackets > 0) {
                            open_brackets--;
                        } else if (tokens[ptr].value == ")" && open_brackets == 0) {
                            break;
                        } else if (tokens[ptr].value == ",") {
                            parameter_num++;
                        }
                        ptr++;
                    }
                    // function_end points to the ")"
                    int function_end = ptr;
                    
                    ptr = ptr_first_parameter;
                    stack<int> parameters_ptr;

                    while(ptr < function_end) {
                        if (tokens[ptr].value == ",") {
                            parameters_ptr.push(ptr + 1);
                            ptr++;
                        } else {
                            ptr++;
                        }
                    }

                    // push other parameters into stack (in reverse order)
                    for (int i = 1; i < parameter_num; i++) {
                        ptr = parameters_ptr.top();
                        parameters_ptr.pop();
                        ptr += caculate_expression(tokens, ptr, assemblyCode);
                        // the result stores in stack
                        assemblyCode += "   pop eax\n";
                        // push eax into stack
                        assemblyCode += "   push eax\n";
                        // pass ","
                        // ptr++;
                    }

                    // push first parameter into stack
                    ptr = ptr_first_parameter;
                    ptr += caculate_expression(tokens, ptr, assemblyCode);
                    // the result stores in stack
                    assemblyCode += "   pop eax\n";
                    // push eax into stack
                    assemblyCode += "   push eax\n";
                    // pass ","
                    // ptr++;

                    // call the function
                    assemblyCode += "   call " + function_name + "\n";
                    // restore esp
                    assemblyCode += "   add esp, " + to_string(parameter_num * 4) + "\n";

                    // function_name is a global variable, move the return value eax to global variable
                    string return_value = function_name + "_return_value";
                    assemblyCode += "   mov " + return_value + ", eax\n";
                    ptr = function_end;
                    
                    // // move pointer to next token in expression
                    // ptr++;
                } else {
                    // if parameters is empty
                    // call the function without parameters
                    assemblyCode += "   call " + function_name + "\n";
                    // function_name is a global variable, move the return value eax to global variable
                    string return_value = function_name + "_return_value";
                    assemblyCode += "   mov" + return_value + ", eax\n";

                    // // move pointer to next token in expression
                    // ptr++;
                }

                string return_value = function_name + "_return_value";
                // push function return value into RPN
                RPN.push_back({"Identifier", return_value});
            } else {
                // If the token is an variable Identifier
                RPN.push_back(tokens[ptr]);
            }
        }
        // move pointer to next token in expression
        ptr++;
    }

    // Add the remaining Operators in stack to RPN
    while (!ops.empty()) {
        RPN.push_back(ops.top().first);
        ops.pop();
    }
    return RPN;
}
// Calculate the postfix expression and output the calculation process in assembly language.
string calculatePostfix(const vector<LexicalAnalyzer::Token>& RPN, map<string, int> identifierMap) {
    string expression_asm;
    stack<LexicalAnalyzer::Token> oprands;

    for (const LexicalAnalyzer::Token& token : RPN) {
        if (token.type == "Constant") {
            oprands.push(token);
            expression_asm += "\n";
            expression_asm += "   mov eax, " + token.value + "\n";
            expression_asm += "   push eax\n";
        } else if (token.type == "Identifier") {
            oprands.push(token);
            expression_asm += "\n";
            if (GlobalIdentifierMap.count(token.value) > 0) {
                // if token is a global variable
                expression_asm += "   mov eax, " + token.value + "\n";
            } else if (identifierMap.count(token.value) > 0) {
                // if token is a local variable
                expression_asm += "   mov eax, DWORD PTR [ebp-" + to_string(identifierMap[token.value] * 4 + 4) + "]\n";
            } else {
                cout << "ERROR! Identifier " << token.value << " has not been defined." << endl;
                exit(1);
            }
            expression_asm += "   push eax\n";
        } else if (token.type == "Operator") {
            if (token.value == "unary_minus_sign") {
                LexicalAnalyzer::Token oprand = oprands.top();
                oprands.pop();
                oprands.push({"Intermediate results", "x"});
                expression_asm += "\n";
                expression_asm += "   pop eax\n";
                expression_asm += "   neg eax\n";
                expression_asm += "   push eax\n";
            } else if (token.value == "!") {
                LexicalAnalyzer::Token oprand = oprands.top();
                oprands.pop();
                oprands.push({"Intermediate results", "x"});
                expression_asm += "\n";
                expression_asm += "   pop eax\n";
                
                // expression_asm += "   test eax, eax\n";  // Perform bitwise AND operation
                // expression_asm += "   setz al\n";  // Set AL to 1 if zero flag is set, otherwise set it to 0
                // expression_asm += "   movzx eax, al\n";  // Zero-extend AL to EAX
                // expression_asm += "   push eax\n";

                expression_asm += "   cmp eax, 0\n";  // Compare eax with 0
                expression_asm += "   sete al\n";     // Set AL (lower byte of EAX) to 1 if equal (i.e., if eax was 0)
                expression_asm += "   movzx eax, al\n"; // Zero-extend AL to EAX
                
                expression_asm += "   push eax\n";

            } else if (token.value == "~") {
                LexicalAnalyzer::Token oprand = oprands.top();
                oprands.pop();
                oprands.push({"Intermediate results", "x"});
                expression_asm += "\n";
                expression_asm += "   pop eax\n";
                expression_asm += "   neg eax\n";
                expression_asm += "   dec eax\n";
                expression_asm += "   push eax\n";
            } else {
                LexicalAnalyzer::Token oprand2 = oprands.top();
                oprands.pop();
                LexicalAnalyzer::Token oprand1 = oprands.top();
                oprands.pop();

                if (token.value == "+") {
                    oprands.push({"Intermediate results", "x"});
                    expression_asm += "\n";
                    expression_asm += "   pop ebx\n";
                    expression_asm += "   pop eax\n";
                    expression_asm += "   add eax, ebx\n";
                    expression_asm += "   push eax\n";
                } else if (token.value == "binary_minus_sign") {
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
                } else if(token.value == "%") {
                    oprands.push({"Intermediate results", "x"});
                    expression_asm += "\n";
                    expression_asm += "   pop ebx\n";
                    expression_asm += "   pop eax\n";
                    expression_asm += "   cdq\n";
                    expression_asm += "   idiv ebx\n";
                    expression_asm += "   push edx\n";
                } else if (token.value == "<") {
                    oprands.push({"Intermediate results", "x"});
                    expression_asm += "\n";
                    expression_asm += "   pop ebx\n";
                    expression_asm += "   pop eax\n";
                    expression_asm += "   cmp eax, ebx\n";
                    expression_asm += "   setl al\n";
                    expression_asm += "   movzx eax, al\n";
                    expression_asm += "   push eax\n";
                } else if (token.value == "<=") {
                    oprands.push({"Intermediate results", "x"});
                    expression_asm += "\n";
                    expression_asm += "   pop ebx\n";
                    expression_asm += "   pop eax\n";
                    expression_asm += "   cmp eax, ebx\n";
                    expression_asm += "   setle al\n";
                    expression_asm += "   movzx eax, al\n";
                    expression_asm += "   push eax\n";
                } else if (token.value == ">") {
                    oprands.push({"Intermediate results", "x"});
                    expression_asm += "\n";
                    expression_asm += "   pop ebx\n";
                    expression_asm += "   pop eax\n";
                    expression_asm += "   cmp eax, ebx\n";
                    expression_asm += "   setg al\n";
                    expression_asm += "   movzx eax, al\n";
                    expression_asm += "   push eax\n";
                } else if (token.value == ">=") {
                    oprands.push({"Intermediate results", "x"});
                    expression_asm += "\n";
                    expression_asm += "   pop ebx\n";
                    expression_asm += "   pop eax\n";
                    expression_asm += "   cmp eax, ebx\n";
                    expression_asm += "   setge al\n";
                    expression_asm += "   movzx eax, al\n";
                    expression_asm += "   push eax\n";
                } else if (token.value == "==") {
                    oprands.push({"Intermediate results", "x"});
                    expression_asm += "\n";
                    expression_asm += "   pop ebx\n";
                    expression_asm += "   pop eax\n";
                    expression_asm += "   cmp eax, ebx\n";
                    expression_asm += "   sete al\n";
                    expression_asm += "   movzx eax, al\n";
                    expression_asm += "   push eax\n";
                } else if (token.value == "!=") {
                    oprands.push({"Intermediate results", "x"});
                    expression_asm += "\n";
                    expression_asm += "   pop ebx\n";
                    expression_asm += "   pop eax\n";
                    expression_asm += "   cmp eax, ebx\n";
                    expression_asm += "   setne al\n";
                    expression_asm += "   movzx eax, al\n";
                    expression_asm += "   push eax\n";
                } else if (token.value == "&") {
                    oprands.push({"Intermediate results", "x"});
                    expression_asm += "\n";
                    expression_asm += "   pop ebx\n";
                    expression_asm += "   pop eax\n";
                    expression_asm += "   and eax, ebx\n";
                    expression_asm += "   push eax\n";
                } else if (token.value == "|") {
                    oprands.push({"Intermediate results", "x"});
                    expression_asm += "\n";
                    expression_asm += "   pop ebx\n";
                    expression_asm += "   pop eax\n";
                    expression_asm += "   or eax, ebx\n";
                    expression_asm += "   push eax\n";
                } else if (token.value == "^") {
                    oprands.push({"Intermediate results", "x"});
                    expression_asm += "\n";
                    expression_asm += "   pop ebx\n";
                    expression_asm += "   pop eax\n";
                    expression_asm += "   xor eax, ebx\n";
                    expression_asm += "   push eax\n";
                } else if (token.value == "&&") {
                    oprands.push({"Intermediate results", "x"});
                    expression_asm += "\n";
                    expression_asm += "   pop ebx\n";
                    expression_asm += "   pop eax\n";
                    expression_asm += "   cmp eax, 0\n";
                    expression_asm += "   je .Lfalse" + to_string(jump_label) + "\n";
                    expression_asm += "   cmp ebx, 0\n";
                    expression_asm += "   je .Lfalse" + to_string(jump_label) + "\n";
                    expression_asm += "   mov eax, 1\n";
                    expression_asm += "   jmp .Lend" + to_string(jump_label) + "\n";
                    expression_asm += ".Lfalse" + to_string(jump_label) + ":\n";
                    expression_asm += "   mov eax, 0\n";
                    expression_asm += ".Lend" + to_string(jump_label) + ":\n";
                    expression_asm += "   push eax\n";
                    jump_label++;
                } else if (token.value == "||") {
                    oprands.push({"Intermediate results", "x"});
                    expression_asm += "\n";
                    expression_asm += "   pop ebx\n";
                    expression_asm += "   pop eax\n";
                    expression_asm += "   cmp eax, 0\n";
                    expression_asm += "   jne .Ltrue" + to_string(jump_label) + "\n";
                    expression_asm += "   cmp ebx, 0\n";
                    expression_asm += "   jne .Ltrue" + to_string(jump_label) + "\n";
                    expression_asm += "   mov eax, 0\n";
                    expression_asm += "   jmp .Lend" + to_string(jump_label) + "\n";
                    expression_asm += ".Ltrue" + to_string(jump_label) + ":\n";
                    expression_asm += "   mov eax, 1\n";
                    expression_asm += ".Lend" + to_string(jump_label) + ":\n";
                    expression_asm += "   push eax\n";
                    jump_label++;
                }
            }
        }
    }
    return expression_asm;
}

int caculate_expression(const vector<LexicalAnalyzer::Token>& tokens, int ptr_expression, string& assemblyCode) {
    // step 1: count the length of expression
    int expression_length = 0;
    int open_brackets = 0;

    int is_in_function = 0;
    stack<int> function_brackets;

    while (true) {

        if (tokens[ptr_expression + expression_length].type == "Identifier") {
            if (UserDefinedFunctionMap.count(tokens[ptr_expression + expression_length].value) > 0) {
                function_brackets.push(0);
            }
        }

        if (tokens[ptr_expression + expression_length].value == "(") {

            if (!function_brackets.empty()) {
                function_brackets.top()++;
            }

            open_brackets++;
        } else if (tokens[ptr_expression + expression_length].value == ")" && open_brackets > 0) {
            open_brackets--;
            if (!function_brackets.empty()) {
                function_brackets.top()--;
                if (function_brackets.top() == 0) {
                    function_brackets.pop();
                }
            }
        } else if (tokens[ptr_expression + expression_length].value == ")" && open_brackets == 0) {
            break;
        } else if (tokens[ptr_expression + expression_length].value == ";" || (tokens[ptr_expression + expression_length].value == "," && function_brackets.empty())) {
            break;
        }
        expression_length++;
    }

    // step 2: convert the infix expression to a postfix expression
    vector<LexicalAnalyzer::Token> RPN = infixToPostfix(tokens, ptr_expression, expression_length, assemblyCode);
    // for (const LexicalAnalyzer::Token& token : RPN) {
    //     cout << "Type: " << token.type << ", Value: " << token.value << endl;
    // }

    // step 3: calculate the postfix expression and output the calculation process in assembly language
    string expression_asm = calculatePostfix(RPN, VariableidentifierMapStack.top());
    assemblyCode += expression_asm;

    // step 4: return the length of the expression
    return expression_length;
}

// Function to generate the tokens into assembly code
string generateAssembly(const vector<LexicalAnalyzer::Token>& tokens) {
    string assemblyCode;
    assemblyCode += "\n";

    // initialize the assembly code
    assemblyCode += ".intel_syntax noprefix\n";
    // assemblyCode += ".global main\n";
    // Check if the source code contains the println_int Lib_Function
    for (const auto& token : tokens) {
        if (token.type == "Lib_Function" && token.value == "println_int") {
            assemblyCode += ".extern printf\n\n";
            assemblyCode += ".data\n";
            assemblyCode += "format_str:\n";
            assemblyCode += "   .asciz \"%d\\n\"\n\n";
            break;
        }
    }
    assemblyCode += ".text\n";

    int ptr = 0; // Pointer to the current token
    
    // push global stack
    enterScope();

    // Loop through each token
    while (ptr < tokens.size()) {
        // If the first token is a Keyword
        if (tokens[ptr].type == "Keyword") {
            // define fuction or variable 
            if (tokens[ptr].value == "int" || tokens[ptr].value == "void") {
                if (tokens[ptr + 1].type == "Keyword" && tokens[ptr + 1].value == "main") {
                    // define fuction main


                    // add identifier to the current scope
                    addFunctionidentifier(tokens[ptr + 1].value, tokens[ptr].value);

                    assemblyCode += "\n";
                    assemblyCode += ".global " + tokens[ptr + 1].value + "\n";

                    if (tokens[ptr].value == "int") {
                        assemblyCode += ".data\n";
                        
                        // it is nasm syntax
                        // assemblyCode += tokens[ptr + 1].value + "_return_value " + "dd 0\n";
                        
                        // we should use gas syntax
                        assemblyCode += tokens[ptr + 1].value + "_return_value:\n" + "    .int 0\n";

                        string return_value = tokens[ptr + 1].value + "_return_value";

                        addGlobalIdentifier(return_value);
                    }

                    assemblyCode += ".text\n";

                    inFuctionWhat.push("main");

                    // push main stack
                    enterScope(); 

                    function_has_ended = 0;

                    assemblyCode += "main:\n";
                    assemblyCode += "   push ebp\n";
                    assemblyCode += "   mov ebp, esp\n";
                    // allocate 512 bytes of memory for main 
                    assemblyCode += "   sub esp, 0x200\n";

                    // push all function in stack<map<string, int>> FunctionidentifierMapStack as a variable
                    // for (const auto& function : FunctionidentifierMapStack.top()) {
                    //     assemblyCode += function.first + " dd 0\n";
                    // }

                    // pass "main(argc argv){""
                    while (tokens[ptr].value != "{") {
                        ptr++;
                    }
                    // enter main fuction scope
                    ptr++;
                } else if (tokens[ptr + 1].type == "Identifier") {
                    // define variable or function
                
                    if (tokens[ptr + 2].type == "Delimiter" && tokens[ptr + 2].value == "(") {      
                        // if Identifier is function

                        // add identifier to the current scope
                        addFunctionidentifier(tokens[ptr + 1].value, tokens[ptr].value);
                        
                        assemblyCode += "\n";
                        assemblyCode += ".global " + tokens[ptr + 1].value + "\n";
                        

                        if (tokens[ptr].value == "int") {
                            assemblyCode += ".data\n";
                            
                            // assemblyCode += tokens[ptr + 1].value + "_return_value " + "dd 0\n";
                            
                            // use gas syntax
                            assemblyCode += tokens[ptr + 1].value + "_return_value:\n" + "    .int 0\n";


                            string return_value = tokens[ptr + 1].value + "_return_value";

                            addGlobalIdentifier(return_value);
                        }

                        assemblyCode += ".text\n";

                        inFuctionWhat.push(tokens[ptr + 1].value);

                        // push function stack
                        enterScope();

                        assemblyCode += tokens[ptr + 1].value + ":\n";
                        assemblyCode += "   push ebp\n";
                        assemblyCode += "   mov ebp, esp\n";
                        // allocate 512 bytes of memory for the function
                        assemblyCode += "   sub esp, 0x200\n";
                        ptr += 3;

                        // scan and get parameters
                        if (tokens[ptr].type == "Delimiter" && tokens[ptr].value == ")") {
                            // If the function has no parameters
                            
                            // points to "{"
                            ptr++;
                        } else {
                            // If the function has parameters
                            int parameters_num = 0;
                            while (tokens[ptr].value != ")") {
                                

                                if (tokens[ptr].type == "Keyword" && tokens[ptr].value == "int") {
                                    ptr++;
                                } else if (tokens[ptr].type == "Identifier") {
                                    // add identifier to the current scope
                                    addVariableidentifier(tokens[ptr].value);

                                    // pass the parameters
                                    
                                    // wrong! can't move memory to memory
                                    // assemblyCode += "   mov DWORD PTR [ebp-" + to_string(VariableidentifierMapStack.top()[tokens[ptr].value] * 4 + 4) + "], DWORD PTR [ebp+" + to_string(parameters_num * 4 + 8) + "]\n";
                                    
                                    // use eax to pass
                                    assemblyCode += "   mov eax, DWORD PTR [ebp+" + to_string(parameters_num * 4 + 8) + "]\n";
                                    assemblyCode += "   mov DWORD PTR [ebp-" + to_string(VariableidentifierMapStack.top()[tokens[ptr].value] * 4 + 4) + "], eax\n";
                                    
                                    parameters_num++;

                                    ptr++;
                                } else if (tokens[ptr].type == "Delimiter" && tokens[ptr].value == ",") {
                                    ptr++;
                                } else {
                                    cout << "ERROR! Wrong parameter format." << endl;
                                    exit(1);
                                }
                            }
                            // points to "{"
                            ptr++;
                        }
                    } else {
                        // If the Identifier is variables

                        // ptr points to first variable
                        ptr++; 

                        while(true) {
                            
                            if (GlobalIdentifierMap.count(tokens[ptr].value) > 0) {
                                cout << "ERROR! Identifier " << tokens[ptr].value << " has been defined." << endl;
                                exit(1);
                            }

                            if (VariableidentifierMapStack.top().count(tokens[ptr].value) > 0) {
                                cout << "ERROR! Identifier " << tokens[ptr].value << " has been defined." << endl;
                                exit(1);
                            }

                            // add identifier to the current scope
                            addVariableidentifier(tokens[ptr].value);

                            string variable_name = tokens[ptr].value;

                            if (tokens[ptr + 1].value == "=") {
                                // If the variable is initialized
                                ptr += 2; // ptr points to start of the expression

                                ptr += caculate_expression(tokens, ptr, assemblyCode);

                                // the result stores in stack
                                assemblyCode += "   pop eax\n";
                                // store the result in the variable
                                assemblyCode += "   mov DWORD PTR [ebp-" + to_string(VariableidentifierMapStack.top()[variable_name] * 4 + 4) + "], eax\n";

                            } else if (tokens[ptr + 1].value == "," || tokens[ptr + 1].value == ";") {
                                // if the variable is not initialized
                                assemblyCode += "   mov DWORD PTR [ebp-" + to_string(VariableidentifierMapStack.top()[variable_name] * 4 + 4) + "], 0\n";
                                ptr++;
                            }

                            // printf("%s", tokens[ptr].value.c_str());

                            if (tokens[ptr].value == ";") {
                                ptr++;
                                break;
                            } else if (tokens[ptr].value == ",") {
                                ptr++;
                            } else {
                                cout << "ERROR! Wrong variable format." << endl;
                                exit(1);
                            }

                            // ptr points to ; next
                        }
                    }
                }
            } else if (tokens[ptr].value == "return") {
                assemblyCode += "\n";
                
                // ptr points to the first token of the expression
                ptr++;
                ptr += caculate_expression(tokens, ptr, assemblyCode);

                // the result stores in stack
                assemblyCode += "\n";
                assemblyCode += "   pop eax\n";
                assemblyCode += "   mov esp, ebp\n";
                assemblyCode += "   pop ebp\n";
                assemblyCode += "   ret\n";

                // leaveScope();

                // function_has_ended = 1;

            } else {
                cout << "ERROR! Unknown Keyword: " << tokens[ptr].value << endl;
                exit(1);
            }
        }
        // If the first token is an Identifier
        else if (tokens[ptr].type == "Identifier") {
            if (tokens[ptr + 1].value == "=") {
                // If the token is a variable Identifier

                string variable_name = tokens[ptr].value;

                if (GlobalIdentifierMap.count(tokens[ptr].value) > 0) {
                    // If the Identifier is a global variable
                    assemblyCode += "\n";
                    ptr += 2; // ptr points to start of the expression

                    ptr += caculate_expression(tokens, ptr, assemblyCode);

                    // the result stores in stack
                    assemblyCode += "   pop eax\n";
                    // store the result in the variable
                    assemblyCode += "   mov " + variable_name + ", eax\n";
                } else {
                    // If the Identifier is a local variable
                    assemblyCode += "\n";
                    ptr += 2; // ptr points to start of the expression

                    ptr += caculate_expression(tokens, ptr, assemblyCode);

                    // the result stores in stack
                    assemblyCode += "   pop eax\n";
                    // store the result in the variable
                    assemblyCode += "   mov DWORD PTR [ebp-" + to_string(VariableidentifierMapStack.top()[variable_name] * 4 + 4) + "], eax\n";
                }

                ptr++;
                // ptr points to , or ; next
            } else if (tokens[ptr + 1].type == "Delimiter" && tokens[ptr + 1].value == "(") {
                // If the token is a user defined function Identifier
                
                if (UserDefinedFunctionMap.count(tokens[ptr].value) > 0) {
                    // If the token is a function Identifier
                
                    string function_name = tokens[ptr].value;

                    ptr+=2; // ptr points to first parameter

                    // start to push parameters into stack
                    // if parameters is not empty
                    if (tokens[ptr].value != ")") {
                        // count number of parameters
                        int parameter_num = 1;
                    
                        int ptr_first_parameter = ptr;

                        int open_brackets = 0;
                        while(true) {
                            if (tokens[ptr].value == "(") {
                                open_brackets++;
                            } else if (tokens[ptr].value == ")" && open_brackets > 0) {
                                open_brackets--;
                            } else if (tokens[ptr].value == ")" && open_brackets == 0) {
                                break;
                            } else if (tokens[ptr].value == ",") {
                                parameter_num++;
                            }
                            ptr++;
                        }
                        // function_end points to the ")"
                        int function_end = ptr;
                        
                        ptr = ptr_first_parameter;
                        stack<int> parameters_ptr;

                        while(ptr < function_end) {
                            if (tokens[ptr].value == ",") {
                                parameters_ptr.push(ptr + 1);
                                ptr++;
                            } else {
                                ptr++;
                            }
                        }

                        

                        // push other parameters into stack (in reverse order)
                        for (int i = 1; i < parameter_num; i++) {
                            ptr = parameters_ptr.top();
                            parameters_ptr.pop();
                            ptr += caculate_expression(tokens, ptr, assemblyCode);
                            // the result stores in stack
                            // assemblyCode += "   pop eax\n";
                            // push eax into stack
                            // assemblyCode += "   push eax\n";
                            // pass ","
                            // ptr++;
                        }

                        // push first parameter into stack
                        ptr = ptr_first_parameter;
                        ptr += caculate_expression(tokens, ptr, assemblyCode);
                        // the result stores in stack
                        // assemblyCode += "   pop eax\n";
                        // push eax into stack
                        // assemblyCode += "   push eax\n";
                        // pass ","
                        // ptr++;

                        // call the function
                        assemblyCode += "   call " + function_name + "\n";
                        // restore esp
                        assemblyCode += "   add esp, " + to_string(parameter_num * 4) + "\n";

                        // function_name is a global variable, move the return value eax to global variable
                        if (FuctionReturnValueMap[function_name] == "int") {
                            string return_value = function_name + "_return_value";
                            assemblyCode += "   mov " + return_value + ", eax\n";
                        }

                        ptr = function_end;
                    
                        // move pointer to ";"
                        ptr++;
                    } else {
                        // if parameters is empty
                        // call the function without parameters
                        assemblyCode += "   call " + function_name + "\n";
                        // function_name is a global variable, move the return value eax to global variable
                        string return_value = function_name + "_return_value";
                        assemblyCode += "   mov" + return_value + ", eax\n";

                        // move pointer to ";"
                        ptr++;
                    }
                    // string return_value = function_name + "_return_value";
                    // // push function return value into RPN
                    // RPN.push_back({"Identifier", return_value});
                } else {
                    cout << "Function "+ tokens[ptr].value + " has not been defined yet!";
                    exit(1);
                }

                // move ptr to ";" next
                ptr++;
            }
        }
        // If the token is a Delimiter
        else if (tokens[ptr].type == "Delimiter") {

            if(tokens[ptr].value == ";" || tokens[ptr].value == ",") {
                ptr++;
            } else if (tokens[ptr].value == "{") {
                ptr++;
            } else if (tokens[ptr].value == "}") {
                // end of function
                string inWhatFunction = inFuctionWhat.top();
                if (FuctionReturnValueMap[inWhatFunction] == "void") {
                    assemblyCode += "\n";
                    assemblyCode += "   mov esp, ebp\n";
                    assemblyCode += "   pop ebp\n";
                    assemblyCode += "   ret\n";
                }

                // leave the current scope
                inFuctionWhat.pop();
                leaveScope();

                // move pointer to next token
                ptr++;
            } else {
                cout << "ERROR! Unknown Delimiter: " << tokens[ptr].value << endl;
                exit(1);
            }  
        }
        // if the token is a Lib_Function
        else if (tokens[ptr].type == "Lib_Function" && tokens[ptr].value == "println_int") {
            // point to start of expression
            ptr+=2;

            ptr += caculate_expression(tokens, ptr, assemblyCode);
            // the result stores in stack
            assemblyCode += "   pop eax\n";
            // push eax into stack
            assemblyCode += "   push eax\n";
            assemblyCode += "   push offset format_str\n";
            assemblyCode += "   call printf\n";
            assemblyCode += "   add esp, 8\n\n";
            
            // point to ";"
            ptr++; 
            
            // // point to first parameter
            // ptr+=2;
            // if (GlobalIdentifierMap.count(tokens[ptr].value) > 0) {
            //     // if token is a global variable

            //     // push and call printf
            //     assemblyCode += "\n";
            //     assemblyCode += "   push DWORD PTR " + tokens[ptr].value + "\n";
            //     assemblyCode += "   push offset format_str\n";
            //     assemblyCode += "   call printf\n";
            //     assemblyCode += "   add esp, 8\n\n";

            // } else if (VariableidentifierMapStack.top().count(tokens[ptr].value) > 0) {
            //     // if token is a local variable
                
            //     // push and call printf
            //     assemblyCode += "\n";
            //     assemblyCode += "   push DWORD PTR [ebp-" + to_string(VariableidentifierMapStack.top()[tokens[ptr].value] * 4 + 4) + "]\n";
            //     assemblyCode += "   push offset format_str\n";
            //     assemblyCode += "   call printf\n";
            //     assemblyCode += "   add esp, 8\n\n";

            // } else if (tokens[ptr].type == "Constant") {
            //     // if token is a constant

            //     // push and call printf
            //     assemblyCode += "\n";
            //     // push the constant value
            //     assemblyCode += "   push " + tokens[ptr].value + "\n"; 
            //     assemblyCode += "   push offset format_str\n";
            //     assemblyCode += "   call printf\n";
            //     assemblyCode += "   add esp, 8\n\n";
            // } else {
            //     cout << "ERROR! Identifier " << tokens[ptr].value << " has not been defined." << endl;
            //     exit(1);
            // }

            // // move pointer to ";"
            // ptr+=2;
        }
        else {
            cout << "ERROR! Unknown token: " << tokens[ptr].value << endl;
            exit(1);
        }
    }
    
    // print the end of assembly code
    // assemblyCode += "\n   mov eax, 0\n";
    // assemblyCode += "   leave\n";
    // assemblyCode += "   ret\n";

    // add \n
    assemblyCode += "\n";

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
    // for (LexicalAnalyzer::Token &token : tokens) {
    //     // la.printToken(token);
    //     cout << "Type: " << token.type << ", Value: " << token.value << endl;
    // }

    // Generate the assembly code
    assemblyCode = generateAssembly(tokens);
    cout << assemblyCode << endl;
    
    return 0;
}