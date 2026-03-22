#include<stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a,b;
    printf
    (
        "Enter two number: "
    );

    scanf
    (
        "%d %d"
        , &a,&b
    );

    printf("Before Swapping\na: %d, b: %d\n",a,b);
    swap(&a,&b);
    printf("After Swapping\na: %d, b: %d\n",a,b);
    return 0;
}