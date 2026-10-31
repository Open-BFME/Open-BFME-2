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

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class Thing;
class ModuleData;
class Object;
class Coord3D;
class Xfer;

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

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

// The +0x20 interface's vftable 0x00C5E8C4 opens with onCollide (0x004C8E83).
class CritterEmitterUpdateIface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
};

class CritterEmitterUpdate : public UpdateModule, public CritterEmitterUpdateIface
{
public:
	CritterEmitterUpdate(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
protected:
	virtual ~CritterEmitterUpdate();
	virtual void xfer(Xfer *xfer);
private:
	bool m_24;
	bool m_25;
};

CritterEmitterUpdate::~CritterEmitterUpdate()
{
}
