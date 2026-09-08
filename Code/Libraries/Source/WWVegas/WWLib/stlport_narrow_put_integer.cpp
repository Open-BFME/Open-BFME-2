// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Modified STLport 4.5.3 stl/_num_put.c and stl/_algobase.h.
// The narrow integer grouping helper reads the stream's cached numpunct and
// grouping directly, copies only when grouping is enabled, then resets width.
//
// Keep the original pointer-copy body visible but out of line. This lets MSVC
// know that the empty dispatch tag is unused, so its storage can overlap the
// prefix-count slot. An opaque declaration caused the six stack-displacement
// differences in the old bank; no artificial storage policy is needed.
//
// __copy_aux is 41 bytes at RVA 0x179B0; __put_integer is 214 bytes at 0xD050.
// Both complete returns and all existing callees are verified. The copy IAT
// is independently named msvcr71.dll!memmove at VA 0xBBA688.
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
template <> __declspec(noinline) char* __copy_aux<char*,char*>(char* first,char* last,char* result,const __true_type&) {
 return (char*)__copy_trivial(first,last,result);
}
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
		copy(buf, iend, (char *)grpbuf);
		buf = grpbuf;
		iend = grpbuf + len;
		len = __insert_grouping(buf, iend, grouping, np.thousands_sep(),
				'+', '-', basechars);
	}

	return __copy_integer_and_fill(buf, len, s, flags, f.width(0), fill,
			'+', '-');
}

}
