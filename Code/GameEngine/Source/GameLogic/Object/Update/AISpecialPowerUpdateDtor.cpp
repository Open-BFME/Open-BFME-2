// cl: /O1 /DNDEBUG /MD /GX
//
// ??1AISpecialPowerUpdate@@UAE@XZ, retail 0x004B2E79, 85 bytes.
// AISpecialPowerUpdate dtor: reinstalls the three MI vtable slots (+0
// 0x00856E1C plus +0x0C 0x00856D60 plus +0x10 0x00856D50) then deletes the
// +0x24 pointee product through slot 0 with arg 0 when non-null (state 0)
// then calls the rowed base ??1Rva0024A797 at 0x0024A797 (state -1). Layout
// from the rowed ctor 0x004B2F2A (UpdateModule base plus m_20 plus pointee
// +0x24 zeroed) and own vtable 0x00856E1C whose slot 0 ??_G at 0x004B2F5F
// calls here. Caller is that slot-0 ??_G. Donor is ZH SpecialPowerUpdateModule
// trivial dtor plus PartTheHeavensUpdateDtor precedent for the +0x24 pointee
// release with EH. Shape follows PoisonedBehaviorDtor (MI three-vptr stores)
// with /GX for the EH state machine.
class Thing;
class ModuleData;
class Object;
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
class AISpecialPowerUpdatePointee
{
public:
	virtual void *pointeeSlot0(int x);
};
class AISpecialPowerUpdate : public Rva0024A797
{
public:
	virtual ~AISpecialPowerUpdate();
private:
	int m_20;
	AISpecialPowerUpdatePointee *m_pointee;
};
void operator delete(void *p);
AISpecialPowerUpdate::~AISpecialPowerUpdate()
{
	void *tmp = 0;
	if (m_pointee)
		tmp = m_pointee->pointeeSlot0((int)tmp);
	delete tmp;
}
