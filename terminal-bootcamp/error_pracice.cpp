#include <iostream>
using namespace std;

int main() {
    int arr[5];
    arr[0] = 10;
    arr[1] = 20;
    
    // Typo
    cout << ar[0] << endl;  // 'ar' instead of 'arr'
    
    // Undeclared variable
    cout << result << endl;
    
    // Type mismatch
    int x = "hello";
    
    return 0;
}
