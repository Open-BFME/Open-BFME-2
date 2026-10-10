// cl: /Ireference/shims/bfmelist /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva0039225E@@UAE@XZ 89B @0x0039225E: virtual dtor storing vtable 0x0081A088. Layout base 0xC plus list<int> at +0xC (size 4) plus Rva0039205C at +0x10 (size 12). Retail calls the Rva dtor twice on the same address (explicit early destroy plus implicit) then list base then GameEngineDeletingBase. Evidence: vptr store plus rowed callees plus ??_G caller at 0x00392DA4. /EHs keeps the list state store.
#include <list>

class Rva004D9A3C
{
public:
	~Rva004D9A3C();
};

class Rva0039205C
{
public:
	~Rva0039205C();
private:
	int m_unk00; // +0
	unsigned char m_pad04[4]; // +4
	Rva004D9A3C *m_array08; // +8
};

// Base dtor at 0x001B4E74 by its row name ??1SubsystemInterface@@UAE@XZ (SubsystemInterface.cpp).
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	char m_pad04[4];
	void *m_member08;
};

class Rva0039225E : public SubsystemInterface
{
public:
	virtual ~Rva0039225E();
private:
	_STL::list<int, _STL::allocator<int> > m_list0C;
	Rva0039205C m_obj10;
};

inline Rva0039225E::~Rva0039225E()
{
	m_obj10.~Rva0039205C();
}

// Header inline that other units including the header emit as select-any
// copies, which the plain definition here collided with. The anchor keeps this
// unit's copy for the row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRva0039225EDtor@@YAXPAVRva0039225E@@@Z present-unmatched
void bfmeEmitRva0039225EDtor(Rva0039225E *p)
{
	p->Rva0039225E::~Rva0039225E();
}
#pragma inline_depth()
