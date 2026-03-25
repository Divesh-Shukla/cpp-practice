#include<iostream>

class Stack
{
private:
    int* stack;
    int top;
    bool dynamic = true;
    int maxIndx;
    void resize()
    {
        int* newArr;
        if (maxIndx == -1)
        {
            newArr = new int[1];
            maxIndx = 0;
            stack = newArr;
            return;
        }
        
        newArr = new int[2*(maxIndx+1)];
        for (int i = 0; i <= maxIndx; i++)
        {
            newArr[i] = stack[i];
        }
        delete[] stack;
        stack = newArr;
        maxIndx = 2*(maxIndx+1) - 1;
    }

public:

    Stack()
    {
        stack = nullptr;
        top = -1;
        maxIndx = -1;
    }

    Stack(int size, bool dynamic)
    {
        stack = new int[size];
        top = -1;
        maxIndx = size - 1;
        this->dynamic = dynamic;
    }

    bool isEmpty()
    {
        if (top == -1)
        {
            std::cout << "Empty Stack!\nStack Underflow!\n";
            return true;
        }
        return false;
    }

    void push(int n)
    {
        if (top == maxIndx && dynamic)
        {
            resize();
        }else if(top==maxIndx && dynamic==false)
        {
            std::cout << "Stack Overflow!\n";
            return;
        }
        
        top++;
        stack[top] = n;
    }

    void pop()
    {
        if (isEmpty())
        {
            return;
        }
        top--;
    }

    void peek()
    {
        if (isEmpty())
        {
            return;
        }
        std::cout << "Top: " << stack[top] << "\n";
    }

    void display()
    {
        if (isEmpty())
        {
            return;
        }
        std::cout << "Stack elements:";   
        for (int i = top; i > -1; i--)
        {
            std::cout<<" "<<stack[i];
        }
        std::cout << "\n";
    }

    ~Stack()
    {
        delete[] stack;
    }

};

int main()
{
    Stack s;
    s.push(10);
    s.display();
    s.push(23);
    s.push(7);
    s.push(32);
    s.display();
    s.push(88);
    s.display();
    s.peek();
    s.push(34);
    s.display();
    return 0;
}