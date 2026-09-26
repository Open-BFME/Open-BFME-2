// cl: /O1 /MD
//
// ??1QueueProductionExitUpdate@@MAE@XZ, retail 0x0049FFF7, 32 bytes.
// Destructor completing the QueueProductionExitUpdate file-unit (ctor rowed
// at 0x4A010E, update/isFreeToExit/reserveDoor/getRallyPoint placed).
//
// Donor: ZH QueueProductionExitUpdate.cpp trivial dtor plus BFME1
// QueueProductionExitUpdateDestructorThunk shape. The body restores the four
// vtable pointers of the complete object -- the derived slot at +0x00 plus
// the BehaviorModuleOther slot at +0x0C, the UpdateModuleInterface slot at
// +0x10 and the ExitInterface slot at +0x20 -- then tail-jumps to the
// UpdateModule base destructor (pinned ??1UpdateModule@@UAE@XZ at
// 0x0024A797). The ExitInterface base has a trivial destructor, so it
// contributes a store but no call. Recipe: InvisibilityUpdateDtor.cpp.

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

class ExitInterface
{
public:
	virtual void exitAnchor();
};

class QueueProductionExitUpdate : public UpdateModule, public ExitInterface
{
protected:
	virtual ~QueueProductionExitUpdate();
};

QueueProductionExitUpdate::~QueueProductionExitUpdate()
{
}
