// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva00289218@Rva00289218@@QAEXPBVModuleData@@@Z, retail 0x00289218, 16 bytes.
//
// Forwards a ModuleData pointer to the vector<const ModuleData*> at +0x14
// through the rowed ModuleFactory push_back at 0x004DFCB0. Same 16-byte
// lea-push-add-call shape as the rowed list/vector push_back twins. Identity:
// unlock lane, thiscall (reads ecx), callers at 0x002892CF and 0x0052D0F8;
// owner class unproven so honest Rva address name.
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
class ModuleData;
typedef _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > ModuleDataVec;
class Rva00289218 {
    char m_pad[20];
    ModuleDataVec m_vec;
public:
    void rva00289218(const ModuleData *p);
};
void Rva00289218::rva00289218(const ModuleData *p)
{
    m_vec.push_back(p);
}
