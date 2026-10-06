// cl: /Ireference/shims/bfmelist /Ireference/shims/stlp_nodealloc /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// _List_base clear @0x00243119, 49B.
#include <list>
struct Rva00240831Dtor {
	~Rva00240831Dtor();
	char m_pad[1];
};
template void _STL::_List_base<Rva00240831Dtor, _STL::allocator<Rva00240831Dtor> >::clear();
