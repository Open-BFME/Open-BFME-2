// ?do_toupper@?$ctype@D@_STL@@MBEPBDPADPBD@Z
// partial score=0.75 date=2026-09-04
// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ctype<char>'s eight virtuals, from its vftable at 0x007BC3E4. The slot order
// confirms the overload rule found in num_put: within one name MSVC lays the
// overloads out in REVERSE declaration order, so each range form comes before
// the single-character form it was declared after -
//
//   1 do_toupper(range)   2 do_toupper(char)
//   3 do_tolower(range)   4 do_tolower(char)
//   5 do_widen(range)     6 do_widen(char)
//   7 do_narrow(range)    8 do_narrow(char, char)
//
// and the two tables the image indexes, 0x00BBC1E0 and 0x00BBC2E0, are
// _S_upper and _S_lower.

#include <locale>
#include <string.h>

namespace _STL
{

char ctype<char>::do_toupper(char __c) const
{
	return _S_upper[(unsigned char) __c];
}

char ctype<char>::do_tolower(char __c) const
{
	return _S_lower[(unsigned char) __c];
}

const char *ctype<char>::do_toupper(char *__low, const char *__high) const
{
	for ( ; __low < __high; ++__low)
		*__low = _S_upper[(unsigned char) *__low];
	return __high;
}

const char *ctype<char>::do_tolower(char *__low, const char *__high) const
{
	for ( ; __low < __high; ++__low)
		*__low = _S_lower[(unsigned char) *__low];
	return __high;
}

char ctype<char>::do_widen(char __c) const
{
	return __c;
}

const char *ctype<char>::do_widen(const char *__low, const char *__high,
                                  char *__to) const
{
	memcpy(__to, __low, __high - __low);
	return __high;
}

char ctype<char>::do_narrow(char __c, char) const
{
	return __c;
}

const char *ctype<char>::do_narrow(const char *__low, const char *__high,
                                   char, char *__to) const
{
	memcpy(__to, __low, __high - __low);
	return __high;
}

}
