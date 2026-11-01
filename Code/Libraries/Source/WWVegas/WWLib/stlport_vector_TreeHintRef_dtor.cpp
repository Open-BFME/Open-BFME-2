// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@UTreeHintRef00217D4C@@V?$allocator@UTreeHintRef00217D4C@@@_STL@@@_STL@@QAE@XZ retail 0x000806B4 63B
// Evidence: same 63B EH shape as EvaMessage vector dtor 0x000B0254 via Destroy 0x005F97BC plus free 0x00030830; callers 0x0008227E 0x00083943 0x00083A3A
#include <vector>

#include "../../Apt/AptRefTarget.h"

// Bind cleanup to the existing rowed STLport bodies instead of emitting copies.
namespace _STL {
template<> void _Destroy<TreeHintRef00217D4C *>(TreeHintRef00217D4C *, TreeHintRef00217D4C *);
template<> __declspec(dllimport) __forceinline void allocator<TreeHintRef00217D4C>::deallocate(TreeHintRef00217D4C *p, size_t) const { if (p) ::free(p); }
}

template _STL::vector<TreeHintRef00217D4C>::~vector();
