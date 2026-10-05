// cl: /Ireference/shims/bfmelist /Ireference/shims/stlp_nodealloc /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// _List_base clear @0x001B4C7A, 49B.
#include <list>
struct BfmeVectorRecord001B4A39 {
	~BfmeVectorRecord001B4A39();
	char m_pad[1];
};
template void _STL::_List_base<BfmeVectorRecord001B4A39, _STL::allocator<BfmeVectorRecord001B4A39> >::clear();
