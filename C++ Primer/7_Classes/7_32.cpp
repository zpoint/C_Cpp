#include <iostream>
#include <string>
#include <vector>

class Screen {
		friend class Window_mgr;
		public:
				typedef std::string::size_type pos;
				Screen() = default;
				Screen(pos hei, pos wid): height(hei), width(wid) {}
				Screen(pos hei, pos wid, char c): height(hei), width(wid), contents(hei * wid, c) {}
				Screen &move(pos, pos);
				char get(pos, pos) const;
				Screen &set(char);
				Screen &set(pos, pos, char);
				Screen &display(std::ostream &os) { do_display(os); return *this; }
				const Screen &display(std::ostream &os) const { do_display(os); return *this; }

		private:
				pos cursor = 0;
				pos height = 0, width = 0;
				std::string contents;
				void do_display(std::ostream &os) const { os << contents; }
};

class Window_mgr {
		public:
				using ScreeIndex = std::vector<Screen>::size_type;
				void clear(ScreeIndex);
		private:
				std::vector<Screen> screens{Screen(24, 80, ' ')};
};

void Window_mgr::clear(ScreeIndex index)
{
		Screen &s = screens[index];
		s.contents = std::string(s.height * s.width, ' ');
}

Screen &Screen::move(pos r, pos c)
{
		pos row = r * width;
		cursor = row + c;
		return *this;
}

char Screen::get(pos r, pos c) const
{
		pos row = r *width;
		return contents[row + c];
}

inline Screen &Screen::set(char c)
{
		contents[cursor] = c;
		return *this;
}

inline Screen &Screen::set(pos r, pos col, char ch)
{
		contents[r*width + col] = ch;
		return *this;
}

int main()
{
		Screen myScreen(5, 5, 'X');
		myScreen.move(4, 0).set('#').display(std::cout);
		std::cout << "\n";
		myScreen.display(std::cout);
		std::cout << "\n";
		return 0;
}
