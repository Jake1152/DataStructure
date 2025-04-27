#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <string> // BinaryTree 출력

#include "Queue.h"
#include "Stack.h"

template<typename T>
class BinaryTree
{
public:
	struct Node
	{
		T item = T();
		Node* left = nullptr; // Left child
		Node* right = nullptr; // Right child
	};

	// 디버깅 도구: 큐에서 주소 대신에 아이템 출력
	class MyQueue : public Queue<Node*>
	{
	public:
		void Print()
		{
			using namespace std;

			for (int i = (this->front_ + 1) % this->capacity_; i != (this->rear_ + 1) % this->capacity_; i = (i + 1) % this->capacity_)
				cout << this->queue_[i]->item << " ";
			cout << endl;
		}
	};

	// 디버깅 도구: 스택에서 주소 대신에 아이템 출력
	class MyStack : public Stack<Node*>
	{
	public:
		void Print()
		{
			using namespace std;

			for (int i = 0; i < this->Size(); i++)
				cout << this->stack_[i]->item << " ";
			cout << endl;
		}
	};

	BinaryTree() {}

	BinaryTree(Node* root)
	{
		root_ = root;
	}

	bool IsEmpty()
	{
		return root_ == nullptr;
	}

	void Visit(Node* node)
	{
		using namespace std;

		if (node)
			cout << node->item << " " << flush; // 수행하고 싶은 작업 구현(여기서는 출력)
	}

	int Sum()
	{
		return Sum(root_);
	}

	int Sum(Node* node)
	{
		Node *cur_node;

 		// TODO:
		if (node)
		{
			// 먼저거르고
			// if (node->left)
			// if (node->right)
			return Sum(node->left) + Sum(node->right) + (node->item);
		}
		return 0;
	}

	/**
	 * 
	*/
	int Height()
	{
		return Height(root_);
	}

	/**
	 * root부터 가장 멀리 있는 레벨에 있는 단말노드까지의 간선의 갯수
	 * 트리에 있는 모든 노드는 자신을 기준으로 루트가 될 수 있다
	*/
	int Height(Node* node)
	{
		// TODO:
		if (node)
			return std::max(this->Height(node->left), this->Height(node->right)) + 1;
		return 0;
	}

	~BinaryTree()
	{
		this->DeleteTree(root_);
		this->root_ = nullptr;
	}

	void DeleteTree(Node* node)
	{
		if (node)
		{
			// TODO: 힌트 Post-order
			if (node->left)
			{
				this->DeleteTree(node->left);
				node->left = nullptr;
			}
			if (node->right)
			{
				this->DeleteTree(node->right);
				node->right = nullptr;
			}
			delete node;
			node = nullptr;
		}
	}

	void Preorder() { Preorder(root_); }
	void Preorder(Node* node)
	{
		// TODO:
		if (node)
		{
			this->Visit(node);
			this->Preorder(node->left);
			this->Preorder(node->right);
		}
	};

	void Inorder() { Inorder(root_); }
	void Inorder(Node* node)
	{
		// TODO:
		if (node)
		{
			this->Inorder(node->left);
			this->Visit(node);
			this->Inorder(node->right);
		}
	}

	void Postorder() { Postorder(root_); }
	void Postorder(Node* node)
	{
		// TODO:
		if (node)
		{
			this->Postorder(node->left);
			this->Postorder(node->right);
			this->Visit(node);
		}
	}

	// LevelOrder
	// 6 2 5 1 4 3
	void LevelOrder()
	{
		Queue<Node*> queue; // 힌트: MyQueue q;
		Node* current = nullptr;

		queue.Enqueue(this->root_);
		while (!queue.IsEmpty())
		{
			current = queue.Front();
			queue.Dequeue();
			Visit(current);
			// TODO:
			// if (current->left)
			if (current)
			{
				// 
				queue.Enqueue(current->left);
				queue.Enqueue(current->right);
			}
		}
	}

	void IterPreorder()
	{
		if (!root_) return;

		Stack<Node*> stack; // 힌트: MyStack q;
		stack.Push(root_);

		while (!stack.IsEmpty())
		{
			// TODO:
			Node* cur_node = stack.Top();

			stack.Pop();
			if (cur_node)
			{
				this->Visit(cur_node);
				stack.Push(cur_node->right);
				stack.Push(cur_node->left);
			}
		}
	}

	/**
	 *        6
	 *     2     5
	 *   1      4  
	 * 3
	*/
	void IterInorder()
	{
		if (!root_) return;

		// Stack<Node*> s;

		// Node* cur_node = root_;
		// while (cur_node || !s.IsEmpty())
		// {
		// 	cur_node = stack.Top();
		// 	// stack.Push(cur_node->right);
		// 	// this->Visit(cur_node);
		// 	// stack.Push(cur_node->left);
		// 	// TODO:
		// }
	}

	void IterPostorder()
	{
		if (!root_) return;

		Stack<Node*> s1, s2;
		s1.Push(root_);

		while (!s1.IsEmpty())
		{
			// TODO:
		}

		while (!s2.IsEmpty())
		{
			// TODO:
		}
	}

	void Print2D();
	void PrintLevel(int n);
	void DisplayLevel(Node* p, int lv, int d);

protected:
	Node* root_ = nullptr;

private:
	BinaryTree(const BinaryTree& other);
	BinaryTree& operator=(const BinaryTree& other);
};

// 디버깅 편의 도구
// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
template<typename T>
void BinaryTree<T>::Print2D()
{
	using namespace std;
	int i = 0;
	while (i < Height()) {
		PrintLevel(i);
		i++;
		cout << endl;
	}
}

template<typename T>
void BinaryTree<T>::PrintLevel(int n) {
	using namespace std;
	Node* temp = root_;
	int val = (int)pow(2.0, Height() - n + 1.0);
	cout << setw(val) << "";
	DisplayLevel(temp, n, val);
}

template<typename T>
void BinaryTree<T>::DisplayLevel(Node* p, int lv, int d) {
	using namespace std;
	int disp = 2 * d;
	if (lv == 0) {
		if (p == NULL) {
			cout << "   ";
			cout << setw(disp - 3) << "";
			return;
		}
		else {
			int result = ((p->item <= 1) ? 1 : (int)log10(p->item) + 1);
			cout << " " << p->item << " ";
			cout << setw(static_cast<streamsize>(disp) - result - 2) << "";
		}
	}
	else
	{
		if (p == NULL && lv >= 1) {
			DisplayLevel(NULL, lv - 1, d);
			DisplayLevel(NULL, lv - 1, d);
		}
		else {
			DisplayLevel(p->left, lv - 1, d);
			DisplayLevel(p->right, lv - 1, d);
		}
	}
}