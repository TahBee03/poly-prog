/*
NAME: Talike Bennett
PROJECT: Polynomial Operations
FILE: PO_main.cpp
*/

#include <iostream>
#include <iomanip> // Needed for setfill() and setw()
#include "PO_polyclass.hpp"
using namespace std;

void PrintSeparator() { // Prints out a series of dashes (-) to separate information

    for(int i = 0; i < 45; i++) cout << "-";
    cout << endl;

}

void AddPoly() {

    int o;

    cout << "What is the order of the first polynomial? ";
    cin >> o;

    double* nums = new double[o + 1];

    for(int i = o; i >= 0; i--) {

        cout << "Enter coefficient " << o - i + 1 << ": ";
        cin >> nums[i];

    }

    Polynomial<double> P1(o, nums);

    cout << "What is the order of the second polynomial? ";
    cin >> o;

    delete[] nums;
    nums = new double[o + 1];

    for(int i = o; i >= 0; i--) {

        cout << "Enter coefficient " << o - i + 1 << ": ";
        cin >> nums[i];

    }

    Polynomial<double> P2(o, nums);

    cout << "P1(x) = " << P1 << endl;
    cout << "P2(x) = " << P2 << endl;
    cout << "P1(x) + P2(x) = " << P1 + P2 << endl;

}

int main() {
    
    cout << "Welcome to Polynomial Operations!" << endl;
    cout << endl;

    int option;
    
    cout << "What would you like to do?" << endl;
    cout << "1| " << left << setw(26) << "polynomial addition" << "(P1 + P2)" << endl;
    cout << "2| " << left << setw(26) << "polynomial subtraction" << "(P1 - P2)" << endl;
    cout << "3| " << left << setw(26) << "polynomial multiplication" << "(P1 * P2)" << endl;
    cout << "4| " << left << setw(26) << "polynomial scaling" << "(P1 * c)" << endl;
    cout << "5| " << left << setw(26) << "solve" << "(P1(x) = c)" << endl;
    cout << "(Enter any other number to quit the program.)" << endl;
    cout << endl;

    cout << "Option: ";
    cin >> option;

    switch(option) {

        case 1:
            AddPoly();
            break;
        default:
            cout << "Goodbye!" << endl;




    }

    return 0;

}
