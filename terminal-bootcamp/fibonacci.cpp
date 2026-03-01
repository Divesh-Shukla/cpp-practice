#include<iostream>

int main(){
    int term;
    std::cout << "Enter the term(>=0) of fibonacci you want to find: ";
    if(!(std::cin >> term) || term < 0){
        std::cerr << "Invalid term!\nPlease enter a non-negative integer.\n";
        return 1;
    }

    int term_1 = 0;
    int term_2 = 1;

    int output;

    if(term == 0){
        output = term_1;
        std::cout << "The " << term <<"th fibonacci number is: " << output << std::endl;
        return 0;
    }else if (term == 1){
        output = term_2;
        std::cout << "The " << term <<"th fibonacci number is: " << output << std::endl;
        return 0;
    }else{
        for(int i = 2; i <= term; i++){
            output = term_1 + term_2;
            term_1 = term_2;
            term_2 = output;
        }
    }

    std::cout << "The " << term <<"th fibonacci number is: " << output << std::endl;
    return 0;

}
