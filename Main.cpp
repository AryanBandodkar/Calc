//The main prg to run if you want to run the Calcultor
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include "Calculator.h"
using namespace std;

int main()
{
    Calculator calc;
    string expression;
    char option;

    while (1)
        {
        cout << "Enter an expression (or type 'exit' to quit)(to use Memory in the expression use 'M')(dont add spaces): "<<endl;
        cin >> expression;

        if (expression == "exit")
            break;

        try {
            double result = calc.evaluateExpression(expression);
            cout<<"Result: "<<result<<endl;

            cout<<"Do you want to save the result to memory? (y/n): ";
            cin >> option;

            if (option == 'y' || option == 'Y') {
                calc.saveToMemory();
                cout <<"Result saved to memory."<<endl;
            }

            cout<<"Memory value: "<<calc.getMemory()<<endl;
        }
        catch (const std::runtime_error& e)
         {
            cerr << "Error: " << e.what() <<endl;
        }
    }

    return 0;
}
