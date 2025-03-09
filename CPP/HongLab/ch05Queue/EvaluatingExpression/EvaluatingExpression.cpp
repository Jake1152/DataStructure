#include <iostream>

#include "../shared/Stack.h"
#include "../shared/Queue.h"

using namespace std;

int Prec(char c); // 연산자 우선순위를 반환
void InfixToPostfix(Queue<char>& q, Queue<char>& output);
int EvalPostfix(Queue<char>& q);

/*
   infix: A/B-C+D*E-A*C
 postfix: AB/C-DE*+AC*-

   infix: 8 / 2 - 3 + 4 * 5 - 1 * 2 = 19
 postfix: 8 2 / 3 - 4 5 * + 1 2 * - // 연산자를 만날때까지 진행
		  = 4 3 - 4 5 * + 1 2 * -
		  = 1 4 5 * + 1 2 * -
		  = 1 20 + 1 2 * -
		  = 21 1 2 * -
		  = 21 2 -
		  = 19
*/

/**
사람은 infix순서로 수식을 계산, 우선순위도 고려해야한다. (*,/ 등등)
컴퓨터에서는 infix 방식을 postfix방식으로 변환하면 쫙 계산한다.
그렇기에 컴퓨터에서는 postfix 방식이 자연스럽다. 왼쪽에서 오른쪽으로 쭉 진행하면 된다.

# +,- 연산자만 있는 경우
피연산자는 큐에 계속 추가
연산자는 연산자 스택에 추가하다가 기존 스택 top에 있는 값보다 우선순위가 더 낮은 것이 나오면 연산자 스택에 있던 값을 pop한다. 해당 값은 임시 변수에 담아둔다.
우선순위가 더 높은 현재 연산자를 스택에 push하고 임시 변수에 담아두었던 연산자를 스택에 push한다.
- +* (OK)
- *- => -*
- -+* => *
  3 - 4 + 2 * 2 => 3
  3 4 - 2 2 * + 

# 연산자 우선순위가 존재하는 경우 (+,-,*,/)
연산자를 비교한다.
연산자 우선순위가 더 높은 것이 그렇지 않은 연산자들보다 스택에 밑에 있어야 한다.

# 괄호 있는 경우 
3 * (3 - 2 * 4)
- * *
3 3 - 2 * 4 *


1 + 4 + 6 + 3

Queue: 1 
Stack: 

Queue: 1 
Stack: +

...

Queue: 1 4 6 3
Stack: + + +


1 4 + 6 



*/

int main()
{
	// 예제에서는 빈칸 없이 한 자리 숫자만 가능

	//const char infix[] = "8/2+(3+4)*5-1*2";
	const char infix[] = "1+(1*2+3)*4";
	//const char infix[] = "1+2*3+3";
	//const char infix[] = "1+2*(3+1)";
	const int size = sizeof(infix) / sizeof(char) - 1;

	// 큐에 모두 넣기
	Queue<char> q;
	for (int i = 0; i < size; i++)
		q.Enqueue(infix[i]);

	Queue<char> postfix;

	cout << "Infix: ";
	q.Print();
	cout << endl;

	InfixToPostfix(q, postfix);

	cout << "Postfix: ";
	postfix.Print();

	cout << "Evaluated = " << EvalPostfix(postfix) << endl;

	return 0;
}

// Function to return precedence of operators
int Prec(char c)
{
	if (c == '/' || c == '*')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1; // '('는 우선순위가 아주 낮은 것으로 처리, ')' 닫는 괄호를 만날때까지 남겨두기 위함
}

void InfixToPostfix(Queue<char>& q, Queue<char>& output)
{
	Stack<char> s; // 우선순위가 낮은 연산을 보류하기 위한 스택

	output.SetDebugFlag(false);

	while (!q.IsEmpty())
	{
		char c = q.Front();
		q.Dequeue();

		cout << c << endl;

		/* TODO: 
		if (c >= '0' && c <= '9') // 숫자(피연산자)라면 output에 추가
			...;
		else if (c == '(') // 여는 괄호라면 스택에 추가
			...;
		else if (c == ')') // 닫는 괄호를 만나면
		{
			// 여는 괄호 전까지를 스택에서 꺼내서 출력에 넣기
			// 여는 괄호 제거
		}
		else // 연산자를 만나면
		{
			// 스택에서 c보다 우선순위가 높거나 같은 것들을 꺼내서 추가
			// c는 스택에 추가
		}
		*/

		cout << "Stack: ";
		s.Print();
		cout << "Output:";
		output.Print();
		cout << endl;
	}

	// 스택에 남아있는 것들을 모두 추가
	while (!s.IsEmpty())
	{
		output.Enqueue(s.Top());
		s.Pop();
	}
}

int EvalPostfix(Queue<char>& q)
{
	Stack<int> s;

	while (!q.IsEmpty())
	{
		char c = q.Front();
		q.Dequeue();

		cout << c << endl;

		/*
		if (c != '+' && c != '-' && c != '*' && c != '/')
		{
			// 입력이 연산자가 아니면 일단 저장
			// 문자를 숫자로 변환 c - '0' 예: int('9' - '0') -> 정수 9
		}
		else
		{
			cout << "Operator: " << c << endl;

			// 입력이 연산자이면 스택에서 꺼내서 연산에 사용

			if (c == '+') {
				...
			}
			else if (c == '-') {
				...
			}
			else if (c == '*') {
				...
			}
			else if (c == '/')
			{
				...
			}
			else
			{
				cout << "Wrong operator" << endl;
				exit(-1); // 강제 종료
			}
		}
		*/

		cout << "Stack: ";
		s.Print();
	}

	return s.Top();
}