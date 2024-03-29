#include "Polynomial.h"

#include <cassert>
#include <iostream>
#include <math.h> // std::powf()

using namespace std;

Polynomial::Polynomial(int max_degree) // 편의상 기본값 사용
{
	assert(max_degree > 0);

	// - 상수항 포함
	// - 예: max_degree가 2이면 c0*x^0 + c1*x^1 + c2*x^2 총 3개의 항들
	capacity_ = max_degree + 1;

	// 동적 메모리 할당
	coeffs_ = new float[capacity_];

	// 0으로 초기화
	for (int i = 0; i < capacity_; i++)
		coeffs_[i] = 0.00000f;
}

Polynomial::Polynomial(const Polynomial& poly)
{
	this->capacity_ = poly.capacity_;
	coeffs_ = new float[capacity_];
	for (int i = 0; i < capacity_; i++)
		coeffs_[i] = poly.coeffs_[i];
}

Polynomial::~Polynomial()
{
	if (coeffs_) delete[] coeffs_;
}

int Polynomial::MaxDegree()
{
	return this->capacity_ - 1;
}

/**
 * 항을 추가함
*/
void Polynomial::NewTerm(const float coef, const int exp)
{
	assert(exp < capacity_); // exp가 너무 크면 resize 하도록 구현할 수도 있음

	// TODO: 쉬워요
	this->coeffs_[exp] = coef;
}

/**
 * - 새로운 다항식의 있는 항에 있는 값이 현재 다항식에도 있는지 확인한 뒤에 degree를 더한다?
 * 
 * - max degree가 다르다면 작은 쪽의 maxdegree를 기준으로 두 식을 더 할 반복문의 반복 조건으로 정한다.
 *    exp < min(p1.cap, p2.cap)
 * - 작은 식의 max degree부터 큰 식의 maxdegree까지는 max degree의 제곱항들의 계수를 그대로 반영한다.
*/
Polynomial Polynomial::Add(const Polynomial& poly)
{
	// assert(poly.capacity_ == this->capacity_); // 문제를 단순화하기 위한 가정

	size_t added_poly_capacity = std::max(this->capacity_, poly.capacity_);
	Polynomial temp(std::max(this->capacity_, poly.capacity_));

	// TODO:
	size_t	for_loop_iter_max = std::min(this->capacity_, poly.capacity_);
	for (size_t exp = 0; exp < for_loop_iter_max; exp++)
		temp.coeffs_[exp] = this->coeffs_[exp] + poly.coeffs_[exp];

	const Polynomial	*temp_poly;

	temp_poly = this;
	if (this->capacity_ > poly.capacity_)
		temp_poly = &poly;
	for (size_t exp = for_loop_iter_max; exp < added_poly_capacity; exp++)
		temp.coeffs_[exp] = temp_poly->coeffs_[exp];

	return temp;
}

/**
 * 다항식의 곱셉
 * 
 * TODO 항이 100개가 넘는 경우에 대한 처리 가능하도록 변경
 * 1. 컴퓨터에서 완전한 0.0 표현이 안되는 이슈 때문에 일부항들의 값이 0.0f로 완전하게 초기화되지 않는 이슈 발생
 * 2. scala 곱을 만들어서 각 항에 특정 수를 곱하는 멤버함수를 구현
 *   - 스칼라 곱한 다항식을 Add() 멤버함수를 이용해서 Poly Mul()에 활용한다.
*/
Polynomial Polynomial::Mult(const Polynomial& poly)
{
	assert(poly.capacity_ == this->capacity_); // 문제를 단순화하기 위한 가정

	// 최고차항의 곱 
	size_t	temp_poly_max_degree = max(this->capacity_ - 1, 0) * max(poly.capacity_ - 1, 0);
	// Polynomial temp(temp_poly_max_degree);
	Polynomial temp(this->capacity_ - 1);
	// coeff_[i]가 0.0f가 아닌 경우에 대해서만 계산 (곱하면 0이 되기 때문)

	size_t max_degree = poly.capacity_ - 1;
	for (size_t exp = 0; exp < temp.capacity_; exp++)
		if (this->coeffs_[exp] != 0.00000f)
			for (size_t arg_poly_exp = 0; arg_poly_exp < poly.capacity_; arg_poly_exp++)
				if (poly.coeffs_[arg_poly_exp] != 0.00000f)
					temp.coeffs_[exp + arg_poly_exp] += this->coeffs_[exp] * poly.coeffs_[arg_poly_exp];

	return temp;
}

/**
 * 주어진 Polynomial에 X를 대입한 결과 
*/
float Polynomial::Eval(float x)
{
	float temp = 0.0f;

	// TODO:
	// 힌트 std::powf(2.0f, float(3)); // 2.0f^3.0f = 8.0f (2.0f의 3.0f 제곱)
	// 상수항 처리, 0의 0제곱은 UB, 편의상 1로 정의될수도 있지만 모든 곳에서 그렇게 정의했다는 보장이 없다.
	temp += this->coeffs_[0];
	for (size_t exp = 1; exp < this->capacity_; exp++)
		temp += (this->coeffs_[exp] * std::pow(x, exp));
	return temp;
}

void Polynomial::Print()
{
	bool is_first = true; // 더하기 출력시 확인용

	for (int i = 0; i < capacity_; i++)
	{
		if (coeffs_[i] != 0.0f) // 주의: 0이 아닌 항들만 출력
		{
			if (!is_first)
				cout << " + "; // 첫 항이 아니라면 사이사이에 더하기 출력

			cout << coeffs_[i];

			if (i != 0) cout << "*" << "x^" << i;

			is_first = false;
		}
	}

	cout << endl;
}