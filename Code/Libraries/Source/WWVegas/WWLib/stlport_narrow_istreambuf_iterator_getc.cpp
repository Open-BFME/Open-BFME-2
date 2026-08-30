// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 narrow istreambuf_iterator cache fill. sgetc stays the
// external streambuf member the retail body calls.

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

template <class CharT, class Traits>
class basic_streambuf
{
public:
	typename Traits::int_type sgetc();
};

template <class CharT, class Traits>
class istreambuf_iterator
{
private:
	void _M_getc() const;

	basic_streambuf<CharT, Traits> *_M_buf;
	mutable CharT _M_c;
	mutable unsigned char _M_eof;
	mutable unsigned char _M_have_c;
};

template <class CharT, class Traits>
void istreambuf_iterator<CharT, Traits>::_M_getc() const
{
	if (_M_have_c)
		return;

	typename Traits::int_type value = _M_buf->sgetc();
	_M_c = static_cast<CharT>(value);
	_M_eof = value == static_cast<typename Traits::int_type>(-1);
	_M_have_c = true;
}

template class istreambuf_iterator<char, char_traits<char> >;

}
