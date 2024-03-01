#include <iostream>


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
	// int arr[] = { 5, 1, 4, 2, 8 }; // 위키피디아 예시
	int arr[] = { 5, 4, 3, 2, 1 }; // Worst Case
	// int arr[] = { 1, 2, 3, 5, 4 }; // Best Case
	int n = sizeof(arr) / sizeof(arr[0]);

	Print(arr, n);
  std::cout << std::endl;

	// Bubble Sort
	{
		// 힌트: Print()로 진행상황 확인하면서 구현
		// 힌트: 2중 for 루프
		// 힌트: for 루프 범위 주의
    for (int i = 0; i < n - 1; i++)
    {
      Print(arr, n);
      for (int j = 0; j < n - i - 1; j++)
      {
        if (arr[j] > arr[j + 1])
        {
          std::cout << "  -> swap() " << arr[j] << "," << arr[j + 1] << std::endl;
          std::swap(arr[j], arr[j + 1]);
        }
        std::cout << "  ";
        Print(arr, n);
      }
    }
    
	}
  std::cout << std::endl;
  std::cout << std::boolalpha << "CheckSorted(arr, n) : " << CheckSorted(arr, n) << std::endl;
  Print(arr, n);

	// Best case
	// Stability
}