// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Wide twin of stlport_list_asciistring_insert.cpp (which holds the narrow
// 2-arg insert worker at 0x001FD72C). Retail 0x00043C072 (95 bytes) is the
// list<UnicodeString>::list(size_type) fill ctor: same shape as a narrow
// fill ctor except the value-temp teardown calls the WIDE StringBase
// releaseBuffer (pinned at 0x00036E70), which names the element type as
// wchar-based. The default ctor is defined inline (m_data null store, the
// retail `and [ebp-0x10],0`) and the dtor is defined inline as a direct
// releaseBuffer call (retail calls 0x00036E70, no out-of-line dtor). The
// _List_base ctor call targets the folded base at 0x004EC36C (rowed under
// the int instantiation) and the fill insert delegates to the worker at
// 0x0043BFA4; both arrive as twin pins.
#include <list>

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "unicode_string.h"


inline bool operator==(const UnicodeString &a, const UnicodeString &b) { return a.compare(b) == 0; }
bool operator<(const UnicodeString &a, const UnicodeString &b);

template class _STL::list<UnicodeString, _STL::allocator<UnicodeString> >;

// find(first, last, value) @0x00433BEE (42B) and its __find worker @0x00433B96 (39B).
typedef _STL::list<UnicodeString>::iterator UnicodeStringListIter;
template UnicodeStringListIter _STL::find<UnicodeStringListIter, UnicodeString>(UnicodeStringListIter, UnicodeStringListIter, const UnicodeString &);
