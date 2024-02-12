#include <iostream>

void swap(int &a, int &b) {
  int temp;

  temp = a;
  a = b;
  b = temp;
}

/*
// lecture cases
int MySwapValue(int i, int j)
{
  // TOOD
  // return ?;
  return 0;
}
*/

void MySwapPtr(int* i, int* j)
{
  int *temp;

  temp = i;
  i = j;
  j = temp;
}

void MySwapRef(int& i, int& j)
{
  int temp;

  temp = i;
  i = j;
  j = temp;
}

template <typename T>
void doSwapTest(int& a, int& b, void (*swapFn)(T&, T&))
{
  std::cout << a << " " << b << std::endl;
  swapFn(a, b);
  std::cout << a << " " << b << std::endl;
}

int main() {
  int a = 3;
  int b = 2;
  //void (*fnPtr)(int&, int&) = MySwapRef;

  doSwapTest(a, b, MySwapRef);
  //fnPtr(a, b);
  /*
  std::cout << a << " " << b << std::endl;
  swapFn(a, b, fnPtr(a, b));
  std::cout << a << " " << b << std::endl;
  */
  return 0;
}

