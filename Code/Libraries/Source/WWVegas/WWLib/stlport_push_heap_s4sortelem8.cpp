// cl: /DNDEBUG /MD /EHsc

// _STL::__push_heap<S4SortElem8 *, int, S4SortElem8,
// S4SortElem8LessCmp>, retail 0x00625A70, 96 bytes. The body carried only a
// This is the Open-BFME-1 conversion of the same STLport instantiation,
// ported across: locate.py places both bodies uniquely in this binary, with
// every call site consistent, so the shape carries over even though the two
// engines put them at different addresses (this one lands at 0x00625880).
// The comparator struct has no name the bytes reach, so it is named for what
// it does instead: a less-than on S4SortElem8::m_bfmeKey.
//
// STLport's sift-up, and the callee the sift-down in this binary tails into.
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

struct S4SortElem8LessCmp
{
	bool operator()(const S4SortElem8 &a, const S4SortElem8 &b) const
	{
		return a.m_bfmeKey < b.m_bfmeKey;
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

template void __push_heap<S4SortElem8 *, int, S4SortElem8, S4SortElem8LessCmp>(
	S4SortElem8 *, int, int, S4SortElem8, S4SortElem8LessCmp);

}
