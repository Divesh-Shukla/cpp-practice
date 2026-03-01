#include <iostream>
using namespace std;

int main() {
    int arr[5];
    arr[0] = 10;
    arr[1] = 20;
    
    // Typo
    cout << arr[0] << endl;  // 'ar' instead of 'arr'
    
    int result = arr[0] + arr[1];//declared later after seeing error
    // Undeclared variable
    cout << result << endl;
    
    // Type mismatch
    int x = arr[0];// replaces "hello" with arr[0]
    
    return 0;
}
