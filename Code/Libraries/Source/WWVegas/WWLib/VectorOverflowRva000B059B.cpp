// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference: pristine STLport4.5.3 vector::_M_insert_overflow.
// Retail 0x000B059B, 183B; Ghidra boundary, ret14 ABI and 28-byte
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

struct Rva000B059BRecord {
 Rva000B059BRecord(); Rva000B059BRecord(const Rva000B059BRecord&); ~Rva000B059BRecord(); Rva000B059BRecord&operator=(const Rva000B059BRecord&);
private: char bytes[28];
};
namespace _STL { template<> void _Construct<Rva000B059BRecord,Rva000B059BRecord>(Rva000B059BRecord*,const Rva000B059BRecord&); }
template void _STL::vector<Rva000B059BRecord>::_M_insert_overflow(Rva000B059BRecord*,const Rva000B059BRecord&,const _STL::__false_type&,unsigned int,bool);
