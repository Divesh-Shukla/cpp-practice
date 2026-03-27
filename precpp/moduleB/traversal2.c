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
    printf("pointer difference: %ld\n", p1-p);

    int brr[size];
    for (int i = 0; i < size; i++)
    {
        *(brr+i) = *(arr+i);
    }
    //Printing brr
    int* temp = brr;
    printf("Elements of brr:");
    while (temp<brr+size)
    {
        printf(" %d", *(temp++));
    }
    printf("\n");


    int arr1[5][5];
    printf("Printing the address of each row in 2D array:");
    for (int i = 0; i < 5; i++)
    {
        printf("%p\n", &arr1[i]);
    }


    printf("\np:   %p\n", p);
    printf("p+1: %p\n", p+1);
    printf("difference in bytes: %ld\n", (char*)(p+1) - (char*)p);
    printf("sizeof(int): %zu\n", sizeof(int));
    

    return 0;
}
