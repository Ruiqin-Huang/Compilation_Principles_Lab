// Step 1: Convert the infix expression to a postfix expression. 

#include <stack>
#include <string>
#include <iostream>

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

std::string infixToPostfix(std::string infix) {
    std::stack<char> ops;
    std::string postfix;

    for (char c : infix) {
        if (c == '(') {
            ops.push(c);
        } else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                postfix += ops.top();
                ops.pop();
            }
            ops.pop();  // Remove '('
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {
                postfix += ops.top();
                ops.pop();
            }
            ops.push(c);
        } else {
            postfix += c;
        }
    }

    while (!ops.empty()) {
        postfix += ops.top();
        ops.pop();
    }

    return postfix;
}

int main() {
    std::string infix = "a+b*(c-d)/e";
    std::string postfix = infixToPostfix(infix);
    std::cout << "Postfix expression: " << postfix << "\n";
    return 0;
}

// Step 2: Calculate the postfix expression and output the calculation process in assembly language.

#include <stack>
#include <string>
#include <iostream>

int calculatePostfix(std::string postfix) {
    std::stack<int> operands;

    for (char c : postfix) {
        if (c >= '0' && c <= '9') {
            operands.push(c - '0');
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            int operand2 = operands.top();
            operands.pop();
            int operand1 = operands.top();
            operands.pop();

            switch (c) {
                case '+':
                    operands.push(operand1 + operand2);
                    break;
                case '-':
                    operands.push(operand1 - operand2);
                    break;
                case '*':
                    operands.push(operand1 * operand2);
                    break;
                case '/':
                    operands.push(operand1 / operand2);
                    break;
            }
        }
    }

    return operands.top();
}

int main() {
    std::string postfix = "123*+4-";
    int result = calculatePostfix(postfix);
    std::cout << "Result: " << result << "\n";
    return 0;
}