#include <iostream>
#include <string>

int main() {
    // Implementation seven
    // int* ptr = nullptr;
    // int z = nullptr; // error: cannot convert 'nullptr_t' to 'int'

    // Implementation eight
    std::string s;
    s = "Harshit";
    std::cout << s << std::endl; // we can initialise string after declaration!
    std::cout << s.length() << std::endl;
    std::cout << s.size() << std::endl;
    
    s.pop_back();
    s.pop_back();
    std::cout << s << std::endl;
    std::cout << "size is reduced too!" << std::endl;
    
    std::cout << "s: " << s << std::endl;
    std::cout << "s[0]: " << s[0] << std::endl;
    std::cout << "s[n-1]: " << s[s.size() - 1] << std::endl;

    std::cout << "Reverse string: ";
    for (int i = s.size() - 1; i > -1; i--)
        std::cout << s.at(i);
    std::cout << std::endl;

    std::cout << "Enter a new sentence: ";
    std::getline(std::cin >> std::ws, s);
    if (!s.empty()) {
        std::cout << "Length of s: " << s.length() << std::endl;
        std::cout << "First char of s: " << s.front() << std::endl;
        std::cout << "Last character of s: " << s.back() << std::endl;
        std::cout << "Reveresed string s: ";
        for (int i = s.size() - 1; i >= 0; i--) {
            std::cout << s.at(i);
        }
        std::cout << std::endl;
    }

    return 0;
}