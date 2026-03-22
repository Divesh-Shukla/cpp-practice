#include<stdio.h>

int my_strlen(char *a)
{
    char *temp = a;
    while (*temp!='\0')
    {
        temp++;
    }
    return temp-a;
    
}

int main()
{
    char a[] = "Divesh Shukla";
    int aLen = my_strlen(a);
    printf("The number of chars in %s: %d\n",a,aLen);
    return 0;
}