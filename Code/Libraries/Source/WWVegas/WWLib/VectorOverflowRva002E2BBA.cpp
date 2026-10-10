// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference: pristine STLport4.5.3 vector::_M_insert_overflow.
// Retail 0x002E2BBA, 191B; Ghidra boundary, ret14 ABI and 216-byte
// arithmetic independently establish the overflow and storage width. The
// address-derived record is an opaque ABI view; no application class or
// member layout is inferred. Each helper pin comes from this target's calls.
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

struct Rva002E2BBARecord {
 Rva002E2BBARecord(); Rva002E2BBARecord(const Rva002E2BBARecord&); ~Rva002E2BBARecord(); Rva002E2BBARecord&operator=(const Rva002E2BBARecord&);
private: char bytes[216];
};
namespace _STL { template<> void _Construct<Rva002E2BBARecord,Rva002E2BBARecord>(Rva002E2BBARecord*,const Rva002E2BBARecord&); }
template void _STL::vector<Rva002E2BBARecord>::_M_insert_overflow(Rva002E2BBARecord*,const Rva002E2BBARecord&,const _STL::__false_type&,unsigned int,bool);
