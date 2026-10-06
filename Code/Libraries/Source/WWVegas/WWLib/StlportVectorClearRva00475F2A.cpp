// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_clear@?$vector@URva00475F2AElement@@V?$allocator@URva00475F2AElement@@@_STL@@@_STL@@IAEXXZ
// @0x004758D6 30B: destroys range via F4 Destroy 0x00470398 then frees storage.
// Evidence: callers overflow 0x00475BE8 plus erase 0x004758F4 plus Destroy pin 0x00470398
// plus stride 4 plus free row 0x00030830. F2A and F4 share 4B layout.
struct Rva00475F2AElement { char m_pad[4]; };
struct Rva004758F4Element { char m_pad[4]; };

namespace _STL {
template <class _Tp> class allocator { };
template <class _ForwardIterator> void _Destroy(_ForwardIterator __first, _ForwardIterator __last);
template <> void _Destroy<Rva004758F4Element *>(Rva004758F4Element *__first, Rva004758F4Element *__last);
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

void _STL::vector<Rva00475F2AElement>::_M_clear()
{
	_STL::_Destroy((Rva004758F4Element *)_M_start, (Rva004758F4Element *)_M_finish);
	Rva00475F2AElement *start = _M_start;
	if (start)
		free(start);
}
