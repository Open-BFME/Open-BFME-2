// cl: /Ireference/shims/bfmelist /Ireference/shims/stlp_nodealloc /DNDEBUG /MD /EHs-c- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva002461DA@Rva002461DA@@QAEXXZ @0x002461DA 23B unlock: list clear plus free
// Evidence: calls rowed List_base clear 0x243119 plus rowed _free 0x30830; layout base at +0 with first dword freed; callers at 0x248CA4 plus jmp 0x247084; prev ArmorStoreCtor next OpaqueScalarDeletingDtors.
#include <list>
struct Rva00240831Dtor {
	~Rva00240831Dtor();
	char m_pad[1];
};
extern "C" void __cdecl free(void *p);
class Rva002461DA {
	_STL::_List_base<Rva00240831Dtor, _STL::allocator<Rva00240831Dtor> > m_base;
public:
	void rva002461DA();
};
void Rva002461DA::rva002461DA()
{
	m_base.clear();
	void *p = *(void **)&m_base;
	if (p)
		free(p);
}
