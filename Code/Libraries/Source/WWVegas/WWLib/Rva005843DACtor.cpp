// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva005843DA@@QAE@PAX@Z @0x005843DA 43B
// Derived ctor: base Rva005D6FCC at +0 via rowed 0x005D6FCC then vector<BfmeE16> at +8
// via rowed Vector_base 0x00211E58 with empty allocator temp at [ebp+0xb] plus bool at +0x14
// cleared; vtable 0x0086FC80 slot0; caller 0x00469319 news 0x18; same recipe as rowed
// ??0Rva00586D8E 0x00586D8E without the second ptr.
#include <vector>

struct Rva00583CE0Elem
{
	int m_00;
	char m_pad04[0x0C];
	bool m_10;
	char m_pad11[0x03];
	unsigned int m_14;
	char m_pad18[0x04];
};
struct SingletonDFE78C
{
	char m_pad[0x40];
	unsigned int m_40;
};
extern SingletonDFE78C *g_00DFE78C;

class Rva005D6FCC
{
public:
	Rva005D6FCC(void *held);
	virtual ~Rva005D6FCC();
	void *m_held;
};

class Rva005843DA : public Rva005D6FCC
{
public:
	Rva005843DA(void *held);
	virtual ~Rva005843DA();
	void rva00583CE0(int unused, int i);
	bool rva00583BE6(int i);
	bool rva00583C1A(int i);
	bool rva00583C4E(int i);
private:
	_STL::vector<Rva00583CE0Elem> m_vec; // +8
	bool m_flag; // +0x14
};

Rva005843DA::Rva005843DA(void *held)
	: Rva005D6FCC(held), m_vec(_STL::allocator<Rva00583CE0Elem>())
{
	m_flag = false;
}
void Rva005843DA::rva00583CE0(int unused, int i)
{
	if (i >= 0 && i < m_vec.size())
		m_vec[i].m_10 = true;
}
bool Rva005843DA::rva00583BE6(int i)
{
	if (i >= 0 && i < m_vec.size())
		return m_vec[i].m_00 == 1;
	return false;
}
bool Rva005843DA::rva00583C1A(int i)
{
	if (i >= 0 && i < m_vec.size())
		return m_vec[i].m_00 == 2;
	return false;
}
bool Rva005843DA::rva00583C4E(int i)
{
	if (i >= 0 && i < m_vec.size())
		return m_vec[i].m_14 > g_00DFE78C->m_40;
	return false;
}
// ?g_00DFE78C@@3PAUSingletonDFE78C@@A: the global at VA 0xdfe78c is ?TheGameLogic@@3PAVGameLogic@@A.
#pragma comment(linker, "/alternatename:?g_00DFE78C@@3PAUSingletonDFE78C@@A=?TheGameLogic@@3PAVGameLogic@@A")
