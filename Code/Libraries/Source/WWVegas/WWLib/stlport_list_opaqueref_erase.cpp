// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// platformsdk
// stlport
//
// ?erase@?$list@UOpaqueRefElement4@@V?$allocator@UOpaqueRefElement4@@@_STL@@@_STL@@QAE?AU?$_List_iterator@UOpaqueRefElement4@@U?$_Nonconst_traits@UOpaqueRefElement4@@@_STL@@@2@U32@@Z retail 0x00054AA1 44B
// Evidence: identical unlink plus destroy plus free shape to list<CameraMarker>::erase at 0x002A12B7 and list<AsciiString>::erase at 0x000BC67A;
// here destroys OpaqueRefElement4 at node+8 via rowed deleting dtor 0x00051B1E then frees via _free 0x00030830;
// element view with inline dtor from StlportOwnedDeque.cpp using Release_Ref 0x00050ED3; callers include pop_front 0x00054ACD and pop_back 0x00054AE3.
#include <windows.h>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include "OpaqueRefCounted.h"

struct OpaqueRefElement4
{
    OpaqueRefCounted *referent;
    ~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
};

bool operator==(const OpaqueRefElement4 &a, const OpaqueRefElement4 &b);
bool operator<(const OpaqueRefElement4 &a, const OpaqueRefElement4 &b);

// Emit the recovered operations and their ownership chain. The whole-class
// instantiation also emitted sort/remove with undefined element comparisons;
// those operations have no retail owner in this unit.
template _STL::list<OpaqueRefElement4>::iterator
_STL::list<OpaqueRefElement4>::erase(iterator);
template void _STL::list<OpaqueRefElement4>::pop_front();
template void _STL::list<OpaqueRefElement4>::pop_back();
template _STL::list<OpaqueRefElement4>::~list();
