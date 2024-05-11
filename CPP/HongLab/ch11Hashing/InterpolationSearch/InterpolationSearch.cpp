#include <iostream>
#include <cmath>

using namespace std;

int rec_count = 0;

/** 접근, 결과적으로 동작하지 않음
 * 값이 정렬되어 있고 균질하게 분포하고 있다는 가정하에 사용
 * 
 * 1~100까지 값이 1씩 차이나며 뺴곡하게 차있다면 
 * 33일 찾을 때는 
 * 
 * 찾는 값이 40이고, low는 26, high는 50 일 때
 * 
 * target - arr[low] / arr[high] - arr[low]
 * 39 / 99 => 13/33 
 * pos = 40이라고 가정
 * 40이라는 값은 39에 위치함
 * 
 * 0, 39
 * 40 - 1 / 39 => 1
*/
/** 강의 공식
 * # 비례식
 * (arr[high] - arr[low]):(target - arr[low]) = (high - low):(pos - low)
 * 
 * # 전개
 * 1. (target_pos - low_pos) / (high_pos - low_pos)
 * 2. (arr[target_pos] - arr[low_pos]) / (arr[high_pos] - arr[low_pos])
 * 1. == 2.
 * target_pos = (arr[target_pos] - arr[low_pos]) /  (arr[high_pos] - arr[low_pos]) * (high_pos - low_pos)
*/
int InterpolationSearch(int arr[], int low_pos, int high_pos, int target)
{
	rec_count++;

	// arr[low_pos], arr[high_pos], target 
	if (low_pos <= high_pos && target >= arr[low_pos] && target <= arr[high_pos])
	{
		// std::cout << "high_pos : " << high_pos << std::endl;
		// std::cout << "low_pos : " << low_pos << std::endl;
		// std::cout << "arr[high_pos] : " << arr[high_pos] << std::endl;
		// std::cout << "arr[low_pos] : " << arr[low_pos] << std::endl;
		// std::cout << "target : " << target << std::endl;
		// std::cout << "(arr[high_pos] - arr[low_pos]) : " << (double)(arr[high_pos] - arr[low_pos]) << std::endl;
		const double ratio = ((target - arr[low_pos])) / (double)(arr[high_pos] - arr[low_pos]);
		// std::cout.precision(4);
		// std::cout << "ratio : " << ratio << std::endl;
		// const int pos = std::round(ratio);
		// std::cout << "scope : " << scope << std::endl;
		const int target_pos = ((high_pos - low_pos) * ratio) + low_pos;// 이진 탐색 (중간)
		// std::cout << "pos : " << target_pos << std::endl;

		// TODO: int target_pos = 보간 탐색으로 수정

		if (arr[target_pos] == target)
			return target_pos;

		if (arr[target_pos] < target)
			return InterpolationSearch(arr, target_pos + 1, high_pos, target);

		if (arr[target_pos] > target)
			return InterpolationSearch(arr, low_pos, target_pos - 1, target);
	}

	return -1;
}

// https://www.geeksforgeeks.org/interpolation-search/
int main()
{
	int arr[] = { 10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47 };
	int n = sizeof(arr) / sizeof(arr[0]);

	for (auto x : { 10, 18, 33, 47, -1, 99 })
	{
		rec_count = 0;

		int index = InterpolationSearch(arr, 0, n - 1, x);

		if (index != -1)
			cout << x << " was found at index " << index << endl;
		else
			cout << x << " was not found." << endl;

		cout << "rec_count = " << rec_count << endl;
		cout << endl;
	}

	return 0;
}