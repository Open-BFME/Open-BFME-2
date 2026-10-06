// cl: /EHsc /MD /Oy- -Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport
//
// STLport __adjust_heap<S4SortElem12*, int, S4SortElem12,
// S4Cmp002E0CD0>, placed from a retail call at 0x00331DED in the byte-true
// Rva002E0BC0PopHeap body (0x00331DAE). The same specialization is called by
// the rowed make_heap body at 0x00331E28. The address pin records the
// REL32-derived target 0x00331C05; Ghidra gives that boundary as 165 bytes.
//
// Target evidence fixes a 12-byte by-value element. Retail compares the
// first dwords in the adjustment loop (0x00331C2C), so the stand-in functor
// compares that member through const references; its original meaning remains
// unknown.
// The BFME1 donor view supplies (int, AsciiString, char). Retail independently
// confirms the 12-byte stride, copy/assignment aliases at 0x00331962 and
// 0x00331759, and member teardown at +4 through the matched AsciiString dtor
// 0x00036410. The original application meaning remains unknown.
#include <algorithm>
#include "ascii_string.h"

struct S4SortElem12
{
	int m_bfmeKey;
	AsciiString m_bfmeText;
	char m_bfmeFlag;

	S4SortElem12(const S4SortElem12 &);
	S4SortElem12 &operator=(const S4SortElem12 &);
};

struct S4Cmp002E0CD0
{
	void *m_bfmeState;
	bool operator()(const S4SortElem12 &left, const S4SortElem12 &right) const
	{
		return left.m_bfmeKey < right.m_bfmeKey;
	}
};

namespace _STL
{
template void __adjust_heap<S4SortElem12 *, int, S4SortElem12,
	S4Cmp002E0CD0>(S4SortElem12 *, int, int, S4SortElem12, S4Cmp002E0CD0);
template void __push_heap<S4SortElem12 *, int, S4SortElem12,
	S4Cmp002E0CD0>(S4SortElem12 *, int, int, S4SortElem12, S4Cmp002E0CD0);
}
