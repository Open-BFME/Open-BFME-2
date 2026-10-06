// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

#include <hash_set>



struct Rva0002CCC3Record {char bytes[1];bool operator<(const Rva0002CCC3Record&)const;bool operator==(const Rva0002CCC3Record&)const;};
namespace _STL {template<>struct hash<Rva0002CCC3Record> {unsigned int operator()(const Rva0002CCC3Record&)const;};}
namespace _STL {template class hashtable<Rva0002CCC3Record,Rva0002CCC3Record,hash<Rva0002CCC3Record>,_Identity<Rva0002CCC3Record>,equal_to<Rva0002CCC3Record>,allocator<Rva0002CCC3Record> >;}
