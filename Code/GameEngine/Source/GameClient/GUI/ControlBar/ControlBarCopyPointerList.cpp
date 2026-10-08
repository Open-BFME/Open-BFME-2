// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// WB 0x00EFFE30 and the complete 0x0035B7D9..0x0035B825 retail body:
// clear the pointer triple at +0xEC, append each source pointer, optionally
// mark TheControlBar+0x28 dirty. No original class or element type is proven.
// Use the ledger-owned void-pointer erase and ModuleData-pointer append ABI
// views, without inferring inheritance or an original template instantiation.
#include <vector>
class ModuleData;
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
