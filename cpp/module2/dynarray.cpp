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

    dynarray(const dynarray &copy)
    {
        std::cout << "COPY CONSTRUCTOR called\n";
        n = new int[copy.capacity];
        int *temp = copy.n;
        for (size_t i = 0; i < copy.size; i++)
        {
            *(n + i) = *(temp + i);
        }
        this->size = copy.size;
        this->capacity = copy.capacity;
    }

    dynarray(dynarray &&other) noexcept
    {
        std::cout << "MOVE CONSTRUCTOR called!\n";
        this->size = other.size;
        this->capacity = other.capacity;
        this->n = other.n;
        other.n = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    dynarray &operator=(dynarray &&other) noexcept
    {
        std::cout << "MOVE ASSIGNMENT called!\n";
        if (this == &other)
            return *this;
        delete[] n;
        this->capacity = other.capacity;
        this->size = other.size;
        this->n = other.n;
        other.n = nullptr;
        other.size = 0;
        other.capacity = 0;
        return *this;
    }

    dynarray &operator=(const dynarray &copy)
    {
        std::cout << "COPY ASSIGNMENT called!\n";
        if (this == &copy)
            return *this;
        delete[] n;
        this->size = copy.size;
        this->capacity = copy.capacity;
        this->n = new int[capacity];
        for (size_t i = 0; i < size; i++)
        {
            *(this->n + i) = *(copy.n + i);
        }
        return *this;
    }

    static dynarray make_array(size_t n)
    {
        dynarray temp(100);
        return temp;
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
    // dynarray a(10);
    // a.push_back(42);
    // dynarray b = a; // copy constructor
    // b[0] = 99;
    // assert(a[0] == 42); // a must not be affected — if this fails, copy is shallow

    // // Test 2: self-assignment
    // a = a; // must not crash, must not corrupt
    // assert(a[0] == 42);

    // // Test 3: assignment
    // dynarray c(5);
    // c = a; // copy assignment
    // c[0] = 77;
    // assert(a[0] == 42);

    // Test 4: move semanticsstd::cout << "--- make_array ---\n";
    dynarray a = dynarray::make_array(100);
    std::cout << "--- dynarray b = a ---\n";
    dynarray b = a;
    std::cout << "--- std::move(a) ---\n";
    dynarray c = std::move(a);
}