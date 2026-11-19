// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// WB 0x00EFFE30 and the complete 0x0035B7D9..0x0035B825 retail body:
// clear the pointer triple at +0xEC, append each source pointer, optionally
// mark TheControlBar+0x28 dirty. No original class or element type is proven.
// Use the ledger-owned void-pointer erase and ModuleData-pointer append ABI
// views, without inferring inheritance or an original template instantiation.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
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
// push_back is called out of line and the copy the link keeps is retail's; this
// unit's own copy differed, so it is declared only.
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::push_back(const ModuleData *const &); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@PBVModuleData@@@_STL@@QBEXPAPBVModuleData@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void allocator<const ModuleData *>::deallocate(const ModuleData **, size_t) const; }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::_M_clear(); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::end() { return this->_M_finish; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::begin() { return this->_M_start; } }

class ControlBar;
extern ControlBar *TheControlBar;
struct ControlBarReloadView { char unknown00[0x28]; bool reloaded; };
class Rva0035B7D9
{
public:
    void rva0035B7D9(Rva0035B7D9 *,bool);
private:
    char unknown00[0xEC];
    _STL::vector<void *> opaquePointers;
};
void Rva0035B7D9::rva0035B7D9(Rva0035B7D9 *source,bool notify)
{
    _STL::vector<void *> *dest=&opaquePointers;
    dest->erase(dest->begin(),dest->end());
    for (void **it=source->opaquePointers.begin(); it<source->opaquePointers.end(); ++it)
        ((_STL::vector<const ModuleData *> *)dest)->push_back(
            reinterpret_cast<const ModuleData *const &>(*it));
    if (notify)
        ((ControlBarReloadView *)TheControlBar)->reloaded=true;
}
