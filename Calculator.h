//Name ; Aryan Bandodkar Roll : 23CO01

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>
using namespace std;

class Calculator
{
    protected:
    double result;
    double memory;

    public:
        Calculator()
        {
            result=0;
            memory=0;
        }
        virtual double evaluateExpression(const string& expression);//
        void saveToMemory();//
        void clearMemory();//
        double getMemory();//

    protected:
        string replaceMemoryWithM(const string& expression);//
        virtual double evaluate(const string& expression);
        void applyOperator(stack<double>& values,stack<char>& operators);//
        bool isOperator(char ch);//
        int precedence(char ch);//
        double calculate(double left, double right, char op);//

};

    double Calculator::evaluateExpression(const string& expression)
    {
        string exp = replaceMemoryWithM(expression);
        result = evaluate(exp);
        return result;
    }

    void Calculator::saveToMemory()
   {
       memory=result;
   }

   void Calculator::clearMemory()
   {
       memory=0;
   }

   double Calculator::getMemory()
   {
       return memory;
   }

   bool Calculator::isOperator(char ch)
   {
        if( ch=='+' || ch=='-' || ch=='*' || ch=='%' || ch=='^' || ch=='/' )
            return 1;
        else
            return 0;
   }

   int Calculator::precedence(char ch)
   {
         if (ch == '^')
            return 3;
        if (ch == '*' || ch == '/' || ch == '%')
            return 2;
        if (ch == '+' || ch == '-')
            return 1;
        return 0;
   }

   double Calculator::calculate(double left,double right,char op)
   {

       switch (op) {
            case '+':
                return left + right;

            case '-':
                return left - right;

            case '*':
                return left * right;

            case '/':
                if (right == 0)
                    throw runtime_error("Division by zero error!");
                return left / right;

            case '%':
                if (right == 0)
                    throw runtime_error("Modulo by zero error!");
                return fmod(left, right);

            case '^':
                return pow(left, right);

            default: return 0;
        }
    }

    string Calculator::replaceMemoryWithM(const string& expression)
   {
        string replacedExpr;
        for (char ch : expression) {
            if (ch == 'M') {
                replacedExpr +=to_string(memory);
            } else {
                replacedExpr += ch;
            }
        }
        return replacedExpr;
    }

    void Calculator::applyOperator(stack<double>& values,stack<char>& operators)
    {
        double right = values.top();
        values.pop();

        double left = values.top();
        values.pop();

        char op = operators.top();
        operators.pop();

        values.push(calculate(left, right, op));
    }

    double Calculator::evaluate(const string& expression)
    {
        stack<double> values;
        stack<char> operators;
        istringstream iss(expression);

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




