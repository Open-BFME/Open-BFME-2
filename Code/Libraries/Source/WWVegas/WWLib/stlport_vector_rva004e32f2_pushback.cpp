// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@VRva004E32F2@@V?$allocator@VRva004E32F2@@@_STL@@@_STL@@QAEXABVRva004E32F2@@@Z, retail 0x00566BB4, 55 bytes.
// STLport 4.5.3 vector<Rva004E32F2>::push_back.
// Evidence: chain lane calls just-landed _M_insert_overflow 0x00566ACA plus rowed _Construct 0x0052D4A2; same 55B shape as rowed 0x005662CC.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAVRva004E32F2@@PAV1@@_STL@@YAPAVRva004E32F2@@PAV1@00ABU__false_ty:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Rva004E32F2;
namespace _STL { template <> Rva004E32F2 * __uninitialized_copy<Rva004E32F2 *,Rva004E32F2 *>(Rva004E32F2 *,Rva004E32F2 *,Rva004E32F2 *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAVRva004E32F2@@IV1@@_STL@@YAPAVRva004E32F2@@PAV1@IABV1@ABU__fal:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> Rva004E32F2 * __uninitialized_fill_n<Rva004E32F2 *,unsigned int,Rva004E32F2>(Rva004E32F2 *,unsigned int,Rva004E32F2 const &,__false_type const &); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAVRva004E32F2@@@_STL@@YAXPAVRva004E32F2@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void _Destroy<Rva004E32F2 *>(Rva004E32F2 *,Rva004E32F2 *); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAVRva004E32F2@@@_STL@@YAXPAVRva004E32F2@@0ABU__false_type@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void __destroy_aux<Rva004E32F2 *>(Rva004E32F2 *,Rva004E32F2 *,__false_type const &); }

class Rva004E32F2
{
public:
	Rva004E32F2(const Rva004E32F2 &o);
	virtual ~Rva004E32F2();
private:
	char m_pad[0x14];
};

namespace _STL
{
template <> void _Construct<Rva004E32F2, Rva004E32F2>(Rva004E32F2 *, const Rva004E32F2 &);
}

template void _STL::vector<Rva004E32F2>::push_back(const Rva004E32F2 &);
