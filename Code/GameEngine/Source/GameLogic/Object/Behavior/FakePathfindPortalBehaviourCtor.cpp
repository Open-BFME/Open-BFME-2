// cl: /DNDEBUG /MD
//
// ??0FakePathfindPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00461944, 99 bytes. Frameless behavior ctor over the rowed
// UpdateModule base (0x253390): two-phase +0x20/+0x24 slots (ints first,
// vtable dummies second), byte zeros at +0x30/+0x31/+0x32 plus int zero at
// +0x34, then CRT memset over +0x28 (8 bytes). The rowed instance factory
// 0x24B50D (news 0x38) is the sole caller. Row supersedes the ctor pin.

extern "C" const void *const __identifier("??_7GhostObject@@6BRva001B3E60SecondBaseCore@@@")[];  // folded vftable 0x00C4EF80 (7 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7SecondaryModuleBase@FXParticleSystem@@6B@")[];  // folded vftable 0x00C1C780 (49 classes), by its data-ledger name

#include <string.h>

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;
static int s_secondary24;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class Xfer;
class Waypoint;

// Retail ctor 0x461944 stores five vptrs: +0x00, +0x0C and +0x10 inside the
// UpdateModule base, +0x20 and +0x24 for two interface bases (whose own
// vtables, 0x00C1C780 and 0x00C4EF80, the inlined base ctors store first).
// The 0x00C42B50 interface's slot 0 is rva0046190A, entered with this at
// +0x20. novtable: the ctor writes those stores explicitly.
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const = 0;
	void xfer(Xfer *xfer);

protected:
	Thing *m_owner;		// +0x04
	int m_pad08;
	const void *m_p0C;	// +0x0C
	const void *m_p10;	// +0x10
	unsigned char m_pad[0x20 - 0x14];
};

class __declspec(novtable) Rva00C42B50Iface
{
public:
	virtual void rva0046190A(void *arg) = 0;
};

class __declspec(novtable) Rva00C42B40Iface
{
public:
	virtual void slot0() = 0;
};

class __declspec(novtable) FakePathfindPortalBehaviour : public UpdateModule, public Rva00C42B50Iface,
	public Rva00C42B40Iface
{
public:
	FakePathfindPortalBehaviour(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void rva0046190A(void *arg);
	void rva0046183B();
	void rva00461C1F();

protected:
	virtual void xfer(Xfer *xfer);

private:
	void regWaypointsWithPathfinder();

	enum { WAYPOINT_COUNT = 2 };
	Waypoint *m_28[WAYPOINT_COUNT];	// +0x28
	bool m_30;
	bool m_31;
	bool m_32;
	int m_34;
};

// ??0FakePathfindPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z @0x461944
FakePathfindPortalBehaviour::FakePathfindPortalBehaviour(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *slot20 = (int *)((char *)this + 0x20);
	int *slot24 = (int *)((char *)this + 0x24);
	*slot20 = ((unsigned int)__identifier("??_7SecondaryModuleBase@FXParticleSystem@@6B@"));
	*slot24 = ((unsigned int)__identifier("??_7GhostObject@@6BRva001B3E60SecondBaseCore@@@"));
	m_30 = false;
	m_31 = false;
	m_32 = false;
	m_34 = 0;
	*reinterpret_cast<const void **>(this) = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	*(int *)((char *)this + 0x20) = (int)&s_secondary20;
	*(int *)((char *)this + 0x24) = (int)&s_secondary24;
	memset(m_28, 0, 8);
}
