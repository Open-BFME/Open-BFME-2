// cl: /O1 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /DWIN32 /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc/stl
// stlport
// Reconstruction of the indexed loop at 0x00319A12 (64B): walk the +0x78
// helper's 8B-element range backwards; when the indexed word's +4 string
// differs from the +0x18 string, run the pinned sibling 0x319517 body on
// the index. Rowed get/compare spellings are referenced through
// reinterpret casts because they live in their own TUs. All names are
// address-derived.
#define _STLP_NO_EXCEPTIONS 1
#include <cstddef>
#include "_alloc.h"
#include <vector>
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int& max<unsigned int>(const unsigned int& a, const unsigned int& b) { return a < b ? b : a; }
}
#pragma optimize("", on)
#include "ascii_string.h"

class Rva0040CB2CIndexedField {
public:
    int get(int index) const;
};

class Rva00319A12Helper {
public:
    unsigned char pad00[0x40];
    int m_40;
    int m_44;
};

class Rva0031979COwner {
public:
    void rva00319517(int value);
};

class Rva00319A12Owner {
public:
    void rva00319A12();
private:
    unsigned char pad00[0x18];
    AsciiString m_18;
    unsigned char pad1C[0x78 - 0x1C];
    Rva00319A12Helper* m_78;
};

void Rva00319A12Owner::rva00319A12()
{
    Rva00319A12Helper* helper = m_78;
    if (helper == 0)
        return;
    int last = ((helper->m_44 - helper->m_40) >> 3) - 1;
    for (int i = last; i >= 0; --i) {
        int p = ((Rva0040CB2CIndexedField*)m_78)->get(i);
        if (((StringBase<char>*)(p + 4))->compare(*(const StringBase<char>*)&m_18) != 0)
            ((Rva0031979COwner*)this)->rva00319517(i);
    }
}
