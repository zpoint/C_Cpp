#include <string>
#include <iostream>

class Token
{
		public:
			Token(): tok(INT), ival{0} { }
			Token(const Token &t): tok(t.tok) { copyUnion(t); }
			Token &operator=(const Token&);
			~Token() { if (tok == STR) sval.~basic_string(); }
			Token &operator=(const std::string&);
			Token &operator=(char);
			Token &operator=(int);
			Token &operator=(double);
		private:
			enum {INT, CHAR, DBL, STR} tok;
			union {
					char cval;
					int ival;
					double dval;
					std::string sval;
			};
			void copyUnion(const Token&);
};

Token &Token::operator=(int i)
{
		if (tok == STR) sval.~basic_string();
		ival = i;
		tok = INT;
		return *this;
}

Token &Token::operator=(char c)
{
		if (tok == STR) sval.~basic_string();
		cval = c;
		tok = CHAR;
		return *this;
}

Token &Token::operator=(double d)
{
		if (tok == STR) sval.~basic_string();
		dval = d;
		tok = DBL;
		return *this;
}

Token &Token::operator=(const std::string &s)
{
		if (tok == STR)
				sval = s;
		else
				new(&sval) std::string(s);
		tok = STR;
		return *this;
}

void Token::copyUnion(const Token &t)
{
		switch (t.tok)
		{
				case Token::INT: ival = t.ival; break;
				case Token::CHAR: cval = t.cval; break;
				case Token::DBL: dval = t.dval; break;
				case Token::STR: new(&sval) std::string(t.sval); break;
		}
}

Token &Token::operator=(const Token &t)
{
		if (tok == STR && t.tok != STR) sval.~basic_string();
		if (tok == STR && t.tok == STR)
				sval = t.sval;
		else
				copyUnion(t);
		tok = t.tok;
		return *this;
}

int main()
{
		Token t, t2;
		t = 3;
		t = 4.5;
		t = "123";
		t2 = 22;
		t2 = t;
		return 0;
}
