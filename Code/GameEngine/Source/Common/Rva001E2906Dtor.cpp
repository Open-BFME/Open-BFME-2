// cl: /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// ??1Rva001E2906@@UAE@XZ retail 0x001E2906 76B
// Two-base dtor: own vptrs BDD978 at +0 and BDD974 at +0x28; under EH state 1
// the body empties the inherited list<int> at +4 through the rowed
// ?clear@?$_List_base@H... 0x0023DAA5; the second base (vtable BC6F20,
// Rva0007DF07) is restored inline and the first base dtor
// ??1Rva001E2747@@UAE@XZ 0x001E27C6 is called. Caller: rowed ??_G 0x001E28EA
// (vtable 0x00BDD978). Names address-derived.

#include <list>

template <> void _STL::_List_base<int, _STL::allocator<int> >::clear();

class Rva001E2747
{
public:
	virtual ~Rva001E2747();

protected:
	_STL::list<int> m_list; // +0x04
	unsigned char m_pad08[0x28 - 8];
};

class Rva0007DF07
{
public:
	virtual ~Rva0007DF07() {}
};

class Rva001E2906 : public Rva001E2747, public Rva0007DF07
{
public:
	virtual ~Rva001E2906();
};

Rva001E2906::~Rva001E2906()
{
	m_list.clear();
}
