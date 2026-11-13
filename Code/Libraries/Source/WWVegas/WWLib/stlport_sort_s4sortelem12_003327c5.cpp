// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME5: _STL::sort<S4SortElem12 *, S4Cmp002E1690> family, second retail
// copy around 0x00331A46-0x0033280A (sort 0x003327C5, sole caller 0x00332849).
// Same element and comparator as stlport_introsort_loop_s4sortelem12_002e1b60.cpp,
// whose __unguarded_partition / __partial_sort / make_heap rows already sit in
// this range. Bodies are placed by the REL32 graph from sort 0x003327C5 and
// accepted only where byte-equal. Element copies call the rowed record copy
// 0x00331962 and assignments the rowed record assign 0x00331759 (pinned).

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
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void __linear_insert<S4SortElem12 *,S4SortElem12,S4Cmp002E1690>(S4SortElem12 *,S4SortElem12 *,S4SortElem12,S4Cmp002E1690); }
// The rowed copies live in StringRecordCopyBFME2.cpp (0x00331A46) and
// Rva002E0BC0PopHeap12_Rva00331dae.cpp (0x00331DAE); bind to them.
namespace _STL { template <> void __unguarded_linear_insert<S4SortElem12 *,S4SortElem12,S4Cmp002E1690>(S4SortElem12 *,S4SortElem12,S4Cmp002E1690); }
namespace _STL { template <> void __pop_heap<S4SortElem12 *,S4SortElem12,S4Cmp002E1690,int>(S4SortElem12 *,S4SortElem12 *,S4SortElem12 *,S4SortElem12,S4Cmp002E1690,int *); }
namespace _STL { template <> S4SortElem12 *__unguarded_partition<S4SortElem12 *,S4SortElem12,S4Cmp002E1690>(S4SortElem12 *,S4SortElem12 *,S4SortElem12,S4Cmp002E1690); }

// The heap helpers are rowed in stlport_adjust_heap_s4sortelem12_00331c05.cpp
// (0x00331C05 / 0x00331A91) and Rva002E0BC0PopHeap12_Rva00331dae.cpp
// (0x00331DAE); bind to them instead of emitting this unit's copies.
namespace _STL { template <> void __adjust_heap<S4SortElem12 *,int,S4SortElem12,S4Cmp002E1690>(S4SortElem12 *,int,int,S4SortElem12,S4Cmp002E1690); }
namespace _STL { template <> void __push_heap<S4SortElem12 *,int,S4SortElem12,S4Cmp002E1690>(S4SortElem12 *,int,int,S4SortElem12,S4Cmp002E1690); }

void Rva002E00E0Swap(S4SortElem12 &left, S4SortElem12 &right);

namespace _STL
{

// Rowed in stlport_introsort_loop_s4sortelem12_002e1b60.cpp (0x00331BD2).
void iter_swap(S4SortElem12 *left, S4SortElem12 *right);

template void sort<S4SortElem12 *, S4Cmp002E1690>(S4SortElem12 *, S4SortElem12 *, S4Cmp002E1690);

}
