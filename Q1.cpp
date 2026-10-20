
#include <iostream>
using namespace std;

long long quickCount = 0;
long long mergeCount = 0;

void display(int arr[], int left, int right)
{
    cout << "[";
    for (int i = left; i <= right; i++)
    {
        cout << arr[i];
        if (i < right)
            cout << ", ";
    }
    cout << "]";
}

void displayArray(int arr[], int n)
{
    display(arr, 0, n - 1);
    cout << endl;
}

int partitionArray(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivotValue = arr[high];

        cout << "\nQuick Sort partition:\n";
        cout << "Selected pivot: " << pivotValue << endl;

        int pivotIndex = partitionArray(arr, low, high);

        cout << "Left subarray: ";
        if (low < pivotIndex)
        {
            display(arr, low, pivotIndex - 1);
            quickCount++;
        }
        else
            cout << "Empty";

        cout << "\nPivot: " << arr[pivotIndex];

        cout << "\nRight subarray: ";
        if (pivotIndex < high)
        {
            display(arr, pivotIndex + 1, high);
            quickCount++;
        }
        else
            cout << "Empty";

        cout << endl;

        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

void merge(int arr[], int temp[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (int x = left; x <= right; x++)
        arr[x] = temp[x];

    cout << "Merged subarray: ";
    display(arr, left, right);
    cout << endl;
}

void mergeSort(int arr[], int temp[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        cout << "\nDividing subarray: ";
        display(arr, left, right);
        cout << endl;

        cout << "Left subarray: ";
        display(arr, left, mid);
        cout << endl;

        cout << "Right subarray: ";
        display(arr, mid + 1, right);
        cout << endl;

        mergeCount += 2;

        mergeSort(arr, temp, left, mid);
        mergeSort(arr, temp, mid + 1, right);

        merge(arr, temp, left, mid, right);
    }
}

int main()
{
    int n;

    cout << "Enter number of elements (at least 10): ";
    cin >> n;

    if (n < 10)
    {
        cout << "Please enter at least 10 elements." << endl;
        return 0;
    }

    int *original = new int[n];
    int *quickArr = new int[n];
    int *mergeArr = new int[n];
    int *temp = new int[n];

    cout << "Enter " << n << " elements:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> original[i];
        quickArr[i] = original[i];
        mergeArr[i] = original[i];
    }

    cout << "\n QUICK SORT \n";

    quickSort(quickArr, 0, n - 1);

    cout << "\nFinal sorted array (Quick Sort): ";
    displayArray(quickArr, n);

    cout << "Total subarrays generated: "
         << quickCount << endl;

    cout << "\n MERGE SORT \n";

    mergeSort(mergeArr, temp, 0, n - 1);

    cout << "\nFinal sorted array (Merge Sort): ";
    displayArray(mergeArr, n);

    cout << "Total subarrays generated during division: "
         << mergeCount << endl;

    delete[] original;
    delete[] quickArr;
    delete[] mergeArr;
    delete[] temp;

    return 0;
}
