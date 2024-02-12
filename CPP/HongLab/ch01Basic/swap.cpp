#include <iostream>

void swap(int &a, int &b) {
  int temp;

  temp = a;
  a = b;
  b = temp;
}

typedef struct be_swapped_numbers_s
{
  int a;
  int b;
}		be_swapped_numbers_t

// lecture cases
int MySwapValue(int i, int j)
{
  be_swapped_numbers_t	be_swapped_numbers;

  be_swapped_numbers.a = j;
  be_swappped_numbers.b = i;
  
  return be_swapped_numbers;
  // TOOD
  // return ?;
}
/* */

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


int main() {
  int a = 3;
  int b = 2;
  //void (*fnPtr)(int&, int&) = MySwapRef;

  doSwapTest(a, b, MySwapRef);
  doSwapTest(&a, &b, MySwapPtr);
  //fnPtr(a, b);
  /*
  std::cout << a << " " << b << std::endl;
  swapFn(a, b, fnPtr(a, b));
  std::cout << a << " " << b << std::endl;
  */
  return 0;
}

