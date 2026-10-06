// cl: /DNDEBUG /MD /Oy-
// ?Rva001F87D5Put@@YAAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@AAV12@ABUS001F87D5@@@Z @0x001F87D5 (59B): ostream float-pair put.
// Prints float at +4 then ' ' then float at +8 via rowed float operator<< at
// 0x001F8152 and rowed _M_put_char at 0x001F5E51. Callers at 0x001F8B8E,
// 0x0055B7C6, 0x0055C399. Prev Rva001F84A7Put next Rva001F8810Put share flags.
namespace _STL
{
template <class C> class char_traits
{
};

template <class C, class T> class basic_ostream
{
public:
	basic_ostream &operator<<(float f);
	void _M_put_char(char c);
};

template <class C, class T>
inline basic_ostream<C, T> &operator<<(basic_ostream<C, T> &os, char c)
{
	os._M_put_char(c);
	return os;
}
}

struct S001F87D5
{
	char _0[4];
	float x;
	float y;
};

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F87D5Put(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	const S001F87D5 &s)
{
	float y = s.y;
	((os << s.x) << ' ') << y;
	return os;
}
