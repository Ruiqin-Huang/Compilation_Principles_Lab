#include <iostream>
#include <vector>
#include <string>

struct Token {
    std::string value;
};

int main() {
    // 创建一个包含多个表达式的 tokens 数组
    std::vector<Token> tokens = {
        {"1"}, {"+"}, {"2"}, {";"}, 
        {"("}, {"3"}, {"+"}, {"4"}, {")"}, {";"}, 
        {"5"}, {","}, 
        {"("}, {"6"}, {"+"}, {"7"}, {")"}, {")"}
    };

    // 测试你的代码是否能正确地计算每个表达式的长度
    int ptr_expression = 0;
    while (ptr_expression < tokens.size()) {
        int expression_length = 0;
        int open_brackets = 0;
        while (true) {
            if (tokens[ptr_expression + expression_length].value == "(") {
                open_brackets++;
            } else if (tokens[ptr_expression + expression_length].value == ")" && open_brackets > 0) {
                open_brackets--;
            } else if (tokens[ptr_expression + expression_length].value == ")" && open_brackets == 0) {
                break;
            } else if (tokens[ptr_expression + expression_length].value == ";" || tokens[ptr_expression + expression_length].value == ",") {
                break;
            }
            expression_length++;
        }

        // 打印表达式的长度
        std::cout << "Expression length: " << expression_length << std::endl;

        // 移动到下一个表达式
        ptr_expression += expression_length + 1;
    }

    return 0;
}