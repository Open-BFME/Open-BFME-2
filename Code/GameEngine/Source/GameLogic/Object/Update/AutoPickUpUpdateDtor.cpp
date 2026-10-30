// cl: /MD
// ??1AutoPickUpUpdate@@UAE@XZ retail 0x00495C48 32 bytes.
// AutoPickUpUpdate destructor: restores the four vtable pointers of the
// complete object -- the derived slot at +0x00 plus the BehaviorModuleOther
// slot at +0x0C, the UpdateModuleInterface slot at +0x10 and the trailing
// AutoPickUpUpdateInterface slot at +0x20 -- then tail-jumps to the
// UpdateModule base destructor at rowed 0x0024A797. The trailing interface
// base has a trivial destructor, so it contributes a store but no call.
// Evidence: slot restores match the rowed ctor 0x00495D31 installs;
// sole caller at 0x00495DAD in ??_GAutoPickUpUpdate; BFME1 donor
// AutoPickUpUpdateDestructor.cpp trivial dtor.
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

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
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

class AutoPickUpUpdateInterface
{
public:
	virtual void autoPickUpAnchor();
};

class AutoPickUpUpdate : public UpdateModule, public AutoPickUpUpdateInterface
{
public:
	virtual UpdateSleepTime update(); // UpdateModuleInterface slot 0, the rowed override
	virtual ~AutoPickUpUpdate();
private:
	unsigned int m_24;
	unsigned char m_28;
	unsigned char m_29;
};

// ??1AutoPickUpUpdate@@UAE@XZ @0x00495C48
AutoPickUpUpdate::~AutoPickUpUpdate()
{
}
