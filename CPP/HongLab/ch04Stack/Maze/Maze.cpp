#include <iostream>

#include "../shared/Stack.h"

using namespace std;

constexpr int kNumRows = 10;
constexpr int kNumCols = 9;

char maze[kNumRows][kNumCols] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', 'S', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '0', '1', '0', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '1', '1'},
	{'1', '1', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', 'G', '1'}, // <- 'G'를 만나면 종료
	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

void PrintMaze()
{
	for (int j = 0; j < kNumRows; j++)
	{
		for (int i = 0; i < kNumCols; i++)
			cout << maze[j][i] << " ";
		cout << endl;
	}
}

struct Pos
{
	int row;
	int col;

	// 디버깅을 위한 편의 기능
	friend ostream& operator<<(ostream& os, const Pos& pos)
	{
		cout << "(" << pos.row << ", " << pos.col << ")" << flush;
		return os;
	}
};

bool CheckValidScope(Pos current_pos)
{
	return ((current_pos.row >= 0 && current_pos.row < kNumRows) || \
					current_pos.col >= 0 && current_pos.col < kNumCols);
}

bool CheckAdvanceCondition(Pos current_pos)
{
	return (maze[current_pos.row][current_pos.col] == '0' || \
					maze[current_pos.row][current_pos.col] == 'G');
}

void RecurMaze(Pos p)
{
	const char mark = maze[p.row][p.col];

	if (mark == 'G')
	{
		cout << "Found!" << endl;
		return;
	}
	// 방문했던 적이 없고 ('X'가 아니고)
	// cout << p << endl;
	// 벽도 아닌 경우 ('1'도 아닌 경우)
	// if (...)
	// {
	// 	'X' 표시

	// 	옆으로 이동
	// }
	maze[p.row][p.col] = 'v';
	Pos directions[] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
	for (const Pos& direction: directions)
	{
		Pos next_bound = { p.row + direction.row, p.col + direction.col };
		if (CheckValidScope(next_bound) && CheckAdvanceCondition(next_bound))
			RecurMaze(next_bound);
	}
}

//조기 종료가 가능한 버전
//int RecurMaze(Pos p)
//{
//	// TODO:
//}


void StackMaze()
{
	Stack<Pos> s;

	Pos start = { 1, 1 }; // i = 1, j = 1  시작 지점
	//Pos start;
	//start.row = 1;
	//start.col = 1;

	s.Push(start); // s.Push({1, 1});

	// s.Print(); // 디버깅에 사용 가능

	while (!s.IsEmpty())
	{
		Pos p = s.Top();
		s.Pop();

		cout << p << " "; // 디버깅 출력

		const char mark = maze[p.row][p.col];

		if (mark == 'G')
		{
			cout << "\nFound!" << endl;
			break;
		}
		maze[p.row][p.col] = 'v'; 

		// TODO: 상하좌우 확인하여 갈 수 있는 곳이면 stack에 추가한다.
		// counterclockwise
		// 0 -> North, 1 -> West, 2 -> South, 3 -> East
		Pos directions[] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
		for (const Pos& direction: directions)
		{
			Pos next_bound = { p.row + direction.row, p.col + direction.col };
			if (CheckValidScope(next_bound) && CheckAdvanceCondition(next_bound))
				s.Push(next_bound);
		}
	}
}

int main()
{
	PrintMaze();

	RecurMaze({ 1, 1 });

	std::cout << std::endl;
	// StackMaze();

	PrintMaze();

	return 0;
}
