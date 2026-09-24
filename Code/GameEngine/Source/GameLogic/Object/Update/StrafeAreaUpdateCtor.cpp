// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0StrafeAreaUpdate@@QAE@PAVThing@@PBVModuleData@@@Z retail 0x003A4D23
// 129 bytes. Behavior-side ctor completing the StrafeAreaUpdate file-unit
// (behavior instance factory rowed at 0x24D6FF news 0x48 with this 2-arg
// ctor as its sole caller; poolkey rowed at 0x3A4CCD; ModuleData proc
// 0x3A4D12 plus ModuleData factory 0x24D737 plus ModuleData ctor 0x3A4E5A
// all rowed; the proc ends exactly where this ctor begins).
//
// Shape follows the RubbleRiseUpdate/DefaultProductionExitUpdate behavior
// ctor precedent over the same rowed UpdateModule base 0x253390: EH prolog
// plus three vtable installs (+0/+0xC/+0x10) plus float/int/byte zero stores
// plus setWakeFrame tail (frame literal 1, not the RubbleRise never-wake).
// Scheduling: the sourced-before float take on the +0x20 slot holds that
// store early while the object take holds the m_object push late, so the
// frame push hoists above the three +0x34/+0x30/+0x2C stores but stays below
// the take-held +0x20 store (take-split law; a take on +0x34 instead traps
// the push below it). Member names are strafe-run state inferred from the
// zero-init layout and the ModuleData sweep table (WeaponName,
// StrafeAreaRadius, SweepFrequency, SweepAmplitude, Slope); no donor names
// the behavior members. /GX for the EH prologue plus the single mid-body
// state store; the declared-only base dtor arms it with no emitted code.
// Row supersedes the ctor pin (surgical delete, same commit).

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

class StrafeAreaUpdate : public UpdateModule
{
public:
	StrafeAreaUpdate(Thing *thing, const ModuleData *moduleData);

private:
	float m_strafeFromX;
	float m_strafeFromY;
	float m_strafeFromZ;
	float m_strafeToX;
	float m_strafeToY;
	float m_strafeToZ;
	float m_sweepOffset;
	int m_strafeMode;
	unsigned char m_strafing;
	int m_strafeCounter;
};

// ??0StrafeAreaUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x003A4D23
StrafeAreaUpdate::StrafeAreaUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float fzero = 0.0f;
	int zero = 0;
	float *fromSlot = &m_strafeFromX;
	m_vtable = (const void *)0x00C1B164;
	m_secondary0C = (const void *)0x00BEFF90;
	m_secondary10 = (const void *)0x00C1B158;
	m_sweepOffset = fzero;
	m_strafeMode = zero;
	m_strafing = 0;
	m_strafeCounter = zero;
	m_strafeFromZ = fzero;
	m_strafeFromY = fzero;
	*fromSlot = fzero;
	m_strafeToZ = fzero;
	m_strafeToY = fzero;
	m_strafeToX = fzero;
	Object **objSlot = &m_object;
	setWakeFrame(*objSlot, 1);
}
