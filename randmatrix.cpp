#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

int* genRandArray(int size, int maxValue)
{
    int* arr = new int[size + 1];
    arr[0] = size;
    for(int i = 1; i <= size; i++)
    {
        arr[i] = rand() % maxValue;
    }
    return arr;
}

void print(int* arr)
{
    cout << arr[0] << ": ";
    for(int i = 1; i <= arr[0]; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int** genRandMatrix(int size, int maxValue)
{
    if(size == 0)
    {
        return NULL;
    }
    int** matrix = new int* [size];
    for(int i = 0; i < size; i++)
    {
        matrix[i] = genRandArray(rand() % 10, maxValue);
    }
    return matrix;
}

void printMatrix(int** matrix, int size)
{
    if ((matrix == NULL) || (size == 0))
    {
        cout << "Matrix create error" << endl;
        return;
    }
    for(int i = 0; i < size; i++)
    {
        print(matrix[i]);
    }
}

void deleteMatrix(int** matrix, int size)
{
    if ((matrix == NULL) || (size == 0))
    {
        return;
    }
    for(int i = 0; i < size; i++)
    {
        delete [] matrix[i];
    }
    delete [] matrix;
}

int main()
{
    srand(time(0));
    int size = rand() % 10;
    int maxValue = 100;
    int** matrix = genRandMatrix(size, maxValue);
    printMatrix(matrix, size);
    deleteMatrix(matrix, size);
}