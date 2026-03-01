#include <iostream>
#include <vector>

int main(){
    int v_size;
    std::cout << "Enter the size of the array: ";
    if(!(std::cin >>v_size) || v_size <= 0){
	std::cerr << "Invalid size input!";
	return 1;
    }

    std::vector <int> v(v_size);

    std::cout << "Enter the elements of the array: ";
    for(int i = 0; i < v_size; i++){
        if(!(std::cin >> v[i])){
            std::cerr << "Invalid element input!";
            return 1;
        }
    }

    //Reversing the array
    int n = v_size;
    
    for(int i = 0; i < n/2; i++){
        int temp = v[i];
        v[i] = v[n-1-i];
        v[n-1-i] = temp;
    }

    std::cout << "The reversed array is: ";
    for(int i = 0; i < n; i++){
	if(i<n-1){
            std::cout << v[i] << " ";
	}else{
	    std::cout << v[i];
	}
    }
    return 0;
}
