// cl: /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common -DNDEBUG -MD -EHsc /Os
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

// AsciiString and its StringBase<char> base come from the canonical header
// (reverse/canonical_classes.csv); the donor's private copies are the views the
// class gate refuses, and its StringBase view was already incomplete here.
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

	__forceinline bool operator()(const Q3SortElem16 &left,
		const Q3SortElem16 &right) const
	{
		return left.m_a < right.m_a;
	}
};
struct Rva004748F0Compare { void *m_state; };
static __forceinline const Q3SortElem16 *Q3SortElem16Median(
	const Q3SortElem16 *a, const Q3SortElem16 *b,
	const Q3SortElem16 *c, const Q3SortCompare &comp)
{
	if (comp(*a, *b))
	{
		if (comp(*b, *c))
			return b;
		if (comp(*a, *c))
			return c;
		return a;
	}
	if (comp(*a, *c))
		return a;
	if (comp(*b, *c))
		return c;
	return b;
}
struct Q3InputIteratorTag {};
struct Q3ForwardIteratorTag : Q3InputIteratorTag {};
struct Q3BidirectionalIteratorTag : Q3ForwardIteratorTag {};
struct Q3IteratorCategory : Q3BidirectionalIteratorTag {};
inline Q3IteratorCategory Q3IteratorCategoryOf(Q3SortElem16 *const &)
{
    return Q3IteratorCategory();
}
struct BfmeElemVOX;
BfmeElemVOX *bfmeCopyBackVOX(const BfmeElemVOX *, const BfmeElemVOX *, BfmeElemVOX *);
// Retail passes two unused iterator tags through this cdecl call.
typedef Q3SortElem16 *(__cdecl *Q3CopyWithTags)(Q3SortElem16 *, Q3SortElem16 *, Q3SortElem16 *, const Q3IteratorCategory &, int *);
__declspec(noinline) void __unguarded_linear_insert(Q3SortElem16 *, Q3SortElem16, Q3SortCompare);
void __linear_insert(Q3SortElem16 *, Q3SortElem16 *, Q3SortElem16, Q3SortCompare);

// Full retail191B ends at ret0x0047586E (exclusive0x0047586F).
void __linear_insert(Q3SortElem16 *first, Q3SortElem16 *last,
    Q3SortElem16 value, Q3SortCompare comp)
{
    if (comp(value, *first)) {
        reinterpret_cast<Q3CopyWithTags>(bfmeCopyBackVOX)(first, last, last + 1,
            Q3IteratorCategoryOf(first), (int *)0);
        *first = value;
    } else {
        __unguarded_linear_insert(last, value, comp);
    }
}

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
