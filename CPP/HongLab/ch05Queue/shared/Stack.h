#pragma once

#include <cassert>
#include <iostream>
#include <cstring>

template<typename T> // 템플릿 사용
class Stack
{
public:
	Stack(int capacity = 1)
	{
		assert(capacity > 0);
		Resize(capacity);
	}

	~Stack()
	{
		if (this->stack_)
        {
            delete[] this->stack_;
            this->capacity_ = 0;
            this->top_ = -1;
            this->stack_ = nullptr;
        }
	}

	void Resize(int new_capacity)
	{
		T* new_stack = new T[new_capacity];
		std::memcpy(new_stack, this->stack_, sizeof(T) * Size());
		if (this->stack_) delete[] this->stack_;
		this->stack_ = new_stack;
		this->capacity_ = new_capacity;
	}

	bool IsEmpty() const
	{
        // if (this->top_ == -1)
		//     return true;
        // return false;
        return this->top_ == -1;
	}

	int Size() const
	{
		return this->top_ + 1;
	}

	void Print()
	{
		using namespace std;

		for (int i = 0; i < Size(); i++) // Size() 사용
			cout << stack_[i] << " ";
		cout << endl;
	}

	// Returns TOP element of stack.
	T& Top() const
	{
		assert(!IsEmpty());

		return stack_[top_];
	}

	// Insert item into the TOP of the stack
	void Push(const T& item)
	{
		// TODO: 필요하면 리사이즈 
        if (this->Size() >= this->capacity_)
            this->Resize(this->Size() * 2);

        this->top_ += 1;
        this->stack_[this->top_] = item;
	}

	// Delete the TOP element of the stack
    /**
     * memory가 부족한 경우에는 resize하여 크기를 줄여준다.
    */
	void Pop()
	{
		assert(!IsEmpty());

        this->top_ -= 1;
        // this->top_-- vs this->top_ -= 1;
        // 메모리를 지워야하는 경우
        // stack[top--].~T(); // 소멸자를 수동으로 호출
	}

protected: // 뒤에서 상속해서 사용
	T* stack_ = nullptr;
	int top_ = -1; // 0 아님, last_element_index
	int capacity_ = 0;
};