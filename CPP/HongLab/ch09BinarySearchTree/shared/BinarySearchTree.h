#pragma once

#include <iomanip>
#include <cassert>
#include <iostream>
#include <cmath>

template<typename K, typename V>
class BinarySearchTree
{
public:
	struct Item // key와 value의 쌍(pair)
	{
		K key = K();	// first
		V value = V();	// second
	};

	struct Node
	{
		Item item;

		Node* left = nullptr;
		Node* right = nullptr;
	};

	void Preorder()
	{
		using namespace std;
		Preorder(root_);
		cout << endl;
	}

	void Preorder(Node* node)
	{
		using namespace std;
		if (node)
		{
			cout << node->item.key << " ";
			Preorder(node->left);
			Preorder(node->right);
		}
	}

	void Inorder()
	{
		using namespace std;
		Inorder(root_);
		cout << endl;
	}

	void Inorder(Node* node)
	{
		using namespace std;
		if (node)
		{
			Inorder(node->left);
			cout << node->item.key << " ";
			Inorder(node->right);
		}
	}

	Item* RecurGet(const K& key)
	{
		return RecurGet(root_, key);
	}

	Item* RecurGet(Node* node, const K& key)
	{
		if (!node) return nullptr; // <- 동일한 키를 가진 노드를 찾지 못하면 nullptr을 반환하는 기능

		if (key < node->item.key)
			return RecurGet(node->left, key);
		if (key > node->item.key)
			return RecurGet(node->right, key);

		return &(node->item); // if (key == node->item.key)
	}

	Item* IterGet(const K& key)
	{
		// TODO:
		Node *cur_node = this->root_;

		while (cur_node)
		{
			if (cur_node->item.key > key)
				cur_node = cur_node->left;
			else if (cur_node->item.key < key)
				cur_node = cur_node->right;
			else // ==
				return &(cur_node->item);
		}

		return nullptr; // No matching
	}

	void Insert(const Item& item)
	{
		using namespace std;
		cout << "Insert " << item.key << ", " << item.value << endl;
		// root_ = Insert(root_, item);
		Insert(root_, item);
	}

	Node* Insert(Node* node, const Item& item)
	{
		// 힌트: RecurGet()

		// TODO:
		if (node == nullptr && node == this->root_)
		{
			if (this->root_ == nullptr)
				std::cout << "# item : " << item.key << ", "<< item.value << std::endl;
			Node *new_node = new Node{item, nullptr, nullptr};
			this->root_ = new_node;

			return new_node;
		}
		if (item.key < node->item.key)
		{
			if (node->left == nullptr)
			{
				Node *new_node = new Node{item, nullptr, nullptr};
				node->left = new_node;

				return new_node;
			}
			else
				return Insert(node->left, item);
		}
		else if (item.key > node->item.key)
		{
			if (node->right == nullptr)
			{
				Node *new_node = new Node{item, nullptr, nullptr};
				node->right = new_node;

				return new_node;
			}
			else
				return Insert(node->right, item);
		}
		else
		{
			node->item = item;

			return node;
		}
		// return node;
	}

	void IterInsert(const Item& item)
	{
		// TODO:
		Node *new_node = new Node{item, nullptr, nullptr};

		if (this->root_ == nullptr)
		{
			this->root_ = new_node;
			return ;
		}
		
		Node *cur_node = this->root_;
		while (cur_node)
		{
			if (new_node->item.key < cur_node->item.key)
			{
				if (cur_node->left == nullptr)
				{
					cur_node->left = new_node;
					return ;
				}
				cur_node = cur_node->left;
			}
			else if (new_node->item.key > cur_node->item.key)
			{
				if (cur_node->right == nullptr)
				{
					cur_node->right = new_node;
					return ;
				}
				cur_node = cur_node->right;
			} else if (new_node->item.key == cur_node->item.key)
			{
				// std::cout << "## cur_node->item : " << cur_node->item << std::endl;
				cur_node->item = item;
				// std::cout << "## cur_node->item : " << cur_node->item << std::endl;
				delete new_node;
				return ;
			}
		}
	}

	Node* MinKeyLeft(Node* node)
	{
		assert(node);
		while (node->left)
			node = node->left;
		return node;
	}

	void Remove(const K& key)
	{
		using namespace std;
		cout << "Remove " << key << endl;
		root_ = Remove(root_, key);
	}

