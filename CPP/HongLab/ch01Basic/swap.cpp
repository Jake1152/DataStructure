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
  std::cout << "### Sort ###"<< std::endl;
  {
    int arr[] = { 3, 2 };
    std::cout << "Before sort : " << arr[0] << " " << arr[1] << std::endl;

    // TODO: ascending sort
    if (arr[0] > arr[1])
      swap(arr[0], arr[1]);

    std::cout << "After sort : " << arr[0] << " " << arr[1] << std::endl;
  }

  return 0;
}

