#include<iostream>
#include<cmath>

struct point
{
private:

    int x, y;

public:
    point(int x = 0, int y = 0)
    {
        if (x<0 || y<0)
        {
            this->x = 0;
            this->y = 0;
            std::cout << "Co-ordinates initialesed to 0!\nNegative values encountered!\nUse setter to initialise!\n";
            return;
        }
        
        this->x = x;
        this->y = y;
    }

    void getter() const
    {
        std::cout << "x: " << x << ", y: " << y << std::endl;
    }

    int getx() const
    {
        return x;
    }

    int gety() const
    {
        return y;
    }

    void setter(int x, int y)
    {
        if (x<0 || y<0)
        {
            std::cout << "Co-ordinates not chnaged!\nNegative values encountered!\n";
            return;
        }
        this->x = x;
        this->y = y;
    }

    void setx(int x)
    {
        if(x<0)
        {
            std::cout << "Co-ordinates not chnaged!\nNegative values encountered!\n";
            return;
        }
        this->x = x;
    }

    void sety(int y)
    {
        if(y<0)
        {
            std::cout << "Co-ordinates not chnaged!\nNegative values encountered!\n";
            return;
        }
        this->y = y;
    }
    
    double distance() const
    {
        int a = x*x;
        int b = y*y;
        return std::sqrt(a+b);
    }
};

int main()
{
    point p(3, 4);
    const point cp(1, 2);
    std::cout << "p-> ";
    p.getter();
    std::cout << "cp: ";
    cp.getter();

    p.setx(10);          // should work
    p.getter();
    cp.distance();       // should work
              // ❌ should fail at compile
    



    return 0;
}

