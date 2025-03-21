#include <iostream>
#include <string> // std::string

using namespace std;

template<typename K, typename V>
class HashTable
{
public:
	struct Item
	{
		K key = K();
		V value = V();
	};

	/**
	 * 해시함수가 복잡하더라도 충돌을 막을 수는 없다.
	 * 그렇기에 해시함수를 만들때는 충돌을 고려해서 만들어야 한다.
	*/

	HashTable(const int& cap = 8)
	{
		capacity_ = cap;
		table_ = new Item[capacity_];
	}

	~HashTable()
	{
		delete[] table_;
	}

	// Honglab
	void Insert(const Item& item)
	{
		size_t index = HashFunc(item.key);
		// key가 int 자료형일때는 0이면 비어있는 것으로 가정
		// key가 문자열 자료형일때는 길이가 0 비어있는 것으로 가정

		if (table_[index].key != K())
			cout << "Collision!" << endl;

		for (int i = 0; i < capacity_; i++)
		{
			int temp = (index + i) % capacity_;
			if (table_[temp].key == K())
			{
				table_[temp] = item;
				return;
			}
		}
		cout << "Failed to insert" << endl;
	}

	/** OpenAddressing Way
	 * 
	*/
	// void Insert(const Item& item)
	// {
	// 	// TODO:
	// 	// size_t index = item.key; // 키를 인덱스로 사용
	// 	size_t index = HashFunc(item.key);

	// 	// bool type_result = std::is_same_v<decltype(item), std::string>;

	// 	// key가 int 자료형 일때는 0이면 비어있느 것으로 가정

	// 	// key가 문자열 일때는 ㅣㄹ이가 0이면 비어있느 것으로 가정
		
	// 	// cout << "type_result  : " << type_result  << "\ttypeid(table_[index].key).name() : " << typeid(table_[index].key).name() << endl;
	// 	// K() 생성자 호출을 이용하여, 문자열은 "", 숫자는 0으로 초기화되게 하고 그것을 이용하여 비었는지를 판단한다.
	// 	while (table_[index].key != K()) /** && index < table_size*/
	// 		index++;
	// 	table_[index] = item;
	// }

	V Get(const K& key)
	{
		// TODO: 못 찾으면 0을 반환
		size_t index = HashFunc(key);
		
		// Honglab Way
		for (int i = 0; i < capacity_; i++)
		{
			// index = (index + i) % capacity_;
			size_t compare_index = (index + i) % capacity_;
			if (table_[compare_index].key == key)
				return table_[compare_index].value;
		}
		return V();
	}

	// 정수 -> 해시값
	size_t HashFunc(const int& key)
	{
		// TODO:
		size_t result = key % this->capacity_;
		// std::cout << "\nresult : " << result << std::endl;
		return result;
	}

	// 문자열을 정수 인덱스(해시값)로 변환
	// Horner's method
	size_t HashFunc(const string& s)
	{
		size_t key = 0;

		// "ABC"
		// "BCA"
		// index = g * (g * int('A") + int('B')) + int('C');
		const int g = 31;
		for (size_t idx = 0; idx < s.length(); idx++)
			key =  g * key + int(s.at(idx));
			// s.at(idx) + '0';
		// std::cout << "key : " << key << std::endl;
		// TODO:
		size_t result = key % this->capacity_;
		// std::cout << "\nresult : " << result << std::endl;
		return result;
	}

	void Print()
	{
		for (int i = 0; i < capacity_; i++)
			cout << i << " : " << table_[i].key << " " << table_[i].value << endl;
		cout << endl;
	}
	/**
	 * 이미지 검색은 어떤 과정으로 되는가?
	*/

private:
	Item* table_ = nullptr;
	int capacity_ = 0;
};

int main()
{
	// 충돌 
	// - 개방 주소법: 선형 조사법
	// - 체이닝: 멤버 변수 Item* table_ 대신에 LinkedList<Item>* table_사용

	// 키: int, 값: int 인 경우
	// 키의 범위가 아주 크고 아이템의 개수는 적을 경우
	{
		using Item = HashTable<int, int>::Item;

		HashTable<int, int> h(8);

		h.Insert(Item{ 123, 456 });

		h.Print();

		cout << "Get 123 " << h.Get(123) << endl;

		h.Insert(Item{ 1000021, 9898 });

		h.Print();

		cout << "Get 1000021 " << h.Get(1000021) << endl;

		h.Insert(Item{ 1211, 999 }); // 충돌!

		h.Print();

		cout << "Get 123 " << h.Get(123) << endl;
		cout << "Get 1211 " << h.Get(1211) << endl;
	}

	// 키: std::string, 값: int
	/*
	*/
	{
		using Item = HashTable<string, int>::Item;

		HashTable<string, int> h(8);

		h.Insert(Item{ "apple", 1 });
		h.Insert(Item{ "orange", 2 });
		h.Insert(Item{ "mandarin", 4 });

		h.Print();

		cout << "apple " << h.Get("apple") << endl;
		cout << "orange " << h.Get("orange") << endl;
		cout << endl;

		h.Print();

		h.Insert(Item{ "tomato", 4 });

		h.Print(); 

		cout << "apple " << h.Get("apple") << endl;
		cout << "orange " << h.Get("orange") << endl;
		cout << "pineapple " << h.Get("pineapple") << endl;
		cout << endl;
	}
	return 0;
}