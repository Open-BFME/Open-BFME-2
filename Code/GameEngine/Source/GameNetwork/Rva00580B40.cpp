// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00580B40@Rva00580B40@@QAEXPBVModuleData@@@Z @0x00580B40 28B.
// Pushes non-null arg into vector<const ModuleData*> at +0x00 via rowed push_back
// then clears byte at +0x15. Evidence: callers 0x00445E64 0x005A06CD.
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

class Rva00580B40
{
public:
    void rva00580B40(const ModuleData *p);

private:
    _STL::vector<const ModuleData *> m_vec;
    char m_pad[0x15 - 0x0C];
    unsigned char m_15;
};

void Rva00580B40::rva00580B40(const ModuleData *p)
{
    if (p != 0) {
        m_vec.push_back(p);
        m_15 = 0;
    }
}
