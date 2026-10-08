// cl: /DNDEBUG /MD /EHsc
//
// ??0FiringTracker@@QAE@PAVThing@@PBVModuleData@@@Z @0x004DEB10 (149B).
// FiringTracker ctor over rowed UpdateModule base 0x00253390 with
// setWakeFrame FOREVER via rowed 0x0044DF71. Layout from matched xfer
// 0x004DEBC1 (UpdateModule base 0x20 plus consecutiveShots plus victimID
// plus victimPosition plus victimIsPosition plus auxID plus three frames
// plus lastShotPosition plus stopLooping plus audioHandle) and donor
// BFME1 FiringTrackerBFMECtor (Thing plus ModuleData plus zero plus
// FOREVER). Identity via vtable 0x00861530 at +0 plus pool key 0x004DEACB
// with FiringTracker string plus deleting dtor 0x004DEBA5. Neighbours
// FiringTrackerPoolKey 0x004DEACB and FiringTrackerDtor share flags.

typedef int ObjectID;
typedef int AudioHandle;

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

class Module
{
protected:
	virtual ~Module();

private:
	const void *m_moduleData;
};

class ObjectModule : public Module
{
public:
	ObjectModule(Thing *thing, const ModuleData *data);

protected:
	Object *m_object;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *data);
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data);
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_pad;
};

class Coord3D
{
public:
	float x;
	float y;
	float z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

class FiringTracker : public UpdateModule
{
public:
	FiringTracker(Thing *thing, const ModuleData *data);

private:
	int m_consecutiveShots;
	ObjectID m_victimID;
	Coord3D m_victimPosition;
	bool m_victimIsPosition;
	unsigned char m_pad35[3];
	ObjectID m_auxiliaryObjectID;
	unsigned int m_frameToStartCooldown;
	unsigned int m_frameToForceReload;
	unsigned int m_lastShotFrame;
	Coord3D m_lastShotPosition;
	unsigned int m_frameToStopLoopingSound;
	AudioHandle m_audioHandle;
};

FiringTracker::FiringTracker(Thing *thing, const ModuleData *data) :
	UpdateModule(thing, data)
{
	m_consecutiveShots = 0;
	m_victimID = 0;
	m_victimPosition.zero();
	m_lastShotPosition.zero();
	m_victimIsPosition = false;
	m_auxiliaryObjectID = 0;
	m_frameToStartCooldown = 0;
	m_frameToForceReload = 0;
	m_lastShotFrame = 0;
	m_frameToStopLoopingSound = 0;
	m_audioHandle = 1;
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
