#include <iostream>
#include <cassert>
#include <limits>

void swap(int &a, int &b) {
  int temp;

  temp = a;
  a = b;
  b = temp;
}

/**
 * ASC
 * 특정 정렬방법을 쓰지 않고 
 * 3개의 값만 들어온다는 점을 감안해서 만들어본다
 * 값이 같은 경우가 있어서 min, max를 이용한 방식으로는 답이 안나올 수 있다.
 * 
 * 왼쪽이 오른쪽보다 작아야한다.
 * # Case
 * 4 2 1
 *   2 4 1
 *   2 1 4
 * 
 *   1 2 4
 * 
*/
void MySort(int *arr, size_t size) 
{
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
        std::swap(arr[j], arr[j + 1]);
    }
}

/**
 * CPP function naming convention은 Pascal
 * 
 * ref: https://www.geeksforgeeks.org/naming-convention-in-c/
*/
bool  CheckSorted(int *arr, size_t size)
{
  for (int idx = 0; idx < size - 1; idx++)
    if (arr[idx] > arr[idx + 1])
      return false;
  return true;
}

/**
 * 3개의 인자가 있는 배열을 넘겨받아서 화면에 출력 
 * 
*/
int main() {
  // 3개 정렬
  {
    const int size = 3;
    for (int k = 0; k < size; k++)
      for (int j = 0; j < size; j++)
        for (int i = 0; i < size; i++)
        {
          // int arr[size] = { i, j, k, k + 1, k + 2};
          int arr[size] = { i, j, k };
          int arr_size = sizeof(arr) / sizeof(arr[0]);

          for (int e = 0; e < arr_size; e++)
          {
            std::cout << arr[e] << " " << std::flush;
          }

          std::cout << " -> " << std::flush;

          // TODO: 정렬 해보기
          MySort(arr, arr_size);

          for (int e = 0; e < arr_size; e++)
          {
            std::cout << arr[e] << " " << std::flush;
          }

          std::cout << std::boolalpha;
          std::cout << CheckSorted(arr, arr_size);
          std::cout << std::endl;
        }
  }

  // 가장 작은 수 찾기
  {
    long arr[] = { 42, 233 ,12, 45, 85 , std::numeric_limits<long int>::min(), 44, 42, 34, 77};
    int size = sizeof(arr) / sizeof(arr[0]);

    assert(size > 0); // s

    // TODO 
    long int min_number = std::numeric_limits<long int>::max();
    for (auto num : arr)
      if (min_number > num)
        min_number = num;

    std::cout  << "Minimum number is " << min_number << std::endl;
  }

  return 0;
}

