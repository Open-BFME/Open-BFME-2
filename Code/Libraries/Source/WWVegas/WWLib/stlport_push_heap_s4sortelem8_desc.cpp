// cl: /DNDEBUG /MD /EHsc

// _STL::__push_heap<S4SortElem8 *, int, S4SortElem8,
// S4SortElem8GreaterCmp>, retail 0x00625AD0, 96 bytes. The body carried only a
// This is the Open-BFME-1 conversion of the same STLport instantiation,
// ported across: locate.py places both bodies uniquely in this binary, with
// every call site consistent, so the shape carries over even though the two
// engines put them at different addresses. The comparator struct is a
// placeholder named for the address it sits at HERE, not the one it had in
// the other tree.
//
// STLport's sift-up, and the callee the sift-down at 0x009F3190 tails into.
// Same eight-byte element and same inlined comparator: fld of the parent's
// float at +4, fcomp against the by-value element on the stack, fnstsw and a
// status test against 5, so the ordering is a less-than on that float.
//
// The value arrives by value, which is why the comparison reads it from the
// frame rather than through a pointer, and the final store writes it back into
// the array.

struct S4SortElem8
{
	int m_bfmeA;						// +0x00
	float m_bfmeKey;					// +0x04
};

struct S4SortElem8GreaterCmp
{
	bool operator()(const S4SortElem8 &a, const S4SortElem8 &b) const
	{
		return a.m_bfmeKey > b.m_bfmeKey;
	}
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp val, Compare comp)
{
	Distance parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex && comp(*(first + parent), val))
	{
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = val;
}

template void __push_heap<S4SortElem8 *, int, S4SortElem8, S4SortElem8GreaterCmp>(
	S4SortElem8 *, int, int, S4SortElem8, S4SortElem8GreaterCmp);

}
