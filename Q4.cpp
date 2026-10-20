
#include <iostream>
using namespace std;

int getBitLength(int num)
{
    int length = 0;

    do
    {
        length++;
        num = num / 2;
    }
    while (num > 0);

    return length;
}

int countSetBits(int num)
{
    int count = 0;

    while (num > 0)
    {
        count += num % 2;
        num = num / 2;
    }

    return count;
}

void displayBinary(int num, int bits)
{
    for (int i = bits - 1; i >= 0; i--)
        cout << ((num >> i) & 1);
}

void displayArray(int arr[], int n, int bits)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " = ";
        displayBinary(arr[i], bits);
        cout << endl;
    }
}

void radixSortBinary(int arr[], int n, int maxBits)
{
    int *output = new int[n];

    for (int bit = 0; bit < maxBits; bit++)
    {
        int zeros = 0;
        int ones = 0;

        for (int i = 0; i < n; i++)
        {
            if (((arr[i] >> bit) & 1) == 0)
                zeros++;
            else
                ones++;
        }

        int zeroIndex = 0;
        int oneIndex = zeros;

        for (int i = 0; i < n; i++)
        {
            if (((arr[i] >> bit) & 1) == 0)
                output[zeroIndex++] = arr[i];
            else
                output[oneIndex++] = arr[i];
        }

        for (int i = 0; i < n; i++)
            arr[i] = output[i];

        cout << "\n====================================\n";
        cout << "Pass " << bit + 1
             << " - Bit Position " << bit;

        if (bit == 0)
            cout << " (LSB)";
        else if (bit == maxBits - 1)
            cout << " (MSB)";

        cout << "\n====================================\n";
        cout << "Zeros: " << zeros << endl;
        cout << "Ones: " << ones << endl;

        cout << "Array (Decimal): ";
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";

        cout << "\nArray (Binary): ";
        for (int i = 0; i < n; i++)
        {
            displayBinary(arr[i], maxBits);
            cout << " ";
        }

        cout << endl;
    }

    delete[] output;
}

int main()
{
    int n;

    cout << "Enter the number of elements: ";
    cin >> n;

    if (n < 10)
    {
        cout << "Please enter at least 10 elements." << endl;
        return 0;
    }

    int *arr = new int[n];

    cout << "Enter decimal integers:\n";

    int maxValue = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];

        if (arr[i] < 0)
        {
            cout << "Please enter non-negative integers only."
                 << endl;

            delete[] arr;
            return 0;
        }

        if (arr[i] > maxValue)
            maxValue = arr[i];
    }

    int maxBits = getBitLength(maxValue);

    cout << "\nBinary Representations:\n";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " = ";
        displayBinary(arr[i], maxBits);
        cout << endl;
    }

    radixSortBinary(arr, n, maxBits);

    cout << "\n====================================\n";
    cout << "Final Sorted Array\n";
    cout << "====================================\n";

    cout << "Decimal:\n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    cout << "\nBinary:\n";
    for (int i = 0; i < n; i++)
    {
        displayBinary(arr[i], maxBits);
        cout << " ";
    }
    cout << endl;

    int longestID = arr[0];
    int longestLength = getBitLength(arr[0]);

    for (int i = 1; i < n; i++)
    {
        int length = getBitLength(arr[i]);

        if (length > longestLength)
        {
            longestLength = length;
            longestID = arr[i];
        }
    }

    cout << "\n====================================\n";
    cout << "Additional Analysis\n";
    cout << "====================================\n";

    cout << "Longest Binary Representation:\n";
    cout << longestID << " = ";
    displayBinary(longestID, longestLength);
    cout << "\nLength = " << longestLength << " bits\n";

    cout << "\nLargest Input Value:\n";
    cout << maxValue << " = ";
    displayBinary(maxValue, maxBits);

    int largestSetBits = countSetBits(maxValue);

    cout << "\nNumber of set bits (1s): "
         << largestSetBits << endl;

    cout << "\nNumbers with the same number of set bits:\n";

    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if (countSetBits(arr[i]) == largestSetBits)
        {
            cout << arr[i] << " ";
            count++;
        }
    }

    cout << "\nCount: " << count << endl;

    delete[] arr;

    return 0;
}
