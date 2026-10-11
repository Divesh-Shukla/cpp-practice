#include<iostream>
#include<cmath>

class point
{
int x, y;

public:

    point(int x = 0, int y = 0)
    {
        if (x<0 || y<0)
        {
            this->x = 0;
            this->y = 0;
            std::cout << "Co-ordinates initialesed to 0!\nNegative values encountered!\n";
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
        this->x = x;
    }

    void sety(int y)
    {
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








/*
### TASK — Point Class

**TASK:** Build a `Point` class with proper encapsulation

**INPUT:**

* Two integers `x`, `y` (set via constructor or setter)

**OUTPUT:**

* Function `distance()` → returns distance from origin (√(x² + y²))

**CONSTRAINT:**

* `x`, `y` must be **private**
* Provide **getter(s)** (read-only access)
* `distance()` must be a **const member function**
* No direct access to `x`, `y` from `main`
* Compile with `-Wall -Wextra` → zero warnings

**VERIFY:**

* Create object → set values → print distance
* Try calling `distance()` on a `const Point` → must work

**EDGE CASE:**

* Negative values for `x`, `y`

---
*/