	Node* Remove(Node* node, const K& key)
	{
		if (!node) return node;

		if (key < node->item.key)
			node->left = Remove(node->left, key);
		else if (key > node->item.key)
			node->right = Remove(node->right, key);
		else
		{
			// TODO:
			// 단말노드인 경우
			bool root_flag = false;

			if (node == this->root_)
				root_flag = true;
			std::cout << std::boolalpha << "root_flag : " << root_flag << std::endl;
			// root노드가 단말노드인 경우, 단말의 부모노드들에게서는 단말노드와의 연결을 끊어야 한다. return이 되게 되므로 끊길 것
			if (node->left == nullptr && node->right == nullptr)
			{				
				delete node;
				node = nullptr;
			}
			// 왼쪽 자식이 있는 경우 
			else if (node->left)
			{
				// 왼쪽 중 가장 큰 후손노드를 삭제될 위치에 삽입
				Node *replace_node = node->left;
				while (replace_node->right)
				{
					if (replace_node->right->right == nullptr)
					{
						/**
						 * Height = 3
										5F                              
								'3D'               7H              
							1B       4E       6Z       8I   

							replace_node가 '3D' 인 상황
						*/
						Node *temp = replace_node->right;
						
						// 대체될 노드의 부모노드 입장에서 대체될 노드에 대한 연결을 끊는다.
						replace_node->right = nullptr;
						replace_node = temp;
					}
					else
					{
						replace_node = replace_node->right;
					}
				}
				std::cout << "replace_node : " << replace_node->item.key << std::endl;
				if (replace_node == node->left)
				{
					replace_node->right = node->right;
					delete node;
					node = replace_node;
				}
				else
				{
					replace_node->left = node->left;
					replace_node->right = node->right;
					delete node;
					node = replace_node;
				}
			}
			// 오른쪽 자식이 있는 경우
			else if (node->right)
			{
				// 오른쪽 서브트리 중 가장 작은 후손노드를 삭제될 위치에 삽입
				Node *replace_node = node->right;
				while (replace_node->left)
				{
					if (replace_node->left->left == nullptr)
					{
						Node *temp = replace_node->left;
						
						// 대체될 노드의 부모노드 입장에서 대체될 노드에 대한 연결을 끊는다.
						replace_node->left = nullptr;
						replace_node = temp;
					}
					else
					{
						replace_node = replace_node->left;
					}
				}
				if (replace_node == node->right)
				{
					replace_node->left = node->left;
					delete node;
					node = replace_node;
				}
				else
				{
					replace_node->left = node->left;
					replace_node->right = node->right;
					delete node;
					node = replace_node;
				}
			}
			if (root_flag)
				this->root_ = node;
			if (node)
				std::cout << "# node : " << node->item.key << std::endl;
			if (this->root_)
				std::cout << "# root_ : " << this->root_->item.key << std::endl;
			if (node && node->left)
				std::cout << "# left : " << node->left->item.key << std::endl;
			if (node && node->right)
				std::cout << "# right : " << node->right->item.key << std::endl;
		}
		return node;
	}

	int Height()
	{
		return Height(root_);
	}

	int Height(Node* node)
	{
		if (!node) return 0;
		return 1 + std::max(Height(node->left), Height(node->right));
	}

	void Print2D();
	void PrintLevel(int n);
	void DisplayLevel(Node* p, int lv, int d);

protected:
	Node* root_ = nullptr;

private:
	// copy_assign() // =, ()
};

// 디버깅 편의 도구
// https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
template<typename K, typename V>
void BinarySearchTree<K, V>::Print2D()
{
	using namespace std;
	cout << "Height = " << Height() << endl;
	int i = 0;
	while (i < Height()) {
		PrintLevel(i);
		i++;
		cout << endl;
	}
	cout << endl;
}

template<typename K, typename V>
void BinarySearchTree<K, V>::PrintLevel(int n) {
	using namespace std;
	Node* temp = root_;
	int val = (int)std::pow(2.0, Height() - n + 1.0);
	cout << setw(val) << "";
	DisplayLevel(temp, n, val);
}

template<typename K, typename V>
void BinarySearchTree<K, V>::DisplayLevel(Node* p, int lv, int d) {
	using namespace std;
	int disp = 2 * d;
	if (lv == 0) {
		if (p == NULL) {
			cout << "   ";
			cout << setw(disp - 3) << "";
			return;
		}
		else {
			int result = ((p->item.key <= 1) ? 1 : (int)log10(p->item.key) + 1);
			cout << " " << p->item.key << p->item.value << " ";
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