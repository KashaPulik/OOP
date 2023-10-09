#include <iostream>
#include <stdlib.h>

using namespace std;

int **create_matrix(int size, int maxVal)
{
    int **matrix = new int *[size];
    for (int i = 0; i < size; i++)
        matrix[i] = new int[size];
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = rand() % maxVal;
    return matrix;
}

int *a_init(int **matrix, int *arr, int size)
{
    int n = size - 1;
    int i, j, g = 0;
    while (n >= 0)
    {
        i = 0;
        j = n--;
        while (j < size)
            arr[g++] = matrix[i++][j++];
    }
    n = 1;
    while (n < size)
    {
        j = 0;
        i = n++;
        while (i < size)
            arr[g++] = matrix[i++][j++];
    }
    return arr;
}

int *b_init(int **matrix, int *arr, int size)
{
    int n = 0;
    int i, j, g = 0;
    while (n < size)
    {
        j = 0;
        i = n++;
        while (i >= 0)
            arr[g++] = matrix[i--][j++];
    }
    n = 1;
    while (n < size)
    {
        i = size - 1;
        j = n++;
        while (j < size)
            arr[g++] = matrix[i--][j++];
    }
    return arr;
}

int *d_init(int**, int*, int);

int *c_init(int **matrix, int *arr, int size)
{
    int arr_size = size * size;
    int *tmp_arr = new int [arr_size];
    tmp_arr = d_init(matrix, tmp_arr, size);
    int i = 0, j = arr_size - 1;
    while(i < arr_size)
        arr[i++] = tmp_arr[j--];
    delete [] tmp_arr;
    return arr;
}

int *d_init(int **matrix, int *arr, int size)
{
    int stop_hor = size;
    int stop_ver = 0;
    int i = 0, n = 0, m = 0;
    while (1)
    {
        if ((size % 2 == 1) && (stop_hor - stop_ver == 1))
        {
            arr[i] = matrix[n][m];
            break;
        }
        while (m < stop_hor)
            arr[i++] = matrix[n][m++];
        m--;
        n++;
        while (n < stop_hor)
            arr[i++] = matrix[n++][m];
        n--;
        m--;
        while (m >= stop_ver)
            arr[i++] = matrix[n][m--];
        m++;
        n--;
        stop_hor--;
        stop_ver++;
        if (stop_hor == stop_ver)
            break;
        while (n >= stop_ver)
            arr[i++] = matrix[n--][m];
        n++;
        m++;
    }
    return arr;
}

void print_matrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << endl;
        for (int j = 0; j < size; j++)
            cout << matrix[i][j] << " ";
    }
    cout << endl;
}

void print_arr(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int size = 4;
    int **matrix = create_matrix(size, 10);
    print_matrix(matrix, size);
    cout << endl;
    int *arr = new int[size * size];
    c_init(matrix, arr, size);
    print_arr(arr, size * size);
    delete [] arr;
}