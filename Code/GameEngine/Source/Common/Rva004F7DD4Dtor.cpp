// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva004F7DD4@@QAE@XZ retail 0x004F7DD4 8B
// Rb dtor tail-jump: add ecx,4 then jmp Vector_base dtor 0x004F7D7F.
// Evidence: callers at 0x004F88DE and 0x004F8B09 in Rva004F8AECErase.cpp plus deleting dtor 0x004F7E91 in FamilyDeletingDtors12.cpp; jmp target pinned ??1?$_Vector_base@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ.
namespace _STL {
template <class _Tp> class allocator {
};
template <class _Tp, class _Alloc> class _Vector_base
{
public:
	void *_M_start;
	void *_M_finish;
	void *_M_end;
	~_Vector_base();
};
}

struct Rva004F7DD4
{
	int m_dummy;
	_STL::_Vector_base<void *, _STL::allocator<void *> > m_vec;
	~Rva004F7DD4();
};

Rva004F7DD4::~Rva004F7DD4()
{
}
