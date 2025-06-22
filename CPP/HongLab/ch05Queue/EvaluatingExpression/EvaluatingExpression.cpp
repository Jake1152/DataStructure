#include <iostream>

#include "../shared/Stack.h"
#include "../shared/Queue.h"

using namespace std;

int Prec(char c); // 연산자 우선순위를 반환

// STEP02
// 홍랩 코드 이용해서 InfixToPostfix 동작하게 한뒤, EvalPostfix 먼저 진행

/**
 * 중위순회를 후위순회로 만들기
 * 
 * # 연산자 우선순위가 없는 상황(덧셈, 뺼셈)
 * - 연산자가 피연산자 바로 뒤에 가게만 하면 됨
 * - "1 + 3 - 4 + 7 "
 * => "1 3 + 4 - 7 +"
 * 
 * # 연산자 우선순위가 있는 상황1(덧셈, 뺼셈, 곱셈, 나눗셈)
 * - "1 + 3 - 4 * 7 "
 * => "1 3 + 4 7 * - "
 * # 연산자 우선순위가 있는 상황2(괄호 포함) 
 * * - "1 + 3 - 4 * 7 "
 */
void InfixToPostfix(Queue<char>& q, Queue<char>& output);

// STEP01
int EvalPostfix(Queue<char>& q);

/*
   infix: A/B-C+D*E-A*C
 postfix: AB/C-DE*+AC*-

   infix: 8 / 2 - 3 + 4 * 5 - 1 * 2 = 19
 postfix: 8 2 / 3 - 4 5 * + 1 2 * - // 연산자를 만날때까지 진행
		  = 4 3 - 4 5 * + 1 2 * -
		  = 1 4 5 * + 1 2 * -
		//   = 1 20 + 1 2 * -
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
- -+* => -*+
  3 - 4 + 2 * 2 => 3
  3 4 - 2 2 * + 
  TOP       BOTTOM

STACK:
OUTPUT: 3 4 2 2 -*+
POSTFIX: 3 4 2 2 -*+

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

	// const char infix[] = "8/2+(3+4)*5-1*2";
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

	cout << "#Evaluated = " << EvalPostfix(postfix) << endl;

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

/**
Infix: A/B-C+D*E-A*C
Postfix: AB/C-DE*+AC*-

infix: 8 / 2 - 3 + 4 * 5 - 1 * 2 = 19
postfix: 8 2 / 3 - 4 5 * + 1 2 * - // 연산자를 만날 때까지 진행
       = 4 3 - 4 5 * + 1 2 * -
	   = 1 4 5 * + 1 2 * -
	   = 1 20 + 1 2 * -
	   = 21 1 2 * -
	   = 21 2 -
	   = 19
어떻게 infix를 postfix로 바꿀 것인가?
유의해야할 사항들은 무엇인가?

연산자의 우선순위가 다른 것들
연산자 우선순위가 높은 것이 더 먼저? 와야함

6 + 3 + 2
=> 6 3 + 2 +

6 + 3 * 2
=> 6 3 2 * +

6 + 3 * 2 / 5
=> 6 3 2 5 /*+
=> 6 3 2 *+ 5  /
// TODO: 맨 앞에가 음수인 경우는 어떻게 할 것인가?
// - 2 + 1 
// 2 - 1 +
 

(6 + 3) * 2 / 5
=> 6 3 + 2 * 5 /

(6 + (3 * 2)) / 5
=> 6 3 2 * + 5 /

- 괄호가 올 때 연산자 우선순위를 어떻게 할 것인가?
- 괄호가 없을 때는 어떠한가, 괄호가 없을 때 연산우선순위의 변동은 어떻게 되는가?

- 연산자 우선순위가 같은 것끼리는 어떻게 되는가?
3 + 2 - 7 + 1 + 5
=> 3 2 + 7 - 1 + 5 +

*/

void InfixToPostfix(Queue<char>& input_queue, Queue<char>& output_queue)
{
	Stack<char> s; // 우선순위가 낮은 연산을 보류하기 위한 스택

	output_queue.SetDebugFlag(false);

	while (input_queue.IsEmpty() == false)
	{
		const char ch = static_cast<const char>(input_queue.Front());

		input_queue.Dequeue();
		
		//  3 + 2 => 3 2 +
		/**
		 * 숫자이면 output_queue에 담는다?
		 * 
		 * 연산자이면 어떻게 처리하는가?
		 * 연산자도 output queue에 담는가?
		 * 연산자 우선순위는 어떻게 되는가?
		 */
		if (std::isdigit(ch)) // 피연산자
		{
			// output
		}
		else  // 연산자
		{
			
		}
	}
}

