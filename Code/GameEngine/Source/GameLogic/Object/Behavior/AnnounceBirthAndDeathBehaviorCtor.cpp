// cl: /O1 /DNDEBUG /MD
//
// ??0AnnounceBirthAndDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00485125, 56 bytes.
// AnnounceBirthAndDeathBehavior behavior ctor over the rowed CreateModule
// base (0x4B8CF7): double-stores +0x18 (C1C780 then C4A54C) around the
// primary vtable slot and the +0x0C/+0x10 secondary slots (address-of
// TU-local dummies, DIR32-masked). The rowed name getter at 0x485163 proves
// the class; the rowed instance factory 0x24C7C7 is the sole raw caller. Row
// supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_first18;
static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_second18;

// Rowed CreateModule base; ctor resolves to its row. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class CreateModule
{
public:
	CreateModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x18 - 0x14];
	const void *m_p18;
};

class AnnounceBirthAndDeathBehavior : public CreateModule
{
public:
	AnnounceBirthAndDeathBehavior(Thing *thing, const ModuleData *moduleData);
};

// ??0AnnounceBirthAndDeathBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x485125
AnnounceBirthAndDeathBehavior::AnnounceBirthAndDeathBehavior(Thing *thing, const ModuleData *moduleData)
	: CreateModule(thing, moduleData)
{
	*(const void * volatile *)&m_p18 = &s_first18;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p18 = &s_second18;
}
