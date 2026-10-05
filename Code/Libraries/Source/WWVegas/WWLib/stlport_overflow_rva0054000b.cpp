// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@VRva0054000B@@V?$allocator@VRva0054000B@@@_STL@@@_STL@@IAEXPAVRva0054000B@@ABV3@ABU__false_type@2@I_N@Z @0x00540412 189B
// Vector growth path striding 0x28 via rowed allocate 0x000B4039 plus rowed copy 0x005400B4 plus Construct 0x00540070 plus fill 0x005400DA plus free 0x00030830.
// Evidence: callees rowed; callers 0x005406FA 0x00540731; sibling overflow 0x005417C6 same 189B shape.
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

template void _STL::vector<Rva0054000B>::_M_insert_overflow(
	Rva0054000B *, const Rva0054000B &, const _STL::__false_type &,
	unsigned int, bool);
