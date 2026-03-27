#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int size;
    int capacity;
    int data[];
} dynArray;

dynArray* create(int capacity)
{
    dynArray *d = malloc(sizeof(dynArray) + capacity*sizeof(int));
    if (d==NULL)
    {
        printf("Array allocation failed!\n");
        return NULL;
    }
    
    d->size = 0;
    d->capacity = capacity;
    return d;
}

void push(dynArray **d, int value)
{
    dynArray *array = *d;
    if (array->size==array->capacity)
    {
        int newCapacity = (array->capacity==0)? 1 : 2*array->capacity;
        dynArray *temp = realloc(array, sizeof(dynArray) + newCapacity*sizeof(int));
        if(temp == NULL) 
        {
            printf("Reallocation failed!\n");
            return;
        }
        temp->capacity = newCapacity;
        *d = temp;
        array = temp;
    }
    array->data[array->size] = value;  
    array->size++; 
}

int get(dynArray *d, int index)
{
    if(index<0 || index>=d->size)
    {
        printf("Index out of bound\n");
        return -1;
    }
    return d->data[index];
}

void destroy(dynArray *d)
{
    free(d);
}

void display(dynArray *d)
{
    if (d->size == 0)
    {
        printf("Empty Array!\n");
        return;
    }
    printf("Current Size: %d, Current Capacity: %d\n", d->size, d->capacity);
    printf("Array:");
    for (int i = 0; i < d->size; i++)
    {
        printf(" %d", d->data[i]);   
    }
    printf("\n");
}

int main()
{
    dynArray *array;
    int size;
    printf("Enter the number elements of the array: ");
    scanf("%d", &size);


    array = create(1);
    if(array == NULL) return 1;
    display(array);

    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++)
    {
        int entry;
        scanf("%d", &entry);
        push(&array, entry);
        display(array);
    }

    destroy(array);

    return 0;
    
}
