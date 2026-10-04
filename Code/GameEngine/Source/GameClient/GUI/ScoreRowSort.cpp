// cl: /DNDEBUG /MD /EHsc /O1 /G7
// stlport
//
// Two STLport 4.5.3 sort(first, last) instantiations over 8-byte records
// ordered by a member operator< (0x005EC52E), built from the score-row family
// of the Open-BFME-1 donors (game/GameEngine/Source/GameClient/GUI/
// ScoreRowIntrosort.cpp and game/Libraries/Source/WWVegas/WWLib/
// stlport_{adjust,push}_heap_s4sortelem8_score.cpp at 1281192f68; donor
// /DNDEBUG /MD /EHsc plus BFME 2's /O1 /G7). The donor sweep placed
// __adjust_heap (0x0051D178) and __push_heap (0x005EC5F5) uniquely; the rest
// of the family follows from their callers and callees.
//
// Target evidence for the shape:
//   * both sorts (0x0051D9E1, called from 0x0051DB60, and 0x005ECD49, called
//     from 0x005ECDA8) take two arguments and pass an uninitialised stack word
//     as the comparator: sort(first, last) with the empty less<T>;
//   * every comparison is a call to 0x005EC52E, the element's operator<;
//   * the heap, insertion and partition leaves exist once and serve both
//     sorts, while sort, __introsort_loop, partial_sort, __partial_sort,
//     sort_heap, pop_heap and __final_insertion_sort exist twice with
//     identical code: the linker folded the identical leaves of two
//     instantiations but not the parents that named them.
// The records are stand-ins (S4SortElem8, S4SortElem8B): the image fixes
// only their size, bitwise copy and shared operator<.
#include <algorithm>

struct S4SortElem8
{
	int m_bfmeFirst;
	int m_bfmeSecond;

	bool operator<(const S4SortElem8 &other) const;
};

struct S4SortElem8B
{
	int m_bfmeFirst;
	int m_bfmeSecond;

	bool operator<(const S4SortElem8B &other) const;
};

template void _STL::sort<S4SortElem8 *>(S4SortElem8 *, S4SortElem8 *);
template void _STL::sort<S4SortElem8B *>(S4SortElem8B *, S4SortElem8B *);
