// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Retail 0x001D9AAC 45B: vector _M_allocate_and_copy twin of E8 0x001D9AD9.
// Calls rowed allocate 0x00523D6C and rowed TailRecord copy 0x001D9A61.
// Callers 0x001D9D75/0x001D9E29 are TailRecord vector growth/clear paths.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// 8-byte element; layout owner StlportVectorDtorChains.cpp.
class BfmeStringTailRecord156 { char m_pad[8]; public: BfmeStringTailRecord156(const BfmeStringTailRecord156 &); ~BfmeStringTailRecord156(); };
namespace _STL
{
template <> void _Construct<BfmeStringTailRecord156, BfmeStringTailRecord156>(BfmeStringTailRecord156 *, const BfmeStringTailRecord156 &);
}

template BfmeStringTailRecord156 *_STL::vector<BfmeStringTailRecord156, _STL::allocator<BfmeStringTailRecord156> >::_M_allocate_and_copy(unsigned int, BfmeStringTailRecord156 *, BfmeStringTailRecord156 *);
template void _STL::vector<BfmeStringTailRecord156>::reserve(unsigned int);
