// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
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
	*slot20 = (int)0x00C6F248;
	int zero = 0;
	m_24 = zero;
	m_vtable = (const void *)0x00C51F1C;
	m_secondary0C = (const void *)0x00C51E60;
	m_secondary10 = (const void *)0x00C51E54;
	m_secondary20 = (const void *)0x00C51E30;
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
