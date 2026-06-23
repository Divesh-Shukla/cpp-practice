#include <iostream>
#include <cassert>

template <typename T>
class dynarray
{
    T *n;
    size_t size;
    size_t capacity;
    void resize()
    {
        T *temp = n;
        size_t new_capacity = 2 * capacity;
        n = new T[new_capacity];
        for (size_t i = 0; i < size; i++)
        {
            n[i] = temp[i];
        }
        delete[] temp;
        this->capacity = new_capacity;
    }

public:
    dynarray(size_t elements = 1) : n(new T[elements]), size(0), capacity(elements) {}

    ~dynarray() { delete[] n; }

    dynarray(const dynarray &copy)
    {
        std::cout << "COPY CONSTRUCTOR called\n";
        n = new T[copy.capacity];
        T *temp = copy.n;
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
        this->n = new T[capacity];
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

    void push_back(T value)
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

    T &operator[](size_t i)
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
    dynarray<int> a(10);
    a.push_back(42);
    dynarray<int> b = a; // copy constructor
    b[0] = 99;
    assert(a[0] == 42); // a must not be affected — if this fails, copy is shallow
    std::cout << "Test 1 passed!\n";

    // Test 2: self-assignment
    a = a; // must not crash, must not corrupt
    assert(a[0] == 42);
    std::cout << "Test 2 passed!\n";

    // Test 3: assignment
    dynarray<int> c(5);
    c = a; // copy assignment
    c[0] = 77;
    assert(a[0] == 42);
    std::cout << "Test 3 passed!\n";

    // Test 4: move semanticsstd::cout << "--- make_array ---\n";
    dynarray<int> d = dynarray<int>::make_array(100);
    std::cout << "--- dynarray b = a ---\n";
    dynarray<int> e = d;
    std::cout << "--- std::move(a) ---\n";
    dynarray<int> f = std::move(d);
}