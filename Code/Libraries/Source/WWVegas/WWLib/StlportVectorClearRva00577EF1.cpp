// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_clear@?$vector@URva002B9062Element@@V?$allocator@URva002B9062Element@@@_STL@@@_STL@@IAEXXZ
// @0x00577EF1 30B: destroys range via rowed Destroy 0x005F97BC then frees storage.
// Evidence: callers overflow 0x002B820A plus 7 more inserts plus Destroy row 0x005F97BC
// plus free row 0x00030830; same 30B Destroy-plus-free shape as rowed sibling _M_clear
// 0x004758D6 for Rva00475F2AElement.
struct Rva002B9062Element { char m_pad[4]; };
struct TreeHintRef00217D4C { char m_pad[4]; };

namespace _STL {
template <class _Tp> class allocator { };
template <class _ForwardIterator> void _Destroy(_ForwardIterator __first, _ForwardIterator __last);
template <> void _Destroy<TreeHintRef00217D4C *>(TreeHintRef00217D4C *__first, TreeHintRef00217D4C *__last);
template <class _Tp, class _Alloc = allocator<_Tp> > class vector
{
protected:
	void _M_clear();
protected:
	_Tp *_M_start;
	_Tp *_M_finish;
	_Tp *_M_end_of_storage;
};
}

extern "C" void __cdecl free(void *);

void _STL::vector<Rva002B9062Element>::_M_clear()
{
	_STL::_Destroy((TreeHintRef00217D4C *)_M_start, (TreeHintRef00217D4C *)_M_finish);
	Rva002B9062Element *start = _M_start;
	if (start)
		free(start);
}
