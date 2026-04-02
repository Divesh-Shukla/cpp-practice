#include<iostream>

char stack[50];
int top{-1};

void push(char c)
{
    stack[++top] = c;
}

char pop()
{
    return stack[top--];
}