// cl: /DNDEBUG /MD /GX
//
// ??0SlavedUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004A18C5,
// 97 bytes. Behavior-side ctor (rowed instance factory 0x24EB7D news 0x48
// with this pinned 2-arg ctor as its sole raw caller; poolkey rowed at
// 0x4A1875 pushes the SlavedUpdate literal).
//
// Shape follows the WallUpgrade/StructureCollapseUpdate precedent over the
// same rowed UpdateModule base 0x253390: two-phase +0x20 slot (C6F248 first
// via sourced-before address-take, C51E30 second) plus an eax-homed int
// zero (PrisonDock idiom) plus float zeros via an xmm0-homed fzero local
// (/arch:SSE emits retail xorps+movss). No setWakeFrame tail call and no
// EH frame: the base is declared without virtuals or a dtor so the derived
// ctor stays frameless. Row supersedes the ctor pin.

extern "C" const void *const __identifier("??_7Rva0044EF5EIface20@@6B@")[];  // folded vftable 0x00C6F248 (4 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7Rva004A1855@@6BRva004A1855_E1@@@")[];  // vftable 0x00C51E30
extern "C" const void *const __identifier("??_7Rva004A1855@@6BUpdateModule@@@")[];  // vftable 0x00C51E54
extern "C" const void *const __identifier("??_7Rva004A1855@@6BBehaviorModuleInterface@@@")[];  // vftable 0x00C51E60
extern "C" const void *const __identifier("??_7Rva004A1855@@6BObjectModule@@@")[];  // vftable 0x00C51F1C

class Thing;
class ModuleData;
class Object;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class SlavedUpdate : public UpdateModule
{
public:
	SlavedUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_secondary20;
	unsigned int m_24;
	float m_28;
	float m_2C;
	float m_30;
	unsigned int m_34;
	unsigned int m_38;
	bool m_3C;
	unsigned int m_40;
	bool m_44;
	bool m_45;
};

// ??0SlavedUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004A18C5
SlavedUpdate::SlavedUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float fzero = 0.0f;
	int *slot20 = (int *)&m_secondary20;
	*slot20 = (int)((unsigned int)__identifier("??_7Rva0044EF5EIface20@@6B@"));
	int zero = 0;
	m_24 = zero;
	m_vtable = (const void *)((unsigned int)__identifier("??_7Rva004A1855@@6BObjectModule@@@"));
	m_secondary0C = (const void *)((unsigned int)__identifier("??_7Rva004A1855@@6BBehaviorModuleInterface@@@"));
	m_secondary10 = (const void *)((unsigned int)__identifier("??_7Rva004A1855@@6BUpdateModule@@@"));
	m_secondary20 = (const void *)((unsigned int)__identifier("??_7Rva004A1855@@6BRva004A1855_E1@@@"));
	m_28 = fzero;
	m_2C = fzero;
	m_30 = fzero;
	_ReadWriteBarrier();
	m_34 = zero;
	m_38 = zero;
	m_3C = false;
	m_40 = zero;
	m_44 = false;
	m_45 = false;
}
