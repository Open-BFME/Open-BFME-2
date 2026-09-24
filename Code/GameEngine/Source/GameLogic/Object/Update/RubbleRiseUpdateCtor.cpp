// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0RubbleRiseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z retail 0x004A4CC7
// 139 bytes. Behavior-side ctor completing the RubbleRiseUpdate file-unit
// (behavior instance factory rowed at 0x24EDCF news 0x48 with this 2-arg
// ctor as its sole caller; poolkey rowed at 0x4A4C82; ModuleData proc
// 0x4A5486 plus ModuleData factory 0x2566F6 plus ModuleData ctor 0x256653
// all rowed).
//
// Shape follows the StructureCollapseUpdate behavior ctor precedent over the
// same rowed UpdateModule base 0x253390: two-phase +0x20 slot
// (C1C780-then-C52858 via sourced-before address-take) plus int zeros at
// +0x24/+0x28/+0x2C via an eax-homed zero local (PrisonDock idiom) plus
// float zeros at +0x30/+0x34/+0x38 before and +0x3C/+0x40/+0x44 after the
// setWakeFrame tail via an xmm0-homed fzero local (/arch:SSE flips x87
// fldz to retail xorps+movss). The sourced-before takes pin the push-imm
// between the float stores: slot20 take holds the +0x20 store early and
// linger take plus object take split the call pushes to retail positions
// (address-take law). Member names follow the delay-rate-scatter pattern
// of the ModuleData table; the frame arg is the 0x3FFFFFFF never-wake
// literal. /GX for the EH prologue plus the single mid-body state store;
// the declared-only base dtor arms it with no emitted code. Zero new pins
// (base ctor resolves via its row; setWakeFrame resolves via the existing
// IAEX Object-uint pin at 0x44DF71). Row supersedes the ctor pin.

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

class RubbleRiseUpdate : public UpdateModule
{
public:
	RubbleRiseUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_secondary20;
	unsigned int m_phaseDelay24;
	unsigned int m_burstDelay28;
	unsigned int m_retryDelay2C;
	float m_riseRate30;
	float m_scatter34;
	float m_linger38;
	float m_fade3C;
	float m_settle40;
	float m_cooldown44;
};

// ??0RubbleRiseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004A4CC7
RubbleRiseUpdate::RubbleRiseUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float fzero = 0.0f;
	int *slot20 = (int *)&m_secondary20;
	*slot20 = (int)0x00C1C780;
	float *lingerSlot = &m_linger38;
	Object **objSlot = &m_object;
	int zero = 0;
	m_vtable = (const void *)0x00C52868;
	m_secondary0C = (const void *)0x00C49188;
	m_secondary10 = (const void *)0x00C5285C;
	m_secondary20 = (const void *)0x00C52858;
	m_phaseDelay24 = zero;
	m_retryDelay2C = zero;
	m_riseRate30 = fzero;
	m_burstDelay28 = zero;
	m_scatter34 = fzero;
	*lingerSlot = fzero;
	m_fade3C = fzero;
	m_settle40 = fzero;
	m_cooldown44 = fzero;
	setWakeFrame(*objSlot, 0x3FFFFFFF);
}
