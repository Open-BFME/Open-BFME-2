// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport

typedef unsigned short wchar_t;

namespace _STL
{

template <class T>
class char_traits {};

template <class CharT, class Traits>
class basic_streambuf;

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	bool equal(const istreambuf_iterator &) const;

private:
	void _M_getc() const;

	basic_streambuf<CharT, Traits> *_M_buf;
	mutable CharT _M_c;
	mutable unsigned char _M_eof;
	mutable unsigned char _M_have_c;
};

template <class CharT, class Traits>
bool istreambuf_iterator<CharT, Traits>::equal(
		const istreambuf_iterator &other) const
{
	if (_M_buf != 0)
		_M_getc();
	if (other._M_buf != 0)
		other._M_getc();
	return _M_eof == other._M_eof;
}

typedef istreambuf_iterator<wchar_t, char_traits<wchar_t> > wide_iterator;

template bool wide_iterator::equal(const wide_iterator &) const;

}
