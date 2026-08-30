// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 mismatch over a narrow istreambuf_iterator and a plain char
// pointer. The iterator's cache fill, its comparison and the streambuf bump
// all stay external here, which is what leaves the loop itself as the only
// code this body emits.

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

template <class T1, class T2>
struct pair
{
	T1 first;
	T2 second;

	pair(const T1 &a, const T2 &b) : first(a), second(b) {}
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	typename Traits::int_type sbumpc();
};

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	CharT operator*() const { this->_M_getc(); return _M_c; }
	istreambuf_iterator<CharT, Traits> &operator++()
	{
		this->_M_bumpc();
		return *this;
	}

	bool equal(const istreambuf_iterator<CharT, Traits> &other) const;

private:
	void _M_getc() const;
	void _M_bumpc()
	{
		_M_buf->sbumpc();
		_M_have_c = false;
	}

	basic_streambuf<CharT, Traits> *_M_buf;
	mutable CharT _M_c;
	mutable unsigned char _M_eof;
	mutable unsigned char _M_have_c;
};

template <class CharT, class Traits>
inline bool operator!=(const istreambuf_iterator<CharT, Traits> &lhs,
		const istreambuf_iterator<CharT, Traits> &rhs)
{
	return !lhs.equal(rhs);
}

template <class _InputIter1, class _InputIter2>
pair<_InputIter1, _InputIter2> mismatch(_InputIter1 __first1,
		_InputIter1 __last1, _InputIter2 __first2)
{
	while (__first1 != __last1 && *__first1 == *__first2) {
		++__first1;
		++__first2;
	}
	return pair<_InputIter1, _InputIter2>(__first1, __first2);
}

template pair<istreambuf_iterator<char, char_traits<char> >, const char *>
mismatch(istreambuf_iterator<char, char_traits<char> >,
		istreambuf_iterator<char, char_traits<char> >, const char *);

}
