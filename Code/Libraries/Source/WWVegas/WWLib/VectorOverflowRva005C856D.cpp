// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference: pristine STLport4.5.3 vector::_M_insert_overflow.
// Retail 0x005C856D, 183B; Ghidra boundary, ret14 ABI and 72-byte
// arithmetic independently establish the overflow and storage width. The
// address-derived record is an opaque ABI view; no application class or
// member layout is inferred. Each helper pin comes from this target's calls.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

struct Rva005C856DRecord { Rva005C856DRecord(); Rva005C856DRecord(const Rva005C856DRecord&); ~Rva005C856DRecord(); Rva005C856DRecord&operator=(const Rva005C856DRecord&); private: char bytes[72]; };
namespace _STL {template<> void _Construct<Rva005C856DRecord,Rva005C856DRecord>(Rva005C856DRecord*,const Rva005C856DRecord&);}
template void _STL::vector<Rva005C856DRecord>::_M_insert_overflow(Rva005C856DRecord*,const Rva005C856DRecord&,const _STL::__false_type&,unsigned int,bool);
