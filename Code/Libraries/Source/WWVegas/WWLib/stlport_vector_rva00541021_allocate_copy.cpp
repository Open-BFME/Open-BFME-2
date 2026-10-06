// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_fill_n@PAURva00541021@@IU1@@_STL@@YAPAURva00541021@@PAU1@IABU1@ABU__false_type@0@@Z @0x005410E3 37B: vector fill helper for 28-byte Rva00541021 (int plus Region3D). Evidence: calls rowed _Construct 0x0054105B; stride 0x1C; caller is vector insert-overflow 0x00541709.
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
struct Region3D
{
    Region3D(const Region3D &that);
    float x_min;
    float y_min;
    float z_min;
    float x_max;
    float y_max;
    float z_max;
};
struct Rva00541021
{
    int m_field0;
    Region3D m_region;
    Rva00541021();
    Rva00541021(const Rva00541021 &other);
};
namespace _STL {
template <> void _Construct<Rva00541021, Rva00541021>(Rva00541021 *, const Rva00541021 &);
}
template class _STL::vector<Rva00541021, _STL::allocator<Rva00541021> >;
