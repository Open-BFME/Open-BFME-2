// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??$__unguarded_insertion_sort@PAUTreeHintRef00217D4C@@URva004F9185Cmp@@@_STL@@YAXPAUTreeHintRef00217D4C@@0URva004F9185Cmp@@@Z, retail 0x004F7273, 23 bytes.
// Public unguarded_insertion_sort wrapper calling rowed __unguarded_insertion_sort_aux 0x004F6CFD with (value*)0 dummy.
// Evidence: same 23B push-push0-push-push-call-add-ret shape as rowed pop_heap 0x00424637 and landed pop_heap 0x004F7AA6;
// caller 0x004F83D6 in final_insertion_sort TU PAUTreeHintRef00217D4CRva004F9565.cpp; unblocks sort chain.

struct TreeHintRef00217D4C
{
	void *m_ptr;
};

struct Rva004F9185Cmp
{
	bool operator()(TreeHintRef00217D4C a, TreeHintRef00217D4C b) const;
};

namespace _STL
{
	template <class _RandomAccessIter, class _Tp, class _Compare>
	void __unguarded_insertion_sort_aux(_RandomAccessIter first, _RandomAccessIter last, _Tp *x, _Compare comp);

	template <class _RandomAccessIter, class _Compare>
	void __unguarded_insertion_sort(_RandomAccessIter first, _RandomAccessIter last, _Compare comp)
	{
		__unguarded_insertion_sort_aux(first, last, (TreeHintRef00217D4C *)0, comp);
	}
}

template void _STL::__unguarded_insertion_sort<TreeHintRef00217D4C *, Rva004F9185Cmp>(TreeHintRef00217D4C *, TreeHintRef00217D4C *, Rva004F9185Cmp);
