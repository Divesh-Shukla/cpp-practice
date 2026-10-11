#include <iostream>
#include <vector>


int main()
{
    int n;
    std::cout << "Enter the size of your array: ";
    std::cin >> n;

    std::vector<int> v(n);
    std::cout << "Enter the elements of the array: ";
    for(auto& x: v)
        std::cin >> x;
        
    //Finding the largest window with sum less than k
    int k;
    std::cin >> k;

    int windowSize = 0;
    bool found = false;
    int bestL = 0, bestR = -1;
    int sum = 0;
    int l = 0;
    for(int r = 0; r < n; r++)
    {
        sum += v[r];
        while (sum > k)
            sum -= v[l++];
        
        int temp = r-l+1;
        if(temp > windowSize)
        {
            found = true;
            windowSize = temp;
            bestL = l;
            bestR = r;
        }
    }

    //Printing the largest subarray whose sum is less than or equal to k
    if(found)
    {
        std::cout << "Largest subarray: [";
        for(int i = bestL; i <= bestR; i++)
            std::cout << v[i]<< ", ";
        std::cout << "]\n";
    }else
        std::cout << "No subarray found!";
    
    return 0;
}