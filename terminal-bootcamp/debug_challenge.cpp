#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;
    
    int arr[n];
    
    cout << "Enter " << n << " numbers: ";
    for(int i = 0; i < n; i++) {  // BUG: should be i < n
        cin >> arr[i];
    }
    
    cout << "Your numbers: ";
    for(int i = 0; i < n; i++) {  // SAME BUG
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
