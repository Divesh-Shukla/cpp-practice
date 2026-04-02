#include<iostream>

class Queue
{
    int* arr;
    int front;
    int rear;
    int size;
    bool dynamic;
    void resize()
    {
        int newSize = size*2;
        int* temp = new int[newSize];
        for (int i = 0; i <= rear; i++)
        {
            temp[i] = arr[i];
        }
        size = newSize;
        delete[] arr;
        arr = temp;
    }
public:

    Queue()
    {
        arr = new int[1];
        size = 1;
        front = rear = -1;
        dynamic = true;
    }

    Queue(int s, bool dynamic = true)    
    {
        arr = new int[s];
        size = s;
        front = rear = -1;
        this->dynamic = dynamic;
    }

    bool isEmpty()
    {
        if (front == -1 || front > rear)
        {
            std::cout << "Queue is empty\n";
            return true;
        }
        return false;
    }

    bool isFull()
    {
        if(rear == size-1)
        {
            std::cout << "Queue is full\n";
            return true;
        }
        return false;
    }

    void enqueue(int data)
    {
        if (isFull())
        {
            if(dynamic) resize();
            else return;
        }
        rear++;
        arr[rear] = data;
        if (front == -1) front = 0;
    }

    void dequeue()
    {
        if (isEmpty()) return;
        front++;
        if (front == rear)
        {
            front = rear = -1;
        }
        
    }

    void peek()
    {
        if (isEmpty()) return;
        std::cout << arr[front] << "\n";
    }

    void display()
    {
        if (isEmpty()) return;
        for (int i = front; i <= rear; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    }


};

int main()
{
    Queue q(5, false);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    q.display();
    q.dequeue();
    q.dequeue();
    q.display();
    q.peek();
    return 0;
}