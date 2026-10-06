// cl: /DNDEBUG /MD /GX
//
// ?rva00483083@PoisonedBehavior@@QAEXXZ, retail 0x00483083, 38 bytes.
// Clears m_poisonDamageFrame at +0x24 and m_poisonOverallStopFrame at +0x28
// and m_poisonDamageAmount float at +0x2C, then reads the owner Object at
// +0x08 through rowed ?getDesiredGatherers@BuildListInfo@@QAEHXZ (7B mov
// eax,[ecx+0x84]) and when nonzero clears bit 4 via rowed
// ?Rva00270619Clear@Rva00270619@@QAEXH@Z. Layout is the rowed
// PoisonedBehavior class from PoisonedBehaviorCtor.cpp (UpdateModule base
// 0x20 plus DamageModuleInterface at +0x20). Callers at 0x0048311A and
// 0x004831B9; neighbours PoisonedBehavior deleting dtor and xfer.

class Thing;
class ModuleData;
class Object;
class DamageInfo;

class BuildListInfo
{
public:
	int getDesiredGatherers();
};

class Rva00270619
{
public:
	void Rva00270619Clear(int bit);
};

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

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class DamageModuleInterface
{
public:
	DamageModuleInterface() {}
	virtual void onDamage(DamageInfo *damageInfo);
};

class PoisonedBehavior : public UpdateModule, public DamageModuleInterface
{
public:
	void rva00483083();
private:
	unsigned int m_poisonDamageFrame;
	unsigned int m_poisonOverallStopFrame;
	float m_poisonDamageAmount;
	int m_deathType;
};

void PoisonedBehavior::rva00483083()
{
	m_poisonDamageFrame = 0;
	m_poisonOverallStopFrame = 0;
	m_poisonDamageAmount = 0.0f;
	int v = ((BuildListInfo *)m_object)->getDesiredGatherers();
	if (v)
		((Rva00270619 *)v)->Rva00270619Clear(4);
}
