// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Address-derived AIUnitBuilder operation at 0x00598D7A (40 bytes).
// Target evidence: the body tests and clears byte +0x2C, calls 0x00598A3D
// and 0x00598961 with this unchanged, calls matched AIUnitBuilder::build at
// 0x00598C3A, then tail-jumps to 0x00598052. The neighboring 0x00598961 body
// reads the +0x14 list, +0x30 value, and +0x34 flag already present in the
// matched build view. The owner is therefore modeled as AIUnitBuilder; the
// original method name and the helper identities remain unknown.
#include <list>

class Rva00598C3AItem
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6(int value, int flags);
};

class AIUnitBuilder
{
public:
	void Rva00598A3D();
	void Rva00598961();
	void build();
	void Rva00598052();
	void Rva00598D7A();
	Rva00598C3AItem *createBestHeroToBuild();
	Rva00598C3AItem *createBestUnitToMake();

private:
	unsigned char m_pad00[0x14];
	_STL::list<Rva00598C3AItem *> m_items; // +0x14
	unsigned char m_pad18[0x2C - 0x18];
	bool m_2C; // +0x2C, read and cleared by target bytes
	unsigned char m_pad2D[0x30 - 0x2D];
	int m_30; // +0x30
	bool m_34; // +0x34
};

void AIUnitBuilder::Rva00598D7A()
{
	if (m_2C)
	{
		Rva00598A3D();
		m_2C = false;
	}
	Rva00598961();
	build();
	return Rva00598052();
}
