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

struct S4SortElem12
{
	int m_bfmeA;
	StringBase<char> m_bfmeName;
	char m_bfmeC;
};

struct S4Cmp002E1690
{
	int m_bfmeSlot;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
	{
		return left.m_bfmeA < right.m_bfmeA;
	}
};

void Rva002E00E0Swap(S4SortElem12 &left, S4SortElem12 &right);

namespace _STL
{

void iter_swap(S4SortElem12 *left, S4SortElem12 *right)
{
	Rva002E00E0Swap(*left, *right);
}

template void sort<S4SortElem12 *, S4Cmp002E1690>(S4SortElem12 *, S4SortElem12 *, S4Cmp002E1690);

}
