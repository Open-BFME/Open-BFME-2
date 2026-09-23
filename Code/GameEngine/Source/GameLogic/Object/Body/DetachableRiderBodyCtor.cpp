// cl: /O1 /DNDEBUG /MD /GX
//
// ??0DetachableRiderBody@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C1C82,
// 109 bytes. Body-side ctor (rowed instance factory 0x251705 news 0x108
// with this pinned 2-arg ctor as its sole raw caller at 0x25172F).
//
// Shape follows the RadiateFearUpdate precedent over the pinned ActiveBody
// base 0x4BF6A1: EH prologue via /GX plus the declared-only base dtor, an
// UpgradeMux member at +0x100 built in the init-list (rowed 0-arg ctor
// 0x4CE2A3; member layout mirrors UpgradeModuleCtor.cpp), the module data
// pointer homed early, the three derived vtable installs, a vtable
// overwrite of the member, and a conditional self-upgrade on the module
// data flag at +0x178 (rowed giveSelfUpgrade 0x45230C). The base runs to
// +0x100 with the module data pointer at +0x04 (FreeLifeBody precedent).
// Row supersedes the ctor pin.

class Thing;
class ModuleData;

struct DetachableRiderBodyModuleData
{
	unsigned char m_pad00[0x178];
	bool m_178;
};

class UpgradeMux
{
public:
	UpgradeMux();
	void giveSelfUpgrade();

private:
	void *m_vtable;
	unsigned int m_executed;
};

class ActiveBody
{
public:
	ActiveBody(Thing *thing, const ModuleData *moduleData);
	~ActiveBody();

protected:
	const void *m_vtable;
	const ModuleData *m_moduleData;
	unsigned char m_pad08[4];
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned char m_pad14[0x100 - 0x14];
};

class DetachableRiderBody : public ActiveBody
{
public:
	DetachableRiderBody(Thing *thing, const ModuleData *moduleData);

private:
	UpgradeMux m_100;
};

// ??0DetachableRiderBody@@QAE@PAVThing@@PBVModuleData@@@Z @0x004C1C82
DetachableRiderBody::DetachableRiderBody(Thing *thing, const ModuleData *moduleData)
	: ActiveBody(thing, moduleData), m_100()
{
	const DetachableRiderBodyModuleData *data = (const DetachableRiderBodyModuleData *)m_moduleData;
	m_vtable = (const void *)0x00C5C0B8;
	m_secondary0C = (const void *)0x00C5BFF8;
	m_secondary10 = (const void *)0x00C5BF48;
	*(void **)&m_100 = (void *)0x00C5BF00;
	if (data->m_178)
		m_100.giveSelfUpgrade();
}
