// cl: /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common -DNDEBUG -MD -EHsc /Os
// ?__make_heap@@YAXPAUQ3SortElem16@@0UQ3SortCompare@@0PAH@Z
// retail 0x00217BAE, 83 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/Q3IntrosortLoop004775D0.cpp
// (reference/open-bfme-1 @ 6d943426), which recompiled /Os emits this body
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's other
// bodies are omitted.
//
// AsciiString and its StringBase<char> base come from the canonical header
// (reverse/canonical_classes.csv) rather than the donor's private copies, which
// the class gate refuses. Sibling __insertion_sort, landed in
// Q3IntrosortLoop004775D0.cpp, carries the same shape.
//
// Retail's body walks parents from (length - 2) / 2 down to 0, calling the
// 16-byte adjust_heap helper with the element copied by value at first+parent
// and the comparator reinterpreted through its state-pointer view.

#include "ascii_string.h"

struct Q3SortElem16
{
	int m_a;
	int m_b;
	int m_c;
	AsciiString m_d;
};
typedef char Q3ElementIs16[(sizeof(Q3SortElem16) == 16) ? 1 : -1];

struct Q3SortCompare
{
	void *m_state;
};

// The donor records this helper at BFME 1 0x00474330 (283 bytes); its REL32
// from retail 0x00217BAE lands on 0x00217934 here. The comparator is taken by
// non-const reference: retail pushes the same [ebp+0x10] slot the donor's
// `Rva004748F0Compare &` view takes, so a const view would emit a different
// argument spelling.
struct Rva004748F0Compare { void *m_state; };
void bfmeAdjustHeap00474330(Q3SortElem16 *, int, int, Q3SortElem16,
	Rva004748F0Compare);

// Retail 0x004749F0/116 ends at ret 0x00474A63; the partial-sort helper calls
// it through ILT 0x32646. Adjust_heap is the existing 283-byte body at
// 0x00474330, reached here through ILT 0x18ABB.
void __make_heap(Q3SortElem16 *first, Q3SortElem16 *last,
    Q3SortCompare comp, Q3SortElem16 *, int *)
{
    if (last - first < 2)
        return;
    int length = last - first;
    int parent = (length - 2) / 2;
    for (;;) {
        bfmeAdjustHeap00474330(first, parent, length,
            *(Q3SortElem16 *)(first + parent),
            *reinterpret_cast<Rva004748F0Compare *>(&comp));
        if (parent == 0)
            return;
        --parent;
    }
}