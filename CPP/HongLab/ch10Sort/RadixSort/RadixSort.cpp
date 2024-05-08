#include <iostream>
#include <cmath>
#include "../shared/Queue.h"

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

int GetMax(int arr[], int n)
{
	assert(arr);

	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

int main()
{
	int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
	int n = sizeof(arr) / sizeof(arr[0]);

	const int base_size = 10;

	Print(arr, n);

	Queue<int> queues[base_size];

	int max_val = GetMax(arr, n); // 가장 큰 자리수를 찾기 위해서

	for (int exp = 1; max_val / exp > 0; exp *= base_size)
	{
		// TODO:
		// for (int element: arr)
		// Print(arr, n);
		for (int idx = 0; idx < n; idx++)
		{
			int element = arr[idx];
			// 170 -> 0
			// 421 -> 1
			// modular 연산 사용

			int divisor = static_cast<int>(base_size * exp);
			// std::cout << "### element : " <<  element << std::endl;
			// std::cout << "# divisor : " << divisor << std::endl;
			int queue_idx = static_cast<int>(element % divisor) / exp;
			// std::cout << "# queue_idx : " << queue_idx << std::endl;
			queues[queue_idx].Enqueue(element);

		}

		int idx = 0;
		// queue_idx < base_size;  대신 queue_idx < n;으로 해서 생겼던 문제
		for (int queue_idx = 0; queue_idx < base_size; queue_idx++)
		{
			while (!(queues[queue_idx].IsEmpty()))
			{
				int current_val = queues[queue_idx].Front();
				// std::cout << "current_val : " << current_val << std::endl;
				queues[queue_idx].Dequeue();
				arr[idx] = current_val;
				idx++;
			}
		}

		Print(arr, n);
	}
	

	CheckSorted(arr, n);

	return 0;
}