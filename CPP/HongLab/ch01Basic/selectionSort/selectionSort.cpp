#include <iostream>

void swap(int &a, int &b) {
  int temp;

  temp = a;
  a = b;
  b = temp;
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

