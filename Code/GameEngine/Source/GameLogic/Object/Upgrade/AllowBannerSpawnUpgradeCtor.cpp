// cl: /DNDEBUG /MD
//
// ??0AllowBannerSpawnUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B8587, 49 bytes.
// AllowBannerSpawnUpgrade behavior ctor over the pinned UpgradeModule base
// (0x460AEC, thing plus data): re-stores the primary vtable slot and the
// +0x0C/+0x10/+0x18 secondary slots (the class's own tables, by
// their retail store immediates). The rowed name getter at 0x4B8520 proves the class; the
// rowed instance factory 0x2508B6 is the sole raw caller. Row supersedes the
// ctor pin.

class Thing;
class ModuleData;

extern "C" const void *const __identifier("??_7AllowBannerSpawnUpgrade@@6BObjectModule@@@")[];  // vftable 0x00C59030
extern "C" const void *const __identifier("??_7AllowBannerSpawnUpgrade@@6BBehaviorModuleInterface@@@")[];  // vftable 0x00C57328
extern "C" const void *const __identifier("??_7AllowBannerSpawnUpgrade@@6BUpgradeMux@@@")[];  // vftable 0x00C58FE8
extern "C" const void *const __identifier("??_7AllowBannerSpawnUpgrade@@6BModuleInterface@@@")[];  // vftable 0x00C58790

// Opaque UpgradeModule base; ctor resolves to its pin. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class UpgradeModule
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x18 - 0x14];
};

class AllowBannerSpawnUpgrade : public UpgradeModule
{
public:
	AllowBannerSpawnUpgrade(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_p18;
};

// ??0AllowBannerSpawnUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B8587
AllowBannerSpawnUpgrade::AllowBannerSpawnUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpgradeModule(thing, moduleData)
{
	m_vtable = __identifier("??_7AllowBannerSpawnUpgrade@@6BObjectModule@@@");
	m_p0C = __identifier("??_7AllowBannerSpawnUpgrade@@6BBehaviorModuleInterface@@@");
	m_p10 = __identifier("??_7AllowBannerSpawnUpgrade@@6BUpgradeMux@@@");
	m_p18 = __identifier("??_7AllowBannerSpawnUpgrade@@6BModuleInterface@@@");
}
