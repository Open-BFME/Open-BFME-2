// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?push_back@?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAEXABUCoord3D@@@Z @0x002CE7DC 55B: vector<Coord3D> push_back fast path via pinned _Construct 0x002CA82C else rowed _M_insert_overflow 0x002CDF8A stride 0xC.
// Evidence: unlock lane cmp je Construct add 0xC vs overflow with n=1; callers 0x002CE8A2 0x000E061B; same 55B shape as sibling pushbacks.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
struct Coord3D {
  float x, y, z;
  Coord3D(const Coord3D &that) throw();
};
namespace _STL {
template <> void _Construct<Coord3D, Coord3D>(Coord3D *, const Coord3D &);
}
template void _STL::vector<Coord3D>::push_back(const Coord3D &);
