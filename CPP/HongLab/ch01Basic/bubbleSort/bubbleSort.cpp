#include <iostream>

struct Element
{
	int key;
	char value;
};

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
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

void Print(Element* arr, int size)
{
	for (int idx = 0; idx < size; idx++)
		std::cout << arr[idx].key << " ";
	std::cout << std::endl;

	for (int idx = 0; idx < size; idx++)
		std::cout << arr[idx].value << " ";
	std::cout << std::endl;
}

void BubbleSort(int *arr, size_t n)
{
  for (int i = 0; i < n - 1; i++)
  {
    // Print(arr, n);
    for (int j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
        std::swap(arr[j], arr[j + 1]);
      // std::cout << "  ";
      // Print(arr, n);
    }
  }
}

int main()
{
	int arr[] = { 5, 1, 4, 2, 8 }; // 위키피디아 예시
	// int arr[] = { 5, 4, 3, 2, 1 }; // Worst Case
	// int arr[] = { 1, 2, 3, 5, 4 }; // Best Case
	int n = sizeof(arr) / sizeof(arr[0]);

	Print(arr, n);
  std::cout << std::endl;

	// Bubble Sort
	// {
	// 	// 힌트: Print()로 진행상황 확인하면서 구현
	// 	// 힌트: 2중 for 루프
	// 	// 힌트: for 루프 범위 주의
  //   for (int i = 0; i < n - 1; i++)
  //   {
  //     Print(arr, n);
  //     for (int j = 0; j < n - i - 1; j++)
  //     {
  //       if (arr[j] > arr[j + 1])
  //       {
  //         std::cout << "  -> swap() " << arr[j] << "," << arr[j + 1] << std::endl;
  //         std::swap(arr[j], arr[j + 1]);
  //       }
  //       std::cout << "  ";
  //       Print(arr, n);
  //     }
  //   }
	// }

	// Best case
	// {
	// 	// 힌트: Print()로 진행상황 확인하면서 구현
	// 	// 힌트: 2중 for 루프
	// 	// 힌트: for 루프 범위 주의
  //   for (int i = 0; i < n - 1; i++)
  //   {
  //     Print(arr, n);
  //     // if (CheckSorted(arr, n))
  //     //     break ;
  //     bool swapped = false;
  //     for (int j = 0; j < n - i - 1; j++)
  //     {
  //       if (arr[j] > arr[j + 1])
  //       {
  //         std::cout << "  -> swap() " << arr[j] << "," << arr[j + 1] << std::endl;
  //         std::swap(arr[j], arr[j + 1]);
  //         swapped = true;
  //       }
  //       std::cout << "  ";
  //       Print(arr, n);
  //     }
  //     if (swapped == false)
  //       break ;
  //   }
	// }
  // std::cout << std::endl;
  // std::cout << std::boolalpha << "CheckSorted(arr, n) : " << CheckSorted(arr, n) << std::endl;
  // Print(arr, n);

	// Stability
  /**
   * bubble sort에서는 키값이 같은 경우 정렬 이후에 둘 사이의 순서가 바뀌지 않는다.
  */
 	// 안정성 확인(unstable)
	{
		Element arr[] = { {2, 'a'}, {2, 'b'}, {1, 'c'} };
		int n = sizeof(arr) / sizeof(arr[0]);

		Print(arr, n); // arr이 Element의 배열
		// TODO: key만 가지고 비교
    for (int i = 0; i < n - 1; i++)
    {
      Print(arr, n);
      // if (CheckSorted(arr, n))
      //     break ;
      bool swapped = false;
      for (int j = 0; j < n - i - 1; j++)
      {
        if (arr[j].key > arr[j + 1].key)
        {
          std::cout << "  -> swap() " << arr[j].key << "," << arr[j + 1].key << std::endl;
          std::swap(arr[j], arr[j + 1]);
          swapped = true;
        }
        std::cout << "  ";
        Print(arr, n);
      }
      if (swapped == false)
        break ;
    }
    std::cout << std::endl;
    // std::cout << std::boolalpha << "CheckSorted(arr, n) : " << CheckSorted(arr, n) << std::endl;
    Print(arr, n);
	}
}