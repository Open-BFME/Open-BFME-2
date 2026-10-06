// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

#include "unicode_string.h"
#include <string>
#include <map>



struct Rva0022CCEFRecord {Rva0022CCEFRecord();Rva0022CCEFRecord(const Rva0022CCEFRecord&);~Rva0022CCEFRecord();Rva0022CCEFRecord&operator=(const Rva0022CCEFRecord&);char bytes[1];};
template class _STL::multimap<_STL::basic_string<unsigned short>,Rva0022CCEFRecord>;
