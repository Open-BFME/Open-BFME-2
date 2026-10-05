// cl: /O1 /G7 /GX- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

// ?get_allocator@?$vector@VRva0054000B@@V?$allocator@VRva0054000B@@@_STL@@@_STL@@QBE?AV?$allocator@VRva0054000B@@@2@XZ present-unmatched
namespace _STL { template<> _Vector_base<Rva0054000B, allocator<Rva0054000B> >::_Vector_base(size_t, const allocator<Rva0054000B>&); }
namespace _STL { template<> __declspec(noinline) vector<Rva0054000B, allocator<Rva0054000B> >::allocator_type vector<Rva0054000B, allocator<Rva0054000B> >::get_allocator() const { return allocator_type(); } }

template _STL::vector<Rva0054000B, _STL::allocator<Rva0054000B> >::vector(const _STL::vector<Rva0054000B, _STL::allocator<Rva0054000B> > &);

// Target Ghidra [540295,5402DC),71B: vector copy construction over40B
// elements. Full38B copy5400B4 calls full18B Construct540070 and29B
// element copy540036. The original application name remains unknown.
// STLport4.5.3 is the algorithm guide; native count division and argument
// order independently prove layout and ABI. /GX- removes exception cleanup
// absent from retail. Visible noinline empty allocator getter preserves
// native ordering and emits the complete7B folded getter ABI. This getter
// remains unrowed because its original folded identity is not unique.
// Full60B base53FF92 allocates n*40 and initializes the three pointer fields;
// its allocator argument is empty. Full7B getter21983A returns that empty
// result storage and consumes no receiver fields. These aliases bind only
// independently verified complete providers with the same consumed ABI.
#pragma comment(linker, "/alternatename:??0?$_Vector_base@VRva0054000B@@V?$allocator@VRva0054000B@@@_STL@@@_STL@@QAE@IABV?$allocator@VRva0054000B@@@1@@Z=??0?$_Vector_base@UBfmePod40@@V?$allocator@UBfmePod40@@@_STL@@@_STL@@QAE@IABV?$allocator@UBfmePod40@@@1@@Z")
#pragma comment(linker, "/alternatename:?get_allocator@?$vector@VRva0054000B@@V?$allocator@VRva0054000B@@@_STL@@@_STL@@QBE?AV?$allocator@VRva0054000B@@@2@XZ=?get_allocator@?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QBE?AV?$allocator@VAsciiString@@@2@XZ")
