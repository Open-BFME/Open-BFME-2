// ?_M_insert_overflow@?$vector@URva00082BE6Element@@V?$allocator@URva00082BE6Element@@@_STL@@@_STL@@IAEXPAURva00082BE6Element@@ABU3@ABU__false_type@2@I_N@Z
// Continued bank from reverse/attempts/0x0008257f.cpp (wave-3 muse-02).
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@URva00082BE6Element@@V?$allocator@URva00082BE6Element@@@_STL@@@_STL@@IAEXPAURva00082BE6Element@@ABU3@ABU__false_type@2@I_N@Z @0x0008257F 178B
// Evidence: same 178B shape as rva0036ca00 overflow 0x00058ADE plus sar 2 for 4B element; callees allocate 0x68E15 copy 0x7E2FA copy 0x87A5C fill 0x577CA0 clear pin 0x577EF1; caller push_back 0x82C13.
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

struct Rva00082BE6Element
{
    Rva00082BE6Element();
    Rva00082BE6Element(const Rva00082BE6Element &);
    ~Rva00082BE6Element();
    Rva00082BE6Element &operator=(const Rva00082BE6Element &);
private:
    void *m_data;
};

namespace _STL {
template <> void _Construct<Rva00082BE6Element, Rva00082BE6Element>(Rva00082BE6Element *, const Rva00082BE6Element &);
}

template void _STL::vector<Rva00082BE6Element>::_M_insert_overflow(
    Rva00082BE6Element *,
    const Rva00082BE6Element &,
    const _STL::__false_type &,
    unsigned int,
    bool);
