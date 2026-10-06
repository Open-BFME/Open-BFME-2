// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// AIUnitBuilder::build, retail 0x00598C3A (66 bytes).
// Identity (target): WorldBuilder's debug AIUnitBuilder.cpp line 456 names it
// and its callees (wb-lead 2/callgraph): unless the flag at +0x34 is set,
// try createBestHeroToBuild (0x0059858C); fall back to createBestUnitToMake
// (0x00598B78); start the chosen item through its slot 6 with the +0x30 value
// and 0, then append it to the list at +0x14 (STLport pointer-list push_back
// fold 0x0005548F). WB's leading getAI() range reads have no effect and are
// gone from retail. Item type and the +0x34/+0x30 member roles are not
// established by target evidence and stay address-named.
#include <list>

// Address-named build item made by the two factories (slot 6 starts it).
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
	void build();
	Rva00598C3AItem *createBestHeroToBuild();
	Rva00598C3AItem *createBestUnitToMake();

private:
	unsigned char m_pad00[0x14];
	_STL::list<Rva00598C3AItem *> m_items; // +0x14
	unsigned char m_pad18[0x30 - 0x18];
	int m_30; // +0x30
	bool m_34; // +0x34
};

void AIUnitBuilder::build()
{
	Rva00598C3AItem *item = 0;
	if (!m_34)
		item = createBestHeroToBuild();
	if (item == 0)
		item = createBestUnitToMake();
	if (item != 0)
	{
		item->slot6(m_30, 0);
		m_items.push_back(item);
	}
}
