#include<iostream>

class Stack
{
private:
    struct Node
    {
        int data;
        struct Node* next;
    };
    struct Node* top;
    int capacity;
    int size;
    
public:
    Stack()
    {
        top = nullptr;
        size = 0;
        capacity = -1;
    }

    Stack(int n)
    {
        top = nullptr;
        size = 0;
        capacity = n;
    }

    bool isEmpty()
    {
        if (top == nullptr)
        {
            std::cout << "Stack Underflow!\n";
            return true;
        }
        return false;
    }

    void push(int n)
    {
        if(size == capacity)
        {
            std::cout << "Stack Overflow!\n";
            return;
        }
        struct Node* newNode = new Node();
        newNode->data = n;
        newNode->next = top;
        top = newNode;
        size++;        
    }

    
    void pop()
    {
        if (isEmpty())
        {
            return;
        }

        struct Node* temp = top;
        top = top->next;
        delete temp;
        size--;
    }

    void peek()
    {
        if(isEmpty())
        {
            return;
        }
        std::cout << "Top: "<< top->data << "\n";
    }

    void display()
    {
        struct Node* temp = top;
        std::cout<< "Stack elements:";
        while (temp!=nullptr)
        {
            std::cout << " " << temp->data;
            temp = temp->next;   
        }
        std::cout << '\n';
    }

    ~Stack()
    {
        struct Node* temp = top;
        while (top!=nullptr)
        {
            top = top->next;
            delete temp;
            temp = top;
        }
    }
};


