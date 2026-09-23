// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0OneRingPenaltyUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x00499A70, 113 bytes. Behavior-side ctor (pinned by its Update factory
// call-site decode: sole E8 caller is factory 0x24E3F4 which news 0x34
// and forwards thing plus data).
//
// Shape follows the TerrainResourceBehavior precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, a two-phase +0x20 slot via sourced-before address-take, an
// eax-homed int zero, a float zero via an xmm0-homed fzero local (/arch:SSE
// emits retail xorps+movss), the setWakeFrame arg pushes hoisted above the
// stores (no intervening call), the three derived vtable installs, zeros
// at +0x24/+0x28/+0x30, and the setWakeFrame tail (protected IAEX
// Object-uint spelling resolves via the existing pin at 0x44DF71). Row
// supersedes the ctor pin.

class Thing;
class ModuleData;
class Object;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	void setWakeFrame(Object *object, unsigned int frame);

	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class OneRingPenaltyUpdate : public UpdateModule
{
public:
	OneRingPenaltyUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_20;
	unsigned int m_24;
	unsigned int m_28;
	float m_2C;
	unsigned int m_30;
};

// ??0OneRingPenaltyUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00499A70
OneRingPenaltyUpdate::OneRingPenaltyUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float fzero = 0.0f;
	int *slot20 = (int *)&m_20;
	*slot20 = (int)0x00C1C780;
	int zero = 0;
	m_vtable = (const void *)0x00C50260;
	m_secondary0C = (const void *)0x00C49188;
	m_secondary10 = (const void *)0x00C50254;
	m_20 = (const void *)0x00C50250;
	m_24 = zero;
	m_28 = zero;
	m_2C = fzero;
	m_30 = zero;
	setWakeFrame(m_object, 1);
}
