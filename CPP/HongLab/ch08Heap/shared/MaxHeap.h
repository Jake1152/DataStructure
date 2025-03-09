#pragma once

#include <cassert>
#include <iostream>
#include <iomanip>
#include <cstring>

template<typename T>
class MaxHeap
{
public:
	MaxHeap(int cap = 10)
	{
		assert(cap > 0);

		capacity_ = cap;
		size_ = 0;
		heap_ = new T[capacity_ + 1]; // heap[0]은 비워둡니다.
	}

	~MaxHeap(void)
	{
		
		std::cout << "# ~MaxHeap" << std::endl;
		for (auto idx = 0 ; idx < this->capacity_; idx++)
		{
			std::cout << this->heap_[idx] << " ";
		}
		std::cout << std::endl;

		if (this->heap_ != nullptr)
		{
			delete [] this->heap_;
			this->size_ = 0;
			this->capacity_ = 0;
		}

		std::cout << "# after delete" << std::endl;
		for (auto idx = 0 ; idx < this->capacity_; idx++)
		{
			std::cout << "this->heap_[idx] : " << this->heap_[idx] << std::endl;
		}

		this->heap_ = nullptr;
	}

	void Resize(int new_capacity)
	{
		T* new_heap = new T[new_capacity];
		memcpy(new_heap, heap_, sizeof(T) * (size_ + 1)); // +1 주의
		if (heap_) delete[] heap_;
		heap_ = new_heap;
		capacity_ = new_capacity;
	}

	T Top()
	{
		return heap_[1]; // 1번 인덱스 자리
	}

	bool IsEmpty()
	{
		return size_ == 0;
	}

	void Print()
	{
		using namespace std;
		cout << "Index: ";
		for (int i = 1; i <= size_; i++)
			cout << setw(3) << i;
		cout << endl;

		cout << "Value: ";
		for (int i = 1; i <= size_; i++)
			cout << setw(3) << heap_[i];
		cout << endl << endl;
	}

	void Push(const T& item)
	{
		using namespace std;
		cout << "Push " << item << endl;

		if (size_ == capacity_)
			Resize(capacity_ * 2);

		// 삽입: 일단 맨 마지막에 삽입한 후에 부모 노드로 올린다.

		size_ += 1;
		int current = size_; // 마지막에 추가가될 위치 (인덱스)
		while (current != 1 && this->heap_[current / 2] < item) // 부모 위치의 값이 추가하려는 값보다 작다면
		{
			// 부모 위치의 값을 자식 위치로 복사해서 내린다.
			// TODO:
			this->heap_[current] = this->heap_[current / 2];

			cout << "Current = " << current << endl;
			Print();

			// TODO:
			current = current / 2;
		}

		heap_[current] = item; // 최종적으로 결정된 위치에 복사
	}

	void Pop()
	{
		assert(!IsEmpty());

		using namespace std;
		cout << "Pop()" << endl;

		/** TO KNOW
		 * 배열인데 특정 인덱스만 메모리 해제하면 어떻게 되는가?
		 * 8짜리 공간을 만들었다고 했을 때, 하나 줄이면 
		 * 7짜리 공간이 되는가?
		 * 또한 지웠던 자리에 다른 값을 넣어도 무방해지는가?
		 * 1000번지가 시작점이라하고 1007번지까지 8개가 있을 때, 
		 * heap_[1]의 번지수는 1001번지이다.
		 * 1001번지를 소멸자 호출하면 
		 * 1000번지, 1002~1007번지만 남는가?
		 * 이 상황에서 
		 */
		cout << "Before sizeof(this->heap_) : " << sizeof(this->heap_) << endl;
		cout << "this->heap_[1] : " << this->heap_[1] << endl;
		// 각 개별 원소 동적할당되어 있지 않으면 g++ 컴파일러에서 아래 소멸자 코드를 스킵하는 것 같다.
		this->heap_[1].~T(); // 소멸자 호출
		cout << "After sizeof(this->heap_) : " << sizeof(this->heap_) << endl;
		cout << "this->heap_[1] : " << this->heap_[1] << endl;
		// this->heap_[this->capacity_+1] = 42;

		// 삭제: 가장 마지막 값을 루트로 옮긴 후에 내려 보낸다.

		T last_item = this->heap_[this->size_]; // 마지막 아이템 복사
		this->size_--;					// 크기 줄이기

		int current = 1;			// 루트 노드에서 시작
		int child = 2;				// current * 2 (루트의 왼쪽 자식 인덱스)
		while (child <= this->size_)
		{
			cout << "Current = " << current << ", child = " << child << ", last_item = " << last_item << endl;
			Print();
			// left, right 중에서 더 큰 자식의 인덱스를 찾는다. 이때 자식이 하나라면 찾을 필요 없음
			// TODO:
			if (child + 1 <= this->size_ && (this->heap_[child] < this->heap_[child + 1]))
				child = child + 1;

			// 마지막 값이 더 큰 자식의 값 이상이면 더이상 적절한 위치를 찾을 필요가 없기 때문에 루프 중단
			// TODO:
			if (last_item > this->heap_[child])
				break ;

			// 자식 값을 부모 위치로 복사, 
			// TODO:
			this->heap_[current] = this->heap_[child];

			// 그 자식 위치로 current 인덱스 변경, child 인덱스도 그 다음 자식 위치로 변경
			// TODO:
			current = child;
			child = current * 2;
		}

		this->heap_[current] = last_item;
	}

private:
	T* heap_ = nullptr;
	int size_ = 0;
	int capacity_ = 0;
};
