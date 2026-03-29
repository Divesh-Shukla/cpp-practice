#include<iostream>
#include<vector>

int binarySearch(std::vector<int>& v, int l, int r, int target)
{
    int mid;
    while (l<=r)
    {
        mid = l + (r-l)/2;
        if (target == v[mid]) return mid;
        else if(target > v[mid]) l = mid+1;
        else r = mid -1;
    }
    return -1;
}

int binarySearch2(std::vector<int>& v, int target)
{
    int mid;
    int l = 0;
    int r = v.size();
    while(l<r)
    {
        mid = l + (r-l)/2;
        if(v[mid] < target) l = mid+1;
        else r = mid ;
    }
    if(v[l] == target) return l;
    return -1;
}

int binarySearch3(std::vector<int>& v, int target)
{
    int mid;
    int l = 0;
    int r = v.size();
    while (l<r)
    {
        mid = l + (r-l)/2;
        if(v[mid] <= target) l = mid + 1;
        else r = mid;
    }
    if(v[l-1] == target ) return l-1;
    return -1;
}

int main()
{
    int size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    std::vector<int> v(size);
    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < size; i++)
    {
        std::cin >> v[i];
    }
    int search;
    std::cout << "Enter 1 if you wanna search else -1: ";
    std::cin >> search;
    while (search == 1)
    {
    
        int target;
        std::cout << "Enter the element you are looking for: ";
        std::cin >> target;

        int targetIndex = binarySearch2(v, target);
        if(targetIndex == -1) std::cout << "Target not found!\n";
        else std::cout<< "Target found at index: "<< targetIndex <<"!\n";

        std::cout << "Answer to continue searching other element else -1: ";
        std::cin >> search;
    }
    return 0;
}