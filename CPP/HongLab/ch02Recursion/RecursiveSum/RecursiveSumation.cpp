#include <iostream>
#include <cassert>
#include <algorithm> // swap

using namespace std;

int Sum(int* arr, int n)
{
	int sum = 0;

	for (int i = 0; i < n; i++)
		sum += arr[i];

	return sum;
}

/**
 * # 나의 생각
 * 합의 결과는 두개의 값의 합 연산으로 이루어진다.
 * 두개의 값이 포인트 
 * 누적 시킬값과 현재 더해질 값의 연산으로 바꾼다.
 * index가 0보다 작아지면 재귀 호출을 종료(return)하게하거나
 * 배열 길이 이상이 되면 종료(return)되게 한다.
 * 
 * # 강의에서 주어진 함수 조건과 설명
 * 
 * 부분 집합의 합으로 구성하는 것 같다.
 * 재귀적인 방식
 * 귀납법
 * 전체의 총합은 n-1개 총합과 n의 합으로 이루어짐
 * n-1개의 총합은 n-2개의 총합과 n-1의 합으로 이루어진
 * ...
 * 3개의 총합은 2개의 총합과 나머지 1개 요소의 합으로 이루어짐
 * 2개의 총합은 1개의 요소와 나머지 1개 요소의 합으로 이루어짐
*/

int RecurSum(int* arr, int n)
{
	/* 힌트: 역순으로 더하기 (매개변수에 시작 인덱스를 추가하지 않아도 되기 때문)
	  (1 + 2 + ... 8 + 9 + 10)
	= (1 + 2 + ... 8 + 9) + 10
	= ((1 + 2 + ... 8) + 9) + 10
	= ...
	*/
	// <- TODO: 
	// My version
	if (n == 1)
		return arr[0];
	// RecurSum(arr, n - 1) + arr[n - 1]; // 함수의 return이 void가 아니므로 무조건 return이 있어야한다
	return RecurSum(arr, n - 1) + arr[n - 1];

}

/** Lecture example00
 * n이 0 이하일때로 되어있기에 혹시나 0보다 작아지는 경우를 버커할 수 있어서
 * 좀더 안전한 코드가 되지 않을까 싶다.
 * 
*/
// int RecurSum(int* arr, int n)
// {
// 	if (n <= 0)
// 	{
// 		return 0;
// 	}
// 	{
// 		return RecurSum(arr, n - 1) + arr[n - 1];
// 	}
// }


/** Lecture example01 Horowitz 
*/
// float rsum(float list[], int n)
// {
// 	if (n) return rsum(list, n-1) + list[n-1];
// 	return 0;
// }


int main()
{
	// Sum vs RecurSum

	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << Sum(arr, n) << endl;
	cout << RecurSum(arr, n) << endl;

	return 0;
}