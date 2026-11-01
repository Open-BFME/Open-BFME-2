// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva002FED8D@@UAE@XZ @0x002FEDEC 64B virtual dtor via vptr plus List_base AsciiString plus releaseBuffer
// Evidence: vtable 0x00807408; List_base dtor 0x002FECBC; releaseBuffer 0x00036410; caller deleting dtor 0x002FFCEA; ctor sibling Rva002FED8DCtor same flags.
#include <list>
#include "../../Include/Common/BfmeStringData.h"
#include "ascii_string.h"

namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<AsciiString> >::deallocate(_List_node<AsciiString>* __p, size_t __n) const {
 _STLP_ASSERT( (__p == 0) == (__n == 0) )
 if (__p != 0) ::free((void*)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<AsciiString>*,_List_node<AsciiString>,allocator<_List_node<AsciiString> > >::deallocate(_List_node<AsciiString>* __p, size_t __n) {
 __stl_alloc_rebind(static_cast<allocator<_List_node<AsciiString> >&>(*this),(_List_node<AsciiString>*)0).deallocate(__p,__n);
}
}

class Rva002FED8D
{
public:
	virtual ~Rva002FED8D();
private:
	AsciiString m_name;
	int m_val8;
	_STL::list<AsciiString> m_list;
	int m_val10;
};
Rva002FED8D::~Rva002FED8D()
{
	m_val10 = 0;
}
