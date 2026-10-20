
#include <iostream>
using namespace std;

int levelCount[1000] = {0};

void display(int arr[], int low, int high)
{
    cout << "[";

    for (int i = low; i <= high; i++)
    {
        cout << arr[i];

        if (i < high)
            cout << ", ";
    }

    cout << "]";
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

void merge(int arr[], int temp[], int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= high)
        temp[k++] = arr[j++];

    for (int x = low; x <= high; x++)
        arr[x] = temp[x];
}

void hybridSort(int arr[], int temp[],
                int low, int high, int level)
{
    if (low >= high)
        return;

    cout << "\nLevel " << level << endl;

    if (level % 2 == 1)
    {
        cout << "Technique: Quick Sort Partitioning" << endl;

        int pivotValue = arr[high];
        int pivotIndex = partitionArray(arr, low, high);

        cout << "Selected pivot: " << pivotValue << endl;

        cout << "Left subarray: ";
        if (low < pivotIndex)
        {
            display(arr, low, pivotIndex - 1);
            levelCount[level]++;
        }
        else
            cout << "Empty";

        cout << "\nPivot in final position: "
             << arr[pivotIndex] << endl;

        cout << "Right subarray: ";
        if (pivotIndex < high)
        {
            display(arr, pivotIndex + 1, high);
            levelCount[level]++;
        }
        else
            cout << "Empty";

        cout << "\nSubarrays generated at this split: "
             << ((low < pivotIndex) + (pivotIndex < high))
             << endl;

        hybridSort(arr, temp, low, pivotIndex - 1, level + 1);
        hybridSort(arr, temp, pivotIndex + 1, high, level + 1);
    }
    else
    {
        cout << "Technique: Merge Sort Division" << endl;

        int mid = low + (high - low) / 2;

        cout << "Left subarray: ";
        display(arr, low, mid);
        cout << endl;

        cout << "Right subarray: ";
        display(arr, mid + 1, high);
        cout << endl;

        levelCount[level] += 2;

        cout << "Subarrays generated at this split: 2"
             << endl;

        hybridSort(arr, temp, low, mid, level + 1);
        hybridSort(arr, temp, mid + 1, high, level + 1);

        merge(arr, temp, low, mid, high);

        cout << "Merged subarray: ";
        display(arr, low, high);
        cout << endl;
    }
}

int main()
{
    int n;

    cout << "Enter number of product IDs (at least 20): ";
    cin >> n;

    if (n < 20 || n >= 1000)
    {
        cout << "Enter a number between 20 and 999." << endl;
        return 0;
    }

    int *arr = new int[n];
    int *temp = new int[n];

    cout << "Enter product IDs:\n";

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "\nOriginal array: ";
    display(arr, 0, n - 1);
    cout << endl;

    hybridSort(arr, temp, 0, n - 1, 1);

    cout << "\n LEVEL-WISE TOTALS \n";

    int total = 0;

    for (int i = 1; i < 1000; i++)
    {
        if (levelCount[i] > 0)
        {
            cout << "Level " << i
                 << ": " << levelCount[i]
                 << " subarrays generated" << endl;

            total += levelCount[i];
        }
    }

    cout << "Total subarrays generated: "
         << total << endl;

    cout << "\nFinal sorted product IDs: ";
    display(arr, 0, n - 1);
    cout << endl;

    delete[] arr;
    delete[] temp;

    return 0;
}
