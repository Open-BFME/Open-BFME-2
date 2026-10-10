// ?_M_insert_overflow@?$vector@URva0008B689Element@@V?$allocator@URva0008B689Element@@@_STL@@@_STL@@IAEXPAURva0008B689Element@@ABU3@ABU__false_type@2@I_N@Z
// Continued bank from reverse/attempts/0x0008257f.cpp (wave-3 muse-02).
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@URva0008B689Element@@V?$allocator@URva0008B689Element@@@_STL@@@_STL@@IAEXPAURva0008B689Element@@ABU3@ABU__false_type@2@I_N@Z @0x0008B503 178B
// Evidence: same 178B shape as rva0036ca00 overflow 0x00058ADE plus sar 2 for 4B element; callees allocate 0x68E15 copy 0x7E2FA copy 0x87A5C fill 0x577CA0 clear pin 0x577EF1; caller push_back 0x8B689.
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

struct Rva0008B689Element
{
    Rva0008B689Element();
    Rva0008B689Element(const Rva0008B689Element &);
    ~Rva0008B689Element();
    Rva0008B689Element &operator=(const Rva0008B689Element &);
private:
    void *m_data;
};

namespace _STL {
template <> void _Construct<Rva0008B689Element, Rva0008B689Element>(Rva0008B689Element *, const Rva0008B689Element &);
}

template void _STL::vector<Rva0008B689Element>::_M_insert_overflow(
    Rva0008B689Element *,
    const Rva0008B689Element &,
    const _STL::__false_type &,
    unsigned int,
    bool);
