#include<iostream>

class Queue
{
    int* arr;
    int size;
    int front;
    int rear;
    bool dynamic;
    void resize()
    {
        int newSize = 2 * size;
        int* temp = new int[newSize];
        for (int i = 0; i < rear; i++)
        {
            temp[i] = arr[i];
        }
        size = newSize;
        delete[] arr;
        arr = temp;
    }

public:


};