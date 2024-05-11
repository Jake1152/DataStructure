#include <iostream>

using namespace std;

int SequentialSearch(int arr[], int start, int stop, int target)
{
	for (int i = start; i < stop; i++)
	{
		if (arr[i] == target)
			return i;
	}

	return -1;
}

int main()
{
	int arr[] = { 1, 2, 8, 13, 22, 45, 55, 75, 88 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);

	// Mine TODO: 기존 테이블로부터 인덱스 테이블을 하드코딩이 아닌 로직을 이용하여 구성
	int keys[] = { 1, 13, 55 };
	int kn = sizeof(keys) / sizeof(keys[0]);

	int indices[] = { 0, 3, 6, arr_size }; // 마지막에 n 하나 더 추가
	int target_idx = -1;

	for (int target : {1, 2, 8, 13, 22, 45, 55, 75, 88, 99, -1, 47, 101, 1000, 7, 10, 50, 60 })
	{
		if (target < arr[0] || target > arr[arr_size - 1])
			cout << target << " was not found" << endl;
		else
		{
			// TODO: 
			// 1. keys에서 먼저 적절한 위치를 찾는다.
			size_t index_table_idx = 0;
			while (keys[index_table_idx] < target && \
					((index_table_idx + 1 < kn) && keys[index_table_idx + 1] < target))
				index_table_idx++;
			std::cout << "index_table_idx : " << index_table_idx << std::endl;
			// 2. keys에서 찾은 적절한 위치 index를 indices에 index로 넣는다.
			const size_t arr_idx = indices[index_table_idx];
			std::cout << "arr_idx : " << arr_idx << std::endl;
			// 3. indicices[index]로부터 얻은 적절한 arr배열에서의 index를 이용하여 index부터 순차탐색한다.
			target_idx = SequentialSearch(arr, arr_idx, arr_size, target);
		}
		std::cout << "# target : " << target << ",\ttarget_idx : " << target_idx << std::endl << std::endl;
	}


	return 0;
}