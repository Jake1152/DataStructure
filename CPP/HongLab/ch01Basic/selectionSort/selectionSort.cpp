#include <iostream>
#include <cassert>
#include <limits>
#include <fstream>

struct Element
{
	int key;
	char value;
};

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

template <typename T>
void Print(T* arr, size_t size)
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

/**
 * @see https://stackoverflow.com/questions/12073689/template-function-specialization-for-integer-types 
 * 
 * 1. Use SFINAE
 * 2. C++ 17
*/
// template<typename T>
// typename std::enable_if<std::is_integral<T>::value>::type f(T t)
// {}


/**
 * 테스트하는 방법
*/
// For all types except integral types:
// template<typename T,
// typename std::enable_if<!std::is_integral<T>::value>::type> 
// T GetMinValueOfArr(T t)
// {
//   std::cerr << "Type is not integral" << std::endl;
//   return -1;
// }

// Except integral, !std::is_integral<T>
// template<typename T, typename = typename std::enable_if<!std::is_integral<T>::value>::type>
// T GetMinValueOfArr(T *arr, size_t size)
// {
//   // throw -1;
//   // try
//   // {

//   // }
//   // catch (std::string error_message)
//   // {
//   //   std::cout << error_message << std::endl;
//   // }
//   std::cerror << "Type is not integral" << std::endl;
//   return -1;
// }


/**
 * for (auto num : arr)
 * 혹은 for (T num : arr)
 * 위와 같은 경우로 반복문 쓰는 경우 원인 파악이 어려운 에러 발생 
 * selectionSort.cpp:125:3: error: ‘begin’ was not declared in this scope; did you mean ‘std::begin’?
*/
template<typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
T GetMinValueOfArr(T *arr, size_t size)
{
  T min_number= 0;

  for (size_t idx = 0; idx < size; idx++)
  // for (auto num : arr)
  {
    int num = arr[idx];
    if (min_number > num)
      min_number = num;
  }
  return min_number;
}

template<typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
size_t GetMinIndexOfArr(T *arr, size_t size)
{
  size_t min_number_idx = 0;

  for (size_t idx = 0; idx < size; idx++)
  {
    int num = arr[idx];
    if (arr[min_number_idx] > num)
      min_number_idx = idx;
  }
  return min_number_idx;
}

/**
 * 정렬되지 않은 범위에서 가장 작은 값을 찾아서 
 * 정렬되지 않은 범에서 가장 왼쪽에 있는 값과 swap한다.
 * 
 * 정렬 되지 않은 배열에서 가장 작은 값의 index를 가져오다보니 
 * index를 토대로 swap할 때 실제 array의 길이와 min값을 가져왔던 array가 다르므로 문제 발생
 * 실제 array와 정렬되지 않은 범위에서 찾은 min값의 index가 일치하도록
 * be_sorted_area_last_index + min_number_index 연산을 한다
 * 
*/
void SelectionSort(int *arr, size_t size) {
  // find min
  // const int     min_value = GetMinValueOfArr(arr, size);
  //   size_t  min_number_idx = GetMinIndexOfArr(arr, size);

  assert(size > 0); // 1 이상
  for (size_t be_sorted_area_last_index = 0; be_sorted_area_last_index < size - 1; be_sorted_area_last_index++)
  {
    size_t min_number_index_of_unsorted_area = GetMinIndexOfArr(
                                              arr + be_sorted_area_last_index, \
                                              size - (be_sorted_area_last_index));

    // std::cout << "min_number_index_of_unsorted_area : " << min_number_index_of_unsorted_area << ", the value : " << arr[min_number_index_of_unsorted_area] << std::endl;
    // std::cout << "be_sorted_area_last_index : " << be_sorted_area_last_index << std::endl;
    if (arr[be_sorted_area_last_index] == arr[min_number_index_of_unsorted_area + be_sorted_area_last_index])
      continue;
    std::swap(arr[be_sorted_area_last_index], arr[min_number_index_of_unsorted_area + be_sorted_area_last_index]);
  }
}


/**
 * 3개의 인자가 있는 배열을 넘겨받아서 화면에 출력 
 * 
*/
int main() {
  // 3개 정렬
  /*
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
  */
  // 가장 작은 수 찾기
  {

    int arr[] = { 42, 233 ,12, 45, 85 , std::numeric_limits<int>::min(), 44, 42, 34, 77};
    int size = sizeof(arr) / sizeof(arr[0]);

    assert(size > 0); // s

    // TODO 
    long int min_number = std::numeric_limits<long int>::max();
    for (auto num : arr)
      if (static_cast<long int>(min_number) > static_cast<long int>(num))
        min_number = num;
    // Print(arr, size);
    // std::cout  << "Minimum number is " << min_number << std::endl;
  }

  // 가장 작은 수의 인덱스 찾기
  {
    long arr[] = { 42, 45, 85 , std::numeric_limits<long int>::min(), 44, 42, 34, 77};
    int size = sizeof(arr) / sizeof(arr[0]);

    assert(size > 0); // s

    // TODO 
    long int min_number_idx = 0;
    for (int idx = 0; idx < size; idx++)
    {
      int num = arr[idx];
      if (arr[min_number_idx] > num)
        min_number_idx = idx;
    }
    // std::cout << std::endl;
    // std::cout  << "# Minimum number index is " << min_number_idx << ", Minimum number is " << arr[min_number_idx] << std::endl;
  }

  // selection sort
  {
    int arr[] = { 42, 45, 85 , std::numeric_limits<int>::min(), 44, 42, 34, 77};
    int size = sizeof(arr) / sizeof(arr[0]);

    Print(arr, size);
    SelectionSort(arr, size);
    Print(arr, size);

    // double double_arr[] = { 3.14, 5.24};
    // GetMinValueOfArr(double_arr, size);
  }

  return 0;
}

