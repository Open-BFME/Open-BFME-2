// cl: /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
// Native 006253F0..00625482 is a masked sibling of CollisionManager ctor758250.
// Target establishes SubsystemInterface call1B4E63, Snapshot base+0C, owned
// 124-byte allocation and rowed state ctor627FB0, stored at+10.
// State type carried from existing627FB0 provider; manager original identity
// is unknown, so retained existing address-derived callee pin name.
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
// needs its 0x124-byte size and the rowed constructor at 0x006C1490.
class Rva009F5970State
{
public:
	Rva009F5970State();
	~Rva009F5970State();

private:
	unsigned char m_data[0x124];
};

class Rva006253F0 : public SubsystemInterface, public Snapshot
{
public:
	Rva006253F0();
	virtual ~Rva006253F0();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	Rva009F5970State *m_grid;
};

Rva006253F0::Rva006253F0()
{
	m_grid = new Rva009F5970State;
}

