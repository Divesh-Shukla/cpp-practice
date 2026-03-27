#include<stdio.h>

int *find(int *arr, int size, int target)
{
    int *end = arr+size;
    while (arr<end)
    {
        if (*arr == target)
        {
            return arr;
        }
        arr++;
    }
    return NULL;
}

int main()
{
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int arr[size];

    printf("Enter your elements: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", arr+i);
    }

    int target;
    printf("Enter the element you are looking for: ");
    scanf("%d", &target);

    int *index = find(arr,size,target);
    if (index==NULL){
        printf("Element not found in the array!\n");}
    else{
        printf("Element found in the array!\n");
    }
    return 0;
    
    
}