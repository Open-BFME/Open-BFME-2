// cl: /O1 /DNDEBUG /MD /GX
//
// ??1CritterEmitterUpdate@@MAE@XZ, retail 0x004C8D1B, 32 bytes. Destructor for
// CritterEmitterUpdate (ctor rowed in CritterEmitterUpdateConstructorThunk.cpp,
// vtable 0x0085E8E8 with slot 0 ??_G at 0x004C8DC6).
//
// The body restores the four vtable pointers of the complete object -- the
// derived slot at +0x00 plus the secondary slots at +0x0C/+0x10/+0x20 -- then
// tail-jumps to the UpdateModule base destructor (pinned ??1UpdateModule@@UAE@XZ
// at 0x0024A797). Recipe: BloodthirstyUpdateDtor.cpp. BFME1 donor
// CritterEmitterUpdateDestructor.cpp proves protected virtual MAE spelling.

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

class CritterEmitterUpdateIface
{
public:
	virtual void trailingAnchor();
};

class CritterEmitterUpdate : public UpdateModule, public CritterEmitterUpdateIface
{
protected:
	virtual ~CritterEmitterUpdate();
};

CritterEmitterUpdate::~CritterEmitterUpdate()
{
}
