// cl: /MD
//
// ??1PoisonedBehavior@@MAE@XZ, retail 0x00482ED9, 32 bytes. Behavior-side
// destructor completing the PoisonedBehavior file-unit (ctor rowed at
// 0x482F7D, calcSleepTime at 0x482EFF, name getter at 0x482EF9).
//
// Donor: BFME1 PoisonedBehavior.cpp trivial dtor. The body restores the four
// vtable pointers of the complete object -- the derived slot at +0x00 plus
// the BehaviorModuleOther slot at +0x0C, the UpdateModuleInterface slot at
// +0x10 and the DamageModuleInterface slot at +0x20 -- then tail-jumps to
// the UpdateModule base destructor (pinned ??1UpdateModule@@UAE@XZ at
// 0x0024A797). The DamageModuleInterface base has a trivial destructor, so
// it contributes a store but no call. The UpdateModule middle is declared
// but never defined here so the call resolves via the pin, and the vtable
// values are DIR32 auto-patches.

// The shared headers declare these members with the access/virtual spelling
// retail's vftables reference; the ledger row keeps the spelling this TU
// compiled to. Same function, same address: bind the header spelling here.
#pragma comment(linker, "/alternatename:??1PoisonedBehavior@@UAE@XZ=??1PoisonedBehavior@@MAE@XZ")
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

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
};

class PoisonedBehavior : public UpdateModule, public DamageModuleInterface
{
protected:
	virtual ~PoisonedBehavior();
private:
	unsigned int m_poisonDamageFrame;
	unsigned int m_poisonOverallStopFrame;
	float m_poisonDamageAmount;
	int m_deathType;
};

// ??1PoisonedBehavior@@MAE@XZ @0x00482ED9
PoisonedBehavior::~PoisonedBehavior()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorModuleOtherAnchor@BehaviorModuleOther@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
