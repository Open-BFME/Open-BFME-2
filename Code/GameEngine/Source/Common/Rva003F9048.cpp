// cl: /O1 /arch:SSE /G7 /MD
// stlport
// ?rva003F9048@Rva003F9048@@QAEXPBVModuleData@@@Z @0x003F9048 23B
// Caller passes a ModuleData pointer and the body appends it to a vector at
// this+0x14; the ModuleFactory header supplies the vector element type only.
// Class identity is unproven, so this uses the packet's honest address name.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "stl/_vector.h"
class ModuleData;
class Rva003F9048 {
public:
    void rva003F9048(const ModuleData *data);
private:
    char m_prefix[0x14];
    _STL::vector<const ModuleData *> m_items;
};
void Rva003F9048::rva003F9048(const ModuleData *data)
{
    if (data)
        m_items.push_back(data);
}
