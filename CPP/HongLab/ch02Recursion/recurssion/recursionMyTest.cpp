#include <iostream>

// using namespace std;

int funReturnNum(int num)
{
  if (num == 0)
    return num;
  funReturnNum(num - 1); 
  std::cout << "Thst is funReturnNum(" << num << ")" << std::endl;
}

int main() {
  std::cout << "funReturnNum(5) : " << funReturnNum(5) << std::endl;

  return 0;
}