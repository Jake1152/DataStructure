#include <iostream>
#include <cassert>
#include <algorithm> // swap
#include <iomanip> // setw

using namespace std;

long long Fibonacci(long long n)
{
	if (n == 0)
		return 0; // F0 = 0 
	else if (n == 1)
		return 1; // F1 = 1
	else
	{

		// TODO:
		long long iter = 2;
		// while(n)
		long long secondFromRear = 0;
		long long firstFromRear = 1;
		for (iter; iter <= n; iter++)
		{
			long long tmp = firstFromRear;
			firstFromRear = firstFromRear + secondFromRear;
			secondFromRear = tmp; 
		}

		return firstFromRear;
	}
}

long long RecurFibonacci(long long n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	return (RecurFibonacci(n - 1) + RecurFibonacci(n - 2));	
}

int main()
{
	// Input      : 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
	// Fibonnacci : 0   1   1   2   3   5   8  13  21  34  55  89 144 233 377
	// Fibonnacci : 0   1   1   2   3   5   8  13  21  34  55  89 144 233 377

	cout << "Input     : ";
	for (long long i = 0; i < 800; i++)
		cout << i << " ";
	cout << endl;

	// Fibonnacci
	cout << "Fibonnacci Repeat: ";
	for (long long i = 0; i < 800; i++)
		cout << Fibonacci(i) << " ";
	cout << endl;

	// cout << "Fibonnacci: ";
	// for (long long i = 0; i < 800; i++)
	// 	cout << RecurFibonacci(i) << " ";
	// cout << endl;

	return 0;
}