// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
#include <list>
class Object;
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<Object *> >::deallocate(_List_node<Object *>* __p, size_t __n) const {
 _STLP_ASSERT( (__p == 0) == (__n == 0) )
 if (__p != 0) ::free((void*)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<Object *>*,_List_node<Object *>,allocator<_List_node<Object *> > >::deallocate(_List_node<Object *>* __p, size_t __n) {
 __stl_alloc_rebind(static_cast<allocator<_List_node<Object *> >&>(*this),(_List_node<Object *>*)0).deallocate(__p,__n);
}
}


namespace _STL {
template<> _List_base<int,allocator<int> >::_List_base(const allocator<int>&);
template<> _List_base<int,allocator<int> >::~_List_base();
}
#include "TunnelTrackerNemesisView.h"
TunnelTracker::TunnelTracker()
{
    m_tunnelCount = 0;
    m_containListSize = 0;
    m_curNemesisID = 0;
    m_nemesisTimestamp = 0;
    m_counter = 0;
}

void TunnelTracker::rva004F5391(bool up)
{
    if (up) ++m_counter;
    else --m_counter;
}
const char *TunnelTracker::GetSnapshotName() const
{
    return "TunnelTracker";
}
