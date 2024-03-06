#include <iostream>
#include <cassert> // assert()

using namespace std;

// 조언
// - 배열의 값들도 정수이고 인덱스도 정수라서 헷갈리는 것이 당연합니다. 
// - 단기 집중력이 필요한데 익숙해지셔야 합니다.

// 배열 arr에 x가 몇 번 나오는지 반환
size_t	Count(int* arr, int n, int x);

// 배열 arr에 x가 있으면 index 반환, 없으면 -1 반환
int SequentialSearch(int* arr, int n, int x); // LinearSearch

// 정렬된 배열에서 x가 몇 번 나오는지 반환
int SortedCount(int* arr, int n, int x);
int SortedCountHelper(int* arr, int n, int x, int start); // start 사용

// 정렬할 때 사용
void InsertionSort(int* arr, int n);

void Print(int* arr, int size);

int main()
{
	// 정렬되지 않은 데이터를 가정

	int arr[] = { 8, 1, 1, 3, 2, 5, 1, 2 , 1, 1 };
	int n = sizeof(arr) / sizeof(arr[0]);

	// 복잡한 알고리즘이나 자료구조를 개발할 때는 
	// 실수할 가능성이 적은 단순한 방법을 기준으로 삼아요.

	cout << "Count 9 => \n" << Count(arr, n, 9) << endl;
	cout << "Count 2 => \n" << Count(arr, n, 2) << endl;
	cout << "Count 8 => \n" << Count(arr, n, 8) << endl;
	cout << "Count 1 => \n" << Count(arr, n, 1) << endl;
	cout << endl;

	cout << "Search 2 => \n" << SequentialSearch(arr, n, 2) << endl;
	cout << "Search 5 => \n" << SequentialSearch(arr, n, 5) << endl;
	cout << "Search 9 => \n" << SequentialSearch(arr, n, 9) << endl;
	cout << endl;

	InsertionSort(arr, n);

	Print(arr, n);

	cout << "Sorted Count 9 => \n" << SortedCount(arr, n, 9) << endl;
	cout << "Sorted Count 2 => \n" << SortedCount(arr, n, 2) << endl;
	cout << "Sorted Count 8 => \n" << SortedCount(arr, n, 8) << endl;
	cout << "Sorted Count 1 => \n" << SortedCount(arr, n, 1) << endl;
	cout << endl;

	return 0;
}

// 배열 arr에 x가 몇 번 나오는지 반환
size_t	Count(int* arr, int n, int x)
{
	// TODO:
	// int myNumbers[5] = {10, 20, 30, 40, 50};
	size_t	count = 0;
	
	for (size_t idx = 0; idx < n; idx++){
		// std::cout << "arr[idx] : " << arr[idx] << std::endl;
		if (arr[idx] == x)
			count++;
	}
	return count;
}

// 배열 arr에 x가 있으면 index 반환, 없으면 -1 반환
int SequentialSearch(int* arr, int n, int x)
{
	// TODO:
	// mine
	// for (size_t idx = 0; idx < n; idx++)
	// {
	// 	// std::cout << "arr[idx] : " << arr[idx] << std::endl;
	// 	if (arr[idx] == x)
	// 		return idx;
	// }
	// Horowitz book style
	int idx;
	for (idx = 0; idx < n && arr[idx] != x; idx++)
	{
		/* Do Nothing */ 
		// 가독성을 위해 아무 것도 안하고 idx만 증가시키는 것을 명시함
	}
	if (idx == n) return -1;
	return idx;
}

int SortedCountHelper(int* arr, int n, int x, int start) // start 사용
{
	// TODO: 
	size_t	count = 0;
	for (size_t idx = start; idx < n; idx++){
		// std::cout << "arr[idx] : " << arr[idx] << std::endl;
		if (arr[idx] == x)
			count++;
		else
			break ; // 정렬이 된 배열에서 찾으므로 다른 값이 나오기 시작했다면 더 이상 볼 필요가 없다
	}
	return count;
}

int SortedCount(int* arr, int n, int x)
{
	int i = SequentialSearch(arr, n, x);

	if (i >= 0)
		return SortedCountHelper(arr, n, x, i + 1) + 1;
	else
		return 0;
}

void InsertionSort(int* arr, int n)
{
	int i, key, j;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}

		arr[j + 1] = key;
	}
}

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}