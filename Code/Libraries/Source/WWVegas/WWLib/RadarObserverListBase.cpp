// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Authentic pointer-list base bodies needed by the native radar destructor.
// This independent TU preserves the declaration-only base destructor view
// in its consumer; its complete clear and teardown are relocation twins of
// the existing int-list providers at23DAA5/4EC395. No element-name claim.
#include <list>
struct Rva004FA1FObserver;
typedef _STL::_List_base<Rva004FA1FObserver*,_STL::allocator<Rva004FA1FObserver*> > RadarObserverListBase;
template void RadarObserverListBase::clear();


// Keep the consumer's explicit specialization declaration honest: this
// definition is the unchanged STLport base cleanup in its provider TU.
namespace _STL {
template<> _List_base<Rva004FA1FObserver*,allocator<Rva004FA1FObserver*> >::~_List_base(){clear();_M_node.deallocate(_M_node._M_data,1);}
}

template RadarObserverListBase::~_List_base();
