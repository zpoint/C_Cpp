#include <iostream>
#include <string>
#include <limits>
#include <utility>

class Book {
		public:
			std::string bookNo = "";
			double price = 0;
			unsigned unit_sold = 0;
			Book(std::string s, double pri, unsigned cnt): bookNo(s), price(pri), unit_sold(cnt) { }
			Book() = default;
			Book(Book &&p) noexcept : bookNo(p.bookNo), price(p.price), unit_sold(p.unit_sold) { }
			Book& operator=(const Book &rhs) { bookNo = rhs.bookNo; price = rhs.price; unit_sold = rhs.unit_sold; return *this; }
};

/*
 * Etc...
 * Data ===> time, size... etc
 * Employee ===> name, sex, position... etc
 * ...
 */

std::istream& operator>>(std::istream &is, Book &item)
{
		std::cout << "preparing to cin" << std::endl;
		is >> item.bookNo >> item.price >> item.unit_sold;
		if (!is)
		{
				Book bk;
				item = bk;
				is.clear();
				is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		return is;
}

std::ostream& operator<<(std::ostream &os, const Book &item)
{
		os << item.bookNo << " " << item.unit_sold << " " << item.price;
		return os;
}

int main()
{
		Book bk, bk2;
		bk = bk2;
		std::cin >> bk;
		std::cin >> bk2;
		std::cout << bk << std::endl;
		std::cout << bk2 << std::endl;
		return 0;
}
