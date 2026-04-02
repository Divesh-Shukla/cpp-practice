#include<iostream>

class Queue
{
    struct Node
    {
        int data;
        Node* next;
    };

    Node* front;
    Node* rear;
    int size;

public:

    Queue()
    {
        front = nullptr;
        rear = nullptr;
        size = -1;
    }

    bool isEmpty()
    {
        if(front == nullptr) return true;
        return false;
    }

    void enqueue(int value)
    {
        Node* temp = new Node();
        temp->data = value;
        temp->next = nullptr;
        size++;
        if(front == nullptr)
        {
            front = temp;
            rear = temp;
            return;
        } 
        rear->next = temp;
        rear = temp;
    }

    void dequeue()
    {
        if(isEmpty()) return;
        Node* temp = front;
        size--;
        if(temp == rear) 
        {
            rear = nullptr;
            front = nullptr;
            delete temp;
            return;
        }
        front = front->next;
        delete temp;
    }

    void peek()
    {
        if(isEmpty()) return;
        std::cout << front->data << "is the front element of queue\n";
    }

    void display()
    {
        if(isEmpty()) return;
        Node* t = front;
        std::cout << "Stack:";;
        while(t)
        {
            std::cout << " "<<t->data;
            t = t->next;
        }
        std::cout << "\n";
    }

};

int main()
{
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.display();
    q.enqueue(5);
    q.enqueue(90);
    std::cout << "Before dequeue: \n";
    q.display();
    q.dequeue();
    std::cout << "After dequeue: \n";
    q.display();
    q.peek();
    q.dequeue();
    q.display();
    q.dequeue();
    q.display();
    q.dequeue();
    q.display();

    return 0;
}