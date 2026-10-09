// cl: /Ireference/shims/bfmelist /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0055B0CC@@QAE@XZ @0x0055B048 113B evidence vtable 0x0086B900 plus dtor layout plus lists plus floats plus caller cluster
// Constructor for the opaque owner of dtor 0x0055B0CC: vtable store, float
// zeros via SSE, int zeros, two list base ctors with EH states 0/1, trailing
// bools 0/1. Layout copied from Rva0055B0CCDestructor.cpp.
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

class Rva0023DAA5List : public _STL::list<int, _STL::allocator<int> >
{
public:
	~Rva0023DAA5List();
	void clear();
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
	virtual ~Rva0055B0CC();
	void rva0055B01F();

private:
	float m_04;
	int m_08;
	AsciiStringMember m_0C;
	unsigned int m_10;
	_STL::list<int, _STL::allocator<int> > m_14;
	float m_18;
	_STL::list<int, _STL::allocator<int> > m_1C;
	bool m_20;
	bool m_21;
	int m_24;
	bool m_28;
};

Rva0055B0CC::Rva0055B0CC() :
	m_04(0.0f),
	m_08(0),
	m_10(0),
	m_18(0.0f)
{
	m_21 = false;
	m_24 = 0;
	m_20 = true;
	m_28 = true;
}
