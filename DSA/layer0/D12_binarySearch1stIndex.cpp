#include<iostream>
#include<vector>

int binarySearch(const std::vector<int>& v,int target)
{
    int size = v.size();
    if(size == 0) return -1;
    int r = size - 1;
    int l = 0;
    while (l<=r)
    {
        int mid = l + (r-l)/2;
        if (target == v[mid])
        {
            return mid;   
        }
        else if(target > v[mid]) l = mid +1;
        else r = mid -1;
        
    }
    return -1;
}

int first_occurrence(const std::vector<int>& v,int target)
{
    int size = v.size();
    if(size == 0) return -1;

    int l = 0, r = size;
    while(l<r)
    {
        int mid = l + (r-l)/2;
        if(v[mid] < target) l = mid + 1;
        else r = mid;
    }

    if(l < size && v[l] == target) return l;
    else return -1;
}

int last_occurrence(const std::vector<int>& v, int target)
{
    int size = v.size();
    if(size == 0) return -1;
    int r = size;
    int l = 0;
    while (l<r)
    {
        int mid = l + (r-l)/2;
        if(v[mid] <= target) l = mid + 1;
        else r = mid;
    }
    if(l > 0 && v[l-1] == target )  return l - 1;

    return -1;

}

int floor(const std::vector<int>& v, int target)
{
    int size = v.size();
    if(size == 0) return -1;

    int l = 0, r = size;
    while (l < r)
    {
        int mid = l + (r - l) / 2;
        if(v[mid] <= target) l = mid + 1;
        else r = mid;
    }

    if (l > 0) return l - 1;
    else return -1;
}

int ceil(const std::vector<int>& v, int target)
{
    int size = v.size();
    if(size == 0) return -1;

    int l = 0, r = size;
    while (l < r)
    {
        int mid = l + (r - l) / 2;
        if(v[mid] < target) l = mid + 1;
        else r = mid;
    }

    if (l < size) return l;
    else return -1;
}

int lower_bound(const std::vector<int>& v, int target)
{
    int size = v.size();
    if(size == 0) return 0;

    int l = 0, r = size;
    while (l<r)
    {
        int mid = l + (r-l)/2;
        if(v[mid] < target) l = mid + 1;
        else r = mid;
    }
    return l;
}

int upper_bound(const std::vector<int>& v, int target)
{
    int size = v.size();
    if(size == 0) return 0;

    int l = 0, r = size;
    while (l<r)
    {
        int mid = l + (r-l)/2;
        if(v[mid] <= target) l = mid + 1;
        else r = mid;
    }

    return l;
}

int bsRecursion(const std::vector<int>& v, int target, int l, int r)
{
    if(l>r) return -1;

    int mid = l + (r-l)/2;
    if (v[mid] == target) return mid;
    else if(v[mid] <  target) return bsRecursion(v, target, mid + 1, r);
    else return bsRecursion(v, target, l, mid -1);
}

int binarySearchRecursive(const std::vector<int>& v, int target)
{
    int l = 0, r = v.size()-1;
    return bsRecursion(v, target, l, r);
}

int main()
{

}