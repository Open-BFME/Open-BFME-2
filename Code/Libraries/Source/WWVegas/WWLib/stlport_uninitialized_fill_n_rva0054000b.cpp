// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_fill_n@PAVRva0054000B@@IV1@@_STL@@YAPAVRva0054000B@@PAV1@IABV1@ABU__false_type@0@@Z @0x005400DA 37B
// 40-byte fill loop striding 0x28 through rowed _Construct 0x00540070.
// Evidence: callee rowed; caller 0x00540412; sibling copy 0x005400B4 same stride.
#include <memory>
#include <vector>

class Rva0054000B
{
public:
	Rva0054000B();
	Rva0054000B(const Rva0054000B &other);

private:
	char m_pad[40];
};

namespace _STL {
template<> void _Construct<Rva0054000B, Rva0054000B>(Rva0054000B *, const Rva0054000B &);
}

// Emit the rowed fill_n directly instead of via the vector fill ctor: the
// vector instantiation also emits allocator::allocate, whose /O1 lea+shl copy
// loses to the /G7 imul copy kept by stlport_overflow_rva0054000b.cpp.
template Rva0054000B *_STL::__uninitialized_fill_n<Rva0054000B *, unsigned int, Rva0054000B>(Rva0054000B *, unsigned int, const Rva0054000B &, const _STL::__false_type &);
