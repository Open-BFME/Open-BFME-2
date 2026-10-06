// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003F4CC0@Rva003F4CC0@@QAEPAURva003F4CC0Inner@@H@Z @0x003F4CC0 73B unlock linear search inners for unk0 matching int arg returning element pointer else NULL; callers 0x003F6755 0x003F4DFD; same dir sizes flags as Rva003F4DCAInnerSize
#include <vector>

struct Rva003F4CC0Inner {
    int unk0;
    _STL::vector<int> vals;
    char pad[32];
};

class Rva003F4CC0 {
    int m_unk0;
    _STL::vector<Rva003F4CC0Inner> m_inners;
public:
    Rva003F4CC0Inner *rva003F4CC0(int id);
};

Rva003F4CC0Inner *Rva003F4CC0::rva003F4CC0(int id)
{
    for (unsigned i = 0; i < m_inners.size(); ++i) {
        if (m_inners[i].unk0 == id)
            return &m_inners[i];
    }
    return 0;
}
