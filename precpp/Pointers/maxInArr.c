#include<stdio.h>

int *maxArr(int *a, int size)
{
    int *max = a;
    int *i;
    for (i = a; i < a+size; i++)
    {
        if (*max<(*i))
        {
            max = i;
        }
        
    }
    return max;
    
}

int main()
{
    printf("Enter the size of your array: ");
    int size;
    scanf("%d",&size);
    int arr[size];

    for (int *i = arr; i < arr+size; i++)
    {
        scanf("%d", i);
    }

    printf("Array:");
    for (int i = 0; i < size; i++)
    {
        printf(" %d", *(arr+i));
    }
    printf("\nLargest element of the array: %d\n", *maxArr(arr,size));
    return 0;
    
}