// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0?$vector@VBfmeStringTailRecord156@@V?$allocator@VBfmeStringTailRecord156@@@_STL@@@_STL@@QAE@ABV01@@Z
// Retail 0x0043351B 68B: vector<BfmeStringTailRecord156> copy ctor.
// Calls rowed AsciiString get_allocator 0x0021983A, rowed E8 _Vector_base(n)
// 0x000B6378 and rowed TailRecord __uninitialized_copy 0x001D9A61.
// Caller 0x004335BC. 8-byte non-POD element like E8 footprint.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// 8-byte element; layout owner StlportVectorDtorChains.cpp.
class BfmeStringTailRecord156 { char m_pad[8]; public: BfmeStringTailRecord156(const BfmeStringTailRecord156 &) throw(); ~BfmeStringTailRecord156() throw(); };
namespace _STL
{
template <> void _Construct<BfmeStringTailRecord156, BfmeStringTailRecord156>(BfmeStringTailRecord156 *, const BfmeStringTailRecord156 &) throw();
}

template _STL::vector<BfmeStringTailRecord156>::vector(const _STL::vector<BfmeStringTailRecord156> &);
