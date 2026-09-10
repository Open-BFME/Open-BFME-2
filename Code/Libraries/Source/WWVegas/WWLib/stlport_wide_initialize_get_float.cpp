// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Dedicated TU for STLport _Initialize_get_float(wchar_t). The wide-read-float
// unit only declares the helper and already holds a matched scanner.

#include <locale>

_STLP_BEGIN_NAMESPACE

void __cdecl _Initialize_get_float(
	const ctype<wchar_t> &ct,
	wchar_t &Plus, wchar_t &Minus,
	wchar_t &pow_e, wchar_t &pow_E,
	wchar_t *digits)
{
	char ndigits[11] = "0123456789";
	Plus = ct.widen('+');
	Minus = ct.widen('-');
	pow_e = ct.widen('e');
	pow_E = ct.widen('E');
	ct.widen(ndigits + 0, ndigits + 10, digits);
}

_STLP_END_NAMESPACE
