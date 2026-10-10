// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0Rva005990DF@@QAE@H@Z, retail 0x00598F3F..0x00598FAF (112 bytes, EH,
// ret 4). Constructor of the AI unit upgrader wrapper whose destructor is
// Rva005990DFDestructor.cpp (vtable 0x00C70D44; the AIUnitUpgrader at +0x0C
// under 0x00C70D38): the first base (vtable 0x00C62888, then 4 and 1 at +4 /
// +8) is built inline, the builder base by the rowed 0x00506B1B, two empty
// vectors at +0x14 / +0x20 and the owner player word at +0x2C. Class name
// address-derived; the vector elements are 4-byte stand-ins.
#include <vector>

class Gen_uwm_004ea016
{
public:
	Gen_uwm_004ea016() : m_04(4), m_08(1) {}
	virtual void slot00();
	~Gen_uwm_004ea016() {}
private:
	int m_04;
	int m_08;
};

class Rva00506B1B
{
public:
	Rva00506B1B();
	virtual ~Rva00506B1B();
};

class Rva005990DF : public Gen_uwm_004ea016, public Rva00506B1B
{
public:
	Rva005990DF(int owner);
	virtual ~Rva005990DF();
private:
	char m_pad10[0x14 - 0x10];
	_STL::vector<int> m_vec14;
	_STL::vector<int> m_vec20;
	int m_2C;
};

Rva005990DF::Rva005990DF(int owner)
	: m_2C(owner)
{
}
