
#include <iostream>
#include <iomanip>
using namespace std;

void display(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << setw(4) << setfill('0') << arr[i]
             << setfill(' ');

        if (i < n - 1)
            cout << " ";
    }
    cout << endl;
}

int digitSum(int id)
{
    int sum = 0;

    while (id > 0)
    {
        sum += id % 10;
        id /= 10;
    }

    return sum;
}

void radixSort(int arr[], int n)
{
    int *output = new int[n];

    for (int exp = 1; exp <= 1000; exp *= 10)
    {
        int count[10] = {0};

        for (int i = 0; i < n; i++)
        {
            int digit = (arr[i] / exp) % 10;
            count[digit]++;
        }

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--)
        {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        for (int i = 0; i < n; i++)
            arr[i] = output[i];

        int evenCount = 0;

        for (int i = 0; i < n; i++)
        {
            int digit = (arr[i] / exp) % 10;

            if (digit % 2 == 0)
                evenCount++;
        }

        cout << "\nAfter ";

        if (exp == 1)
            cout << "Units";
        else if (exp == 10)
            cout << "Tens";
        else if (exp == 100)
            cout << "Hundreds";
        else
            cout << "Thousands";

        cout << " Pass:\n";
        display(arr, n);

        cout << "IDs having an even digit at this position: "
             << evenCount << endl;
    }

    delete[] output;
}

int main()
{
    int n;

    cout << "Enter number of students (at least 20): ";
    cin >> n;

    if (n < 20)
    {
        cout << "Please enter at least 20 students." << endl;
        return 0;
    }

    int *ids = new int[n];

    cout << "Enter the last four digits of each student ID "
         << "(0000 to 9999):\n";

    for (int i = 0; i < n; i++)
    {
        cin >> ids[i];

        if (ids[i] < 0 || ids[i] > 9999)
        {
            cout << "Invalid ID. Enter IDs from 0000 to 9999."
                 << endl;

            delete[] ids;
            return 0;
        }
    }

    cout << "\nOriginal IDs:\n";
    display(ids, n);

    cout << "\n RADIX SORT \n";
    radixSort(ids, n);

    cout << "\n DUPLICATE IDs \n";

    bool duplicateFound = false;

    for (int i = 0; i < n;)
    {
        int j = i + 1;

        while (j < n && ids[j] == ids[i])
            j++;

        if (j - i > 1)
        {
            cout << "ID: "
                 << setw(4) << setfill('0') << ids[i]
                 << setfill(' ')
                 << " | Frequency: " << j - i << endl;

            duplicateFound = true;
        }

        i = j;
    }

    if (!duplicateFound)
        cout << "No duplicate IDs found." << endl;

    cout << "\n DIGIT SUMS \n";

    int maxSum = -1;
    int maxID = ids[0];

    for (int i = 0; i < n; i++)
    {
        int sum = digitSum(ids[i]);

        cout << "ID: "
             << setw(4) << setfill('0') << ids[i]
             << setfill(' ')
             << " | Digit Sum: " << sum << endl;

        if (sum > maxSum)
        {
            maxSum = sum;
            maxID = ids[i];
        }
    }

    cout << "\nID with highest digit sum: "
         << setw(4) << setfill('0') << maxID
         << setfill(' ')
         << "\nHighest digit sum: " << maxSum << endl;

    cout << "\n LONGEST EVEN DIGIT-SUM SEQUENCE \n";

    int bestStart = -1;
    int bestLength = 0;
    int currentStart = 0;
    int currentLength = 0;

    for (int i = 0; i < n; i++)
    {
        if (digitSum(ids[i]) % 2 == 0)
        {
            if (currentLength == 0)
                currentStart = i;

            currentLength++;

            if (currentLength > bestLength)
            {
                bestLength = currentLength;
                bestStart = currentStart;
            }
        }
        else
        {
            currentLength = 0;
        }
    }

    if (bestLength == 0)
    {
        cout << "No IDs have an even digit sum." << endl;
        cout << "Sequence length: 0" << endl;
    }
    else
    {
        cout << "Longest sequence: ";

        for (int i = bestStart;
             i < bestStart + bestLength; i++)
        {
            cout << setw(4) << setfill('0') << ids[i]
                 << setfill(' ');

            if (i < bestStart + bestLength - 1)
                cout << " ";
        }

        cout << "\nSequence length: " << bestLength << endl;
    }

    delete[] ids;

    return 0;
}
