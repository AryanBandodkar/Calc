//MiniProject OOPS
//Scientific Calculator (Main Program)
//Name ; Aryan Bandodkar Roll : 23CO01

#ifndef SCICALC_H
#define SCICALC_H
#include "Calculator.h"
#include <string>
#include <stack>
#include <cmath>
#include<conio.h>




class SciCalculator : public Calc
{
    public:
        SciCalculator():Calc(){}
        double evaluateExpression(const string& expression) override;//i/p = eqn string , o/p =res
        void scientificCalculatorMenu();//Menu driven menu for scicalc
    protected:
        string processFunctions(const string&);//changes sin,cos,tan,log,sqrt into  their respective values
        double evaluateCos(double degrees);
        double evaluateSin(double degrees);
        double evaluateTan(double degrees);
        double evaluateLog(double value);
        double evaluateSqrt(double value);
};

string SciCalculator::processFunctions(const string& input)
{
    string result=input;
    size_t pos = 0;
    while ((pos=result.find("sin("))!=string::npos) 
    {
        size_t start=pos + 4;
        size_t end=result.find(')', start);
        string numberStr=result.substr(start,end-start);
        double number=atof(numberStr.c_str());
        double value=evaluateSin(number);
        result.replace(pos,end-pos+1,to_string(value));
    }

    while ((pos=result.find("cos("))!=string::npos) 
    {
        size_t start=pos+4;
        size_t end=result.find(')',start);
        string numberStr=result.substr(start,end-start);
        double number=atof(numberStr.c_str());
        double value=evaluateCos(number);
        result.replace(pos,end-pos+1,to_string(value));
    }

    while ((pos=result.find("tan("))!=string::npos) 
    {
        size_t start=pos + 4;
        size_t end=result.find(')', start);
        string numberStr=result.substr(start,end-start);
        double number=atof(numberStr.c_str());
        double value=evaluateTan(number);
        result.replace(pos,end-pos+1,to_string(value));
    }
    
    while ((pos=result.find("log("))!=string::npos) 
    {
        size_t start=pos+4;
        size_t end=result.find(')',start);
        string numberStr=result.substr(start,end-start);
        double number=atof(numberStr.c_str());
        double value=evaluateLog(number);
        result.replace(pos,end-pos+1,to_string(value));
    }
    while ((pos = result.find("sqrt("))!=string::npos) 
    {
        size_t start=pos + 5;
        size_t end=result.find(')', start);
        string numberStr=result.substr(start,end-start);
        double number=atof(numberStr.c_str());
        double value=evaluateSqrt(number);
        result.replace(pos,end-pos+1,to_string(value));
    }

    return result;
}


double SciCalculator::evaluateExpression(const string& expression)
    {
       string exp=replaceMemoryWithM(expression);
       string modifiedExp;
   for (size_t i=0;i<exp.length();++i) 
    {
        if (i==0&&exp[i]=='-')
        {
            if(isOperator(exp[i+1]))
                throw runtime_error ("Two Operators Present Without Any Operands");
            modifiedExp +='0';
        }
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
        string formatted_exp=processFunctions(modifiedExp);
        for (size_t i=0;i<formatted_exp.length();++i) 
            if(isalpha(formatted_exp[i]))
                throw runtime_error("Invalid Letter");

        result=evaluate(formatted_exp);
        return result;
    }

double SciCalculator:: evaluateSin(double degrees) 
{
    return sin(degrees*M_PI/180.0);
}
double SciCalculator::evaluateCos(double degrees) 
{
    return cos(degrees*M_PI/180.0);
}

double SciCalculator::evaluateTan(double degrees) 
{
    return tan(degrees*M_PI/180.0);
}

double SciCalculator::evaluateLog(double value) 
{
    return log(value);
}

double SciCalculator::evaluateSqrt(double value) 
{
    return sqrt(value);
}
    void SciCalculator::scientificCalculatorMenu() 
    {
    int option;
    string expression;
    SciCalculator scicalc;

    do {
        cout<<endl<<"\n--- Scientific Calculator Menu ---"<<endl;
        cout<<"1. Evaluate Expression"<<endl;
        cout<<"2. Save Result to Memory"<<endl;
        cout<<"3. Help"<<endl;
        cout<<"0. Return to Main Menu"<<endl;
        cout<<"Enter your choice: "<<endl;
        cin>>option;
        system("cls");
        switch (option) 
        {
            case 1:
                cout<<endl<<"Enter an expression (e.g., 4+sin(30)+log(50)): ";
                cin>>expression;
                try 
                {
                    double result=scicalc.evaluateExpression(expression);
                    cout<<"Result: "<<result<<endl;
                } 
                catch (const std::exception& e) 
                {
                    cerr<<"Error: "<< e.what()<<endl;
                }
                break;

            case 2:
                scicalc.saveToMemory();
                cout<<"Result saved to memory."<<endl;
                break;

            case 3:
                cout<<"\tPerforms Whatever the Normal Calculator Can do"<<endl;
                cout<<"\tCan use 'sin()' , 'cos()' ,  'tan()' , 'log()' , 'sqrt()' with a number in the bracket "<<endl;
                cout<<"\tExample: sin(30) , cos(45) , log(50)"<<endl;
                break;
            case 0:
                cout<<"Returning to main menu..."<<endl;
                break;
            default:
                cout<<"Invalid choice, Please select again."<<endl;
        }
    } while(option!=0);
}




    
#endif
