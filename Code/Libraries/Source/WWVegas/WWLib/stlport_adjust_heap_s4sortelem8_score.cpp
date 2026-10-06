// cl: /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// Libraries/Source/WWVegas/WWLib/stlport_adjust_heap_s4sortelem8_score.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: ??$__adjust_heap@PAUS4SortElem8@@HU1@US4 0x0051D178 (110B).
// Callee addresses are read off retail's call sites (reverse/symbols.csv).
// Only the placed bodies are carried; the donor's other definitions are
// omitted.

// Open-BFME5: _STL::__adjust_heap<S4SortElem8 *, int, S4SortElem8,
// S4Cmp00575AA0>, retail 0x005757E0, 128 bytes.  Its matched make-heap caller
// proves the specialization; the comparator and push-heap targets come from
// this body's direct ILT calls.

struct S4SortElem8
{
	int m_bfmeFirst;
	int m_bfmeSecond;

	bool BfmeLess00574AA0(const S4SortElem8 &other) const;
};

struct S4Cmp00575AA0
{
	void *m_bfmeState;

	bool operator()(const S4SortElem8 &left,
		const S4SortElem8 &right) const
	{
		return left.BfmeLess00574AA0(right);
	}
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp val, Compare comp);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp)
{
	Distance topIndex = holeIndex;
	Distance secondChild = 2 * holeIndex + 2;
	while (secondChild < len)
	{
		if (comp(*(first + secondChild), *(first + (secondChild - 1))))
			secondChild--;
		*(first + holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len)
	{
		*(first + holeIndex) = *(first + (secondChild - 1));
		holeIndex = secondChild - 1;
	}
	__push_heap(first, holeIndex, topIndex, val, comp);
}

template void __adjust_heap<S4SortElem8 *, int, S4SortElem8,
	S4Cmp00575AA0>(S4SortElem8 *, int, int, S4SortElem8, S4Cmp00575AA0);

}
