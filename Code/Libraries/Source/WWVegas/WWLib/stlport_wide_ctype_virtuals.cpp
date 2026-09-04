// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// The single-character half of ctype<wchar_t>'s vftable at 0x007BBAD0. Slot
// order follows the same reversed-overload rule as ctype<char>: each range
// form sits below the single-character form declared before it, so the odd
// slots are ranges and 2, 6, 8, 10 and 12 are the ones here.
//
// do_is reads a table of 32-bit masks at 0x00BBBDDC, which is ctype<char>'s
// classic_table() - &_S_classic_table[1] - and do_toupper and do_tolower index
// the same _S_upper and _S_lower at 0x00BBC1E0 and 0x00BBC2E0 that
// ctype<char> uses. Above 255 each returns its argument unchanged.

#include <locale>

namespace _STL
{

bool ctype<wchar_t>::do_is(ctype_base::mask __m, wchar_t __c) const
{
	return (unsigned) __c < 256 && (ctype<char>::classic_table()[__c] & __m) != 0;
}

wchar_t ctype<wchar_t>::do_toupper(wchar_t __c) const
{
	return (unsigned) __c < 256 ? (wchar_t) ctype<char>::_S_upper[__c] : __c;
}

wchar_t ctype<wchar_t>::do_tolower(wchar_t __c) const
{
	return (unsigned) __c < 256 ? (wchar_t) ctype<char>::_S_lower[__c] : __c;
}

wchar_t ctype<wchar_t>::do_widen(char __c) const
{
	return (wchar_t) __c;
}

char ctype<wchar_t>::do_narrow(wchar_t __c, char __dfault) const
{
	return (char) ((char) __c == __c ? __c : __dfault);
}

}
