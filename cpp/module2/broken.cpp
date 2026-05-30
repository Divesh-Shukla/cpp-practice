#include <iostream>

class brokenArray
{
    int *data;
    int size;

public:
    brokenArray(int n) : size(n), data(new int[n]) {}
    ~brokenArray() { delete[] data; }
};

int main()
{
    brokenArray a(5);
    brokenArray b = a;
    return 0;
}