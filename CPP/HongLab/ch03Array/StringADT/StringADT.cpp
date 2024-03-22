#include "MyString.h"

using namespace std;

int main()
{
	// 생성자, MyString::Print()
	{
		MyString str1("hi hay he hel hello llo ello el el o!");
		str1.Print();
	}

	// Find()
	{
		MyString str1("hi hay he hel hello llo ello el el o!");
		cout << str1.Find(MyString("hell")) << endl;

		cout << "Found at " << MyString("ABCDEF").Find(MyString("A")) << endl;
		cout << "Found at " << MyString("ABCDEF").Find(MyString("AB")) << endl;
		cout << "Found at " << MyString("ABCDEF").Find(MyString("CDE")) << endl;
		cout << "Found at " << MyString("ABCDEF").Find(MyString("EF")) << endl;
		cout << "Found at " << MyString("ABCDEF").Find(MyString("EFG")) << endl;
		cout << "Found at " << MyString("ABCDEF").Find(MyString("EFGHIJ")) << endl;
	}

	// 복사 생성자
	{
		MyString str1("hi hay he hel hello llo ello el el o!");
		MyString str2 = str1; // MyString str2(str1);
		std::cout << "\n# Copy Constructor test" << std::endl;
		cout << boolalpha << str2.IsEqual(MyString(str1)) << endl;
		str2.Print();
	}

	// IsEqual()
	{
		MyString str3("Hello, World!");
		cout << boolalpha;
		cout << str3.IsEqual(MyString("Hello, World!")) << endl;
		cout << str3.IsEqual(MyString("Hay, World!")) << endl;
	}

	// Resize()
	{

		std::cout << "\n# Resize Test" << std::endl;
		MyString str1("Hello, World!");
		MyString str2(str1);

		str1.Print();
		str2.Resize(str2.Length() / 2);
		str2.Print();
		str2.Resize(str2.Length() / 2);
		str2.Print();
		str2.Resize(str2.Length() / 2);
		str2.Print();
		str2.Resize(str2.Length() / 2);
		str2.Print();
		std::cout << "str2.Length() : " << str2.Length() << std::endl;
	}

	// Insert()
	{
		std::cout << "\n# Insert Test" << std::endl;
		MyString str4("ABCDE");
		for (size_t i = 0; i <= str4.Length(); i++)
		{
			MyString str5 = str4.Insert(MyString("123"), i);
			str5.Print();
		}
	}

	// Substr()
	{
		std::cout << "\n# Substr Test" << std::endl;
		MyString str("ABCDEFGHIJ");

		str.Substr(3, 4).Print();
	}

	// Concat()
	{
		std::cout << "\n# Concat Test" << std::endl;
		MyString str1("Hello, ");
		MyString str2("World!");

		MyString str3 = str1.Concat(str2);

		str3.Print();
	}

	// while (1);
	return 0;
}
