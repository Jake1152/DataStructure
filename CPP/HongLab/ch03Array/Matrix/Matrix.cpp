#include "Matrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstring>

using namespace std;

Matrix::Matrix(int num_rows, int num_cols)
{
	// TODO:
	this->num_rows_ = num_rows;
	this->num_cols_ = num_cols;
	this->values_ = new float[num_cols * num_rows];
	std::memset(this->values_, 0, sizeof(float) * num_cols * num_rows);
}

// 복사 생성자 (b를 복사)
Matrix::Matrix(const Matrix& b)
{
	// TODO:
	if (this->values_) delete [] this->values_;
	this->num_rows_ = b.num_rows_;
	this->num_cols_ = b.num_cols_;
	this->values_ = new float[this->num_rows_ * this->num_cols_];
	std::memcpy(this->values_, b.values_, sizeof(float) * (this->num_rows_ * this->num_cols_));
}

Matrix::~Matrix()
{
	if (this->values_)
	{
		delete [] this->values_;
		this->values_ = nullptr;
	}
}

void Matrix::SetValue(int row, int col, float value)
{
	// values_[TODO] = value;
	this->values_[this->num_cols_ * row + col] = value;
}

float Matrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	return this->values_[this->num_cols_ * row + col];
}

/**
 * Row -> cols
 * 
 * cols -> row
*/
Matrix Matrix::Transpose()
{
	Matrix temp(num_cols_, num_rows_); // num_cols_, num_rows_ 순서 주의

	// TODO:
	for (size_t row = 0; row < this->num_rows_; row++)
	{
		for (size_t col = 0; col < this->num_cols_; col++)
		{
			temp.SetValue(col, row, this->GetValue(row, col));
		}
	}

	return temp;
}

Matrix Matrix::Add(const Matrix& b)
{
	assert(b.num_cols_ == num_cols_);
	assert(b.num_rows_ == num_rows_);

	Matrix temp(num_rows_, num_cols_);

	// TODO:
	for (size_t i = 0; i < this->num_rows_; i++) 
	{
		for (size_t j = 0; j < this->num_cols_; j++) 
		{
			size_t cur_idx  = this->num_cols_ * i + j;
			temp.values_[cur_idx] = this->values_[cur_idx] + b.values_[cur_idx];
		}
	}

	return temp;
}

void Matrix::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";

		cout << endl;
	}
}