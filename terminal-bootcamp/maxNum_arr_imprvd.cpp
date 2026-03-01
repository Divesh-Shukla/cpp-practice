#include<iostream>
#include<vector>
#include<climits>

int main(){
    int v_size;
    std::cout << "Enter the size of the array: " ;
    if(!(std::cin >> v_size)||v_size<=0){
        std::cerr << "Invalid size input!\n";
        return 1;
    }

    std::vector<int> v;

    try{
	v.resize(v_size);
    } catch(const std::bad_alloc&){
        std::cerr << "Memory allocation failed!\n";
        return 1;
    }

    std::cout << "Enter the elements of the array: ";
    for(int i = 0; i < v_size; i++){
        if(!(std::cin >> v[i])){
	    std::cerr << "Invalid element input!";
	    return 1;
        }
    }
    int max_val = v[0];
    for(int i = 1; i < v_size; i++){
	if(v[i]>max_val){
	    max_val = v[i];
	}
    }
    std::cout << "The largest element of the array is: " << max_val <<std::endl;
    return 0;
}
