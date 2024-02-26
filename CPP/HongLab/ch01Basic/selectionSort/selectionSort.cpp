#include <iostream>

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
*/
void MySort(int *arr, size_t size) 
{
  /**
   *  1. a b c 
   * 왼쪽이 오른쪽보다 작아야한다.
  */
  int max = arr[0];
  int min = arr[0];
  int mid = arr[0];
  if (size == 3) {
    for (int idx = 1; idx < size; idx++)
    {
      if (arr[idx] > max)
        max = arr[idx];
      if (arr[idx] < min)
        min = arr[idx];
    }
    for (int idx = 1; idx < size; idx++)
    {
      if (arr[idx] >= min && arr[idx] <= max)
        mid = arr[idx];
    }
    arr[0] = min;
    arr[1] = mid;
    arr[2] = max;
  } else {
    // other sort way
    return ;
  }
}

/**
 * CPP function naming convention은 Pascal
 * 
 * ref: https://www.geeksforgeeks.org/naming-convention-in-c/
*/
bool  CheckSorted(int *arr, size_t size)
{
  return false;
}

/**
 * 3개의 인자가 있는 배열을 넘겨받아서 화면에 출력 
 * 
*/
int main() {
  // 3개 정렬
  {
    for (int k = 0; k < 3; k++)
      for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
        {
          int arr[3] = { i, j, k};
          int arr_size = sizeof(arr) / sizeof(arr[0]);

          for (int e = 0; e < arr_size; e++)
          {
            std::cout << arr[e] << " " << std::flush;
          }

          std::cout << " -> " << std::flush;

          // TODO: 정렬 해보기
          MySort(arr, 3);

          for (int e = 0; e < arr_size; e++)
          {
            std::cout << arr[e] << " " << std::flush;
          }

          std::cout << std::boolalpha;
          std::cout << CheckSorted(arr, arr_size);
          std::cout << std::endl;
        }
  }

  return 0;
}

