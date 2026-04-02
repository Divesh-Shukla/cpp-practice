#include <iostream>
#include <vector>

int main() {
    // Implementation six
    std::vector<int> v{1, 2, 3, 4, 5};

    std::cout << "Array:";
    for (const auto& x : v) {
        std::cout << " " << x;
    }
    std::cout << "\n";

    for (auto& x : v) {
        x = 0;
    }

    std::cout << "Array:";
    for (const auto& x : v) {
        std::cout << " " << x;
    }
    std::cout << std::endl;

    return 0;
}