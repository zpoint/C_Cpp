#include <iostream>
#include <string>
#include <memory>
#include <utility>

class StrVec {
		public:
				StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr) { }
				StrVec(const StrVec&);
				StrVec &operator=(const StrVec&);
				~StrVec();

				StrVec(const std::initializer_list<std::string>);
				void push_back(const std::string&);
				size_t size() const { return cap - elements; }
				size_t capacity() const { return cap - elements; }
				std::string *begin() const { return elements; }
				std::string *end() const { return first_free; }
		private:
				static std::allocator<std::string> alloc;
				void chk_n_alloc() { if (size() == capacity()) reallocate(); }
				std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
				void free();
				void reallocate();
				std::string *elements;
				std::string *first_free;
				std::string *cap;
};

std::allocator<std::string> StrVec::alloc;

void StrVec::push_back(const std::string& s)
{
		chk_n_alloc();
		alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
		auto data = alloc.allocate(e - b);
		return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
		if (elements)
		{
				for (auto p = first_free; p != elements; )
						alloc.destroy(--p);
				alloc.deallocate(elements, cap - elements);
		}
}

void StrVec::reallocate()
{
		auto newcapacity = size() ? 2 * size() : 1;
		auto newdata = alloc.allocate(newcapacity);
		auto dest = newdata;
		auto elem = elements;
		for (size_t i = 0; i != size(); ++i)
				alloc.construct(dest++, std::move(*elem++));
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + newcapacity;
}

StrVec::StrVec(const StrVec &s)
{
		auto newdata = alloc_n_copy(s.begin(), s.end());
		elements = newdata.first;
		first_free = cap = newdata.second;
}

StrVec::~StrVec()
{
		free();
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
		auto data = alloc_n_copy(rhs.begin(), rhs.end());
		free();
		elements = data.first;
		first_free = cap = data.second;
		return *this;
}

StrVec::StrVec(const std::initializer_list<std::string> str_lst)
{
		std::cout << "Calling initializer_list constructor" << std::endl;
		auto iniptr = alloc.allocate(str_lst.size());
		auto last = std::uninitialized_copy(str_lst.begin(), str_lst.end(), iniptr);
		elements = iniptr;
		first_free = cap = last;
}


int main()
{
		StrVec ivec{"123", "456", "sdasd"};
		for (const auto &str : ivec)
				std::cout << str << " ";
		std::cout << std::endl;
		return 0;
}

