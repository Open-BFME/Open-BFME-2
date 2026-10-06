// cl: /MD
//
// ??1ReplenishUnitsBehavior@@UAE@XZ, retail 0x00484161, 32 bytes. Behavior-side
// destructor (caller is the slot-0 scalar-deleting dtor at 0x4842C4 in
// BehaviorModuleDeletingDtors.cpp; name getter at 0x484181 in ModuleNameGetters2.cpp).
//
// Donor: BFME1 ReplenishUnitsBehaviorCtorThunk.cpp trivial dtor
// (ReplenishUnitsBehavior : public UpdateModule, public SpawnBehaviorFourthBase
// with virtual ~ReplenishUnitsBehavior() {}). The body restores the four
// vtable pointers -- derived at +0x00, BehaviorModuleOther at +0x0C,
// UpdateModuleInterface at +0x10 and SpawnBehaviorFourthBase at +0x20 --
// then tail-jumps to the UpdateModule base destructor (pinned
// ??1UpdateModule@@UAE@XZ at 0x0024A797, rowed as ??1Rva0024A797@@UAE@XZ).
// SpawnBehaviorFourthBase has a trivial destructor so it contributes a store
// but no call. UpdateModule is declared but never defined here so the call
// resolves via the pin, and vtable values are DIR32 auto-patches.

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

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class SpawnBehaviorFourthBase
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void setReplenishing(bool enabled);
};

class ReplenishUnitsBehavior : public UpdateModule, public SpawnBehaviorFourthBase
{
public:
	virtual ~ReplenishUnitsBehavior();
};

ReplenishUnitsBehavior::~ReplenishUnitsBehavior()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorModuleOtherAnchor@BehaviorModuleOther@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot00@SpawnBehaviorFourthBase@@UAEXXZ=?Is_Valid@RegistryClass@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?slot08@SpawnBehaviorFourthBase@@UAEXXZ=?rva004CE2B0@Rva004CE2B0@@QAE_NPAVRva00406F9C@@@Z")
#pragma comment(linker, "/alternatename:?setReplenishing@SpawnBehaviorFourthBase@@UAEX_N@Z=?rva004CE342@Rva004CE342@@QAE_NPAVRva00406F9C@@@Z")
