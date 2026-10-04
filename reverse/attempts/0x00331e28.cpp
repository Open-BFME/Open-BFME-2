// ?Rva00331E28MakeHeap@@YAXPAUS4SortElem12@@0US4Cmp002E0CD0@@@Z
// partial score=0.97 date=2026-10-04
// cl: /O1 /G7 /EHsc /MD /Oy-
// ?Rva00331E28MakeHeap@@YAXPAUS4SortElem12@@0US4Cmp002E0CD0@@@Z @0x00331E28 88B
// __make_heap worker for 12-byte sort elements via rowed copy 0x00331962 and pinned __adjust_heap 0x00331C05.
// Evidence: unlock lane unblocks make_heap 0x00332097; callees rowed/pinned; donor BfmeAssignRecord32MakeHeap 0x00173A60 shape with (len-2)/2 walk and copy-then-adjust loop.
struct S4SortElem12
{
	int m_a;
	int m_b;
	int m_c;
	S4SortElem12(const S4SortElem12 &other);
};

struct S4Cmp002E0CD0
{
	void *m_state;
};

namespace _STL
{
template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance hole, Distance len, Tp value, Compare comp);
}

void __cdecl Rva00331E28MakeHeap(S4SortElem12 *first, S4SortElem12 *last, S4Cmp002E0CD0 comp)
{
	int len = (int)(last - first);
	if (len < 2)
		return;
	int parent = (len - 2) / 2;
	S4SortElem12 *p = first + parent;
	for (;;) {
		_STL::__adjust_heap<S4SortElem12 *, int, S4SortElem12, S4Cmp002E0CD0>(first, parent, len, *p, comp);
		if (parent == 0)
			break;
		--parent;
		--p;
	}
}
