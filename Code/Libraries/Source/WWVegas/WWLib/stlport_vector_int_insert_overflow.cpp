// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc_alloconly
// stlport46

// STLport vector<SubtitleEntry*>::_M_insert_overflow at 0x006887F0 (callers 0x00688940
// and SubtitleManager::addSubtitle 0x00688AA0; vector<int> folds into 0x002DFCF6). Sibling TU uses the stock node allocator; retail
// routes through the 0x307F0 byte allocator yet keeps stock inline copies
// (memmove import plus inlined loop), so this instantiation lives in its own
// TU on the alloc-only shim (full bfmealloc emits out-of-line __copy_trivial
// and lands 47B short; stock headers keep the 0x80 node-alloc branch).
// No CRTIMP defuse: the CRT headers then keep memmove on its dllimport IAT
// call at 0xBBA688. The re-declaration below drops dllimport from free only
// (the reverse direction is a hard C2375), so the shim's deallocation emits
// retail's direct call to _free at 0x30830.
#include <vector>
// bfme link decl-only begin
class SubtitleEntry;
namespace _STL { template <> _Vector_base<SubtitleEntry *, allocator<SubtitleEntry *> >::_Vector_base(allocator<SubtitleEntry *> const &); }
// bfme link decl-only end

extern "C" void __cdecl free(void *);

template class _STL::vector<SubtitleEntry *, _STL::allocator<SubtitleEntry *> >;

// The complete native allocator-profile owner also emits the rowed subtitle
// push_back/fill_n and trivial backward-copy helper. Their rows are kept here
// so the stock int-vector consumer need not instantiate incompatible growth.
