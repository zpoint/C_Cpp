#include <string>
#include <iostream>

class Quote
{
		public:
			Quote() { std::cout << "Calling default constructor of Quote" << std::endl; };
			Quote(const std::string &book, double sales_price):
					bookNo(book), price(sales_price) { std::cout << "Calling 4 paramters constrctor of Quote" << std::endl; }
			std::string isbn() const { return bookNo; }
			virtual double net_price(std::size_t n) const { return n * price; }
			virtual ~Quote() = default;
		private:
			std::string bookNo;
		protected:
			double price = 0.0;
};

class Disc_quote : public Quote
{
		public:
			Disc_quote() = default;
			Disc_quote(const std::string& book, double price, std::size_t qty, double disc):
					Quote(book, price), quantity(qty), discount(disc) { }
			double net_price(std::size_t) const = 0;
		protected:
			std::size_t quantity = 0;
			double discount = 0.0;
};

class Bulk_quote : public Disc_quote
{
		public:
			Bulk_quote() = default;
			Bulk_quote(const std::string& book, double price,
							std::size_t qty, double disc):
					Disc_quote(book, price, qty, disc) { }
			double net_price(std::size_t) const override;
};

double Bulk_quote::net_price(std::size_t size) const
{
		std::cout << "Bulk_quote::net_price, size: " << size << std::endl;
	   return size * discount;
}	   

int main()
{
		Bulk_quote b;
		return 0;
}
