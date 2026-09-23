// cl: /O1 /DNDEBUG /MD
//
// ??0FakePathfindPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00461944, 99 bytes. Frameless behavior ctor over the rowed
// UpdateModule base (0x253390): two-phase +0x20/+0x24 slots (ints first,
// vtable dummies second), byte zeros at +0x30/+0x31/+0x32 plus int zero at
// +0x34, then CRT memset over +0x28 (8 bytes). The rowed instance factory
// 0x24B50D (news 0x38) is the sole caller. Row supersedes the ctor pin.

#include <string.h>

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;
static int s_secondary24;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
};

class FakePathfindPortalBehaviour : public UpdateModule
{
public:
	FakePathfindPortalBehaviour(Thing *thing, const ModuleData *moduleData);

private:
	int m_20;
	int m_24;
	char m_28[8];
	bool m_30;
	bool m_31;
	bool m_32;
	int m_34;
};

// ??0FakePathfindPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z @0x461944
FakePathfindPortalBehaviour::FakePathfindPortalBehaviour(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *slot20 = (int *)&m_20;
	int *slot24 = (int *)&m_24;
	*slot20 = 0x00C1C780;
	*slot24 = 0x00C4EF80;
	m_30 = false;
	m_31 = false;
	m_32 = false;
	m_34 = 0;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_20 = (int)&s_secondary20;
	m_24 = (int)&s_secondary24;
	memset(m_28, 0, 8);
}
