// cl: /DNDEBUG /MD
// ?Rva001F8810Put@@YAAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@AAV12@ABUVec001F8810@@@Z @0x001F8810 (110B): ostream X/Y/Z float triple put.
// Prints "X:" float " " "Y:" float " " "Z:" float via rowed _M_put_nowiden at
// 0x001F5F65, rowed float operator<< at 0x001F8152, rowed _M_put_char at
// 0x001F5E51. Caller at 0x001F8A11 prints key then " = " then vector then
// newline. Prev Rva001F84A7Put next Rb_tree clear.
namespace _STL
{
template <class C> class char_traits
{
};

template <class C, class T> class basic_ostream
{
public:
	void _M_put_nowiden(char const *s);
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

struct Vec001F8810
{
	float x;
	float y;
	float z;
};

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F8810Put(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	const Vec001F8810 &v)
{
	os._M_put_nowiden("X:");
	(os << v.x) << ' ';
	os._M_put_nowiden("Y:");
	(os << v.y) << ' ';
	os._M_put_nowiden("Z:");
	os << v.z;
	return os;
}
