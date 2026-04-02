#include<iostream>
#include<vector>

void display(const std::vector<int>& v)
{
    for(auto x:v)
    {
        std::cout << " "<< x;
    }
    std::cout << std::endl;
}

int query(const std::vector<int>& prefix, int L, int R)
{
    return prefix[R+1] - prefix[L];
}

int main()
{
    int size{};
    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    std::vector<int> array;
    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < size; i++)
    {
        int temp;
        std::cin>> temp;
        array.push_back(temp); 
    }
    std::cout << "Array:";
    display(array);

    std::vector<int> prefixArr{0};
    for(int i = 0; i < size; i++)
    {
        int temp = prefixArr[i] + array[i];
        prefixArr.push_back(temp);
    }
    std::cout << "Prefix Array:";
    display(prefixArr);

    int l,r;
    std:: cout << "Enter the left and right Index.\nResponse: ";
    std::cin >> l >> r;

    std::cout << "Query for range (" << l << "," << r << ") is: " << query(prefixArr, l, r)<< std::endl;

    return 0;
}