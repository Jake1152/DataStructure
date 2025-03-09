#pragma once

#include <cassert>
#include <stdint.h>
#include <algorithm>

template<typename T>
class DoublyLinkedList
{
public:
	struct Node
	{
		T item = T();

		Node* left = nullptr;
		Node* right = nullptr;

		// 참고: prev/next가 아니라 left/right
	};

	DoublyLinkedList()
	{
	}

	DoublyLinkedList(const DoublyLinkedList& list)
	{
		Node *current = list.first_;

		while (current)
		{
			this->PushBack(current->item);
			current = current->right;
		}
	}

	~DoublyLinkedList()
	{
		Clear();
	}

	void Clear() // 모두 지워야(delete) 합니다.
	{
		// TODO:
		Node *cur_node = this->first_;

		while (cur_node)
		{
			Node *temp = cur_node;

			cur_node = cur_node->right;
			delete temp;
		}
		// this->first_ = nullptr;
	}

	bool IsEmpty()
	{
		// TODO:
		return this->first_ == nullptr;
	}

	int Size()
	{
		int size = 0;

		// TODO:
		Node *cur_node = this->first_;

		while (cur_node)
		{
			cur_node = cur_node->right;
			size++;
		}
		return size;
	}

	void Print()
	{
		using namespace std;

		Node* current = first_;

		if (IsEmpty())
			cout << "Empty" << endl;
		else
		{
			cout << "Size = " << Size() << endl;

			cout << " Forward: ";
			// TODO:
			std::cout << this->first_->item;
			Node *cur_node = this->first_;
			while (cur_node->right)
			{
				cur_node = cur_node->right;
				std::cout  << " " << cur_node->item<< std::flush;
			}
			cout << endl;

			cout << "Backward: ";
			// TODO:
			if (cur_node)
			{
				while (cur_node->left)
				{
					std::cout << cur_node->item << " ";
					cur_node = cur_node->left;
				}
				std::cout << cur_node->item;
			}
			
			cout << endl;
		}
	}

	Node* Find(T item)
	{
		Node *cur_node = this->first_;

		 // TODO:
		while (cur_node)
		{
			// item이 구조체나 클래스라면 성립하지 않을 수 있다(주소값이 같지 않는 이상)
			if (cur_node->item == item)
				break ;
			cur_node = cur_node->right;
		}
		return cur_node;
	}

	void InsertBack(Node* node, T item)
	{
		if (IsEmpty())
		{
			PushBack(item);
		}
		else
		{
			// TODO:
			// # mine
			// Node *new_node = new Node;

			// new_node->item = item;
			// new_node->right = nullptr;
			// new_node->left= nullptr;

			// Node *cur_node = this->first_;

			// while (cur_node)
			// {
			// 	if (cur_node->item == node->item)
			// 	{
			// 		Node *right_node = cur_node->right;

			// 		if (right_node)
			// 			right_node->left = new_node;
			// 		new_node->right = right_node;
			// 		new_node->left = cur_node;
			// 		cur_node->right = new_node;
			// 	}
			// 	cur_node = cur_node->right;
			// }

			// # hong lab 참고
			Node *new_node = new Node;

			new_node->item = item;
			new_node->right = node->right;
			new_node->left= nullptr;

			if (node->right)
				node->right->left = new_node;
			node->right = new_node;
			new_node->left = node;
		}
	}

	void PushFront(T item)
	{
		// TODO:
		Node *new_node = new Node;

		new_node->item = item;
		new_node->right = nullptr;
		new_node->left= nullptr;

		Node *first_node = this->first_;

		if (first_node)
			first_node->left = new_node;
		new_node->right = first_node;
		this->first_ = new_node;
	}

	void PushBack(T item)
	{
		// TODO:
		Node *new_node = new Node;

		new_node->item = item;
		new_node->right = nullptr;
		new_node->left= nullptr;

		if (this->IsEmpty())
		{
			this->first_ = new_node;
		}
		else 
		{
			Node *cur_node = this->first_;

			while (cur_node->right)
				cur_node = cur_node->right;
			cur_node->right = new_node;
			new_node->left = cur_node;
		}
	}

	void PopFront()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopFront()" << endl;
			return ;
		}

		assert(first_);

		// TODO:
		// # mine
		// Node *first_node = this->first_;
		// Node *right_node = nullptr;

		// if (first_node)
		// {
		// 	right_node = first_node->right;
		// 	if (right_node)
		// 		right_node->left = nullptr;
		// 	first_node->right = nullptr;
		// 	delete first_node;
		// }
		// this->first_ = right_node;

		// # honglab way
		Node *temp = this->first_;

		this->first_ = this->first_->right;
		if (this->first_)
			this->first_->left = nullptr;

		delete temp;
	}

	void PopBack()
	{
		if (IsEmpty())
		{
			using namespace std;
			cout << "Nothing to Pop in PopBack()" << endl;
			return ;
		}

		// 맨 뒤에서 하나 앞의 노드를 찾아야 합니다.

		// assert(first_);

		// TODO:
		// # mine
		// Node *cur_node = this->first_;

		// while (cur_node && cur_node->right)
		// {
		// 	cur_node = cur_node->right;
		// }

		// Node *prev_node = nullptr;

		// if (cur_node)
		// {
		// 	prev_node = cur_node->left;

		// 	if (prev_node)
		// 		prev_node->right = nullptr;
		// 	delete cur_node;
		// 	cur_node = nullptr;
		// }
		// if (prev_node  == nullptr)
		// 	this->first_ = nullptr;

		// # honglab way
		Node *current = this->first_;

		if (current->right)
		{
			while (current->right->right)
				current = current->right;

			Node *temp = current->right;

			current->right = current->right->right;

			delete temp;
		}
		else
		{
			delete this->first_;
			this->first_ = nullptr;
		}
	}

	void Reverse()
	{
		// TODO:
		// # mine
		if (IsEmpty())
			return ;

		Node *cur_node = this->first_;
		Node *prev_node = nullptr;

		// A <-> B <-> C
		// B <-> A  
		while (cur_node->right)
		{
			prev_node = cur_node;
			cur_node = cur_node->right;

			Node *temp = prev_node->left;

			prev_node->left = prev_node->right;
			prev_node->right = temp;
		}
		cur_node->left = cur_node->right;
		cur_node->right = prev_node;
		this->first_ = cur_node;

		// # honglab way
		if (IsEmpty())
			return ;
		else
		{
			Node *current = this->first_;
			Node *prev = nullptr;

			while (current)
			{
				prev = current;
				current = current->right;

				std::swap(prev->left, prev->right);
			}
			this->first_ = prev;
		}
	}

	T Front()
	{
		// assert(first_);
		if (IsEmpty())
			return T();
		return T(this->first_->item); // TODO:
	}

	T Back()
	{
		// assert(first_);
		if (IsEmpty())
			return T();

		Node *cur_node = this->first_;

		while (cur_node->right)
			cur_node = cur_node->right;
		return T(cur_node->item); // TODO:
	}

protected:
	Node* first_ = nullptr;
};