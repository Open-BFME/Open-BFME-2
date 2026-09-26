// cl: /O1 /DNDEBUG /MD /GX
//
// ??1BloodthirstyUpdate@@MAE@XZ, retail 0x0044DFE0, 32 bytes. Destructor for
// BloodthirstyUpdate (ctor rowed at 0x0044E0AA in BloodthirstyUpdateCtor.cpp,
// vtable 0x0083F0B4 with slot 0 ??_G at 0x0044E113).
//
// The body restores the four vtable pointers of the complete object -- the
// derived slot at +0x00 plus the secondary slots at +0x0C/+0x10/+0x20 -- then
// tail-jumps to the UpdateModule base destructor (pinned ??1UpdateModule@@UAE@XZ
// at 0x0024A797). Recipe: InvisibilityUpdateDtor.cpp / PoisonedBehaviorDtor.cpp.

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

class BloodthirstyUpdateIface
{
public:
	virtual void trailingAnchor();
};

class BloodthirstyUpdate : public UpdateModule, public BloodthirstyUpdateIface
{
protected:
	virtual ~BloodthirstyUpdate();
};

BloodthirstyUpdate::~BloodthirstyUpdate()
{
}
