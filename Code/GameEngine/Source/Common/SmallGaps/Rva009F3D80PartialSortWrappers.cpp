// ?q3PartialSort009F3D80@@YAXPAUQ3SortElem8@@00UQ3SortCompare@@@Z
// ?q3PartialSort009F3DA0@@YAXPAUQ3SortElem8@@00UQ3SortCompare@@@Z
// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// BFME1 SmallGaps donor Rva009F3D80PartialSortWrappers.cpp (b1 pair
// 0x009F3D80/0x009F3DA0, 31 B each) retargeted: the Gen depth-zero callees
// are the landed STLport rows ??$__partial_sort@PAUS4SortElem8@@... at
// 0x00626530 (ascending) and 0x006265B0 (descending), so the donor Gen
// declarations resolve through the ledger with zero new pins. Q3SortElem8
// is layout-identical to S4SortElem8 (8 bytes); the reinterpret casts emit
// no code.
struct Q3SortElem8 { int m_a; int m_b; };
struct Q3SortCompare { int m_v; };

struct S4SortElem8
{
	int m_bfmeA;						// +0x00
	float m_bfmeKey;					// +0x04
};

struct S4Cmp00625BB0
{
	void *m_bfmeState;

	bool operator()(const S4SortElem8 &a, const S4SortElem8 &b) const
	{
		return a.m_bfmeKey < b.m_bfmeKey;
	}
};

struct S4Cmp00625C10
{
	void *m_bfmeState;

	bool operator()(const S4SortElem8 &a, const S4SortElem8 &b) const
	{
		return a.m_bfmeKey > b.m_bfmeKey;
	}
};

namespace _STL
{

template <class RandomAccessIterator, class Tp, class Compare>
void __partial_sort(RandomAccessIterator first,
	RandomAccessIterator middle, RandomAccessIterator last, Tp *,
	Compare comp);

}

// ?q3PartialSort009F3D80@@YAXPAUQ3SortElem8@@00UQ3SortCompare@@@Z
void q3PartialSort009F3D80(Q3SortElem8 *first, Q3SortElem8 *middle, Q3SortElem8 *last, Q3SortCompare comp)
{
	_STL::__partial_sort((S4SortElem8 *)first, (S4SortElem8 *)middle, (S4SortElem8 *)last, (S4SortElem8 *)0, (S4Cmp00625BB0 &)comp);
}
// ?q3PartialSort009F3DA0@@YAXPAUQ3SortElem8@@00UQ3SortCompare@@@Z
void q3PartialSort009F3DA0(Q3SortElem8 *first, Q3SortElem8 *middle, Q3SortElem8 *last, Q3SortCompare comp)
{
	_STL::__partial_sort((S4SortElem8 *)first, (S4SortElem8 *)middle, (S4SortElem8 *)last, (S4SortElem8 *)0, (S4Cmp00625C10 &)comp);
}
