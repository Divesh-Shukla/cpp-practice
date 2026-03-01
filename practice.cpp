#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter " << n << " integers:\n";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int sum = 0;
    int maximum = arr[0];

    for(int i = 0; i < n; i++) {
        sum += arr[i];
        if(arr[i] > maximum) {
            maximum = arr[i];
        }
    }

    cout << "\nReversed array: ";
    for(int i = n - 1; i >= 0; i--) {
        cout << arr[i] << " ";
    }

    cout << "\nSum: " << sum;
    cout << "\nMaximum: " << maximum << endl;

    return 0;
}