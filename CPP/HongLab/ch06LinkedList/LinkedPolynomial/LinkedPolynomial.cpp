#include <iostream>
#include "../shared/SinglyLinkedList.h"
#include <cmath>

using namespace std;

struct Term
{
	float coef;
	int exp;
};

class LinkedPolynomial : public SinglyLinkedList<Term>
{
public:
	typedef SinglyLinkedList<Term>::Node Node;

	void NewTerm(float coef, int exp)
	{
		// TODO:
		Term new_term;
		
		new_term.coef = coef;
		new_term.exp = exp;
		
		// # 그냥 추가
		// this->PushBack(new_term);

		/** # 정렬고려하며 추가 
		 * 왼쪽이 추가되는 것보다 작거나 없어야하고 오른쪽이 없거나 커야한다
		*/
		// if (this->first_== nullptr)
		// {
		// 	this->PushBack(new_term);
		// 	return ;
		// }

		Node *cur_node = this->first_;
		Node *prev_node = cur_node;

		while (cur_node)
		{
			// 왼쪽이 추가되는 것보다 작고 오른쪽이 없거나 커야한다
			// new term이 왼쪽보다는 크고, 오른쪽보다는 작아야한다.
			if ((new_term.exp > prev_node->item.exp) &&
				((new_term.exp < cur_node->item.exp)))
			{
				this->InsertBack(prev_node, new_term);
				return ;
			}
			else if (new_term.exp == cur_node->item.exp)
			{
				cur_node->item.coef += new_term.coef;
				return ;
			}
			prev_node = cur_node;
			cur_node  = cur_node->next;
		}
		// InsertBacK을 안거치고 온 경우이므로 맨 뒤에 추가
		this->PushBack(new_term);

		// TODO: 같은 차수가 들어오는 경우 감안
	}

	float Eval(float x)

	{
		float temp = 0.0f;

		// TODO:
		Node *cur_node = this->first_;
		while (cur_node)
		{
			temp += std::pow(x, cur_node->item.exp) * cur_node->item.coef;
			cur_node  = cur_node->next;
		}

		return temp;
	}

	LinkedPolynomial Add(const LinkedPolynomial& poly)
	{
		// this와 poly의 terms_가 exp의 오름차순으로 정렬되어 있다고 가정
		// 하나의 다항식 안에 exp가 중복되는 term이 없다라고 가정 (한 exp는 하나의 term만 존재)

		LinkedPolynomial temp;

		Node* my_list_node = this->first_;
		Node* other_list_node = poly.first_;
		
		// Node *cur_node = this->Size() > poly.Size() ? my_list_node : other_list_node;
		// TODO:
		while (my_list_node && other_list_node)
		{
			Term new_term;

			if (my_list_node->item.exp > other_list_node->item.exp)
			{
				new_term.exp = other_list_node->item.exp;
				new_term.coef = other_list_node->item.coef;
				
				other_list_node = other_list_node->next;
			}
			else if (my_list_node->item.exp < other_list_node->item.exp)
			{
				new_term.exp = my_list_node->item.exp;
				new_term.coef = my_list_node->item.coef;
				
				my_list_node = my_list_node->next;
			}
			else  // if (my_list_node->item.exp == other_list_node->item.exp)
			{
				new_term.exp = my_list_node->item.exp;
				new_term.coef = my_list_node->item.coef + other_list_node->item.coef;
				
				my_list_node = my_list_node->next;
				other_list_node = other_list_node->next;
			}
			temp.PushBack(new_term);
		}

		while (other_list_node)
		{
			Term new_term;

			new_term.exp = other_list_node->item.exp;
			new_term.coef = other_list_node->item.coef;
			temp.PushBack(new_term);
			
			other_list_node = other_list_node->next;
		}

		while (my_list_node)
		{
			Term new_term;

			new_term.exp = my_list_node->item.exp;
			new_term.coef = my_list_node->item.coef;
			temp.PushBack(new_term);
			
			my_list_node = my_list_node->next;
		}

		return temp;
	}


	// p1.Print(); // 1 + 1.5*x^1 + 2*x^2 + 5*x^7 + 3.5*x^10 + 5.5*x^20 + 5*x^1000
	void Print()
	{
		bool is_first = true; // 더하기 출력시 확인용

		// TODO:
		Node *cur_node = this->first_;
		Node *prev_node = nullptr;

		if (this->first_->item.exp == 0)
		{
			std::cout << this->first_->item.coef;
			prev_node = cur_node;
			cur_node = cur_node->next;
		}

		while (cur_node)
		{
			if (prev_node)
				std::cout << " + ";
			Term term = cur_node->item;

			std::cout << term.coef << \
						"*" << \
						"x^" << \
						term.exp;
			std::cout << flush;
			prev_node = cur_node;
			cur_node = cur_node->next;
		}

		cout << endl;
	}

private:
};

