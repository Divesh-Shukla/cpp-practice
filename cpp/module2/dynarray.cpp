#include <iostream>
#include <cassert>

class dynarray
{
    int *n;
    size_t size;
    size_t capacity;
    void resize()
    {
        int *temp = n;
        size_t new_capacity = 2 * capacity;
        n = new int[new_capacity];
        for (size_t i = 0; i < size; i++)
        {
            n[i] = temp[i];
        }
        delete[] temp;
        this->capacity = new_capacity;
    }

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

    void push_back(int value)
    {
        if (size < capacity)
        {
            *(n + size) = value;
            size++;
        }
        else
        {
            resize();
            *(n + size) = value;
            size++;
        }
    }

    int &operator[](int i)
    {
        return *(n + i);
    }

    size_t getsize()
    {
        return size;
    }
};

int main()
{
    dynarray a(10);
    a.push_back(42);
    dynarray b = a; // copy constructor
    b[0] = 99;
    assert(a[0] == 42); // a must not be affected — if this fails, copy is shallow

    // Test 2: self-assignment
    a = a; // must not crash, must not corrupt
    assert(a[0] == 42);

    // Test 3: assignment
    dynarray c(5);
    c = a; // copy assignment
    c[0] = 77;
    assert(a[0] == 42);
}