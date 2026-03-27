#include<stdio.h>
#include<stdlib.h>

int* copyArray(int* arr, int size)
{
    if(size <= 0) return NULL;
    int *new = malloc(size * sizeof(int));
    if(new == NULL) return NULL;
    for (size_t i = 0; i < size; i++)
    {
        *(new+i) = *(arr+i);
    }
    return new;
}

int main()
{
    int arr[] = {1,2,3,4,5};
    int *arr2 = copyArray(arr, 5);
    for (int i = 0; i < 5; i++)
    {
        printf(" %d", *(arr2+i));
    }
    printf("\n");
    free(arr2);
    return 0;
}