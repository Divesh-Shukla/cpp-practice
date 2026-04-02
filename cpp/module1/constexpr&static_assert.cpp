#include <iostream>

constexpr int square(int n) {
    return n * n;
}

int main() {
    // Implementation five
    /*
    Concept of constexpr functions:
    - The constexpr function has dual nature:
    1. Compile-time path:- when we pass a constant to this function and assign the result to constexpr variable,
                             the function gets evaluated during compilation
    2. Run-time path:- When the function receives a constant or an obect whose value is run-time dependent and the returned value is not assigned to 
                        a constexpr variale then it is evaluated during run-time.
    */

    /*
    Test 01:
    int n;
    std::cout << "Enter the size of the array: ";
    std::cin >> n;
    const int size = n;
    static_assert(size>0, "Error!"); // throws error: non-constant condition for static assert
    int arr[size];
    */

    const int n = 6;
    constexpr int m = square(n);
    static_assert(square(n) == 36, "Error!");
    std::cout << m << std::endl;

    /*
    int x;
    std::cout << "Enter a number: ";
    std::cin >> x;
    // constexpr int o = x; // This would fail as x is runtime-dependent
    */

    return 0;
}