#include <iostream>
#include <string>

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

class Bulk_quote : public Quote
{
		public:
			Bulk_quote() { std::cout << "Default constructor of Bulk_quote" << std::endl; };
			Bulk_quote(const std::string& book, double p,
							std::size_t qty, double disc) : Quote(book, p), min_qty(qty), discount(disc) { }
			double net_price(std::size_t) const override;
		private:
			std::size_t min_qty = 0;
			double discount = 0.0;
};

double Bulk_quote::net_price(std::size_t cnt) const
{
		if (cnt >= min_qty)
				return cnt * (1 - discount) * price;
		else
				return cnt * price;
}

int main()
{
		Quote q;
		Bulk_quote bk;
		return 0;
}
