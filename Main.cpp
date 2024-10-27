//MiniProject OOPS
//Scientific Calculator (Main Program)
//Name : Aryan Bandodkar RollNo:23CO01
#include <iostream>
#include<conio.h>
#include "Calculator.h"
#include "SciCalc.h"
using namespace std;

int main() 
{
    int choice;
    do
    {
        cout<<"\n--- Calculator Application ---\n";
        cout<<"1. Normal Calculator\n";
        cout<<"2. Scientific Calculator\n";
        cout<<"0. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        system("cls");
        switch (choice) 
        {
            case 1:
                {
                    Calc c;
                    c.normalCalculatorMenu();
                    break;
                }

            case 2:
                {
                    SciCalculator s;
                    s.scientificCalculatorMenu();
                    break;
                }

            case 0:
                cout<<"\tThanks For Using The Calculator.\n";
                break;

            default:
                cout<<"\tInvalid choice, Please select again." <<endl;
        }
    }while(choice!=0);

    return 0;
}

