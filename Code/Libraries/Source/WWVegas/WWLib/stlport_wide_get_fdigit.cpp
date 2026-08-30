// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 __get_fdigit and __get_fdigit_or_sep for wide input. Both fold
// a locale digit back to its ASCII form so the buffer handed to strtod is
// plain; the separator variant answers first and otherwise inlines the digit
// lookup whole. find over a const wchar_t* range folds onto the non-const
// instantiation already landed at 0x00010F60.

typedef unsigned short wchar_t;

namespace _STL
{

struct random_access_iterator_tag {};

template <class RandomAccessIter, class T>
RandomAccessIter __cdecl __find(RandomAccessIter first, RandomAccessIter last,
		const T &value, const random_access_iterator_tag &);

template <class InputIter, class T>
__declspec(dllimport) __forceinline InputIter find(InputIter first,
		InputIter last, const T &value)
{
	random_access_iterator_tag category;

	return __find(first, last, value, category);
}

bool __cdecl __get_fdigit(wchar_t &character, const wchar_t *digits)
{
	const wchar_t *position = find(digits, digits + 10, character);

	if (position != digits + 10)
	{
		character = static_cast<char>('0' + (position - digits));
		return true;
	}
	else
		return false;
}

bool __cdecl __get_fdigit_or_sep(wchar_t &character, wchar_t separator,
		const wchar_t *digits)
{
	if (character == separator)
	{
		character = static_cast<char>(',');
		return true;
	}
	else
		return __get_fdigit(character, digits);
}

}
