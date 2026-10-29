// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// STLport 4.6.2 numeric grouping, matching the semantic donor embedded in
// stlport_float_format.cpp (archive SHA256
// b506f0e79adc60663a0dbef7192efa0936566c0d5bcf67637807df70541b9fe3).
// The narrow external wrapper is native 0x1A600 / WB 0x6F1AB0; its jump
// targets the char auxiliary instantiation at 0x1A4A0 / WB 0x6F1950.
// The wide wrapper is native 0x1A610 / WB 0x6F1AC0, targeting the wide
// instantiation at 0x1A540 / WB 0x6F19F0. Each whole implementation and
// wrapper is independently byte verified.
// No original identity is inferred from instruction shape alone: the donor
// supplies the wrapper/template distinction and retail proves that split.
/*
 * Copyright (c) 1999 Silicon Graphics Computer Systems, Inc.
 * Copyright (c) 1999 Boris Fomitchev
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 * Modified to preserve the independently verified BFME2 compiler settings.
 */

#include <algorithm>
#include <string>

_STLP_BEGIN_NAMESPACE

template <class Char>
ptrdiff_t __cdecl __insert_grouping_aux(
	Char *first, Char *last, const string &grouping,
	Char separator, Char Plus, Char Minus, int basechars)
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
	Char *cur_group = last;
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

int __cdecl __insert_grouping(char *first, char *last, const string &grouping, char separator, char Plus, char Minus, int basechars)
{ return __insert_grouping_aux(first,last,grouping,separator,Plus,Minus,basechars); }

int __cdecl __insert_grouping(
	wchar_t *first, wchar_t *last, const string &grouping,
	wchar_t separator, wchar_t Plus, wchar_t Minus, int basechars)
{
	return __insert_grouping_aux(first, last, grouping, separator, Plus, Minus, basechars);
}

_STLP_END_NAMESPACE
