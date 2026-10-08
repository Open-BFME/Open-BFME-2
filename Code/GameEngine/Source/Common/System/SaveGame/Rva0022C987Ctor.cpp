// cl: /EHsc /MD
// stlport
//
// ??0Rva0022C9F6@@QAE@XZ @0x0022C987 75B: ctor for the class whose
// virtual dtor lives rowed at 0x0022C9F6. Calls rowed baseConstruct
// 0x001B4E63 via the novtable base, stores vtable 0xBE74F0, constructs
// BitFlags<11> at +0xC via rowed 0x003B31AD then _List_base at +0x10
// via rowed 0x0035C9A6, then or 0x28 into the flag word. Evidence: leaf
// packet calls rowed baseConstruct plus rowed BitFlags and List_base;
// vtable matches the rowed dtor; caller at 0x0022F405.
//
// Register-allocation note (established from the byte match): retail binds
// this to edi and keeps esi as the +0xC scratch, so the bitword address is
// materialised into a callee-save before the base ctor and re-dereferenced
// after it. Reproducing that live range needs the address local to survive
// past the flag write, hence the two |0x28 stores rather than one.
#include <list>

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class __declspec(novtable) Rva0022C987Base
{
public:
	Rva0022C987Base() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~Rva0022C987Base();
private:
	char m_pad[8];
};

template <int NUM_BITS>
class BitFlags
{
public:
	BitFlags();
public:
	unsigned int m_word;
};

struct BfmePod8 { int a[2]; };

class Rva0022C9F6 : public Rva0022C987Base
{
public:
	Rva0022C9F6();
	virtual ~Rva0022C9F6();
private:
	BitFlags<11> m_flags0C;
	_STL::_List_base<BfmePod8, _STL::allocator<BfmePod8> > m_list10;
};

Rva0022C9F6::Rva0022C9F6()
	: m_flags0C()
	, m_list10(_STL::allocator<BfmePod8>())
{
	unsigned int *w = &m_flags0C.m_word;
	*(int *)&m_flags0C |= 0x28;
	*w |= 0x28;
}