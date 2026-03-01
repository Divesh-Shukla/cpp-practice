#include <iostream>

int main(){

    int num;
    bool isPrime = true;

    std::cout << "Enter the number(>1) you wanna check: ";
    if(!(std::cin >> num) || num <= 1){
        std::cerr << "Invalid number input!";
        return 1;
    }

    if(num==2){
    std::cout << "The number enetered is Prime";
    return 0;
    }
    if(num%2==0){
        std::cout << "The number enetered is Not Prime";
        return 0;
    }

    for(int i = 2; i*i <= num; i++){
        if(num%i == 0){
            isPrime = false;
            break;
        }
    }

    (isPrime)? std::cout<<"The entered number is a prime number" : std::cout << "The entered number is not a prime number.";

    return 0;
}

    
