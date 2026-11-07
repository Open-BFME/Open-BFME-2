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
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEX:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::_M_insert_overflow(const ModuleData **, const ModuleData *const &, const __true_type &, size_t, bool); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@PBVModuleData@@@_STL@@QBEPAPBVModuleData@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> const ModuleData **allocator<const ModuleData *>::allocate(size_t, const void *) const; }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@PBVModuleData@@@_STL@@QBEXPAPBVModuleData@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void allocator<const ModuleData *>::deallocate(const ModuleData **, size_t) const; }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::_M_clear(); }
#include "../../Include/Common/ModuleData.h"
extern unsigned int g_00DFE1AC[3];
void __cdecl Rva0020DFFBRegister(const ModuleData* md)
{
    _STL::vector<const ModuleData *> &g_moduleDataList0020DFFB =
        *reinterpret_cast<_STL::vector<const ModuleData *> *>(&g_00DFE1AC);
    for (const ModuleData** it = g_moduleDataList0020DFFB.begin(); it != g_moduleDataList0020DFFB.end(); ++it) {
        if (*it == md)
            return;
    }
    g_moduleDataList0020DFFB.push_back(md);
}
