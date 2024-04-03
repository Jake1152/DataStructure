#include <iostream>

#include "../shared/Stack.h"

using namespace std;

Stack<char> tower[3];

void PrintTowers()
{
	cout << "# Towers" << endl;
	cout << "0: ";
	tower[0].Print();
	cout << "1: ";
	tower[1].Print();
	cout << "2: ";
	tower[2].Print();
}

// 실제로 디스크를 움직여서 스택들을 업데이트
void MoveDisk(int from, int to)
{
	if (tower[from].IsEmpty())
	{
		std::cout << "I can not move it" << std::endl;
		std::cout << "Tower " << from << " is empty." << std::endl;
	}
	const auto disk = tower[from].Top();
	if (!tower[to].IsEmpty() && tower[to].Top() < disk)
	{
		std::cout << "Cannot place " << disk << " on " << tower[to].Top() << std::endl;
		exit(0);
	}
	tower[from].Pop();
	tower[to].Push(disk);

	std::cout << "Move disk " << disk << " from " << from << " to " << to << std::endl;
	PrintTowers();
}

void RecurMoveDisks(int n, int from, int temp, int to)
{
	if (n <= 0)
		return ;
	// TODO:
	// n-1개를 temp로 옮긴다
	RecurMoveDisks(n - 1, from, to, temp);
	// n번쨰 디스크를 목적지로 옮긴다.
	// std::cout << "n : " << n << std::endl;
	MoveDisk(from, to);
	// n-1개를 to로 옮긴다
	RecurMoveDisks(n - 1, temp, from, to);
	// MoveDisk(from, to)
	// 재귀적으로 알아서 옮겨짐
}

int main()
{
	int num_disks = 12;

	for (int i = num_disks - 1; i >= 0; i--)
		tower[0].Push('A' + i);

	PrintTowers();

	// MoveDisk(0, 2); // <- 디스크 하나만 움직이는 함수 tower 0 -> tower 2

	RecurMoveDisks(num_disks, 0, 1, 2);
	std::cout << "\n\n#Done"<< std::endl;
	PrintTowers();

	return 0;
}