#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;


template <typename T>
void my_swap(T& a, T& b)
{
	T tmp;

	tmp = a;
	a = b;
	b = tmp;
}

bool CheckSorted(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

void Print(int* arr, int low, int high, int n)
{
	for (int i = 0; i < n; i++)
		if (i >= low && i <= high)
			cout << setw(3) << arr[i] << " ";
		else
			cout << "    ";
	cout << endl;
}


// Hong lab 구현 예시
// 추가 힌트: do-while 사용
/***/
int Partition(int arr[], int low, int high, int n)
{
    int pivot = arr[size_t(floorf((high - low) / 2.0f)) + low];
    int i = low - 1;
    int j = high + 1;

    cout << "pivot=" << pivot << endl;
    cout << "         ";
    Print(arr, low, high, n);

    while (true)
    {
        do i = i + 1;
        while (arr[i] < pivot);

        do j = j - 1;
        while (arr[j] > pivot);

        if (i >= j)
        return j;

        swap(arr[i], arr[j]);

        cout << "i=" << i << ", j=" << j << endl;
        cout << "         ";
        Print(arr, low, high, n);
    }
}


/** Mine
// Hoare partition scheme
int Partition(int arr[], int low, int high, int n)
{
	int pivot = arr[size_t(floorf((high - low) / 2.0f)) + low];
	// int i = low - 1;
	// int j = high + 1;
	int i = low;
	int j = high;

	while (true)
	{
		// TODO:
		// for ()
		for (;arr[i] < pivot;i++)
			continue ;
		for (;arr[j] > pivot;j--)
			continue ;
		my_swap(arr[i], arr[j]);
		cout << "pivot=" << pivot << ", i=" << i << ", j=" << j << endl;
		cout << "         ";
		Print(arr, low, high, n);
		if (i==j)
			return i;
	}
}
*/

void QuickSort(int arr[], int low, int high, int n) // 마지막 n은 출력용
{
	if (low >= 0 && high >= 0 && low < high)
	{
		// Partitioning Index
		cout << "# low=" << low << ", high=" << high << endl;
		int p = Partition(arr, low, high, n);

		QuickSort(arr, low, p, n); // Note: the pivot is now included
		QuickSort(arr, p + 1, high, n);
	}
}

int main()
{
	int arr[] = { 4, 17, 2, 9, 7, 5, 8, 1, 14, 6 };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << "         ";
	Print(arr, 0, n - 1, n);
	cout << endl;

	QuickSort(arr, 0, n - 1, n);

	cout << "         ";
	Print(arr, 0, n - 1, n);
	cout << endl;
}