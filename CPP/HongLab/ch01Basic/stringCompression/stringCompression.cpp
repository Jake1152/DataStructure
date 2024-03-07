#include <iostream>
#include <cassert>

using namespace std;

void InsertionSort(char* arr, int n)
{
	int i, key, j;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key) // <- while 사용
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}

		arr[j + 1] = key;
	}
}

int Count(char* arr, int n, char x)
{
	int count = 0;
	for (int i = 0; i < n; i++) // start index 사용
	{
		if (arr[i] == x)
			count++;
	}

	return count;
}

int main()
{
	// 문제
	// - 어떤 알파벳에 몇 번 나오는지로 출력
	// - 예시) aaabbccdddeeeff -> a3b2c2d3e3f2
	// - 알파벳은 총 26 글자	

	// cout << int('a') << " " << int('z') << endl; // 97 122

	// char arr[] = "ababcdfdceeefda";
	// char arr[] = "a";
	char arr[] = "ababcdfdceeedag";
	int arr_size = sizeof(arr) - 1; // 마지막 안보이는 '\0' 제외

	// 글자가 하나이상이라고 가정
	// 글자가 없으면 if로 아예 수행을 안하도록 처리 가능
	assert(arr_size >= 1);

	cout << arr << endl;

	// 풀이 1. 모든 알파벳에 대해서 Count()
	// 힌트: 소문자 알파벳 'a'~'z'는 int로는 97~122에 대응
	// 단점: 없는 알파벳도 세야 한다.

	// 표를 사용할 수도 있고 사용하지 않을 수도 있음

	// 1-1 table사용하는 방법
	std::cout << "# Way1-1" << std::endl;
	int table[26] = { 0 }; // 모든 값을 0으로 초기화

	int iter = arr_size;
	for (int idx = 0; idx < 26; idx++)
	{
		// 힌트: char(idx + 97)
		char cur_char = 'a' + idx;

		// 표를 만들고 나중에 몰아서 출력하는 방법
		// table[idx] = ...
		table[idx] = Count(arr, arr_size, cur_char);

		// 표를 만들지 않고 직접 출력하는 방법
		int cur_char_count = Count(arr, arr_size, cur_char);
		std::cout << cur_char << cur_char_count  << std::flush;
		iter -= cur_char_count;
		if (iter <= 0)
			break ;
		// ...
	}
	cout << endl;
	// 출력 table 사용하는 방식
	size_t	table_size = sizeof(table) / sizeof(table[0]);
	// std::cout << "table_size : " << table_size << std::endl;
	for (int idx = 0; idx < table_size; idx++)
		if (table[idx])
			std::cout << static_cast<char>('a' + idx) << table[idx] << std::flush;

	cout << endl << endl;

	// 1-2 table없이 처리 
	/**
	 * 문제 이해 잘못함
	 * 출력은 배열에 있던 문자열의 문자 순서가 아니라
	 * 알파벳 순서이어야한다.
	*/
	// int iter0 = arr_size;
	// int idx = 0;
	// std::cout << "# Way1-2" << std::endl;
	// while (iter0)
	// {
	// 	int char_count = Count(arr + idx, arr_size - idx, arr[idx]);
	// 	std::cout << arr[iter0] << char_count << std::flush;
	// 	idx += char_count;
	// 	iter0 -= char_count;
	// }
	// cout << endl << endl;
	// 풀이 2. 정렬 후 찾기
	// 여기서는 별도의 문자열을 만드는 것이 아니라 출력이 목표
	// Table도 만들지 않음

	InsertionSort(arr, arr_size);

	cout << arr << endl;

	char c = arr[0];
	int count = 1;

	cout << c;

	/**
	 * 굳이 조건문을 더 추가할 필요 없이 일치하는 문자이면 count만 증가시키면 되며
	 * 다른 문자가 나오게 되면 이전까지 담아둔 값을 출력하고 
	 * count와 출력 형식을 새로 들어온 문자에 맞게 초기화하여 반복문을 진행한다
	*/
	for (int i = 1; i < arr_size; i++)
	{
		if (arr[i] == c)
		{
			// TODO: ...
			count++;
		}
		else
		{
			// TODO: ...
			std::cout << count  << arr[i] << std::flush;
			c = arr[i];
			count = 1;
		}
	}

	cout << count << endl; // 마지막 count 출력

	return 0;
}