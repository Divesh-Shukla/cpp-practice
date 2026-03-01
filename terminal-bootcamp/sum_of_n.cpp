#include <iostream>
using namespace std;
int main(){
    int inp, n, sum=0;
    cout << "Enter the number of inputs: ";
    cin >> n;
    cout << "Enter n inputs: ";
    for(auto i = 0; i<n; i++){
	cin >> inp;
	sum +=inp;
    }

    cout << "The sum of n numers: " << sum << '.' << endl;
    return 0;
}
