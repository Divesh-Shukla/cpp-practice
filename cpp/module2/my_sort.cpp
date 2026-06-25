#include <iostream>

template <typename T, typename Compare>
void my_sort_helper_merger(T *arr, size_t left, size_t mid, size_t right, Compare comp)
{
    size_t new_array_size = right - left + 1;
    T *arr1 = new T[new_array_size];
    int l = 0, r;
    for (size_t i = left; i <= right; i++)
    {
        arr1[i - left] = arr[i];
        if (i == mid)
            r = i - left + 1;
    }

    int temp_var = r;
    int temp_var1 = mid + 1;
    while (l < temp_var && r < new_array_size)
    {
        if (comp(arr1[l], arr1[r]))
            arr[left++] = arr1[l++];
        else
            arr[left++] = arr1[r++];
    }

    while (l < temp_var)
        arr[left++] = arr1[l++];
    while (r < new_array_size)
        arr[left++] = arr1[r++];

    delete[] arr1;
}

template <typename T, typename Compare>
void my_sort_helper(T *arr, int left, int right, Compare comp)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    my_sort_helper(arr, left, mid, comp);
    my_sort_helper(arr, mid + 1, right, comp);
    my_sort_helper_merger(arr, left, mid, right, comp);
}

template <typename T, typename Compare>
void my_sort(T *arr, size_t n, Compare comp)
{
    my_sort_helper(arr, 0, n - 1, comp);
}

int main()
{
    int arr[] = {7, 2, 4, 9, 4, 0};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    my_sort(arr, arr_size, [](int a, int b)
            { return a < b; });
    std::cout << "[" << arr[0];
    for (int i = 1; i < arr_size; i++)
        std::cout << ", " << arr[i];
    std::cout << "]\n";

    my_sort(arr, arr_size, [](int a, int b)
            { return a > b; });
    std::cout << "[" << arr[0];
    for (int i = 1; i < arr_size; i++)
        std::cout << ", " << arr[i];
    std::cout << "]\n";

    double arr1[] = {2.3, 4.1, 3.113, 0.65, 3.141, 1.22};
    int arr1_size = sizeof(arr1) / sizeof(arr1[0]);

    my_sort(arr1, arr1_size, [](double a, double b)
            { return a < b; });
    std::cout << "[" << arr1[0];
    for (int i = 1; i < arr1_size; i++)
        std::cout << ", " << arr1[i];
    std::cout << "]\n";

    my_sort(arr1, arr1_size, [](double a, double b)
            { return a > b; });
    std::cout << "[" << arr1[0];
    for (int i = 1; i < arr1_size; i++)
        std::cout << ", " << arr1[i];
    std::cout << "]\n";
}
