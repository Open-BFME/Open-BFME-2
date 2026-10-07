// cl: /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
// Sibling of rowed ??0CollisionManager@@QAE@XZ at 0x00758250 (146B).
// Retail 0x006C08F0 (143B) is BfmeTaintManager's constructor. It has the
// same SubsystemInterface+Snapshot base layout, the same SEH frame and the
// same base ctor call 0x001B4E63; it allocates the 0x30-byte Gen_008812D0
// grid at 0x006C1490 and stores it at +0x10. The only encoded delta is the
// allocation size: 0x30 fits in a signed byte, so push imm8 shortens the
// body by three bytes versus the template's push 0xC070.
#include "Common/Snapshot.h"

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	unsigned char m_unknown04[4];
	void *m_name;
};

// The grid type is fully defined in BfmeGridRasterCircle.cpp; this unit only
// needs its 0x30-byte size and the rowed constructor at 0x006C1490.
class Gen_008812D0
{
public:
	Gen_008812D0();
	~Gen_008812D0();

private:
	unsigned char m_data[0x30];
};

class BfmeTaintManager : public SubsystemInterface, public Snapshot
{
public:
	BfmeTaintManager();
	virtual ~BfmeTaintManager();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	Gen_008812D0 *m_grid;
};

BfmeTaintManager::BfmeTaintManager()
{
	m_grid = new Gen_008812D0;
}

// Retail 0x006C09A0 (115B), the destructor the scalar deleting destructor at
// 0x006C0B60 calls: the same two vtables and SEH frame as the constructor,
// then the owned grid is destroyed through its rowed destructor 0x006C0D70
// and freed, Snapshot's inline destructor resets +0x0C to 0x00BBB554, and
// the SubsystemInterface base destructor (pin 0x001B4E74) runs last.
BfmeTaintManager::~BfmeTaintManager()
{
	delete m_grid;
}
