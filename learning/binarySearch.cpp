#include<iostream>
#include<vector>

int binaryS(std::vector<int>& v, int target)
{
    return binaryS(v,target, 0, v.size()-1);
}

int binaryS(std::vector<int>& v, int target, int l, int r)
{
    int mid;
    while(l<=r)
    {
        mid = l + (r-l)/2;
        if(v[mid]==target) return mid;
        else if(v[mid]> target) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}
