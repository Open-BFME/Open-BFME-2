// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__copy_ptrs@PAVRva0040AEE3@@PAV1@@_STL@@YAPAVRva0040AEE3@@PAV1@00U__false_type@0@@Z @ 0x0040B350 (29B). Wrapper via pinned __copy 0x0040B218.
// Evidence: chain lane calls rowed Rva0040B218Copy 0x0040B218 with tag plus 0; callers 0x0040B680 0x0040B6A0 in vector assign 0x0040B61A; same 29B shape as rowed 0x0040D8FB.
#include <vector>
#include <algorithm>

class Rva0040AEE3
{
public:
	Rva0040AEE3 &operator=(const Rva0040AEE3 &other);
};

template Rva0040AEE3 *_STL::__copy_ptrs<Rva0040AEE3 *, Rva0040AEE3 *>(Rva0040AEE3 *, Rva0040AEE3 *, Rva0040AEE3 *, _STL::__false_type);
