#include<iostream>

int lengthOfLongestSubstring(const std::string& s)
{
    int array[256] = {0};

    int k = 0, l = 0;
    for (int r = 0; r < s.size(); r++)
    {
        array[s[r]]++;

        while(array[s[r]]>1)
            array[s[l++]]--;
        
        k = std::max(k, r-l+1);        
    }

    return k;
    
}