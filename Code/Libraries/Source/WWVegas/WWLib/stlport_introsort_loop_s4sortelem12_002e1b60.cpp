// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME5: _STL::__introsort_loop<S4SortElem12 *, S4SortElem12, int,
// S4Cmp002E1690>, retail 0x002E1B60, 259 bytes.  The twelve-byte element
// carries a narrow StringBase member and a byte flag, so STLport emits the
// member copy constructor while it partitions the range.

#include <algorithm>

template <class T>
class StringBase
{
private:
	StringBase(const StringBase<T> &other);
	void releaseBuffer(void);
	~StringBase(void) { releaseBuffer(); }
	T *m_bfmeData;

	friend struct S4SortElem12;
};

#include "../../../../GameEngine/Include/Common/S4SortElem12.h"

struct S4Cmp002E1690
{
	int m_bfmeSlot;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
	{
		return left.m_bfmeA < right.m_bfmeA;
	}
};

// The heap helpers are rowed in stlport_adjust_heap_s4sortelem12_00331c05.cpp
// (0x00331C05 / 0x00331A91) and Rva002E0BC0PopHeap12_Rva00331dae.cpp
// (0x00331DAE); bind to them instead of emitting this unit's copies.
namespace _STL { template <> void __adjust_heap<S4SortElem12 *,int,S4SortElem12,S4Cmp002E1690>(S4SortElem12 *,int,int,S4SortElem12,S4Cmp002E1690); }
namespace _STL { template <> void __push_heap<S4SortElem12 *,int,S4SortElem12,S4Cmp002E1690>(S4SortElem12 *,int,int,S4SortElem12,S4Cmp002E1690); }
namespace _STL { template <> void __pop_heap<S4SortElem12 *,S4SortElem12,S4Cmp002E1690,int>(S4SortElem12 *,S4SortElem12 *,S4SortElem12 *,S4SortElem12,S4Cmp002E1690,int *); }

void Rva002E00E0Swap(S4SortElem12 &left, S4SortElem12 &right);

namespace _STL
{

void iter_swap(S4SortElem12 *left, S4SortElem12 *right)
{
	Rva002E00E0Swap(*left, *right);
}

template void __introsort_loop<S4SortElem12 *, S4SortElem12, int,
	S4Cmp002E1690>(S4SortElem12 *, S4SortElem12 *, S4SortElem12 *, int,
	S4Cmp002E1690);

}
