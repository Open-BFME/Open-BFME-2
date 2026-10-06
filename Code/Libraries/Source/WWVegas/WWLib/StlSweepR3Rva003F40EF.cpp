// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
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

#include <algorithm>
#include <memory>



struct Rva003F40EFRecord {Rva003F40EFRecord();Rva003F40EFRecord(const Rva003F40EFRecord&);~Rva003F40EFRecord();Rva003F40EFRecord&operator=(const Rva003F40EFRecord&); char bytes[104];bool operator<(const Rva003F40EFRecord&)const;bool operator==(const Rva003F40EFRecord&)const;};
namespace _STL {template<>void _Construct<Rva003F40EFRecord,Rva003F40EFRecord>(Rva003F40EFRecord*,const Rva003F40EFRecord&);}
template Rva003F40EFRecord* _STL::uninitialized_copy(const Rva003F40EFRecord*,const Rva003F40EFRecord*,Rva003F40EFRecord*);
template Rva003F40EFRecord* _STL::uninitialized_fill_n(Rva003F40EFRecord*,unsigned int,const Rva003F40EFRecord&);
template void _STL::sort(Rva003F40EFRecord*,Rva003F40EFRecord*);
template void _STL::make_heap(Rva003F40EFRecord*,Rva003F40EFRecord*);
