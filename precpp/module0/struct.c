#include<stdio.h>
#include<math.h>
struct Student
{
    int rollNo;
    int marks;
    char name[29];
};

struct point
{
    double x,y;
};

struct Node
{
    int value;
    struct Node* next;
};

double distance(struct point, struct point);

int main()
{
    // struct Student s[5];

    // printf("Enter the details of the 5 students:-\n");
    // for (int i = 0; i < 5; i++)
    // {
    //     printf("Enter the name of student %d:- ",i);
    //     scanf("%s", s[i].name);

    //     printf("Enter the Roll Number of student %d:- ",i);
    //     scanf("%d", &s[i].rollNo);

    //     printf("Enter the marks of student %d:- ",i);
    //     scanf("%d", &s[i].marks);
    // }

    // int topScoreIndx = 0;
    // for (int i = 0; i < 5; i++)
    // {
    //     if(s[topScoreIndx].marks<s[i].marks){
    //         topScoreIndx = i;
    //     }
    // }
    
    // printf("The higesht scorer of class is %s with a score of %d.\n", s[topScoreIndx].name,s[topScoreIndx].marks);
    // printf("Size of Student struct: %zu bytes\n", sizeof(struct Student));
    // printf("Size of char[29]: %zu\n", sizeof(char) * 29);
    // printf("Size of int: %zu\n", sizeof(int));
    // printf("Sum of members: %zu\n", sizeof(char)*29 + sizeof(int) + sizeof(int));

    // struct point a = {12,5};
    // struct point b = {6,8};
    // double doori = distance(a,b);
    // printf("%g", doori);

    struct Node n1,n2;
    n1.value = 10;
    n1.next = &n2;
    n2.value = 13;
    n2.next = NULL;
    struct Node* head = &n1;

    struct Node* temp = head;
    int i = 1;

    while (temp!=NULL)
    {
        printf("Node %d has value %d and address %p.\n", i, temp->value, temp->next);
        temp = temp->next;
        i++;
    }
    

    return 0;
    
}

double distance(struct point a, struct point b){
    double xVal = (a.x-b.x)*(a.x-b.x);
    double yVal = (a.y-b.y)*(a.y-b.y);
    double doori = sqrt(xVal+yVal);
    return doori; 
}

