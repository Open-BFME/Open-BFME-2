// Reference: pristine STLport4.5.3. Address-derived opaque record ABI.
// Target boundary and literal pointer stride establish storage width only; no application identity inferred.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

#include <vector>



struct BfmePod88 { char bytes[88]; };
namespace _STL {
template <> vector<BfmePod88>::vector(const vector<BfmePod88> &);
template <> vector<BfmePod88>::~vector();
}

struct Rva00500EFARecord
{
    _STL::vector<BfmePod88> m_values;
};

// Retail reserve calls the existing outer-vector clear at 0x00500EDC.
// This identifies the cleanup helper, not the opaque record's application type.
namespace _STL {
template <> void vector<vector<BfmePod88> >::_M_clear();
}
struct Rva00500EFAClearOwner : _STL::vector<_STL::vector<BfmePod88> >
{
    using _STL::vector<_STL::vector<BfmePod88> >::_M_clear;
};
namespace _STL {
template <> __declspec(dllimport) __forceinline void vector<Rva00500EFARecord>::_M_clear()
{
    reinterpret_cast<Rva00500EFAClearOwner *>(this)->_M_clear();
}
}
template void _STL::vector<Rva00500EFARecord>::reserve(unsigned int);
