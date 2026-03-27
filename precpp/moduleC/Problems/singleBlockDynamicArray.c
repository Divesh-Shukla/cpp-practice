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
}

void push(dynArray* d, int value)
{
    if (d->size==d->capacity)
    {
        int newCapacity = (d->capacity==0)? 1 : 2*d->capacity;
        dynArray *temp = realloc(d, sizeof(dynArray) + newCapacity*sizeof(int));
        if(temp == NULL) 
        {
            printf("Reallocation failed!\n");
            return;
        }
        /*temp->size = d->size;
        temp->capacity = newCapacity;// Realloc copies the content, so this is unnecessary!
        free(d);*/ //Not needed because the realloc free the old pointer if moves
        // and if it didn't we freed the wrong thing
        
        d = temp;
    }
    d->data[d->size] = value;  
    d->size++; 
}

int get(dynArray *d, int index)
{
    if(index<0 || index>d->capacity)
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
    display(array);

    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++)
    {
        int entry;
        scanf("%d", &entry);
        push(array, entry);
        display(array);
    }

    destroy(array);

    return 0;
    
}
/*
edistob@Edis:~/dev/semester-2/cpp/cpp-practice/precpp/DMA/Problems$ ./sBDA
Enter the number elements of the array: 5
Empty Array!
Enter the elements of the array: 19 
Current Size: 1, Current Capacity: 1
Array: 19
93
Current Size: 2, Current Capacity: 1
Array: 19 93
293
Current Size: 3, Current Capacity: 1
Array: 19 93 293
5587]
Current Size: 4, Current Capacity: 1
Array: 19 93 293 5587
Current Size: 5, Current Capacity: 1
Array: 19 93 293 5587 5587

*/