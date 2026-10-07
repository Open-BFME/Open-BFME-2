// cl: /DNDEBUG /MD
//
// ??0ScavengerSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C4353, 46 bytes.
// ScavengerSpecialPower behavior ctor over the pinned SpecialPowerModule
// intermediate base (0x493C5A, thing plus data): re-stores the primary
// vtable slot and the +0x0C/+0x10 secondary slots, then zeroes the byte at
// +0x34 (address-of TU-local dummies, DIR32-masked). The rowed name getter
// at 0x4C43BC proves the class; the rowed instance factory 0x251D94 is the
// sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Constructor-only view of the verified SpecialPowerModule base at RVA
// 0x00493C5A (SpecialPowerModuleCtor.cpp). Retail calls pass this unchanged,
// followed by Thing* and ModuleData*. Keep the already verified field view;
// the explicit vptr member preserves the native store order.
class SpecialPowerModule
{
public:
	SpecialPowerModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	unsigned char m_pad04[0x0C - 4];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad14[0x34 - 0x14];
};

class ScavengerSpecialPower : public SpecialPowerModule
{
public:
	ScavengerSpecialPower(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_34;
};

// ??0ScavengerSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x4C4353
ScavengerSpecialPower::ScavengerSpecialPower(Thing *thing, const ModuleData *moduleData)
	: SpecialPowerModule(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_34 = 0;
}
