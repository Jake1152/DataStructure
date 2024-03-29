#include "Array2D.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

Array2D::Array2D(int num_rows, int num_cols)
{
	//TODO:
	this->arrays_ = new float *[num_rows];
	for (size_t idx = 0; idx < num_rows; idx++)
		this->arrays_[idx] = new float [num_cols];
	for (size_t row = 0; row < this->num_rows_; row++)
	{
		for (size_t col = 0; col < this->num_cols_; col++)
		{
			this->arrays_[row][col] = 0.0f;
		}
	}

	this->num_rows_ = num_rows;
	this->num_cols_ = num_cols;
}

// 복사 생성자 (b를 복사)
Array2D::Array2D(const Array2D& b)
{
	//TODO:
	
	this->arrays_ = new float *[b.num_rows_];
	for (size_t idx = 0; idx < b.num_rows_; idx++)
		this->arrays_[idx] = new float [b.num_cols_];

	for (size_t row = 0; row < this->num_rows_; row++)
	{
		for (size_t col = 0; col < this->num_cols_; col++)
		{
			this->arrays_[row][col] = b.arrays_[row][col];
		}
	}

	this->num_rows_ = b.num_rows_;
	this->num_cols_ = b.num_cols_;
}

Array2D::~Array2D()
{
	//TODO:
	for (size_t row = 0; row < this->num_rows_; row++)
	{
		delete [] this->arrays_[row];
		this->arrays_[row] = nullptr;
	}

	delete [] this->arrays_;
	this->arrays_ = nullptr;
}

void Array2D::SetValue(int row, int col, float value)
{
	// TODO:
	this->arrays_[row][col] = value;
}

float Array2D::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	return this->arrays_[row][col]; // TODO:
	// return 0.0f; // TODO:
}

Array2D Array2D::Transpose()
{
	Array2D temp(num_cols_, num_rows_); // num_cols_, num_rows_ 순서 주의

	for (int r = 0; r < num_rows_; r++)
		for (int c = 0; c < num_cols_; c++)
			temp.SetValue(c, r, GetValue(r, c));

	return temp;
}

Array2D Array2D::Add(const Array2D& b)
{
	assert(b.num_cols_ == num_cols_);
	assert(b.num_rows_ == num_rows_);

	Array2D temp(num_rows_, num_cols_);

	for (int r = 0; r < num_rows_; r++)
		for (int c = 0; c < num_cols_; c++)
			temp.SetValue(r, c, GetValue(r, c) + b.GetValue(r, c));

	return temp;
}

void Array2D::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";

		cout << endl;
	}
}