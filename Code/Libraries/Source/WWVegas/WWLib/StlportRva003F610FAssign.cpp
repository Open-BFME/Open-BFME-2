// cl: /O1 /G7 /EHsc /MD /Oi /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4Rva003F610FElement@@QAEAAU0@ABU0@@Z @0x003F554C 56B vector assign plus tail20.
// Evidence: same 48-byte layout as int ctor 0x003F55D6 in StlportRva003F610FIntCtor.cpp; m_00 then vector m_04 via 4-byte assign 0x0026F4F4 then m_10 via Vector104 assign 0x003F5254 then tail20 rep movsd; callers 0x003F55A8/0x003F58CD/0x003F5914.
#include <vector>
#include <cstring>

class ModuleData;

struct BfmeE16
{
	float x, y, z, w;
};

struct BfmePod104
{
	int a[26];
};

struct BfmeAssignRecord104
{
	int a[26];
};

struct Rva003F5254Vector104
{
	void *m_00;
	void *m_04;
	void *m_08;
	Rva003F5254Vector104 &operator=(const Rva003F5254Vector104 &x);
};

struct Rva003F610FElement
{
	int m_00;
	_STL::vector<BfmeE16> m_04;
	_STL::vector<BfmeE16> m_10;
	int m_1C[5];
	Rva003F610FElement &operator=(const Rva003F610FElement &x);
};
Rva003F610FElement &Rva003F610FElement::operator=(const Rva003F610FElement &x)
{
	m_00 = x.m_00;
	((_STL::vector<unsigned int> &)m_04) = ((_STL::vector<unsigned int> &)x.m_04);
	((Rva003F5254Vector104 &)m_10) = ((Rva003F5254Vector104 &)x.m_10);
	memcpy(m_1C, x.m_1C, sizeof(m_1C));
	return *this;
}
