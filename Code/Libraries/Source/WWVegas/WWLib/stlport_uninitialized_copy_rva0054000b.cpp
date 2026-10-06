// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_copy@PBVRva0054000B@@PAV1@@_STL@@YAPAVRva0054000B@@PBV1@0PAV1@ABU__false_type@0@@Z @0x005400B4 38B
// 40-byte copy loop striding 0x28 through rowed _Construct 0x00540070.
// Evidence: callee rowed; callers 0x0054016A 0x00540295 0x00540412 twice; sibling fill 0x005400DA same stride.
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

template _STL::vector<Rva0054000B, _STL::allocator<Rva0054000B> >::vector(const _STL::vector<Rva0054000B, _STL::allocator<Rva0054000B> > &);
