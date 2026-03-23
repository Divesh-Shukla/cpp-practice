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
    printf("Elements printed using pointer arithmetic: ");
    while (p<arr+size)
    {
        printf(" %d", *p);
        p++;
    }
    p = arr;
    printf("\n");
    printf("Elements printed using subscript:");
    for (int i = 0; i < size; i++)
    {
        printf(" %d", arr[i]);
    }
    printf("\n"); 

    int *p1 = &arr[size-2];
    printf("pointer difference: %p\n", p1-p);

    return 0;
}
