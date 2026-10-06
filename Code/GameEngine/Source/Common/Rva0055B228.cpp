// cl: /Ireference/shims/bfmelist /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0055B228@Rva0055B0CC@@QAEXXZ @0x0055B228 62B
// Vslot 5 method via m_04 plus list m_14 size plus m_18.
// Evidence: thiscall 0 args ret void; movss m_04 to m_18 plus list chase at +0x14 counting via next at +0 plus fild unsigned size plus fadd m_04 plus fstp m_18; vtable slot 5 of 0x0086B900 class Rva0055B0CC; neighbours 0x0055B166 0x0055B266; float 2^32 via fild adjust.
#include <list>

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
	void rva0055B228();
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

void Rva0055B0CC::rva0055B228()
{
	float f = m_04;
	m_18 = f;
	m_18 = f + m_14.size();
}
