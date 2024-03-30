#include "SparseMatrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstring>

using namespace std;

SparseMatrix::SparseMatrix(int num_rows, int num_cols, int capacity)
	: num_rows_(num_rows), num_cols_(num_cols), capacity_(capacity), num_terms_(0)
{
	// TODO:
	this->terms_ = new MatrixTerm[this->capacity_];
}

// 복사 생성자 (b를 복사)
SparseMatrix::SparseMatrix(const SparseMatrix& b)
	: num_rows_(b.num_rows_), num_cols_(b.num_cols_), capacity_(b.capacity_), num_terms_(b.capacity_)
{
	// TODO:
	this->terms_ = new MatrixTerm[this->capacity_];

	for (size_t idx = 0; idx < this->capacity_; idx++)
	{
		this->terms_[idx].row = b.terms_[idx].row;
		this->terms_[idx].col = b.terms_[idx].col;
		this->terms_[idx].value = b.terms_[idx].value;
	}
	// std::memcpy(this->terms_, b.terms_, sizeof(MatrixTerm) * this->capacity_);
}

/**
 * 나머지 멤버변수도 0으로 초기화?
*/
SparseMatrix::~SparseMatrix()
{
	// TODO:
	if (this->terms_) delete [] this->terms_;
	this->terms_ = nullptr;
}

/**
 * 1. 같은 자리에 값을 덮어 쓰는 경우를 감안해야한다.
 * 2. 정렬해서 처리 (insertion sort 참고)
 *   적당한 위치에 놓이도록 한다.
*/
void SparseMatrix::SetValue(int row, int col, float value)
{
	if (value == 0.0f) return; // value가 0이 아닌 term만 저장

	// TODO:
	// 이미 같은 자리에 값이 있는지 확인
	for (size_t iter = 0; iter < this->num_terms_; iter++)
	{
		if (this->terms_[iter].row == row && this->terms_[iter].col == col)
		{
			this->terms_[iter].value = value;
			return ;
		}
	}

	// 새로 들어온 값
	if (this->num_terms_ >= this->capacity_)
	{
		MatrixTerm	*terms = nullptr;

		terms = new MatrixTerm[this->capacity_ * 2];
		std::memcpy(terms, this->terms_, sizeof(MatrixTerm) * this->capacity_);
		delete [] this->terms_;
		std::memcpy(this->terms_, terms, sizeof(MatrixTerm) * this->capacity_);
		this->capacity_ *= 2;

	}

	// TODO: 좌표를 기준으로 정렬되어 있을 수 있도록 처리 필요
	this->terms_[this->num_terms_].row = row;
	this->terms_[this->num_terms_].col = col;
	this->terms_[this->num_terms_].value = value;
	this->num_terms_++;
}

float SparseMatrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	// TODO: key = col + num_cols * row;

	for (size_t iter = 0; iter < this->num_terms_; iter++)
	{
		if(this->terms_[iter].row == row && this->terms_[iter].col == col)
			return this->terms_[iter].value;
	}
	return 0.0f;
}

SparseMatrix SparseMatrix::Transpose()
{
	SparseMatrix temp(num_cols_, num_rows_, capacity_); // num_cols_, num_rows_ 순서 주의

	// TODO:
	for (size_t iter = 0; iter < this->num_terms_; iter++)
	{
		// this->num_terms_
		temp.SetValue(this->terms_[iter].col, this->terms_[iter].row, this->terms_[iter].value);
		// temp
		// this->terms_[iter]
	}

	return temp;
}

void SparseMatrix::PrintTerms()
{
	for (int i = 0; i < num_terms_; i++)
		cout << "(" << terms_[i].row
		<< ", " << terms_[i].col
		<< ", " << terms_[i].value
		<< ")" << endl;
}

void SparseMatrix::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";
		cout << endl;
	}
}