// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@VRva004E2382@@V?$allocator@VRva004E2382@@@_STL@@@_STL@@QAE@XZ @ 0x004E3C32 (63B).
// Vector<Rva004E2382> dtor: destroys range via rowed _Destroy 0x004E377E then
// frees via rowed _free 0x00030830. Caller 0x004E3CD0 lea ecx [esi+0x14]
// proves parent vector at +0x14. Twin 0x004C7767 proves explicit-dtor recipe.
#include <vector>

class Rva004E2382 {
public:
    ~Rva004E2382();
private:
    char m_pad[32];
};

typedef _STL::vector<Rva004E2382, _STL::allocator<Rva004E2382> > Rva004E2382Vec;

template Rva004E2382Vec::~vector();
