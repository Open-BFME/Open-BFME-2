// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0055B01F@Rva0055B0CC@@QAEXXZ @ 0x0055B01F, 41 bytes.
// Walks the list at +0x1C, asks each peer to remove this object from its
// +0x14 list via 0x0055AFBF, then clears the list. The receiver layout is
// shared with the destructor at 0x0055B0CC; the peer method is address-named.
#include <list>

// Retain bfmealloc's native null-checked free and proxy forwarding inline.
// The matched bodies already inline these STLport ownership wrappers.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(pointer p, size_type n) const
{ if (p != 0) ::free((void*)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int>*, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int>* p, size_t n)
{ __stl_alloc_rebind(static_cast<_Base&>(*this), (_List_node<int>*)0).deallocate(p, n); }
}

class Rva0055AFBF
{
public:
	void rva0055AFBF(int value);
	char m_pad00[0x14];
	_STL::list<int, _STL::allocator<int> > m_list; // +0x14
};

class AsciiStringMember
{
public:
	AsciiStringMember() : m_data(0) {}
	~AsciiStringMember();
	void *m_data;
};

class Rva0055B0CC
{
public:
	Rva0055B0CC();
	void rva0055B01F();
	void rva0055AFA3();
	virtual ~Rva0055B0CC();
private:
	float m_04; // +0x04
	int m_08; // +0x08
	AsciiStringMember m_0C; // +0x0C
	unsigned int m_10; // +0x10
	_STL::list<int, _STL::allocator<int> > m_14; // +0x14
	float m_18; // +0x18
public:
	_STL::list<int, _STL::allocator<int> > m_1C; // +0x1C
private:
	bool m_20; // +0x20
	bool m_21; // +0x21
	char m_pad22[0x2];
	int m_24; // +0x24
	bool m_28; // +0x28
	char m_pad29[0x3];
};

void Rva0055B0CC::rva0055B01F()
{
	for (_STL::list<int, _STL::allocator<int> >::iterator it = m_1C.begin(); it._M_node != m_1C.end()._M_node; ++it) {
		((Rva0055AFBF *)*it)->rva0055AFBF((int)this);
	}
	m_1C.clear();
}
