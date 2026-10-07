// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// F6 shape family: three vector _M_clear siblings of the rowed 0x004758D6.
// 0x0008B4AF destroys via _Destroy 0x0008AFDC, 0x00577EF1 via the matched
// TreeHintRef _Destroy 0x005F97BC, 0x005C84D3 via _Destroy 0x005C847B,
// then frees storage through the free row 0x00030830. Element types are
// address-derived views; only the Destroy reloc varies per member.
struct Rva0008B4AFElement { char m_pad[4]; };
struct Rva00577EF1Element { char m_pad[4]; };
struct Rva005C84D3Element { char m_pad[4]; };
struct TreeHintRef00217D4C { char m_pad[4]; };

namespace _STL {
template <class _Tp> class allocator { };
template <class _ForwardIterator> void _Destroy(_ForwardIterator __first, _ForwardIterator __last);
template <> void _Destroy<Rva0008B4AFElement *>(Rva0008B4AFElement *__first, Rva0008B4AFElement *__last);
template <> void _Destroy<TreeHintRef00217D4C *>(TreeHintRef00217D4C *__first, TreeHintRef00217D4C *__last);
template <> void _Destroy<Rva005C84D3Element *>(Rva005C84D3Element *__first, Rva005C84D3Element *__last);
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

template <>
void _STL::vector<Rva0008B4AFElement>::_M_clear()
{
	_STL::_Destroy(_M_start, _M_finish);
	Rva0008B4AFElement *start = _M_start;
	if (start)
		free(start);
}


template <>
void _STL::vector<Rva005C84D3Element>::_M_clear()
{
	_STL::_Destroy(_M_start, _M_finish);
	Rva005C84D3Element *start = _M_start;
	if (start)
		free(start);
}

class Rva0008B470
{
public:
	~Rva0008B470();
};

class Rva0008B4CD
{
public:
	void rva0008B4CD();
};

void Rva0008B4CD::rva0008B4CD()
{
	((Rva0008B470 *)this)->~Rva0008B470();
}

