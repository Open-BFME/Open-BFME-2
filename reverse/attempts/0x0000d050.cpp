// ??$__put_integer@V?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@YA?AV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@0@PAD0V10@AAVios_base@0@HD@Z
// partial score=0.9719626168224299 date=2026-09-07
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 _num_put.c narrow grouping helper, RVA 0xD050 / 214.
// 208/214 strict bytes match. Remaining offsets: 0x21,0x47,0x4D,0x57,0x70,0x74.
// Actual vendor types reproduce the old hand-written interface exactly;
// the declaration-only __copy_aux retains the established out-of-line body.
// A named empty dispatch tag suppresses the six-byte temporary zeroing store.
// Retail overlays the empty tag and prefix count in the dead iend parameter
// home. An empty-base count policy fixes all six storage offsets, but swaps
// EBX/EBP roles and differs at 20 bytes. A 32-bit bitfield, inherited count,
// nested count, and inline getter all reproduce that same register swap.
// Primary full monetary.cpp context also fails to reproduce the wide cleanup
// mix; these observations are not evidence that conversion is impossible.
// Prior bank notes about exhaustive compiler-flag sweeps remain in git history.
// No ASM or inline assembly; no altered shared headers or new symbol pins.
/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */ 

#include <locale>
namespace _STL {
typedef ostreambuf_iterator<char,char_traits<char> > narrow_output_iterator;
template <> char* __copy_aux<char*,char*>(char*,char*,char*,const __true_type&);
template <> narrow_output_iterator __copy_integer_and_fill<char,narrow_output_iterator>(const char*,ptrdiff_t,narrow_output_iterator,ios_base::fmtflags,streamsize,char,char,char);
template <>
narrow_output_iterator __put_integer<narrow_output_iterator>(
		char *buf, char *iend, narrow_output_iterator s,
		ios_base &f, ios_base::fmtflags flags, char fill)
{
	ptrdiff_t len = iend - buf;

	const numpunct<char> &np =
			*(const numpunct<char> *)f._M_numpunct_facet();
	const string &grouping = f._M_grouping();

	if (!grouping.empty())
	{
		int basechars;
		if (flags & ios_base::showbase)
			switch (flags & ios_base::basefield)
			{
			case ios_base::hex:
				basechars = 2;
				break;
			case ios_base::oct:
				basechars = 1;
				break;
			default:
				basechars = 0;
			}
		else
			basechars = 0;

		// make sure there is room at the end of the buffer
		// we pass to __insert_grouping
		char grpbuf[64];
		__true_type tag;
__copy_aux(buf, iend, (char *)grpbuf, tag);
		buf = grpbuf;
		iend = grpbuf + len;
		len = __insert_grouping(buf, iend, grouping, np.thousands_sep(),
				'+', '-', basechars);
	}

	return __copy_integer_and_fill(buf, len, s, flags, f.width(0), fill,
			'+', '-');
}

}
