// cl: /O1 /DNDEBUG /MD /arch:SSE /EHsc
//
// ??1RebuildHoleBehavior@@UAE@XZ, retail 0x0048353E, 118 bytes. Behavior-side
// destructor restoring the five MI vptrs (+0 0x849A74 +0x0C 0x849188 +0x10
// 0x849A68 +0x20 0x849A64 +0x24 0x849A50 DIR32) then the ZH worker cleanup
// (INVALID_ID-guarded TheGameLogic 0x9FE78C findObjectByID rowed 0x49DC5 plus
// destroyObject rowed 0x242C09 plus and-zero at +0x28) then the UpdateModule
// base dtor (pinned 0x24A797). Layout follows the rowed ctor TU 0x483271
// (UpdateModule base size 0x20 plus Die plus RebuildHole interfaces plus six
// words +0x28..+0x3C plus float +0x40 plus bool +0x44; factory 0x24C3FB news
// 0x48). Identity is the own vtable 0x849A74 plus slot 0 deleting dtor
// 0x483629 calling this body plus the RebuildHoleBehavior literal poolkey
// row. BFME1 donor RebuildHoleBehaviorDestructorThunk.cpp proves public
// virtual UAE; ZH RebuildHoleBehavior.cpp proves the find-plus-destroy shape.

class Thing;
class ModuleData;
class ThingTemplate;

enum ObjectID
{
	INVALID_ID = 0
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

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
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class DieModuleInterface
{
public:
	virtual void onDie();
};

class RebuildHoleBehaviorInterface
{
public:
	virtual void startRebuildProcess(const ThingTemplate *rebuild, ObjectID spawnerID);
	virtual ObjectID getSpawnerID();
	virtual ObjectID getReconstructedBuildingID();
	virtual const ThingTemplate *getRebuildTemplate() const;
};

class RebuildHoleBehavior : public UpdateModule,
	public DieModuleInterface,
	public RebuildHoleBehaviorInterface
{
public:
	virtual ~RebuildHoleBehavior();

private:
	ObjectID m_workerID;
	ObjectID m_reconstructingID;
	ObjectID m_spawnerObjectID;
	unsigned int m_workerWaitCounter;
	const ThingTemplate *m_workerTemplate;
	const ThingTemplate *m_rebuildTemplate;
	float m_40;
	bool m_44;
};

RebuildHoleBehavior::~RebuildHoleBehavior()
{
	if (m_workerID != INVALID_ID)
	{
		GameLogic *gameLogic = TheGameLogic;
		Object *worker = gameLogic->findObjectByID(m_workerID);
		if (worker)
		{
			gameLogic->destroyObject(worker);
			m_workerID = INVALID_ID;
		}
	}
}
