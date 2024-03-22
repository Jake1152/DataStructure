
#include "MyString.h"
#include <cstring>

using namespace std;

// 비어 있는 MyString() 생성
MyString::MyString()
{
	str_ = nullptr;
	size_ = 0;
}

// 맨 뒤에 널 캐릭터'\0'가 들어 있는 문자열로부터 초기화
MyString::MyString(const char* init)
{
	// 크기(size_) 결정
	this->size_ = std::strlen(init);

	// 메모리 할당
	this->str_ = new char[this->size_];

	// 데이터 복사
	// std::strncpy(this->str_, init); // \0 안넣고 처리, 어차피 size_가 있으니 없어도 가능
	for (size_t idx = 0; idx < this->size_; idx++)
		this->str_[idx] = init[idx];
}

// MyString의 다른 instance로부터 초기화
MyString::MyString(const MyString& str)
{
	// 기본 복사 생성자는 포인터 주소만 복사하기 때문에 
		// 얕은 복사를 의미하는가?
	// 소멸시 오류 발생
	// 여기서는 새로 메모리를 할당 받아서 복사
	// return ;
	// MyString = this->Insert(str, 0); // 쓰고 싶었지만 값을 리턴하니까 무의미
	this->size_ = str.size_;
	this->str_ = new char[this->size_];
	for (size_t idx = 0; idx < this->size_; idx++)
		this->str_[idx] = str.str_[idx];
}

MyString::~MyString()
{
	// 메모리 해제
	delete this->str_;
	this->str_ = nullptr;
	this->size_ = 0;
}


bool MyString::IsEmpty()
{
	return Length() == 0;
}

bool MyString::IsEqual(const MyString& str) // 편의상 참조& 사용
{
	// 힌트: str.str_, str.size_ 가능
	// str.Length(); // 왜 에러인가?
	if (this->size_ != str.size_)
		return false;
	for (size_t idx = 0; idx < this->size_; idx++)
		if (this->str_[idx] != str.str_[idx])
			return false;
	return true;
}

size_t	MyString::Length()
{
	return this->size_;
}

/**
 * 사이즈가 더 작아지는 경우는?
*/
void MyString::Resize(int new_size)
{
	// 메모리 재할당과 원래 갖고 있던 내용 복사
	if (this->size_ == 0)
	{
		// Do something
	}
	else
	{
		// this->size_;
	}
}

// 인덱스 start위치의 글자부터 num개의 글자로 새로운 문자열 만들기
MyString MyString::Substr(int start, int num)
{
	// 복사할 인덱스: start, start + 1, ... , start + num - 1
	// assert(start + num - 1 < this->size_); // 문제를 단순하게 만들기 위해 가정

	MyString temp;

	// TODO:

	return temp;
}

/**
 * Insert 이용
*/
MyString MyString::Concat(MyString app_str)
{
	MyString temp;

	// TODO: 

	return temp;
}

/**
 * # 고려사항
 * - 할당 실패케이스 감안?
 * - assert로 된 부분 에러 문구는 발생하되 return이 있도록 실행흐름이 이어지게 하기
 * 
 * # 로직 흐름
 * 삼등분하여 복사 진행
 * 1. start 이전
 * 2. start부터 target문자열 길이만큼
 * 3. start + strlen(target) ~ size_ + strlen(target)
*/
MyString MyString::Insert(MyString target, int start)
{
	assert(start >= 0);
	assert(start <= this->size_);

	MyString	temp;
	size_t		target_size;

	target_size = target.Length();
	temp.str_ = new char[target_size + this->size_];
	// TODO:
	// 1. start 이전 부분 복사 
	for (size_t idx = 0; idx < start; idx++)
		temp.str_[idx] = target.str_[idx];
	// this->str_[idx] = init[idx];
	// * 2. start부터 start + target문자열 길이만큼
	for (size_t idx = start; idx < start + target_size; idx++)
		temp.str_[idx] = target.str_[idx];
	// * 3. start + strlen(target) ~ size_ + strlen(target)
	for (size_t idx = start + target_size; idx < this->size_ + target_size; idx++)
		temp.str_[idx] = target.str_[idx];

	return temp;
}

/**
 * 특정 문자열이 포함되어 있는가?
 * strstr => \0이 MyString 멤버변수 str_에는 없으므로 사용 불가.
 * strncmp()를 쓴다
*/
int MyString::Find(MyString pat)
{
	//TODO:
	// pat.str_;
	// char *char_pos = std::strstr(this->str_, pat.str_);
	// str 불가 이유는 \0을 기준으로 찾으니까 불가.
	// if (char_pos)
	// 	return char_pos - this->str_;
	for (size_t idx = 0; idx < this->size_; idx++)
	{
		if (std::strncmp(&(this->str_[idx]), pat.str_, pat.size_) == 0)
			return idx;
	}
	return -1;
}

void MyString::Print()
{
	for (int idx = 0; idx < size_; idx++)
		std::cout << str_[idx];
	std::cout << endl;
}

// Resize가 적합할 듯
// void MyString::Copy(const char* init)
// {
// 	// 혹시 안맞을 수도 있는 size 측정용
// 	// this->CalSize(init);
// 	for (size_t idx = 0; idx < this->size_; idx++)
// 		this->str_[idx] = init[idx];
// }

// size_t MyString::CalSize(const char *init)
// {
// 	return std::strlen(init);
// }
