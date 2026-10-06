// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0055B01F@Rva0055B0CC@@QAEXXZ @ 0x0055B01F, 41 bytes.
// Walks the list at +0x1C, asks each peer to remove this object from its
// +0x14 list via 0x0055AFBF, then clears the list. The receiver layout is
// shared with the destructor at 0x0055B0CC; the peer method is address-named.
#include <list>

class Rva0055AFBF
{
public:
	void rva0055AFBF(int value);
};

class Rva0055B0CC
{
public:
	void rva0055B01F();
	char m_pad[0x1C];
	_STL::list<int, _STL::allocator<int> > m_list;
};

void Rva0055B0CC::rva0055B01F()
{
	for (_STL::list<int, _STL::allocator<int> >::iterator it = m_list.begin(); it._M_node != m_list.end()._M_node; ++it) {
		((Rva0055AFBF *)*it)->rva0055AFBF((int)this);
	}
	m_list.clear();
}
