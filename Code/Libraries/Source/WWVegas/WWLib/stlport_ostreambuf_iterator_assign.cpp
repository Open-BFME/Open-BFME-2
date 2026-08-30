// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 ostreambuf_iterator character assignment. The streambuf's
// sputc stays the external library member the retail body calls, so the
// iterator body is the whole conversion.

typedef unsigned short wchar_t;

namespace _STL
{

template <class T>
class char_traits {};

template <>
class char_traits<char>
{
public:
	typedef int int_type;
};

template <>
class char_traits<wchar_t>
{
public:
	typedef wchar_t int_type;
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	typename Traits::int_type sputc(CharT value);
};

template <class CharT, class Traits>
class ostreambuf_iterator
{
public:
	ostreambuf_iterator &operator=(CharT value);

private:
	basic_streambuf<CharT, Traits> *_M_buf;
	bool _M_ok;
};

template <class CharT, class Traits>
ostreambuf_iterator<CharT, Traits> &
ostreambuf_iterator<CharT, Traits>::operator=(CharT value)
{
	_M_ok = _M_ok &&
			_M_buf->sputc(value) != static_cast<typename Traits::int_type>(-1);
	return *this;
}

template class ostreambuf_iterator<char, char_traits<char> >;
template class ostreambuf_iterator<wchar_t, char_traits<wchar_t> >;

}
