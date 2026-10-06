// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// A vendored instantiation unit. It exists so the linker-selected bodies of
// this container appear as COMDATs that build/objplace.py can place against
// unlanded functions; the suffix says which optimisation level, because for
// these containers different bodies survive the link from different units.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

template class _STL::list<int, _STL::allocator<int> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva004EC395Member@@QAE@XZ=??1?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva0023DAA5List@@QAE@XZ=??1?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?clear@Rva0023DAA5List@@QAEXXZ=?clear@?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAEXXZ")
#pragma comment(linker, "/alternatename:??0?$_List_base@MV?$allocator@M@_STL@@@_STL@@QAE@ABV?$allocator@M@1@@Z=??0?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@ABV?$allocator@H@1@@Z")
#pragma comment(linker, "/alternatename:??0?$_List_base@UFloodMember@@V?$allocator@UFloodMember@@@_STL@@@_STL@@QAE@ABV?$allocator@UFloodMember@@@1@@Z=??0?$_List_base@HV?$allocator@H@_STL@@@_STL@@QAE@ABV?$allocator@H@1@@Z")
