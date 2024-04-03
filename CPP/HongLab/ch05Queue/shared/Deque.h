#pragma once

#include "Queue.h"

#include <cassert>
#include <iostream>
#include <iomanip>

// Double Ended Queue (덱, dequeue와 구분)
template<typename T>
class Deque : public Queue<T>
{

	typedef Queue<T> Base;

public:
	Deque(int capacity)
		: Queue<T>(capacity)
	{
	}

	T& Front()
	{
		return Base::Front();
	}

	T& Back()
	{
		return Base::Rear();
	}

	void PushFront(const T& item)
	{
		if (Base::IsFull())
			Base::Resize();

		// TODO:
        this->front_ = (this->front_) % this->capacity_;
        this->queue_[this->front_] = item;
		if (this->front_ == 0)
			this->front_ = this->capacity_ - 1;
		else
			this->front_ -= 1;
	}

	void PushBack(const T& item)
	{
		Base::Enqueue(item);
	}

	void PopFront()
	{
		Base::Dequeue();
	}

	void PopBack()
	{
		assert(!Base::IsEmpty());

		// TODO!!: (this->rear_ - 1) 
		this->rear_ = (this->rear_ - 1) % this->capacity_;
		// this->front_ = (this->front_) % this->capacity_;
        // this->queue_[this->front_] = item;
		// if (this->front_ == 0)
		// 	this->front_ = this->capacity_ - 1;
		// else
		// 	this->front_ -= 1;
	}

private:
	// Queue와 동일
};