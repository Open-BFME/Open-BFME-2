// cl: /O1 /MD
//
// ??1InvisibilityUpdate@@MAE@XZ, retail 0x004A389F, 32 bytes. Behavior-side
// destructor completing the InvisibilityUpdate file-unit (ctor rowed at
// 0x4A382D, friend-new at 0x24ECB4 news 0x28, pool key at 0x4A393C).
//
// The body restores the four vtable pointers of the complete object -- the
// derived slot at +0x00 plus the BehaviorModuleOther slot at +0x0C, the
// UpdateModuleInterface slot at +0x10 and the trailing interface slot at
// +0x20 -- then tail-jumps to the UpdateModule base destructor (pinned
// ??1UpdateModule@@UAE@XZ at 0x0024A797). The trailing base has a trivial
// destructor, so it contributes a store but no call. The UpdateModule middle
// is declared but never defined here so the call resolves via the pin, and
// the vtable values are DIR32 auto-patches. Recipe: PoisonedBehaviorDtor.cpp.

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

class TrailingModuleInterface
{
public:
	virtual void trailingAnchor();
};

class InvisibilityUpdate : public UpdateModule, public TrailingModuleInterface
{
protected:
	virtual ~InvisibilityUpdate();
};

InvisibilityUpdate::~InvisibilityUpdate()
{
}
