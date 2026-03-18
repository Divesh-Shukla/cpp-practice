#include "mathutils.h"
#include "mathutils.h"
#include<stdio.h>

int main()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    float arr[n];

    printf("Enter the nubers to find array: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &arr[i]);
    }

    float avg = average(arr,n);
    printf("Average: %f\n",avg);
    float sum = add(arr[0],arr[1]);
    printf("Sum: %f\n", sum);
    float prdct = multiply(arr[0],arr[1]);
    printf("Product: %f\n", prdct);

    return 0;
}