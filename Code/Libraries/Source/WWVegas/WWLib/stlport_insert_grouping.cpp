// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Dedicated TU for STLport __insert_grouping. The aux template lives in
// stlport_float_format.cpp but that unit already holds matched bodies.

#include <algorithm>
#include <string>

_STLP_BEGIN_NAMESPACE

int __cdecl __insert_grouping(
	char *first, char *last, const string &grouping,
	char separator, char Plus, char Minus, int basechars)
{
	typedef string::size_type str_size;

	if (first == last)
		return 0;

	int sign = 0;

	if (*first == Plus || *first == Minus) {
		sign = 1;
		++first;
	}

	first += basechars;
	str_size n = 0;
	char *cur_group = last;
	int groupsize = 0;

	while (true) {
		groupsize = n < grouping.size() ? grouping[n] : groupsize;
		++n;

		if (groupsize <= 0 || groupsize >= cur_group - first)
			break;

		cur_group -= groupsize;
		++last;
		copy_backward(cur_group, last, last + 1);
		*cur_group = separator;
	}

	return (last - first) + sign + basechars;
}

// ?__insert_grouping@_STL@@YAHPAG0ABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@1@GGGH@Z present-unmatched
int __cdecl __insert_grouping(
	wchar_t *first, wchar_t *last, const string &grouping,
	wchar_t separator, wchar_t Plus, wchar_t Minus, int basechars)
{
	typedef string::size_type str_size;

	if (first == last)
		return 0;

	int sign = 0;

	if (*first == Plus || *first == Minus) {
		sign = 1;
		++first;
	}

	first += basechars;
	str_size n = 0;
	wchar_t *cur_group = last;
	int groupsize = 0;

	while (true) {
		groupsize = n < grouping.size() ? grouping[n] : groupsize;
		++n;

		if (groupsize <= 0 || groupsize >= cur_group - first)
			break;

		cur_group -= groupsize;
		++last;
		copy_backward(cur_group, last, last + 1);
		*cur_group = separator;
	}

	return (last - first) + sign + basechars;
}

_STLP_END_NAMESPACE
