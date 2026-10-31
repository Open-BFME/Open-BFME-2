// cl: /DNDEBUG /MD /EHsc

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

// The base is retail's UpdateModule: its constructor (0x00253390) and
// destructor are rowed elsewhere, so they are declared, never defined here.
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

// ??0CritterEmitterUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
CritterEmitterUpdate::CritterEmitterUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_24 = false;
    m_25 = true;
}
