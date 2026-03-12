#include<iostream>
#include "operations.h"
using namespace std;

int main(){

    int a,b;
    cout << "Enter the numbers(two) on which you wanna perform operation on: ";
    cin >> a >> b;

    cout <<"Sum: " << add(a,b) << endl;
    cout <<"Product: "<< multiply(a,b) << endl;
    cout << "Subtract: " << ((a>b) ? subtract(a,b) : subtract(b,a)) << endl;

    return 0;
}

