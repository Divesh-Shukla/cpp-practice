#include<iostream>

class point
{
private:
    int x, y;
public:
    point(int a = 0, int b = 0)
    {
        x = a;
        y = b;
    }

    void print()
    {
        std::cout << "x: " << x << ", y: " << y <<"\n";
    }

    ~point()
    {
        std::cout << "Destroying point at " << x << "," << y <<"\n" ;
    }
};

int main()
{
    point p;
    //std::cout << "Size of p: "<< sizeof(p)<< "\n";
    p.print();

    point p1(5);
    p1.print();


    return 0;
}