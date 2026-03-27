#include<stdio.h>

int main()
{
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int arr[size];

    int *p = arr;
    printf("Enter the elements of the array: ");
    while (p<arr+size)
    {
        scanf("%d", p);
        p++;
    }
    p = arr;
    printf("Elements: ");
    while (p<arr+size)
    {
        printf(" %d", *p);
        p++;
    }
    printf("\n");
    
     
    return 0;
}
