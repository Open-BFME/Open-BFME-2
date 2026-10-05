// cl: /O1 /EHsc /MD
// stlport

// _STL::__final_insertion_sort over two (element, comparator) pairs,
// retail 0x00332308 (12B S4SortElem12, 71B) and 0x004F8C99
// (12B Rva004F6352, 71B).
// Threshold split at sixteen elements: over it, guarded insertion sort
// of the head plus the unguarded forwarder over the tail; under it,
// guarded sort of the whole range. Follows the rowed S4SortElem8
// precedent (stlport_final_insertion_sort_s4sortelem8.cpp), except the
// tail routes through the 3-argument __unguarded_insertion_sort
// forwarder. All four callee targets are pinned from each body's own
// REL32. Element layouts are size-faithful only;
// __final_insertion_sort touches pointers, never members.

struct S4SortElem12
{
	char m_data[12];
};

struct S4Cmp002E1690
{
	int m_bfmeSlot;
};

struct Rva004F6352
{
	char m_data[12];
};

struct Rva004F6352Cmp
{
};

namespace _STL
{

const int __stl_threshold = 16;

template <class RandomAccessIter, class Compare>
void __insertion_sort(RandomAccessIter first, RandomAccessIter last,
	Compare comp);

template <class RandomAccessIter, class Compare>
void __unguarded_insertion_sort(RandomAccessIter first,
	RandomAccessIter last, Compare comp);

template <class RandomAccessIter, class Compare>
void __final_insertion_sort(RandomAccessIter first, RandomAccessIter last,
	Compare comp)
{
	if (last - first > __stl_threshold)
	{
		__insertion_sort(first, first + __stl_threshold, comp);
		__unguarded_insertion_sort(first + __stl_threshold, last, comp);
	}
	else
		__insertion_sort(first, last, comp);
}

template void __final_insertion_sort<S4SortElem12 *, S4Cmp002E1690>(
	S4SortElem12 *, S4SortElem12 *, S4Cmp002E1690);
template void __final_insertion_sort<Rva004F6352 *, Rva004F6352Cmp>(
	Rva004F6352 *, Rva004F6352 *, Rva004F6352Cmp);

}
