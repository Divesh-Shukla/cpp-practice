#include <stdio.h>

int divide(int a, int b){
    return a/b;
}

int main(){
    int x = divide(10, 0);
    printf("%d\n", x);
    return 0;
}
