#include<iostream>
#include<vector>
#include<climits>


int minSubArrayLen(int target, std::vector<int>& nums) 
{
    int size = nums.size();
    int sum = 0;

    int k = INT_MAX;
    int l = 0;
    for(int r = 0; r < size; r++)
    {
        sum += nums[r];

        while(sum >= target)
        {
            k = std::min(k, r- l + 1);
            sum -= nums[l++];
        }

    }
        
    return (k==INT_MAX) ? 0 : k;
}

int main()
{
    int n;
    std::cout<< "Enter the length of your test case array: ";
    std::cin>>n;

    std::vector<int> v(n);

    std::cout << "Enter all the elements of the array: ";
    for(auto& x: v)
        std::cin>>x;

    int target;
    std::cout << "Enter the target value: ";
    std::cin>>target;

    int k = minSubArrayLen(target, v);

    std::cout << "k: " << k << std::endl;

    return 0;
}

/* ATTEMPT 1
int minSubArrayLen(int target, std::vector<int>& nums) 
{
    int size = nums.size();
    int sum = 0;
    bool found = false;

    int k = size;
    int r = 0;
    for(int l = 0; l < size; l++)
    {

        while(sum < target && r<size)
            sum += nums[r++];


        int temp = r-l;

        if(sum>=target && temp<k)
        {
            k = temp;
            found = true;
        }

        sum-=nums[l];
    }
        
    if(found) return k;

    return 0;
}
*/