int main()
{
	using namespace std;

	LinkedPolynomial p1;

	// exp가 작은 항부터 추가한다고 가정
	p1.NewTerm(1.0f, 0);	// 1 * x^0 = 1
	p1.Print();
	
	p1.NewTerm(1.5f, 1);	// 1.5 * x^1
	p1.Print();

	p1.NewTerm(2.0f, 2);	// 2 * x^2
	p1.Print(); // 1 + 1.5*x^1 + 2*x^2

	p1.NewTerm(2.0f, 2);	// 4 * x^2
	p1.Print(); // 1 + 1.5*x^1 + 4*x^2

	cout << p1.Eval(0.0f) << endl; // 1 + 1.5*0 + 2*0^2 = 1
	cout << p1.Eval(1.0f) << endl; // 1 + 1.5*1 + 2*1^2 = 6.5
	cout << p1.Eval(2.0f) << endl; // 1 + 1.5*2 + 4*2^2 = 1 + 3 + 16 = 20

	cout << endl;

	// Add() Test1
	cout << "Add() Test" << endl;
	{
		LinkedPolynomial p1; // max_degree는 기본값으로 설정

		// exp가 작은 항부터 추가한다고 가정
		p1.NewTerm(1.0f, 0);
		p1.NewTerm(1.5f, 1);
		p1.NewTerm(2.0f, 2);

		p1.Print(); // 1 + 1.5*x^1 + 2*x^2
		// p1.Eval(2.0f);
		cout << "# p1.Eval(2.0f) : " << p1.Eval(2.0f) << endl; // 1 + 1.5*2 + 2*2^2 = 1 + 3 + 8 = 12

		LinkedPolynomial p2;

		// exp가 작은 항부터 추가한다고 가정
		p2.NewTerm(1.0f, 1);
		p2.NewTerm(3.0f, 2);
		p2.NewTerm(5.0f, 7);
		p2.NewTerm(2.0f, 11);
		cout << "# p2.Eval(2.0f) : " << p2.Eval(2.0f) << endl; // 1 + 1.5*2 + 2*2^2 = 1 + 3 + 8 = 12

		p2.Print(); // 1*x^1 + 3*x^2 + 5*x^7 + 2*x^11

		cout << endl;

		LinkedPolynomial psum = p1.Add(p2);
		psum.Print(); // 1 + 2.5*x^1 + 5*x^2 + 5*x^7 + 2*x^11
		psum.Eval(2.0f);
		cout << "# psum.Eval(2.0f) : " << psum.Eval(2.0f) << endl; // 1 + 1.5*2 + 2*2^2 = 1 + 3 + 8 = 12

		cout << endl;
	}

	// Add() Test2
	cout << "Add() Test2" << endl;
	{
		LinkedPolynomial p1; // max_degree는 기본값으로 설정

		// exp가 작은 항부터 추가한다고 가정
		p1.NewTerm(1.0f, 0);
		p1.NewTerm(1.5f, 1);
		p1.NewTerm(2.0f, 2);
		p1.NewTerm(5.0f, 7);
		p1.NewTerm(3.5f, 10);
		p1.NewTerm(5.5f, 20);
		p1.NewTerm(5.0f, 1000);

		p1.Print(); // 1 + 1.5*x^1 + 2*x^2 + 5*x^7 + 3.5*x^10 + 5.5*x^20 + 5*x^1000

		LinkedPolynomial p2;

		// exp가 작은 항부터 추가한다고 가정
		p2.NewTerm(3.2f, 0);
		p2.NewTerm(1.0f, 1);
		p2.NewTerm(3.0f, 2);
		p2.NewTerm(2.0f, 11);

		p2.Print(); // 3.2 + 1*x^1 + 3*x^2 + 2*x^11

		cout << endl;

		LinkedPolynomial psum = p1.Add(p2);
		psum.Print(); // 4.2 + 2.5*x^1 + 5*x^2 + 5*x^7 + 3.5*x^10 + 2*x^11 + 5.5*x^20 + 5*x^1000

		cout << endl;
	}

	return 0;
}