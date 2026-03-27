#include<iostream>

class my_vector
{
private:
    int *data;
    int size;
    int capacity;
    void resize()
    {
        size_t newCapacity = (capacity == 0) ? 1 : 2*capacity;
        int *temp = new int[newCapacity];
        for (int i = 0; i < size; i++)
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        capacity = newCapacity;
    }
public:
    my_vector()
    {
        size = 0;
        capacity= 1;
        data = new int[1];
    }

    my_vector(size_t n)
    {
        if(n==0){
            size = 0;
            capacity = 1;
            data = new int[1];
            return;
        }
        data = new int[n];
        capacity = n;
        size = 0;
    }

    my_vector(const my_vector& other)
    {
        data = new int[other.capacity];
        for (int i = 0; i < other.size; i++)
        {
            this->data[i] = other.data[i];
        }
        
        this->capacity = other.capacity;
        this->size = other.size;
    }

    my_vector& operator=(const my_vector& other)
    {
        if(this == &other)
        {
            return *this;
        }
        delete[] data;
        data = new int[other.capacity];
        for (int i = 0; i < other.size; i++)
        {
            this->data[i] = other.data[i];
        }
        
        this->capacity = other.capacity;
        this->size= other.size;

        return *this;
    }

    void push(int value)
    {
        if (capacity == 0 || capacity == size)
        {
            resize();
        }
        data[size] = value;
        size++;
    }

    void display()
    {
        if (size>0)
        {
            std::cout << "Array:";
            for (int i = 0; i < size; i++)
            {
                std::cout << " " << data[i];
            }
            std::cout << "\n";
        }
        
    }

    void get(int index)
    {
        if(index < 0 || index>= size)
        {
            std::cout << "Index out of bound!\n";
            return;
        }
        std::cout << data[index] << "\n";
    }

    ~my_vector()
    {
        delete[] data;
    }
};


int main()
{
    my_vector v;
    v.push(5);
    v.push(8);
    v.push(45);
    v.display();
    v.push(9);
    v.push(55);
    v.get(2);
    v.display();

    return 0;

}