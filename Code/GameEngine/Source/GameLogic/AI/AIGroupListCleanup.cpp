// cl: /O1 /G7 /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP=
// stlport
// NativeAI constructor2FEA85 proves list<AIGroup*> at+14. Destructor
// 2FEBB7 calls retail's folded23B list-base cleanup at4EC395.
// Keep its definition separate: the AI destructor must not infer nothrow.
#include <list>
class AIGroup;
namespace _STL {
template<> _List_base<AIGroup *,allocator<AIGroup *> >::~_List_base()
{ clear(); _M_node.deallocate(_M_node._M_data,1); }
}

template class _STL::_List_base<AIGroup *,_STL::allocator<AIGroup *> >;
