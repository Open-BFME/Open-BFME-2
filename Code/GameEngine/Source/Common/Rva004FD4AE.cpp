// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva004FD4AE@Rva004FD4AE@@QAEXPBVModuleData@@@Z @0x004FD4AE 19B.
// Vector<ModuleData*> push_back at this+0x98.
// Evidence: unlock lane unblocks 0x0059E6D3; abuts 0x004FD448; rowed push_back
// 0x004DFCB0; neighbours carry /O1 /GX /MD.
// Keep this inlined unsigned max overload local; retail has one external owner.
// Define it for speed, then restore this unit's flags for its vector bodies.
#pragma optimize("s", off)
#pragma optimize("t", on)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

class ModuleData;

class Rva004FD4AE {
public:
    void rva004FD4AE(const ModuleData *p);
private:
    char m_pad00[0x98];
    _STL::vector<const ModuleData *> m_vec;
};

void Rva004FD4AE::rva004FD4AE(const ModuleData *p)
{
    m_vec.push_back(p);
}
