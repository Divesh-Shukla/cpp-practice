#include<stdio.h>

int factorial(int n)
{
    
    return n*factorial(n);
}

int main()
{
    int n = 5;
    int prdct = factorial(n);
    printf("%d\n", prdct);
    return 0;
}