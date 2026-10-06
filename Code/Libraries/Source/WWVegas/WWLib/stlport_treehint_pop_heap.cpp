// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??$pop_heap@PAUTreeHintRef00217D4C@@URva004F9185Cmp@@@_STL@@YAXPAUTreeHintRef00217D4C@@0URva004F9185Cmp@@@Z, retail 0x004F7AA6, 23 bytes.
// Public pop_heap wrapper calling rowed __pop_heap_aux 0x004F76BC with (value*)0 dummy.
// Evidence: same 23B push-push0-push-push-call-add-ret shape as rowed pop_heap 0x00424637;
// caller 0x004F8181 in sort_heap loop 0x004F8162/58 decrements by 4; unblocks 0x004F8162.

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
	void __pop_heap_aux(_RandomAccessIter first, _RandomAccessIter last, _Tp *x, _Compare comp);

	template <class _RandomAccessIter, class _Compare>
	void pop_heap(_RandomAccessIter first, _RandomAccessIter last, _Compare comp)
	{
		__pop_heap_aux(first, last, (TreeHintRef00217D4C *)0, comp);
	}
}

template void _STL::pop_heap<TreeHintRef00217D4C *, Rva004F9185Cmp>(TreeHintRef00217D4C *, TreeHintRef00217D4C *, Rva004F9185Cmp);
