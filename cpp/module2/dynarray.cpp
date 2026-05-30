#include <iostream>

class dynarray
{
    int *n;
    size_t size;
    size_t capacity;

public:
    dynarray(int n = 1) : size(0), capacity(n), n(new int[n]) {}
    ~dynarray() { delete[] n; }
    dynarray(const dynarray &other)
    {
        n = new int[other.capacity];
        int *temp = other.n;
        for (size_t i = 0; i < other.size; i++)
        {
            *(n + i) = *(temp + i);
        }
        this->size = other.size;
        this->capacity = other.capacity;
    }
    dynarray &operator=(const dynarray &other)
    {
        if (this == &other)
            return *this;
        delete[] n;
        this->size = other.size;
        this->capacity = other.capacity;
        this->n = new int[capacity];
        for (size_t i = 0; i < size; i++)
        {
            *(this->n + i) = *(other.n + i);
        }
        return *this;
    }
};

int main()
{
    dynarray a(5);
    dynarray b(3);
    b = a;
    b = b; // self-assignment test
}