/*
void InfixToPostfix(Queue<char>& q, Queue<char>& output)
{
	Stack<char> s; // 우선순위가 낮은 연산을 보류하기 위한 스택

	output.SetDebugFlag(false);

	while (!q.IsEmpty())
	{
		char c = q.Front();
		q.Dequeue();

		cout << c << endl;

		if (c >= '0' && c <= '9') // 숫자(피연산자)라면 output에 추가
			output.Enqueue(c);
		else if (c == '(') // 여는 괄호라면 스택에 추가
			s.Push(c);
		else if (c == ')') // 닫는 괄호를 만나면
		{
			// 여는 괄호 전까지를 스택에서 꺼내서 출력에 넣기
			while (s.Top() != '(')
			{
				output.Enqueue(s.Top());
				s.Pop();
			}
			s.Pop(); // 여는 괄호 제거
		}
		else // 연산자를 만나면
		{
			// 스택에서 c보다 우선순위가 높거나 같은 것들을 꺼내서 추가
			while (!s.IsEmpty() && Prec(c) <= Prec(s.Top()))
			{
				output.Enqueue(s.Top());
				s.Pop();
			}

			// c는 스택에 추가
			s.Push(c);
		}

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
*/

/*
* Postfix 방식대로 연산을 진행하여 결과를 반환함
*/
int EvalPostfix(Queue<char>& q)
{
	Stack<int> s;

	while (!q.IsEmpty())
	{
		char ch = q.Front();
		q.Dequeue();

		if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		{
			int post_value, pre_value, result;

			post_value = s.Top();
			s.Pop();
			pre_value= s.Top();
			s.Pop();

			if (ch == '+')
				result = pre_value + post_value;
			else if (ch == '-')
				result = pre_value - post_value;
			else if (ch == '*')
				result = pre_value * post_value;
			else if (ch == '/')
				result = pre_value / post_value;
			
			// std::cout << "#pre_value : " << pre_value << "\t,post_value : " << post_value << ",\tresult :  " << result << std::endl;

			s.Push(result);
		}
		else
		{
			// TODO: - '0'을 하지 않고 바로 변환하였기에 잘못된 값이 나오게 됨.
			// int num = static_cast<int>(ch);
			int num = static_cast<int>(ch - '0');

			// std::cout << "ch : " << ch << "\t,num : " << num << std::endl;
			s.Push(num);
		}
	}

	return s.Top();
}

// int EvalPostfix(Queue<char>& q)
// {
// 	Stack<int> s;

// 	while (!q.IsEmpty())
// 	{
// 		char c = q.Front();
// 		q.Dequeue();

// 		cout << c << endl;

// 		if (c != '+' && c != '-' && c != '*' && c != '/')
// 		{
// 			// 입력이 연산자가 아니면 일단 저장
// 			// 문자를 숫자로 변환 c - '0' 예: int('9' - '0') -> 정수 9
// 			s.Push(c - '0');
// 		}
// 		else
// 		{
// 			cout << "Operator: " << c << endl;

// 			// 입력이 연산자이면 스택에서 꺼내서 연산에 사용

// 			int val2 = s.Top();
// 			s.Pop();

// 			int val1 = s.Top();
// 			s.Pop();

// 			// cout << "val1 : " << val1 << ",\t" << "val2 : " << val2 << endl;

// 			if (c == '+') {
// 				// ...
// 				// int value = s.Pop()
// 				s.Push(val1 + val2);
// 			}
// 			else if (c == '-') {
// 				s.Push(val1 - val2);
// 			}
// 			else if (c == '*') {
// 				s.Push(val1 * val2);
// 			}
// 			else if (c == '/')
// 			{
// 				s.Push(val1 / val2);
// 			}
// 			else
// 			{
// 				cout << "Wrong operator" << endl;
// 				exit(-1); // 강제 종료
// 			}
// 		}
// 		/*
// 		*/

// 		cout << "Stack: ";
// 		s.Print();
// 	}

// 	return s.Top();
// }