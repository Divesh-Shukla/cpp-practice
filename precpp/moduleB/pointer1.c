#include<stdio.h>

int main()
{
    int x = 5, *p = &x;// declaration and assignment of a pointer   
    printf("x: %d\n", x);
    printf("*p: %d\n", *p);//Dereferncing pointer

    (*p)++;// modifying original
    printf("x: %d, *p: %d\n", x, *p);

    //Printing p and *p
    printf("p: %p, *p: %d\n", p, *p);

    //Showing that &x and p are one and same
    printf("&x: %p, p: %p\n", &x, p);

    //Declaring and assigning double pointer
    int **p1 = &p;
    int y = 8;
    printf("p before using double refernence to change the value of p\nx: %d, &x: %p\n*p: %d, p: %p\ny: %d, &y: %p\n",x, &x, *p, p, y, &y);
    *p1 = &y;
    printf("p after using double refernence to change the value of p\nx: %d, &x: %p\n*p: %d, p: %p\ny: %d, &y: %p\n",x, &x, *p, p, y, &y);
    **p1 = 9;
    printf("p after using double refernence to change the value of y\nx: %d, &x: %p\n*p: %d, p: %p\ny: %d, &y: %p\n",x, &x, *p, p, y, &y);
    
    printf("Size of pointer p: %zu, Size of object p is pointing to: %zu\n", sizeof(p), sizeof(*p));

    int *p2 = &x;

    printf("Check 1: ");
    p==p2 ? printf("p and p2 points to the same obect!\n") : printf("p and p2 points to different object!\n");

    p2 = p;

    printf("Check 2: ");
    p==p2 ? printf("p and p2 points to the same obect!\n") : printf("p and p2 points to different object!\n");

    int* p3 = NULL;
    int z = 69;
    if(p3) *p3 = 96;
    printf("p3: %p\n", p3);
    printf("\nWhen p3 points to NULL\n");
    p3 == NULL ? printf("p3 points to NULL!\n") : printf("*p3: %d\n", *p3);

    p3 = &z;
    printf("\nWhen p3 points to z\n");
    p3 == NULL ? printf("p3 points to NULL!\n") : printf("*p3: %d\n", *p3);

    //using array name as a pointer!
    int arr[5];
    printf("Enter the elements of array: ");
    for (int i = 0; i < (int)(sizeof(arr)/sizeof(*arr)); i++)
    {
        scanf("%d", arr+i);
    }
    


    return 0;
}