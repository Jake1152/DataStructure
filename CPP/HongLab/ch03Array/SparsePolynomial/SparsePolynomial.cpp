#include "SparsePolynomial.h"

#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

// 새로운 항을 추가할 때 자기 위치를 찾아서 넣어줘야 함

// exp항이 이미 존재하면 거기에 coef를 더해준다.
// 존재하지 않는다면 exp 오름 차순으로 정렬된 상태로 새로 추가한다.
void SparsePolynomial::NewTerm(float coef, int exp)
{
	if (coef == 0.0f) return; // 0이면 추가하지 않음

	if (this->num_terms_ >= this->capacity_)
	{
		// capacity 증가 (num_terms는 일단 고정)
		this->capacity_ = this->capacity_ > 0 ? this->capacity_ * 2 : 1; // 2배씩 증가
		Term* new_term = new Term[this->capacity_];

		// 원래 가지고 있던 데이터 복사
		memcpy(new_term, terms_, sizeof(Term) * this->num_terms_);

		// 메모리 교체
		if (this->terms_) delete[] this->terms_;
		this->terms_ = new_term;
	}

	terms_[this->num_terms_].coef = coef;
	terms_[this->num_terms_].exp = exp;

	this->num_terms_++;
}

float SparsePolynomial::Eval(float x)
{
	float temp = 0.0f;

	// TODO:
	// this->terms_->coef;
	// this->terms_->exp;

	for (size_t iter = 0; iter < this->num_terms_;iter++)
	{
		temp += std::pow(x, this->terms_[iter].exp) * this->terms_[iter].coef;
	}

	return temp;
}

SparsePolynomial SparsePolynomial::Add(const SparsePolynomial& poly)
{
	// this와 poly의 terms_가 exp의 오름차순으로 정렬되어 있다고 가정
	// 하나의 다항식 안에 exp가 중복되는 term이 없다라고 가정 (한 exp는 하나의 term만 존재)

	// 간단한 방법 (메모리를 더 사용하는 방법)
	// - 1. 최대 exp를 찾는다.
	// - 2. 필요한 크기의 Polynomial을 만든다. (Sparse 아님)
	// - 3. 더하면서 Polynomial에 업데이트 한다. 구조가 고정되어 있어서 쉽다.
	// - 4. Polynomial을 SparsePolynomial로 변환한다.

	SparsePolynomial temp;

	// TODO:
	// size_t max_iter = std::min(this->num_terms_, poly.num_terms_);
	size_t poly_one_iter = 0;
	size_t poly_two_iter = 0;
	while ((poly_one_iter < this->num_terms_) && (poly_two_iter < poly.num_terms_))
	{
		float coef;

		if (this->terms_[poly_one_iter].exp == poly.terms_[poly_two_iter].exp)
		{
			coef = this->terms_[poly_one_iter].coef + poly.terms_[poly_two_iter].coef;
			temp.NewTerm(coef, this->terms_[poly_one_iter].exp);
			poly_one_iter++;
			poly_two_iter++;
		}
		else if (poly.terms_[poly_two_iter].exp < this->terms_[poly_one_iter].exp )
		{
			coef = poly.terms_[poly_two_iter].coef;
			temp.NewTerm(coef, poly.terms_[poly_two_iter].exp);
			poly_two_iter++;
		}
		else // (this->terms_[poly_one_iter].exp < this->terms_[poly_two_iter].exp)
		{
			coef = this->terms_[poly_one_iter].coef;
			temp.NewTerm(coef, this->terms_[poly_one_iter].exp);
			poly_one_iter++;
		}
	}

	while (poly_one_iter < this->num_terms_)
	{
		float coef;

		coef = this->terms_[poly_one_iter].coef;
		temp.NewTerm(coef, this->terms_[poly_one_iter].exp);
		poly_one_iter++;
	}

	while (poly_two_iter < poly.num_terms_)
	{
		float coef;

		coef = poly.terms_[poly_two_iter].coef;
		temp.NewTerm(coef, poly.terms_[poly_two_iter].exp);
		poly_two_iter++;
	}

	return temp;
}

void SparsePolynomial::Print()
{
	bool is_first = true; // 더하기 출력시 확인용

	for (int i = 0; i < num_terms_; i++)
	{
		// 0이 아닌 항들만 골라서 출력할 필요가 없음

		if (!is_first)
			cout << " + "; // 첫 항이 아니라면 사이사이에 더하기 출력

		cout << terms_[i].coef;

		if (terms_[i].exp != 0) cout << "*" << "x^" << terms_[i].exp;

		is_first = false;
	}

	cout << endl;
}