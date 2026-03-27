#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *p = malloc(sizeof(int));
    p = NULL;
    return 0;
}

//Implementation 1, Shows use after free

/*****************************************************************************************
* int *p = malloc(sizeof(int));
*   *p = 5;
*  printf("p: %p, *p before free: %d\n",p, *p);
*   free(p);
*   printf("p: %p, *p after free: %d\n",p, *p);
*    p = malloc(sizeof(int));
*    *p = 99;
*    printf("p: %p, *p after second allocation: %d\n",p, *p);
*    free(p);
*   printf("p: %p, *p after 2nd free: %d\n",p, *p);
***********************************************************************************************
*OUTPUT:
*p: 0x5bc6b987f2a0, *p before free: 5
*p: 0x5bc6b987f2a0, *p after free: -1133799297
*p: 0x5bc6b987f2a0, *p after second allocation: 99
*p: 0x5bc6b987f2a0, *p after 2nd free: -1133799297
****************************************************************************************************/


//Implementation 2, double free

/*******************************************************************************************
 *   int *p = malloc(sizeof(int));
 *   *p = 5;
 *   free(p);
 *   free(p);
 *   
 *  OUTPUT:
 * free(): double free detected in tcache 2
 *   Aborted (core dumped)
 * 
 ************************************************************************************************/


//Implementation 3, memory leak