#include<stdio.h>

int main()
{
    int x = 1, y = 2, z = 3;

    const int *p = &x;
    int* const q = &y;
    const int* const r = &z;
    //testing the const int:
    
    //testing the int* const

    // testing the const int* const
    printf("%d\n", *r);
    
    
    return 0;
}

/*   Test 01:

Testing the const int
    p = &y;
    *p = 0;
    p = &z;
    *p = 9;
    p = &x;
    *p = 12;

constPointer.c: In function ‘main’:
constPointer.c:10:8: error: assignment of read-only location ‘*p’
   10 |     *p = 0;
      |        ^
constPointer.c:12:8: error: assignment of read-only location ‘*p’
   12 |     *p = 9;
      |        ^
constPointer.c:14:8: error: assignment of read-only location ‘*p’
   14 |     *p = 12;
      |        ^

    
      Test 02: 
      p = q;
    printf("p:%p\n", p);  
    p=r;
    printf("p:%p\n", p);
    p=&x;
    printf("p:%p\n", p);

    Passed, pointer assignmnet works but not object assignment to which the pointer points to.
*/ 


/* Test case 01:
testing the int* const
    q = &y;
    q = p;
    q = r;
    x = 5;

Compilation Error:

constPointer.c: In function ‘main’:
constPointer.c:13:7: error: assignment of read-only variable ‘q’
   13 |     q = &y;
      |       ^
constPointer.c:14:7: error: assignment of read-only variable ‘q’
   14 |     q = p;
      |       ^
constPointer.c:15:7: error: assignment of read-only variable ‘q’
   15 |     q = r;
      |       ^

          printf("y: %d\n", *q);

    *q = x;
    printf("y: %d\n", *q);


    *q = *r;
    printf("y: %d\n", *q);

assignment to memory location works properly

*/

/* Test Case 01:

    r = &y;
    r = p;
    r = q;
    *r = x;
    *r = y;
    *r = z;
constPointer.c: In function ‘main’:
constPointer.c:16:7: error: assignment of read-only variable ‘r’
   16 |     r = &y;
      |       ^
constPointer.c:17:7: error: assignment of read-only variable ‘r’
   17 |     r = p;
      |       ^
constPointer.c:18:7: error: assignment of read-only variable ‘r’
   18 |     r = q;
      |       ^
constPointer.c:19:8: error: assignment of read-only location ‘*(const int *)r’
   19 |     *r = x;
      |        ^
constPointer.c:20:8: error: assignment of read-only location ‘*(const int *)r’
   20 |     *r = y;
      |        ^
constPointer.c:21:8: error: assignment of read-only location ‘*(const int *)r’
   21 |     *r = z;
      |        ^
*/