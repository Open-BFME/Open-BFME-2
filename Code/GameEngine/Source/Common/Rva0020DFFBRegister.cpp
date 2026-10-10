// cl: /DNDEBUG /MD
// stlport
//
// ?Rva0020DFFBRegister@@YAXPBVModuleData@@@Z, retail 0x0020DFFB, 44 bytes.
// Unique-register helper over global vector at 0x00DFE1AC (end at +4):
// scans [begin,end) for the ModuleData pointer and push_backs through the
// rowed 0x004DFCB0 when absent. Called from 0x004ABEAE plus 0x00285755 and
// 0x00286F65. Flags /O1 give the retail jmp-first loop shape.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
class ModuleData { public: int x; };
extern _STL::vector<const ModuleData*> g_moduleDataList0020DFFB;
void __cdecl Rva0020DFFBRegister(const ModuleData* md)
{
    for (const ModuleData** it = g_moduleDataList0020DFFB.begin(); it != g_moduleDataList0020DFFB.end(); ++it) {
        if (*it == md)
            return;
    }
    g_moduleDataList0020DFFB.push_back(md);
}
