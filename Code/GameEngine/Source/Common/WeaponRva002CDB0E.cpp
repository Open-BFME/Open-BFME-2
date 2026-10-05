// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva002CDB0E@Weapon@@QAEXPBVModuleData@@@Z @0x002CDB0E 69B unlock: Weapon-adjacent vectors at +0xC/+0x18 via rowed voidptr erase and ModuleData push_back, callers 0x002CE160
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

class ModuleData
{
public:
    char m_pad00[0x174];
    mutable int m_174;
};

class WeaponTemplate;

class Weapon
{
public:
    void rva002CDB0E(const ModuleData *arg);
private:
    char m_pad00[4];
    WeaponTemplate *m_template;
    char m_pad08[4];
    _STL::vector<void *> m_vecC;
    _STL::vector<const ModuleData *> m_vec18;
};

void Weapon::rva002CDB0E(const ModuleData *arg)
{
    if (!arg)
        return;
    void **finish = (void **)m_vecC.end();
    for (void **it = (void **)m_vecC.begin(); it != finish; ++it)
    {
        if ((void *)arg == *it)
        {
            arg->m_174 = 1;
            m_vecC.erase(it);
            m_vec18.push_back(arg);
            return;
        }
    }
}
