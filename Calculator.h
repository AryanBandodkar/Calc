//MiniProject
//Scientific Calculator (Normal Calculator)
//Name : Aryan Bandodkar RollNo : 23CO01
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <cstddef>
#include <conio.h>

using namespace std;
class Calc
{
    protected:
    double result; //Holds The Result of each expression
    double memory; //Memory Feature to keep track of an o/p if required

    public:
        Calc():result(0),memory(0){}
        virtual double evaluateExpression(const string& expression);//Arg = Input eqn , o/p = soln of string
        void saveToMemory();// Saves result to Memory
        void normalCalculatorMenu();//Menu driven for normal calc

    protected:
        void clearMemory();//Sets Mem to 0
        double getMemory();//Returns Mem with the stroed value
        void applyOperators(stack<double>& values,stack<string>& operators);// i/p = stack of operands and operators, sends the first 2 operands and 1 operator
        int precedence(char ch);//Sends the Precedence level of the operator
        bool isOperator(char ch);//Checks if its an operand or not
        string replaceMemoryWithM(const string& expression);//Removes 'M' and Replaces it with the stored value of Mem
        virtual double evaluate(string& expression);//Parses the i/p string
        double calculate(double left,double right,char op);//Gets the i/p from applyOperator and performs arithmetic of 2 operands and 1 operator


};
double Calc::evaluateExpression(const string& expression)
    {
        string exp =replaceMemoryWithM(expression);
       string modifiedExp;
    
    for (size_t i=0;i<exp.length();++i) 
    {
        if (i==0&&exp[i]=='-')
        {
            if(isOperator(exp[i+1]))
                throw runtime_error ("Two Operators Present Without Any Operands");
            modifiedExp +='0';
        }
        else if(isalpha(exp[i]))
            throw runtime_error("Invalid Letter");
            
        else if (isOperator(exp[i])&&exp[i+1]=='-') 
        {
            modifiedExp +=exp[i];
            modifiedExp +='0';
            continue;
        }
        else if(isOperator(exp[i])&&exp[i+1]=='\0')
            throw runtime_error("Two Operator Present Without Any Operands");
        else if(isOperator(exp[i])&&isOperator(exp[i+1]))
            throw runtime_error("Two Operator Present Without Any Operands");
        modifiedExp +=exp[i];
    }
     result =evaluate(modifiedExp);
        return result;
    }

    void Calc::saveToMemory()
   {
       memory=result;
   }

   void Calc::clearMemory()
   {
       memory=0;
   }

   double Calc::getMemory()
   {
       return memory;
   }

   bool Calc::isOperator(char ch)
   {
        if( ch=='+' || ch=='-' || ch=='*' || ch=='%' || ch=='^' || ch=='/' )
            return 1;
        else
            return 0;
   }

   int Calc::precedence(char ch)
   {
         if (ch=='^')
            return 3;
        if (ch=='*' || ch=='/' || ch=='%')
            return 2;
        if (ch=='+' || ch=='-')
            return 1;
        return 0;
   }

   double Calc::calculate(double left,double right,char op)
   {

       switch (op) {
            case '+':
                return left+right;

            case '-':
                return left-right;

            case '*':
                return left*right;

            case '/':
                if (right==0)
                    throw runtime_error("Division by zero error!");
                return left/right;

            case '%':
                if (right==0)
                    throw runtime_error("Modulus by zero error!");
                return fmod(left,right);

            case '^':
                return pow(left,right);

            default:
                return 0;
        }
    }

    string Calc::replaceMemoryWithM(const string& expression)
   {
    string replaced = expression;
    stringstream ss;
    ss<<memory;
    size_t pos;
    while ((pos=replaced.find('M'))!=string::npos) 
        replaced.replace(pos,1, ss.str());
    return replaced;
   }


    void Calc::applyOperators(stack<double>& values,stack<string>& operators)
    {
        char op =operators.top()[0];
        operators.pop();
        double right=values.top();
        values.pop();
        double left=values.top();
        values.pop();

       values.push(calculate(left, right, op));
    }

    double Calc::evaluate(string& expression)
    {
        stack<double> values;
        stack<string> operators;
        istringstream iss(expression);

        char token;
        double num;

        while (iss>>token)
         {
            if (isdigit(token))
            {
                iss.putback(token);
                iss>>num;
                values.push(num);
            }
            else if(token=='(')
            {
                string op(1,token);
                operators.push(op);
            }
            else if (token==')')
            {
                while (!operators.empty()&&operators.top()!="(")
                {
                    applyOperators(values, operators);
                }
                operators.pop();
            }
            else if (isOperator(token))
            {

                while (!operators.empty() && precedence(operators.top()[0])>=precedence(token))
                {
                    applyOperators(values, operators);
                }
                 string op(1, token);
                operators.push(op);
            }
        }

        while (!operators.empty())
        {
            applyOperators(values, operators);
        }

        return values.top();
    }
    void Calc:: normalCalculatorMenu()
     {
        Calc calc;
        int option;
        string expression;

        do
        {
            cout<<"\n--- Normal Calculator Menu ---"<<endl;
            cout<<"1. Evaluate Expression"<<endl;
            cout<<"2. Save Result to Memory"<<endl;
            cout<<"3. Help"<<endl;
            cout<<"0. Return to Main Menu\n";
            cout<<"Enter your choice: "<<endl;
            cin>>option;
             
        system("cls");
        switch (option) {
            case 1:
                cout<<"\tEnter an expression (e.g: 4+5-3/2): ";
                cin>>expression;
                try 
                {
                    double result=calc.evaluateExpression(expression);
                    cout<<"Result: "<< result << endl;
                } 
                catch (const exception& e) 
                {
                    cerr<<"\t Error: " << e.what() << endl;
                }
                break;

            case 2:
                calc.saveToMemory();
                cout<<"\tResult saved to memory."<<endl;
                break;

            case 3:
                cout<<"\tCan Perform Normal arithmetic only with precedence into consideration"<<endl;
                cout<<"\tUse the foll operators only *,^,%,+,-"<<endl;
                cout<<"\tUse 'M' to use the saved memory value "<<endl;
                break;

            case 0:
                cout<<"\tReturning to main menu..."<<endl;
                break;

            default:
                cout<<"\tInvalid choice! Please select again."<<endl;
        }
    
    } while (option!=0);
}

#endif


