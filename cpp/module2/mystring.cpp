#include <iostream>
#include <cstring>
#include <cassert>

class myString
{
    char *data;
    size_t length;

public:
    myString(const char *str)
    {
        length = strlen(str);
        data = new char[this->length + 1];
        for (size_t i = 0; i <= length; i++)
        {
            *(data + i) = *(str + i);
        }
    }
    ~myString()
    {
        delete[] data;
    }

    myString(const myString &other)
    {
        this->length = other.length;
        data = new char[length + 1];
        for (size_t i = 0; i <= length; i++)
        {
            *(data + i) = *(other.data + i);
        }
    }

    myString &operator=(const myString &other)
    {
        if (this == &other)
            return *this;
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        for (size_t i = 0; i <= length; i++)
        {
            *(data + i) = *(other.data + i);
        }
        return *this;
    }

    myString operator+(const myString &other)
    {
        char str[length + other.length + 1];
        for (size_t i = 0; i < length + other.length + 1; i++)
        {
            if (i < length)
                str[i] = data[i];
            else if (i >= length && i < length + other.length)
                str[i] = other.data[i - length];
            else
                str[i] = '\0';
        }
        myString temp(str);
        temp.length = length + other.length;
        return temp; // On returning by value, the caller receives a copy before the function even returns. So the local temp gets destroyed when the
        // function exits, but the caller already has their copy!
    }

    size_t size() const
    {
        return length;
    }

    const char *c_str() const
    {
        return data;
    }
};

int main()
{
    myString s1("Divesh");
    myString s2(" Shukla");

    myString s3 = s1;
    s3 = "Copy assignment!";
    assert(s1.size() == 6);

    myString s4 = s1 + s2;
    assert(s4.size() == 13);

    s1 = s1;
    assert(s1.size() == 6);
}