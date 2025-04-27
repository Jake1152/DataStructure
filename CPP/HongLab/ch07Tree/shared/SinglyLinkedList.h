#pragma once

#include <cassert>
#include <stdint.h>

template<typename T>
class SinglyLinkedList
{
public:
	struct Node
	{
		T item = T();
		Node* next = nullptr;
	};

	SinglyLinkedList()
	{
	}

	SinglyLinkedList(const SinglyLinkedList& list)
	{
		// TODO: 연결 리스트 복사
		if (this != &list)
		{
			if (list.first_ == nullptr)
				return ;

			Node *first_node = new Node;

			first_node->item = list.first_->item;
			first_node->next = nullptr;

			this->first_ = first_node;

			Node *cur_node = this->first_;
			Node *origin_list_cur_node = list.first_->next;

			while (origin_list_cur_node)
			{
				Node *copied_node = new Node;

				copied_node->item = origin_list_cur_node->item;
				copied_node->next = origin_list_cur_node->next;
				cur_node->next = copied_node;
				cur_node = cur_node->next;
				origin_list_cur_node = origin_list_cur_node->next;
			}
		}
	}

	~SinglyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		// TODO: 모두 삭제
		Node *cur_node = this->first_;
		while (cur_node)
		{
			Node *be_removed_node;

			be_removed_node = cur_node;
			cur_node = cur_node->next;
			delete be_removed_node;
		}
		this->first_ = nullptr;
	}

	bool IsEmpty()
	{
		return first_ == nullptr;
	}

	int Size()
	{
		Node *cur_node = this->first_;
		int size = 0;

		// TODO: size를 하나하나 세어서 반환
		while (cur_node)
		{
			size++;
			cur_node = cur_node->next;
		}
		return size;
	}

	T Front()
	{
		assert(first_);

		return this->first_->item; // TODO: 수정
	}

	T Back()
	{
		assert(first_);

		Node *cur_node = this->first_;

		while (cur_node->next)
		{
			cur_node = cur_node->next;
		}
		return cur_node->item; // TODO: 수정
	}

	Node* Find(T item)
	{
		// TODO: item이 동일한 노드 포인터 반환
		Node *cur_node = this->first_;

		while (cur_node)
		{
			if (cur_node->item == item)
				return cur_node;
			cur_node = cur_node->next;
		}
		return nullptr;
	}

	void InsertBack(Node* node, T item)
	{
		// TODO:
		Node *new_node = new Node;
		new_node->item = item;
		new_node->next = nullptr;

		if (node == nullptr)
		{
			this->first_ = new_node;
			return ;
		}

		Node *cur_node = this->first_;
		while (cur_node->next)
		{
			if (node == cur_node)
			{
				new_node->next = cur_node->next;
				cur_node->next = new_node;
				break ;
			}
			cur_node = cur_node->next;
		}
		
	}

	void Remove(Node* target_node)
	{
		assert(first_);

		// 하나 앞의 노드를 찾아야 합니다.
		// TODO:
		if (this->first_ == target_node)
		{
			this->first_ = this->first_->next;
			delete target_node;
			target_node = nullptr;
			return ;
		}

		Node *prev_node = this->first_;
		Node *cur_node = this->first_;

		while (cur_node->next)
		{
			if (cur_node == target_node )
			{
				prev_node->next = cur_node->next;
				delete target_node;
				target_node = nullptr;
				break ;
			}
			prev_node = cur_node;
			cur_node = cur_node->next;
		}
	}

	void PushFront(T item)
	{
		// first_가 nullptr인 경우와 아닌 경우 나눠서 생각해보기 (결국은 두 경우를 하나로 합칠 수 있음)

		// 새로운 노드 만들기
		// TODO:
		Node *new_node = new Node;
		new_node->item = item;
		new_node->next = nullptr;

		// 연결 관계 정리
		// TODO:
		if (this->first_)
		{
			new_node->next = this->first_;
		}
		this->first_ = new_node;
	}

	void PushBack(T item)
	{
		Node *new_node = new Node;
		new_node->item = item;
		new_node->next = nullptr;
		if (this->first_)
		{
			// TODO:
			Node *cur_node = this->first_;
			while (cur_node->next)
			{
				cur_node = cur_node->next;
			}
			cur_node->next = new_node;
		}
		else
		{
			// TODO:
			this->first_ = new_node;
		}
		// this->InsertBack(this->first_, item);
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return;
		}

		assert(first_);

		// TODO: 메모리 삭제
		Node *temp;

		temp = this->first_;
		if (this->first_)
		{
			this->first_ = this->first_->next;
			delete temp;
			temp = nullptr;
		}
		else
			this->first_;
	}

	void PopBack()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return;
		}

		// 맨 뒤에서 하나 앞의 노드를 찾아야 합니다.

		assert(first_);

		// TODO: 메모리 삭제
		// 남아있는 node가 2개 이상 일 때
		if (this->first_->next)
		{
			Node *prev_node = this->first_;
			Node *cur_node = this->first_;

			while(cur_node->next)
			{
				prev_node = cur_node;
				cur_node = cur_node->next;
			}
			prev_node->next = nullptr;
			delete cur_node;
		}
		else // 남아있는 node가 1개 일 때
		{
			delete this->first_;
			this->first_ = nullptr;
		}

	}

	void Reverse()
	{
		if (this->first_)
		{
			// TODO: 
			// # mine
			// Node *cur_node = this->first_;
			// Node *prev_node = this->first_;
			// Node *next_node = this->first_->next; 
			// prev_node->next = nullptr;
			// while (next_node)
			// {
			// 	next_node = cur_node->next;
			// 	cur_node = next_node;
			// 	cur_node->next = prev_node;
			// 	prev_node = cur_node;
			// }
			// this->first_ = cur_node;

			// # Honglab way
			Node *temp = nullptr;
			Node *prev = nullptr;
			Node *current = this->first_;

			while (current)
			{
				prev = current;
				current = current->next;
				prev->next = temp;
				temp = prev;
			}
			this->first_ = prev;
		}
	}

	void SetPrintDebug(bool flag)
	{
		print_debug_ = flag;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << " " << endl;

			while (current)
			{
				if (print_debug_)
				{
					//cout << "[" << current << ", " << current->item << ", " << current->next << "]";

					// 주소를 짧은 정수로 출력 (앞 부분은 대부분 동일하기때문에 뒷부분만 출력)
					cout << "[" << reinterpret_cast<uintptr_t>(current) % 100000 << ", "
						<< current->item << ", "
						<< reinterpret_cast<uintptr_t>(current->next) % 100000 << "]";
				}
				else
				{
					cout << current->item;
				}

				if (current->next)
					cout << " -> ";
				else
					cout << " -> NULL";

				current = current->next;
			}
			cout << endl;
		}
	}

protected:
	Node* first_ = nullptr;

	bool print_debug_ = false;
};