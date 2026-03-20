#include<stdio.h>
#include<stdlib.h>


int main(){
    int x = 10;
    int y,z,a,b;
    printf("Stack:\n%p\n%p\n%p\n%p\n%p\nHeap:\n", &x,&y,&z,&a,&b);
    int* p = (int*)malloc(sizeof(int));
    int* q = (int*)malloc(sizeof(int));
    int* r = (int*)malloc(sizeof(int));
    int* s = (int*)malloc(sizeof(int));
    int* t = (int*)malloc(sizeof(int));
    printf("%p\n%p\n%p\n%p\n%p\n", p,q,r,s,t);
    free(p);
    free(q);
    free(r);
    free(s);
    free(t);
    return 0;
}