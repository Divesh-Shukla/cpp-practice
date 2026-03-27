#include<stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverseArray(int *a, int size)
{
    int *temp = a+size-1;
    while (a<temp)
    {
        swap(a++,temp--);
    }
    
    
}

int main()
{
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int arr[size];

    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", arr+i);
    }

    reverseArray(arr, size);

    printf("Reversed array:");
    for (int i = 0; i < size; i++)
    {
        printf(" %d", *(arr+i));  
    }
    printf("\n");

    return 0;
}