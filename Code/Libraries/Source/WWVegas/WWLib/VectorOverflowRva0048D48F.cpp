// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference: pristine STLport4.5.3 vector::_M_insert_overflow.
// Retail 0x0048D48F, 178B; Ghidra boundary, ret14 ABI and 8-byte
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

struct Rva0048D48FRecord {
 Rva0048D48FRecord(); Rva0048D48FRecord(const Rva0048D48FRecord&); ~Rva0048D48FRecord(); Rva0048D48FRecord&operator=(const Rva0048D48FRecord&);
private: char bytes[8];
};
namespace _STL { template<> void _Construct<Rva0048D48FRecord,Rva0048D48FRecord>(Rva0048D48FRecord*,const Rva0048D48FRecord&); }
template void _STL::vector<Rva0048D48FRecord>::_M_insert_overflow(Rva0048D48FRecord*,const Rva0048D48FRecord&,const _STL::__false_type&,unsigned int,bool);
