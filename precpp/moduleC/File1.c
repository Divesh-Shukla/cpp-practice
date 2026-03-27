#include<stdio.h>
#include<stdlib.h>

struct dynArray
{
    int *data;
    int size;
    int capacity;
};


struct dynArray *create(int capacity)
{
    struct dynArray *d = malloc(sizeof(struct dynArray));
    d->data = malloc(capacity * sizeof(int));
    if (d == NULL || d->data == NULL)
    {
        free(d);
        free(d->data);
        return NULL;
    }
    
    d->capacity = capacity;
    d->size = 0;
    return d;

}

void display(struct dynArray *d)
{
    if(d->size == 0)
    {
        printf("Empty array!");
        return;
    }
    printf("Array:");
    for (int i = 0; i < d->size; i++)
    {
        printf(" %d", d->data[i]);
    }
    printf("\n");
}


void push(struct dynArray *d, int value)
{
    if(d->size == d->capacity)
    {
        int newCapacity = (d->capacity == 0) ? 1 : 2 * d->capacity;
        int *temp = realloc(d->data, newCapacity*sizeof(int));
        if(temp == NULL){
            printf("Realloc failed!\n");
            exit(1);
        }
        d->data = temp;
        d->capacity = newCapacity;
    }
    d->data[d->size] = value;
    d->size++;
}

int getIndex(struct dynArray *d, int i)
{
    if(i<0 || i>=d->size)
    {
        printf("Index out of bound!\n");
        return -1;
    }
    return (d->data)[i];
}

int getNumIndx(struct dynArray *d, int num)
{
    for (int i = 0; i < d->size; i++)
    {
        if ((d->data)[i] == num)
        {
            return i;
        }
        
    }
    return -1;
}

void pop(struct dynArray *d)
{
    if(d->size == 0){
        return;
    }
    d->size--;
}

void destroy(struct dynArray *d)
{
    if(d == NULL) return;
    free(d->data);
    free(d);
}

int main()
{
    //Implementation 1.
    int *p1 = malloc(sizeof(int));
    *p1 = 82;
    free(p1);

    //Implementation 2 and 3
    size_t size1 = 10;
    p1 = malloc(size1 * sizeof(int));
    printf("Malloc array:");
    for (size_t i = 0; i < size1; i++)
    {
        printf(" %d", *(p1+i));
    }
    
    free(p1);

    p1 = calloc(size1,sizeof(int));
    printf("\nCalloc array:");
    for (size_t i = 0; i < 10; i++)
    {
        printf(" %d", *(p1+i));
    }
    printf("\n");

    //Implementation 4
    p1 = realloc(p1, 2*size1*sizeof(int));
    free(p1);

    //Implementation 5
    printf("\nAddress of p1 after free: %p\n", p1);

    //Implementation 6, intentional double free.
    //free(p1);

    //Implementation 7, 8 and 9
    int **arr = (int **)malloc(size1 *sizeof(int*));
    for (size_t i = 0; i < size1; i++)
    {
        *(arr+i) = malloc(size1*sizeof(int));
    }

    for (size_t i = 0; i < size1; i++)
    {
        for (size_t j = 0; j < size1; j++)
        {
            *(*(arr+i)+j) = 0;
        }
        
    }

    for (size_t i = 0; i < size1; i++)
    {
        free(*(arr+i));
    }

    free(arr);

    //Implementation 10
    struct dynArray *d;
    int size2;
    printf("Enter the size of the dynamic array: ");
    scanf("%d", &size2);
    d = create(size2);
    if (d==NULL)
    {
        printf("Allocation failed!\n");
        return 1;
    }
    
    printf("Enter the elements of the array: ");
    for (size_t i = 0; i < size2; i++)
    {
        scanf("%d", &d->data[i]);
        d->size++;
    }

    push(d, 23);
    display(d);
    push(d,99);
    display(d);
    pop(d);
    pop(d);
    display(d);
    destroy(d);

    return 0;
}