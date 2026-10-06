// cl: /O1 /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/Q3IntrosortLoop004775D0.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// __push_heap 0x0021773C (116B), __make_heap 0x00217BAE (83B),
// __insertion_sort 0x00218398 (57B). Callee addresses are read off retail's
// call sites (reverse/symbols.csv). Only the placed bodies are carried; the
// donor's other definitions are omitted.
//
// Open-BFME5: the 16-byte STLport __introsort_loop called by the matched
// Rva00477960 driver.  The retail body inlines median-of-three over the first
// integer, copies the trailing StringBase<char> handle, then calls the partition,
// recursive loop and typed partial-sort helper below.
// Parent raw tracing: ILT1492A -> iter-swap473BC0/170B (two pointers),
// ILT34F95 -> partition4747F0/133B, ILTAEBB -> this217B loop,
// ILT32501 -> partial-sort4768F0/130B. Its fourth argument is the
// STLport value-type pointer, not a depth integer (_algo.c __partial_sort).
// noinline keeps the separate retail partition call; copies/releases use
// actual StringBase<char> constructors and releaseBuffer, not dummy owners.

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

// The real inline AsciiString forwarding layer is needed by the retail
// by-value copy schedule; its implicit destructor runs StringBase cleanup.
// class-gate: allow AsciiString the donor's own view; the placed bodies are byte-exact under it

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

	__forceinline bool operator()(const Q3SortElem16 &left,
		const Q3SortElem16 &right) const
	{
		return left.m_a < right.m_a;
	}
};

__declspec(noinline) Q3SortElem16 *__unguarded_partition(Q3SortElem16 *, Q3SortElem16 *,
	Q3SortElem16, Q3SortCompare);

void __partial_sort(Q3SortElem16 *, Q3SortElem16 *, Q3SortElem16 *,
	Q3SortElem16 *, Q3SortCompare);
void __make_heap(Q3SortElem16 *, Q3SortElem16 *, Q3SortCompare,
	Q3SortElem16 *, int *);
struct Rva004748F0Element
{
    int m_a;
    int m_b;
    int m_c;
    AsciiString m_d;
};
struct Rva004748F0Compare { void *m_state; };
void Rva004748F0PopHeap(Rva004748F0Element *, Rva004748F0Element *, Rva004748F0Element *,
    Rva004748F0Element, Rva004748F0Compare, int *);
void bfmeSortVOV(void *, void *, void *);


__declspec(noinline) void iter_swap(Q3SortElem16 *, Q3SortElem16 *);


// STLport __make_heap for the same owning 16-byte record.
// Retail 0x004749F0/116 ends at ret 0x00474A63; the partial-sort
// helper calls it through ILT 0x32646. Adjust_heap is the existing
// 283-byte body at 0x00474330, reached here through ILT 0x18ABB.
void bfmeAdjustHeap00474330(Rva004748F0Element *, int, int, Rva004748F0Element, Rva004748F0Compare);

void __make_heap(Q3SortElem16 *first, Q3SortElem16 *last,
    Q3SortCompare comp, Q3SortElem16 *, int *)
{
    if (last - first < 2)
        return;
    int length = last - first;
    int parent = (length - 2) / 2;
    for (;;) {
        bfmeAdjustHeap00474330((Rva004748F0Element *)first, parent, length,
            *(Rva004748F0Element *)(first + parent), reinterpret_cast<const Rva004748F0Compare &>(comp));
        if (parent == 0)
            return;
        --parent;
    }
}

// STLport __push_heap; the matched adjust_heap body calls ILT0x49657
// to this full207B body at0x00473D60, ending ret0x00473E2E.
void __push_heap(Q3SortElem16 *first, int holeIndex,
    int topIndex, Q3SortElem16 value, Q3SortCompare comp)
{
    int parent = (holeIndex - 1) / 2;
    while (holeIndex > topIndex && comp(first[parent], value)) {
        first[holeIndex] = first[parent];
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    first[holeIndex] = value;
}

__declspec(noinline) void __linear_insert(Q3SortElem16 *, Q3SortElem16 *, Q3SortElem16, Q3SortCompare);

// Retail92B ends at ret0x0047622B; matched final split0x00476880
// calls through ILT0x20D65. Linear insertion uses the same owning record.
void __insertion_sort(Q3SortElem16 *first, Q3SortElem16 *last,
    Q3SortCompare comp)
{
    if (first == last)
        return;
    for (Q3SortElem16 *current = first + 1; current != last; ++current)
        __linear_insert(first, current, *current, comp);
}

// STLport random-access iterator tag inheritance (_iterator_base.h).
struct Q3InputIteratorTag {};
struct Q3ForwardIteratorTag : Q3InputIteratorTag {};
struct Q3BidirectionalIteratorTag : Q3ForwardIteratorTag {};
struct Q3IteratorCategory : Q3BidirectionalIteratorTag {};

struct BfmeElemVOX;
BfmeElemVOX *bfmeCopyBackVOX(const BfmeElemVOX *, const BfmeElemVOX *, BfmeElemVOX *);
// Retail passes two unused iterator tags through this cdecl call.
typedef Q3SortElem16 *(__cdecl *Q3CopyWithTags)(Q3SortElem16 *, Q3SortElem16 *, Q3SortElem16 *, const Q3IteratorCategory &, int *);
__declspec(noinline) void __unguarded_linear_insert(Q3SortElem16 *, Q3SortElem16, Q3SortCompare);


