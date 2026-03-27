#include<stdio.h>

size_t my_strlen(const char *c)
{
    size_t counter = 0;
    while (*c)
    {
        c++;
        counter++;
    }
    return counter;
}

int my_strcmp(const char *a, const char *b)
{
    while (*a!='\0' && *b!='\0')
    {
        if(*a != *b) return *a - *b;
        a++;
        b++;
    }
    return *a - *b;
}

char* my_strcpy(char* dest, const char* src)
{
    char* temp = dest;
    while (*src != 0)
    {
        *temp++ = *src++;
    }
    *temp = '\0';
    return dest;
}

char* my_strcat(char* dest,const char* src)
{
    char* temp = dest;
    while (*dest != '\0') dest++;
    while (*src!='\0') *dest++ = *src++;
    *dest = '\0';
    return temp;
}


void test_strlen() {
    printf("\n==== Testing my_strlen ====\n");

    printf("Empty: %zu\n", my_strlen(""));
    printf("Single char: %zu\n", my_strlen("A"));
    printf("Normal: %zu\n", my_strlen("Hello World"));
    printf("Spaces: %zu\n", my_strlen("   "));
}

void test_strcmp() {
    printf("\n==== Testing my_strcmp ====\n");

    printf("Equal: %d\n", my_strcmp("abc", "abc"));
    printf("a < b: %d\n", my_strcmp("abc", "abd"));
    printf("a > b: %d\n", my_strcmp("abe", "abd"));

    printf("Prefix (shorter): %d\n", my_strcmp("abc", "abcd"));
    printf("Prefix (longer): %d\n", my_strcmp("abcd", "abc"));

    printf("Empty vs empty: %d\n", my_strcmp("", ""));
    printf("Empty vs non-empty: %d\n", my_strcmp("", "a"));
    printf("Non-empty vs empty: %d\n", my_strcmp("a", ""));

    // High ASCII test 
    char s1[] = "\xFF";
    char s2[] = "\x01";
    printf("High ASCII compare: %d\n", my_strcmp(s1, s2));
}

void test_strcpy() {
    printf("\n==== Testing my_strcpy ====\n");

    char dest[50];

    // Basic copy
    my_strcpy(dest, "Hello");
    printf("Copy 'Hello': %s\n", dest);

    // Empty string
    my_strcpy(dest, "");
    printf("Copy empty: '%s'\n", dest);

    // Overwriting existing content
    my_strcpy(dest, "First");
    my_strcpy(dest, "Second");
    printf("Overwrite test: %s\n", dest);

    // Long string (within bounds)
    my_strcpy(dest, "This is a longer string test");
    printf("Long copy: %s\n", dest);
}

void test_strcat() {
    printf("\n==== Testing my_strcat ====\n");

    char buffer[100] = "Hello";

    // Basic append
    my_strcat(buffer, " World");
    printf("Append: %s\n", buffer);

    // Multiple appends
    my_strcat(buffer, "!!!");
    printf("Multiple append: %s\n", buffer);

    // Append empty
    my_strcat(buffer, "");
    printf("Append empty: %s\n", buffer);

    // Append to empty dest
    char empty[50] = "";
    my_strcat(empty, "Start");
    printf("Empty dest: %s\n", empty);
}

void test_vs_standard() {
    printf("\n==== Comparing with standard library ====\n");

    char a[] = "Hello";
    char b[] = "World";

    // strcmp comparison
    printf("my_strcmp vs strcmp: %d vs %d\n",
           my_strcmp(a, b), strcmp(a, b));

    // strlen comparison
    printf("my_strlen vs strlen: %zu vs %zu\n",
           my_strlen(a), strlen(a));

    // strcpy comparison
    char d1[50], d2[50];
    my_strcpy(d1, a);
    strcpy(d2, a);
    printf("my_strcpy vs strcpy: %s vs %s\n", d1, d2);

    // strcat comparison
    char c1[50] = "Hi";
    char c2[50] = "Hi";
    my_strcat(c1, b);
    strcat(c2, b);
    printf("my_strcat vs strcat: %s vs %s\n", c1, c2);
}

int main() {
    test_strlen();
    test_strcmp();
    test_strcpy();
    test_strcat();
    test_vs_standard();

    return 0;
}