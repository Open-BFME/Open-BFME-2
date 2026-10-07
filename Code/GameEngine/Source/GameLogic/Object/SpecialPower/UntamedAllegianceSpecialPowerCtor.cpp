// cl: /DNDEBUG /MD
//
// ??0UntamedAllegianceSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C7B06, 42 bytes.
// UntamedAllegianceSpecialPower behavior ctor over the pinned SpecialPowerModule
// intermediate base (0x493C5A, thing plus data): re-stores the primary
// vtable slot and the +0x0C/+0x10 secondary slots (address-of TU-local
// dummies, DIR32-masked). The rowed name getter at 0x4C7B4F proves the
// class; the rowed instance factory 0x25247A is the sole raw caller. Row
// supersedes the ctor pin.

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
};

class UntamedAllegianceSpecialPower : public SpecialPowerModule
{
public:
	UntamedAllegianceSpecialPower(Thing *thing, const ModuleData *moduleData);
};

// ??0UntamedAllegianceSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z @0x4C7B06
UntamedAllegianceSpecialPower::UntamedAllegianceSpecialPower(Thing *thing, const ModuleData *moduleData)
	: SpecialPowerModule(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
}
