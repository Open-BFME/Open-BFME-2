// cl: /O1 /GX- /MD /DNDEBUG
// ArrowStormUpdate's scalar deleting destructor (0x00490A58) over an opaque view.


class PoolMember
{
public:
	void Rva00268902();

private:
	unsigned char m_pad[16];
};

// Base dtor resolves to the opaque pin at 0x00451F45.
class Rva00451F45
{
public:
	virtual ~Rva00451F45();
};

class Rva004907C0 : public Rva00451F45
{
public:
	virtual ~Rva004907C0();

private:
	unsigned char m_pad04[8];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad14[12];
	const void *m_p20;
	unsigned char m_pad24[0x88 - 0x24];
	PoolMember m_mem88;
};

// The destructor is retail's ArrowStormUpdate::~ArrowStormUpdate (0x004907C0, rowed
// in ArrowStormUpdateBehaviorDtor.cpp); this unit only emits the deleting
// destructor that calls it. Deleting a freshly-newed object devirtualizes to a
// direct ??_G call, which emits that COMDAT; the anchor itself is unclaimed.
#include <new>

void Rva004907C0_Anchor()
{
	Rva004907C0 *p = new Rva004907C0;
	delete p;
}
