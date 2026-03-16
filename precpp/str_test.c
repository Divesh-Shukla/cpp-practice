#include<stdio.h>

int my_strlen(char* v){    
    int counter=0;
    while((*v)!='\0'){
        counter++;
        v += 1;;
    }
    return counter;
}

char* my_strcpy(char* dest, char* src){
    int i = 0;
    while (*(src+i) != '\0')
    {
        *(dest+i)=*(src+i);
        i++;
    }
    *(dest+i)=*(src+i);
    return dest;
}

int my_strcmp(char* str1, char* str2){
    while (*str1!='\0'&&*str2!='\0')
    {
        if (*str1!=*str2)
        {
            return *str1-*str2;
        }
        str1++;
        str2++;
        
    }
    return *str1-*str2;
    
}

char* my_strcat(char* dest, char* src){
    char* temp = dest;
    while (*dest!='\0')
    {
        dest++;
    }
    while (*src!='\0')
    {
        *dest=*src;
        dest++;
        src++;
    }
    
    
    *dest='\0';

    return temp;
    
    
}

int main(){
    //Test CODE for strlen
    // char s1[] = "hello";
    // char s2[] = "";
    // char s3[] = "a";
    // printf("%d\n", my_strlen(s1));  // expect 5
    // printf("%d\n", my_strlen(s2));  // expect 0
    // printf("%d\n", my_strlen(s3));  // expect 1

    //Test CODE for my_strcmp
    printf("%d\n",my_strcmp("hello", "hello"));
    printf("%d\n",my_strcmp("Vampire","Vampires"));
    printf("%d\n",my_strcmp("Vampires","Vampire"));
    printf("%d\n", my_strcmp("hello", "hello"));  // expect 0
    printf("%d\n", my_strcmp("abc", "abd"));      // expect negative
    printf("%d\n", my_strcmp("abd", "abc"));      // expect positive
    printf("%d\n", my_strcmp("ab", "abc"));       // expect negative
    
    //TEST CODE FOR my_strcpy;
    // char s1[] = "Harmeer";
    // char s2[] = "Prabhu";
    // char s3[10];
    // char s4[10];
    // char s5[10];

    // my_strcpy(s3, s1);
    // my_strcpy(s4, s2);
    // my_strcpy(s5, s3);

    // printf("%s\n", s3);   // Harmeer
    // printf("%s\n", s4);   // Prabhu
    // printf("%s\n", s5);   // Harmeer


    //TEST code for strcat
    // char s1[20] = "Hello";
    // char s2[] = " World";
    // char s3[20] = "Test";
    // char s4[] = "";

    // my_strcat(s1, s2);
    // printf("%s\n", s1);  // expect: Hello World

    // my_strcat(s3, s4);
    // printf("%s\n", s3);  // expect: Test
    return 0;
}

/* ATTEMPT 1:-
int strlen(char* v){
    if (*v == '\0')  This is a redundant condition check as the while loop also takes care of this!
    {
return 0;
    }
int counter=0;
while((*v)='\0'){ The not equal operator is not placed correctly. Mistake
counter++;
v += 1;;
    }
return counter;
}


Attempt 1 of strcmp:-
int my_strcmp(char* str1, char* str2){
    while (*str1!='\0'&&*str2!='\0')
    {
if (*str1 == *str2)
        {
str1 += 1;
str2 += 1;
        }else if (*str1>*str2)
        {
return -1;
        }else
        {
return 1;
        }
    }
if (*str1=='\0'&&*str2=='\0')
    {
return 0;
    }else if (*str1=='\0')
    {
return 1;
    }else
    {
return -1;
    }
}

Learnings:-
The convention of return was exactly opposite of what I used:-
i)I returned -1 for *str1>*str2
ACTUAL +1. 
ii)I returned +1 for *str1<*str2
ACTUAL +1. 
Half of the code was redundant.
return *str1-*str2 reduced the code to a great extent.
*/