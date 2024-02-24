#include <iostream>

void swap(int &a, int &b) {
  int temp;

  temp = a;
  a = b;
  b = temp;
}

/** three differnt case
 * call by value
 * call by reference
 * call by pointer
*/
void MySwapValue(int i, int j)
{
  int temp;

  temp = i;
  i = j;
  j = temp;
}

void MySwapPtr(int* i, int* j)
{
  int temp;

  temp = *i;
  *i = *j;
  *j = temp;
}

void MySwapRef(int& i, int& j)
{
  int temp;

  temp = i;
  i = j;
  j = temp;
}

template <typename T>
void doSwapTest(T& a, T& b, void (*swapFn)(T&, T&))
{
  std::cout << a << " " << b << std::endl;
  swapFn(a, b);
  std::cout << a << " " << b << std::endl;
}

template <typename T>
void doSwapTest(T* a, T* b, void (*swapFn)(T*, T*))
{
  std::cout << *a << " " << *b << std::endl;
  swapFn(a, b);
  std::cout << *a << " " << *b << std::endl;
}

template <typename T>
void doSwapTest(T a, T b, void (*swapFn)(T, T))
{
  std::cout << a << " " << b << std::endl;
  swapFn(a, b);
  std::cout << a << " " << b << std::endl;
}

void compareTwoValue(int a, int b)
{
  std::string compareResult = "false";
  if (b >= a)
    compareResult = "true";
  std::cout << a << " " << b << " " << compareResult << std::endl;
}

int main() {
  int a = 3;
  int b = 2;

  // swap test
  doSwapTest(a, b, MySwapRef);
  std::cout<< std::endl;
  doSwapTest(&a, &b, MySwapPtr);
  std::cout<< std::endl;
  doSwapTest(a, b, MySwapValue);

  /** Sort
   * 배열 원소 2개만 있을 때의 정렬
  */
  {
    std::cout << "### Sort ###"<< std::endl;
    int arr[] = { 3, 2 };
    std::cout << "Before sort : " << arr[0] << " " << arr[1] << std::endl;

    // TODO: ascending sort
    if (arr[0] > arr[1])
      swap(arr[0], arr[1]);

    std::cout << "After sort : " << arr[0] << " " << arr[1] << std::endl;
  }

  // 값과 상관 없이 항상 작은 값이 먼저 출력되게 하려면?
  /** 주어진 배열이 정렬되어있는지 확인하는 로직 
   * 00. 간단한 비교결과 출력
   * 왼쪽 값이 오른쪽 값보다 작거나 같으면 true를 출력
   * e.g) 
   *    0 1 true
   *    1 0 false
   *    2 0 false
   *    ...
   *    0 1 true
   *    1 1 true
   *    2 1 false
   *    3 1 false
   *    4 1 false
  */
  {
    std::cout<<std::endl;
    std::cout << "### Compare sorted result ###"<< std::endl;
    // 인자 한개만 넣어보는 경우 
    compareTwoValue(0, 0);
    // std::cout << std::endl;

    // 첫 번째 인자를 배열로 주는 경우 
    int arr[2] = {42,21};
    for (size_t idx = 0; idx < (sizeof(arr) / sizeof(arr[0])); idx++)
    {
      compareTwoValue(arr[idx], 0);
    }
    std::cout << std::endl;
  }

  return 0;
}

