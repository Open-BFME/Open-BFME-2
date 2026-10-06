// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference: pristine STLport4.5.3 vector::_M_insert_overflow.
// Retail 0x0048D48F, 178B; Ghidra boundary, ret14 ABI and 8-byte
// arithmetic independently establish the overflow and storage width. The
// address-derived record is an opaque ABI view; no application class or
// member layout is inferred. Each helper pin comes from this target's calls.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

struct Rva0048D48FRecord {
 Rva0048D48FRecord(); Rva0048D48FRecord(const Rva0048D48FRecord&); ~Rva0048D48FRecord(); Rva0048D48FRecord&operator=(const Rva0048D48FRecord&);
private: char bytes[8];
};
namespace _STL { template<> void _Construct<Rva0048D48FRecord,Rva0048D48FRecord>(Rva0048D48FRecord*,const Rva0048D48FRecord&); }
template void _STL::vector<Rva0048D48FRecord>::_M_insert_overflow(Rva0048D48FRecord*,const Rva0048D48FRecord&,const _STL::__false_type&,unsigned int,bool);
