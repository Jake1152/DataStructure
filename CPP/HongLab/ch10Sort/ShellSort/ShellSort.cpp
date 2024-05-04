#include <iostream>
#include <iomanip>

using namespace std;

bool CheckSorted(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}

	return true;
}

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << setw(3) << arr[i] << " ";
	cout << endl;
}

void Print(int* arr, int size, int start, int gap)
{
	for (int i = 0; i < size; i++)
	{
		if ((i - start) % gap == 0)
			cout << setw(3) << arr[i] << " ";
		else
			cout << "    ";
	}
	cout << endl;
}

template <typename T>
void my_swap(T& a, T& b)
{
	T tmp;

	tmp = a;
	a = b;
	b = tmp;
}

/**
 * 하나씩 뽑아서 적절한 위치에 놓는다.
 * 왼쪽부터 채운다.
 * 오른쪽 정렬되지 않은 영역에서 값을 하나 뽑아서 
 * 정렬된 영역 속 적당한 위치를 찾아서 넣어준다.
 * 
*/
void InsertionSort(int arr[], int n)
{
	// 5 2 1 4 6
	for (int be_sorted_idx = 0; be_sorted_idx < n; be_sorted_idx++)
	{
		// arr[sorted_idx]
		Print(arr, n);
		for (int sorted_id = be_sorted_idx; sorted_id > 0 && arr[sorted_id - 1] > arr[sorted_id]; sorted_id--)
		{
			cout << "         ";
			Print(arr, n);
			my_swap(arr[sorted_id - 1], arr[sorted_id]);
		}
	}
}

void InsertionSort(int arr[], int n, int gap) // gap 추가
{
	cout << "gap = " << gap << endl;

	for (int i = gap; i < n; i += 1)
	{
		cout << "Before : ";
		Print(arr, n, i, gap);

		// TODO:

		cout << " After : ";
		Print(arr, n, i, gap);
	}
}

void ShellSort(int arr[], int n)
{
	// for (int gap = n / 2; gap > 0; gap /= 2)
	// {
	// 	cout << "         ";
	// 	Print(arr, n);

	// 	InsertionSort(arr, n, gap);
	// }
	InsertionSort(arr, n);

	// cout << "         ";
	cout << endl;
	Print(arr, n);
	cout << endl;
}

int main()
{
	int arr[] = { 99, 83, 18, 66, 7, 54, 95, 86, 47, 69, 25, 28 };
	int n = sizeof(arr) / sizeof(arr[0]);

	ShellSort(arr, n);

	// 최악 O(n^2), 평균 O(n^1.5)
}
