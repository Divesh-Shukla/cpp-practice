#include<iostream>

class Stack
{
private:
    struct Node
    {
        char data;
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
            return true;
        }
        return false;
    }

    void push(char n)
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

    char peek()
    {
        if(isEmpty())
        {
            return -1;
        }
        //std::cout << "Top: "<< top->data << "\n";
        return top->data;
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

bool isBalanced(std::string s)
{
    Stack s1;
    for (int i = 0; i < (int)s.size(); i++)
    {
        char ch = s[i];
        if(ch=='(' || ch == '{' || ch == '[')
        {
            s1.push(ch);
        }else if (ch == ')')
        {
            if (s1.peek() == '(')
            {
                s1.pop();
            }else
            {
                return false;
            }
        }else if (ch == '}')
        {
            if (s1.peek() == '{')
            {
                s1.pop();
            }else
            {
                return false;
            }
        }else if (ch == ']')
        {
            if (s1.peek() == '[')
            {
                s1.pop();
            }else
            {
                return false;
            }
        }
        
    }
    if(s1.isEmpty()) return true;
    
    
    return false;
}


int main()
{
    std::string s = "(My) name is [Divesh] {Shukla}.";
    std::string t = "[{(My) name is} Aditi.]";
    std::string u = "()[]{}";
    std::string v = "(}[)";
    std::string w = "((()";
    std::cout << "is Balnced: \n";
    std::cout << "s: "<< isBalanced(s)<<'\n';
    std::cout << "t: "<< isBalanced(t)<<'\n';
    std::cout << "u: "<< isBalanced(u)<<'\n';
    std::cout << "v: "<< isBalanced(v)<<'\n';
    std::cout << "w: "<< isBalanced(w)<<'\n';
    
    return 0;
}
    
