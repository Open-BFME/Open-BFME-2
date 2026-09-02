// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Two of the narrow basic_streambuf base defaults, written out rather than
// instantiated. basic_streambuf<char> is an explicit specialisation in the
// vendored headers, so `template class` on it is C2950 and no user TU emits
// its members - the wide facet has no such problem, which is why
// stlport_wide_streambuf.cpp covers the wide side of this vtable.
//
// Both bodies are the upstream defaults from vendor/stlport/stl/_streambuf.h:
// underflow and pbackfail each return eof, which for char_traits<char> is the
// int -1, so each is an or eax, -1 and a return. The narrow streambuf vtable
// holds 0x0001CA70 in both slot 9 and slot 12, so overflow folded onto
// pbackfail; that alias is pinned rather than given a row of its own.

namespace _STL
{

template <class T>
class char_traits
{
public:
	typedef int int_type;

	static int_type eof() { return -1; }
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	typedef typename Traits::int_type int_type;

	virtual ~basic_streambuf() {}

protected:
	virtual int_type underflow() { return Traits::eof(); }
	virtual int_type pbackfail(int_type c) { return Traits::eof(); }
};

template class basic_streambuf<char, char_traits<char> >;

}
