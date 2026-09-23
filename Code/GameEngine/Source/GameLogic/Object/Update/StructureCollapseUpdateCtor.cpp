// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0StructureCollapseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004A42E4, 139 bytes. Behavior-side ctor completing the
// StructureCollapseUpdate file-unit (behavior instance factory rowed at
// 0x24ED97 news 0x44 with this pinned 2-arg ctor as its sole caller at
// 0x24EDBE; poolkey rowed at 0x4A429F; helpers inList/doCollapseDoneStuff
// rowed at 0x4A423A/0x4A4DBE).
//
// Shape follows WallUpgradeUpdate precedent over the same rowed UpdateModule
// base 0x253390: two-phase +0x20 slot (C1C780-then-C52638 via sourced-before
// address-take) plus int zeros at +0x24/+0x28/+0x2C via an eax-homed zero
// local (PrisonDock idiom) plus float zeros at +0x30/+0x34 before and
// +0x38/+0x3C/+0x40 after the setWakeFrame tail via an xmm0-homed fzero
// local (/arch:SSE flips x87 fldz to retail xorps+movss, DemoTrap precedent).
// Member names follow the Bloodthirsty donor (m_object at +0x08); the frame
// arg is the 0x3FFFFFFF never-wake literal. /GX for the EH prologue plus
// the single mid-body state store; the declared-only base dtor arms it with
// no emitted code. Zero new pins (base ctor resolves via its row;
// setWakeFrame resolves via the existing IAEX Object-uint pin at 0x44DF71).

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

class StructureCollapseUpdate : public UpdateModule
{
public:
	StructureCollapseUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_secondary20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	float m_30;
	float m_34;
	float m_38;
	float m_3C;
	float m_40;
};

// ??0StructureCollapseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004A42E4
StructureCollapseUpdate::StructureCollapseUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float fzero = 0.0f;
	int *slot20 = (int *)&m_secondary20;
	*slot20 = (int)0x00C1C780;
	int zero = 0;
	m_vtable = (const void *)0x00C52648;
	m_secondary0C = (const void *)0x00C49188;
	m_secondary10 = (const void *)0x00C5263C;
	m_secondary20 = (const void *)0x00C52638;
	m_24 = zero;
	m_2C = zero;
	m_30 = fzero;
	m_28 = zero;
	m_34 = fzero;
	setWakeFrame(m_object, 0x3FFFFFFF);
	m_38 = fzero;
	m_3C = fzero;
	m_40 = fzero;
}
