#include <iostream>
#include <string>

int main() {
    // first implementation
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;

    int a, b;
    std::cout << "Enter two integers: ";
    std::cin >> a >> b;

    std::cout << "I'm " << name << " and the sum of " << a << "and " << b << " is " << a + b << std::endl;

    // Second Implementation
    int sum = 0;
    int val;
    std::cout << "Enter the numbers you wanna add.\nNumbers: ";
    /*
    Concepts used:-
    1. The std::cin>>n not only performs the input but also it also returns a refernce to the std::cin object which
    when used as a condition return the stream condition,i.e, if the entered input is type match for the variable the stream returns true
    otherwise false.
    */
    while (std::cin >> val) {
        sum += val;
    }

    std::cout << "The sum of the numbers you entered is: " << sum << std::endl;

    return 0;
}
