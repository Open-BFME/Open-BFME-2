// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

#include <hash_map>



struct Rva001FDC0FRecord {Rva001FDC0FRecord();Rva001FDC0FRecord(const Rva001FDC0FRecord&);~Rva001FDC0FRecord();Rva001FDC0FRecord&operator=(const Rva001FDC0FRecord&);char bytes[1];bool operator<(const Rva001FDC0FRecord&)const;bool operator==(const Rva001FDC0FRecord&)const;};
namespace _STL {template class hashtable<pair<const int,Rva001FDC0FRecord>,int,hash<int>,_Select1st<pair<const int,Rva001FDC0FRecord> >,equal_to<int>,allocator<pair<const int,Rva001FDC0FRecord> > >;}
