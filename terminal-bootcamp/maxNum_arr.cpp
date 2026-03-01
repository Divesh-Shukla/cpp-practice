#include<iostream>
#include<vector>
#include<climits>

int main(){
    int v_size;
    std::cout << "Enter the size of the array: " ;
    std::cin >> v_size;
    if(v_size<=0){            
        return 1; 
    }

    std::vector<int> v(v_size);

    std::cout << "Enter the elements of the array: ";
    for(int i = 0; i < v_size; i++){
        std::cin >> v[i];
    }
    int max = INT_MIN;
    for(int i = 0; i < v_size; i++){
        if(v[i]>max){
            max = v[i];
        }
    }
    std::cout << "The largest element of the array is: " << max <<std::endl;
    return 0;
}

