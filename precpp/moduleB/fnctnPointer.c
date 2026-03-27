#include<stdio.h>
#include<stdlib.h>

struct Data
{
    int value;
    char character;
};


int* createInt()
{
    int* newint = (int*)malloc(sizeof(int));
    return newint;
}

int* createint(int n)
{
    int newint = n;
    return &newint;
}

int main()
{
    int *p = createInt();
    *p = 5;
    printf("p: %d\n", *p);
    free(p);

    // int *p = createint(5); // This will give a segmentation fault and core dumped message when run.
    // printf("%d\n", *p);

    struct Data d;
    d.value = 5;
    d.character = 'f';

    struct Data* e = (struct Data*)malloc(sizeof(struct Data)); 
    e->value = 6;
    (*e).character = 's';

    free(e);

    return 0;
}