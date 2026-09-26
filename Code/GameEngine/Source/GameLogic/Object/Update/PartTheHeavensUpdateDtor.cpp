// cl: /O1 /DNDEBUG /MD /GX
//
// ??1PartTheHeavensUpdate@@UAE@XZ, retail 0x004AC8EF, 77 bytes.
// PartTheHeavensUpdate dtor: reinstalls the three MI vtable slots (+0
// 0x00C54DA4 plus +0x0C 0x007EFF90 plus +0x10 0x00C54D98) then releases the
// +0x24 pointee through slot 2 (+8) when non-null (state 0) then calls the
// rowed UpdateModule base 0x0024A797 (state -1). Layout from the rowed ctor
// 0x004AC998 (UpdateModule base plus m_20 plus pointee +0x24 zeroed) and own
// vtable 0x00854DA4. Caller is the slot-0 ??_G at 0x004AC9DE. Donor is BFME1
// PartTheHeavensUpdateDestructors.cpp:78 plus UpdateModule.h:241. Shape
// follows PoisonedBehaviorDtor (MI three-vptr stores) plus Flammable holder
// (conditional Release) with /GX for the EH state machine.
class Thing;
class ModuleData;
class Object;
class DamageInfo;
class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};
class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};
class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};
class UpdateModuleInterface
{
public:
	virtual void update();
};
class Rva0024A797 : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~Rva0024A797();
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};
class PartTheHeavensUpdatePointee
{
public:
	virtual void pointeeSlot0();
	virtual void pointeeSlot1();
	virtual void releasePointee();
};
class PartTheHeavensUpdate : public Rva0024A797
{
public:
	virtual ~PartTheHeavensUpdate();
private:
	int m_20;
	PartTheHeavensUpdatePointee *m_pointee;
};
PartTheHeavensUpdate::~PartTheHeavensUpdate()
{
	if (m_pointee)
		m_pointee->releasePointee();
}
