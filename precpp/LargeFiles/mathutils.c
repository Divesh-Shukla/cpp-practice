#include "mathutils.h"

float add(float a, float b)
{
    return a+b;
}

float multiply(float a, float b)
{
    return a*b;
}

float average(float* arr, int n)
{
    float avg = 0;
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    avg = sum/n;

    return avg;
}