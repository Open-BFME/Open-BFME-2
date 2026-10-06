// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva004FD4C1@Rva004FD4C1@@QAEXPBVModuleData@@@Z @0x004FD4C1 19B.
// Vector<ModuleData*> push_back at this+0xa4.
// Evidence: unlock lane unblocks 0x0059E9BD; abuts 0x004FD4AE; rowed push_back
// 0x004DFCB0; same 0x0c family step as 0x004FD448 0x8c and 0x004FD4AE 0x98;
// neighbours carry /O1 /GX /MD.
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

class Rva004FD4C1 {
public:
    void rva004FD4C1(const ModuleData *p);
private:
    char m_pad00[0xa4];
    _STL::vector<const ModuleData *> m_vec;
};

void Rva004FD4C1::rva004FD4C1(const ModuleData *p)
{
    m_vec.push_back(p);
}
