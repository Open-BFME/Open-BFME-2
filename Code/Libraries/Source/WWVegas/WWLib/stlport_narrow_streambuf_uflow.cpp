// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// The four basic_streambuf<char> base defaults nothing had reached: xsgetn,
// uflow, xsputn and _M_xsputnc, slots 6, 8, 10 and 11 of the vftable at
// 0x007BBC30. They are worth four tables, not one - stdio_istreambuf,
// stdio_ostreambuf and stdio_streambuf_base all inherit these same four
// addresses unchanged.
//
// uflow settles which basic_streambuf<char> the game links. It reaches its get
// area through [this+4] and then reads a pointer at [+0] and a count at [+4]
// of whatever that points to, decrementing the count and post-incrementing the
// pointer. That is a C FILE - _ptr and _cnt - so this build is STLport's
// stdio-backed specialisation, the one the vendored header declares, and not
// the three-pointer primary template. The other three follow from it: each
// asks the FILE for its available count rather than differencing two area
// pointers.

#include <locale>
#include <streambuf>

namespace _STL
{

streamsize basic_streambuf<char, char_traits<char> >::xsgetn(char *__s, streamsize __n)
{
	const int_type __eof = char_traits<char>::eof();
	streamsize __result = 0;

	while (__result < __n) {
		ptrdiff_t __avail = _FILE_I_avail(_M_get);
		if (__avail > 0) {
			size_t __chunk = (min) (__STATIC_CAST(size_t, __avail),
			                        __STATIC_CAST(size_t, __n - __result));
			char_traits<char>::copy(__s, _FILE_I_next(_M_get), __chunk);
			__result += __chunk;
			__s += __chunk;
			_FILE_I_bump(_M_get, __chunk);
		}
		else {
			int_type __c = this->sbumpc();
			if (!char_traits<char>::eq_int_type(__c, __eof)) {
				*__s = __c;
				++__result;
				++__s;
			}
			else
				break;
		}
	}

	return __result;
}

basic_streambuf<char, char_traits<char> >::int_type
basic_streambuf<char, char_traits<char> >::uflow()
{
	return char_traits<char>::eq_int_type(this->underflow(), char_traits<char>::eof())
	       ? char_traits<char>::eof()
	       : char_traits<char>::to_int_type(_FILE_I_postincr(_M_get));
}

streamsize basic_streambuf<char, char_traits<char> >::xsputn(const char *__s, streamsize __n)
{
	const int_type __eof = char_traits<char>::eof();
	streamsize __result = 0;

	while (__result < __n) {
		ptrdiff_t __avail = _FILE_O_avail(_M_put);
		if (__avail > 0) {
			size_t __chunk = (min) (__STATIC_CAST(size_t, __avail),
			                        __STATIC_CAST(size_t, __n - __result));
			char_traits<char>::copy(_FILE_O_next(_M_put), __s, __chunk);
			__result += __chunk;
			__s += __chunk;
			_FILE_O_bump(_M_put, __chunk);
		}
		else if (!char_traits<char>::eq_int_type(
		             this->overflow(char_traits<char>::to_int_type(*__s)), __eof)) {
			++__result;
			++__s;
		}
		else
			break;
	}
	return __result;
}

streamsize basic_streambuf<char, char_traits<char> >::_M_xsputnc(char __c, streamsize __n)
{
	const int_type __eof = char_traits<char>::eof();
	streamsize __result = 0;

	while (__result < __n) {
		ptrdiff_t __avail = _FILE_O_avail(_M_put);
		if (__avail > 0) {
			size_t __chunk = (min) (__STATIC_CAST(size_t, __avail),
			                        __STATIC_CAST(size_t, __n - __result));
			char_traits<char>::assign(_FILE_O_next(_M_put), __chunk, __c);
			__result += __chunk;
			_FILE_O_bump(_M_put, __chunk);
		}
		else if (!char_traits<char>::eq_int_type(
		             this->overflow(char_traits<char>::to_int_type(__c)), __eof))
			++__result;
		else
			break;
	}
	return __result;
}

}
