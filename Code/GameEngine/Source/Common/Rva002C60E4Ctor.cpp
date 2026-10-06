// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva002C60E4@@QAE@PAX_N@Z @0x002C60E4 203B
// Evidence: unlock lane prev Rva002C5FE8Search next DispDword setter caller
// 0x002C6EE0 callees Rva00506B1B ctor plus Vector_base BfmeE16 plus operator
// new plus AITargetChooser/AITacticsGenerator/Rva00506A34 ctors vtable g_00C004E4
// offsets 0x08/0x0c/0x10/0x14/0x18/0x1c/0x20 ret 8 two args voidptr plus bool.
// Identity: honest-address thiscall ctor with two args.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva00506B1B
{
public:
	Rva00506B1B();
	virtual ~Rva00506B1B() {}
	virtual void v1();
	bool m_04;
};

class AITargetChooser
{
public:
	AITargetChooser(void *p);
	char m_pad[0x20];
};

class AITacticsGenerator
{
public:
	AITacticsGenerator(void *p);
	char m_pad[0x64];
};

class Rva00506A34
{
public:
	Rva00506A34(void *p);
	char m_pad[0x10];
};

class Rva002C60E4 : public Rva00506B1B
{
public:
	Rva002C60E4(void *arg0, bool arg1);
	virtual ~Rva002C60E4() {}

private:
	void *m_08;
	AITargetChooser *m_0C;
	AITacticsGenerator *m_10;
	int m_14;
	int m_18;
	Rva00506A34 *m_1C;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec;
};

Rva002C60E4::Rva002C60E4(void *arg0, bool arg1)
	: m_08(arg0), m_0C(0), m_14(0), m_18(0), m_1C(0)
{
	if (arg1)
		m_0C = new AITargetChooser(arg0);
	m_10 = new AITacticsGenerator(arg0);
	m_1C = new Rva00506A34(arg0);
}
