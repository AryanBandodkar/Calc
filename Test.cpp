#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>  // For exception handling

class Calculator {
protected:
    double result;
    double memory;

public:
    Calculator() : result(0), memory(0) {}

    // Method to evaluate an expression
    double evaluateExpression(const std::string& expression) {
        std::string exp = replaceMemoryWithM(expression);
        result = evaluate(exp);
        return result;
    }

    // Method to save the result to memory
    void saveToMemory() {
        memory = result;
    }

    // Method to clear the memory
    void clearMemory() {
        memory = 0;
    }

    // Display current memory value
    double getMemory() const {
        return memory;
    }

protected:
    // Replace 'M' with the current memory value
    std::string replaceMemoryWithM(const std::string& expression) {
        std::string replacedExpr;
        for (char ch : expression) {
            if (ch == 'M') {
                replacedExpr += std::to_string(memory);
            } else {
                replacedExpr += ch;
            }
        }
        return replacedExpr;
    }

    // Function to evaluate the expression considering BODMAS
    double evaluate(const std::string& expression) {
        std::stack<double> values;
        std::stack<char> operators;
        std::istringstream iss(expression);

        char token;
        double num;

        while (iss >> token) {
            if (isdigit(token)) {
                iss.putback(token);
                iss >> num;
                values.push(num);
            } else if (token == '(') {
                operators.push(token);
            } else if (token == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    applyOperator(values, operators);
                }
                operators.pop(); // Remove '('
            } else if (isOperator(token)) {
                while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                    applyOperator(values, operators);
                }
                operators.push(token);
            }
        }

        while (!operators.empty()) {
            applyOperator(values, operators);
        }

        return values.top();
    }

    // Function to apply operator
    void applyOperator(std::stack<double>& values, std::stack<char>& operators) {
        double right = values.top();
        values.pop();

        double left = values.top();
        values.pop();

        char op = operators.top();
        operators.pop();

        values.push(calculate(left, right, op));
    }

    // Check if a character is an operator
    bool isOperator(char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^';
    }

    // Get operator precedence
    int precedence(char op) {
        if (op == '^')
            return 3;
        if (op == '*' || op == '/' || op == '%')
            return 2;
        if (op == '+' || op == '-')
            return 1;
        return 0;
    }

    // Perform calculation based on operator
    double calculate(double left, double right, char op) {
        switch (op) {
            case '+': return left + right;
            case '-': return left - right;
            case '*': return left * right;
            case '/':
                if (right == 0)
                    throw std::runtime_error("Division by zero error!");
                return left / right;
            case '%':
                if (right == 0)
                    throw std::runtime_error("Modulo by zero error!");
                return fmod(left, right);  // Use fmod for modulus with doubles
            case '^': return pow(left, right);   // Use pow for exponentiation
            default: return 0;
        }
    }
};

int main() {
    Calculator calc;
    std::string expression;
    char option;

    while (true) {
        std::cout << "Enter an expression (or type 'exit' to quit): ";
        std::cin >> expression;

        if (expression == "exit")
            break;

        try {
            double result = calc.evaluateExpression(expression);
            std::cout << "Result: " << result << std::endl;

            std::cout << "Do you want to save the result to memory? (y/n): ";
            std::cin >> option;

            if (option == 'y' || option == 'Y') {
                calc.saveToMemory();
                std::cout << "Result saved to memory." << std::endl;
            }

            std::cout << "Memory value: " << calc.getMemory() << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}



