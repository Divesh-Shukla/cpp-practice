#include <iostream>
#include <typeinfo>

int main() {
    // Implementation three
    /*
    Concepts used:-
    - The list based initialisation does not allowing narrowing conversions. Whenever a narrowing conversion takes place, the compiler throws an error!
    
    Error: narrowing coversion of '3.14' from 'double' to 'int'
    */
    int c{0};
    // int d{3.5}; // Commented out to allow compilation

    // Implementation four
    auto e = 5l;
    std::cout << "type of e: " << typeid(e).name() << std::endl;
    auto f = 3ull;
    std::cout << "type of f: " << typeid(f).name() << std::endl;
    auto g = 3.14f;
    std::cout << "type of g: " << typeid(g).name() << std::endl;
    auto h = 'a';
    std::cout << "type of h: " << typeid(h).name() << std::endl;

    return 0;
}