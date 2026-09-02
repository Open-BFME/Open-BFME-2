// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 mismatch over a WIDE istreambuf_iterator and a plain wchar_t
// pointer, plus the money_get helper __get_string that wraps it. The
// iterator's cache fill, its comparison and the streambuf bump all stay
// external here, which is what leaves the loop itself as the only code the
// mismatch body emits.

typedef unsigned short wchar_t;

namespace _STL
{

template <class T>
class char_traits {};

template <>
class char_traits<wchar_t>
{
public:
	typedef wchar_t int_type;
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

template pair<istreambuf_iterator<wchar_t, char_traits<wchar_t> >, const wchar_t *>
mismatch(istreambuf_iterator<wchar_t, char_traits<wchar_t> >,
		istreambuf_iterator<wchar_t, char_traits<wchar_t> >, const wchar_t *);

template <class T1, class T2>
inline pair<T1, T2> make_pair(const T1 &a, const T2 &b)
{
	return pair<T1, T2>(a, b);
}

template <class _InIt1, class _InIt2>
pair<_InIt1, bool> __get_string(_InIt1 __first, _InIt1 __last,
		_InIt2 __str_first, _InIt2 __str_last)
{
	pair<_InIt1, _InIt2> __pr = mismatch(__first, __last, __str_first);
	return make_pair(__pr.first, __pr.second == __str_last);
}

template pair<istreambuf_iterator<wchar_t, char_traits<wchar_t> >, bool>
__get_string(istreambuf_iterator<wchar_t, char_traits<wchar_t> >,
		istreambuf_iterator<wchar_t, char_traits<wchar_t> >, const wchar_t *,
		const wchar_t *);

}
