#include <iostream>

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
		cout << arr[i] << " ";
	cout << endl;
}

void insertionSort(int *arr, size_t size)
{
	std::cout << "# " << std::flush;
	Print(arr,size);
	for (int i = 1; i < size; i++){
		int current_picked_value = arr[i];
		// 오른쪽으로 밀어내면서 복사
		int j = i;
		for (; j > 0 && arr[j - 1] > current_picked_value; j--)
		{
			arr[j] = arr[j - 1];
			std::cout << "    Inner : " << std::flush;
			Print(arr, size);
			// if (arr[j] <= current_picked_value)
			// {
			// 	arr[j] = current_picked_value;
			// 	break ;
			// } 
			// else if (j == 1)
			// 	arr[0] = current_picked_value;
			// std::cout << "    After : " << std::flush;
			// Print(arr, size);
		}
		arr[j] = current_picked_value;
		std::cout << "  Outer : " << std::flush;
		Print(arr, size);
	}
	std::cout << "# " << std::flush;
	Print(arr,size);
}

int main()
{
	// 오른쪽으로 하나씩 밀기 (삽입 정렬의 중간 단계)
	
	{
		int arr[] = { 1, 2, 4, 5, 3, 6 };
		int n = sizeof(arr) / sizeof(arr[0]);

		Print(arr, n);

		// i = 4인 경우에 대해서 구현
		int i = 4;
		int pick = arr[i];
		int j = i;
		// 오른쪽으로 밀어내면서 복사
		for (; j > 0 && arr[j-1] > pick; j--)
		{
			// if (arr[j-1] <= pick)
			// {
			// 	arr[j] = pick;
			// 	break ;
			// }
			arr[j] = arr[j - 1];

			std::cout << "  " << std::flush;
			Print(arr, n);
		}
		arr[j] = pick;

		Print(arr, n);
		cout << endl;

		std::cout << std::boolalpha << "CheckSorted(arr, n) : " << CheckSorted(arr, n) << std::endl;
	}
	/**/
	// int arr[] = { 8, 3, 2, 5, 1, 2 };
	// // int arr[] = { 6, 5, 4, 3, 2, 1 }; // Worst
	// // int arr[] = { 1, 2, 3, 4, 5, 6 }; // Best
	// int n = sizeof(arr) / sizeof(arr[0]);

	// // Insertion Sort
	// {
	// 	insertionSort(arr, static_cast<size_t>(n));
	// 	std::cout << std::boolalpha << "CheckSorted(arr, n) : " << CheckSorted(arr, n) << std::endl;
	// }

	// # Best
	// 바깥쪽 루프만 돈다
	// # Stability
	// 쉬프트하며 복사하므로 같은 크기의 키값에 대해서 정렬이후에 순서가 바뀌지 않는다
	// 그러므로 stable하다
}