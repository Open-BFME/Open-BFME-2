// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva004FD448@Rva004FD448@@QAEXPBVModuleData@@@Z @0x004FD448 102B.
// Multimap<int int> insert per int plus vector<ModuleData*> push_back.
// Evidence: unlock lane unblocks 0x004FD7FB TeamDefeatCondition ParseINI;
// caller 0x004FD834 passes new 0x24 object with vector<int> at +4 in push
// and holder in ecx; map at this+0x68 via rowed insert_equal 0x004FF876;
// vector at this+0x8c via rowed push_back 0x004DFCB0; same 0x24 spacing as
// siblings 0x004FD37F 0x50/0x74 and 0x004FD3E2 0x5c/0x80; neighbours carry
// /O1 /GX /MD.
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
#include <map>

class ModuleData;

struct Rva004FCD49Vec {
    void *vtbl;
    _STL::vector<int> m_vec;
    int m_10;
};

class Rva004FD448 {
public:
    void rva004FD448(const ModuleData *p);
private:
    char m_pad00[0x68];
    _STL::multimap<int, int> m_map;
    char m_pad1[0x8c - 0x68 - sizeof(_STL::multimap<int, int>)];
    _STL::vector<const ModuleData *> m_vec;
};

void Rva004FD448::rva004FD448(const ModuleData *p)
{
    if (!p)
        return;
    const _STL::vector<int> &vec = ((const Rva004FCD49Vec *)p)->m_vec;
    for (unsigned int i = 0; i < vec.size(); ++i) {
        int v = vec[i];
        m_map.insert(_STL::multimap<int, int>::value_type(v, (int)p));
    }
    m_vec.push_back(p);
}
