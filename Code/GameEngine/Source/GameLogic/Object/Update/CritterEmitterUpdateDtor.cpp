// cl: /DNDEBUG /MD /GX
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

class Coord3D;

// The +0x20 interface's vftable 0x00C5E8C4 opens with onCollide (0x004C8E83).
class CritterEmitterUpdateIface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
};

class CritterEmitterUpdate : public UpdateModule, public CritterEmitterUpdateIface
{
public:
	virtual UpdateSleepTime update(); // UpdateModuleInterface slot 0, the rowed override
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
protected:
	virtual ~CritterEmitterUpdate();
};

CritterEmitterUpdate::~CritterEmitterUpdate()
{
}
