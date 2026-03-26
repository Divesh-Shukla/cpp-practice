#include<stdio.h>
#include<stdlib.h>

int my_strlen(char* s)
{
    int counter = 0;
    while (*s!='\0')
    {
        s++;
        counter++;
    }
    return counter;
}

size_t my_strlen2(char* s)
{
    char* c = s;
    while (*s!='\0')
    {
        s++;
    }
    return s-c;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int* arr, int size)
{
    printf("Array:");
    int* temp = arr;
    while(temp < arr+size)
    {
        printf(" %d", *temp++);
    }
    printf("\n");
}

int main(){
    int a = 5, b = 6;
    printf("Pre swap: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("Post swap: a = %d, b = %d\n", a, b);
    
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int arr[size];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", arr+i);
    }

    printArray(arr,size);

    char name[] = "Divesh";
    printf("Length of name string: %d\n", my_strlen2(name));
    
    printf("Length of name string: %d\n", my_strlen(name));
    
    return 0;
}