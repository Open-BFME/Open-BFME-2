// ?rva0048337A@RebuildHoleBehavior@@QAEXPAVObject@@@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE /EHsc
// ?rva0048337A@RebuildHoleBehavior@@QAEXPAVObject@@@Z 0x0048337A 114B evidence: gap between rowed ModuleData dtor 0x0048334A and rowed xfer 0x004833EC; RebuildHoleBehavior layout from rowed dtor 0x0048353E and ctor 0x00483271; rowed destroyObject 0x00242C09 via TheGameLogic plus rowed maskObject plus rowed Rva00391F4E ctor 0x00391F4E plus pinned Rva0028CDEB plus rowed setSelectable plus rowed pathfind add; callers 0x004835F1 0x00483681 0x004836A5; honest Rva name
class Thing;
class ThingTemplate;

enum ObjectID
{
	INVALID_ID = 0
};

class Object;
struct ObjectStatusMask;

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

class ModuleData
{
public:
	char m_pad[8];
	float m_08;
};

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

class Object
{
public:
	void maskObject(bool flag);
	void Rva0028CDEB(struct ObjectStatusMask *mask);
	void setSelectable(bool flag);
};

struct Rva00391F4E
{
	unsigned m_bits[4];
	Rva00391F4E(int unused, int b1, int b2);
};

class AI;
extern AI *g_Va009FF0F8;

class BFMEPathfinderMapShim
{
public:
	void addObjectToPathfindMap(Object *obj);
};

class AI
{
public:
	char m_pad[0x10];
	BFMEPathfinderMapShim *m_10;
};

class RebuildHoleBehavior : public UpdateModule,
	public DieModuleInterface,
	public RebuildHoleBehaviorInterface
{
public:
	void rva0048337A(Object *obj);

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

// ?rva0048337A@RebuildHoleBehavior@@QAEXPAVObject@@@Z present-unmatched
void RebuildHoleBehavior::rva0048337A(Object *obj)
{
	Object *myObj = m_object;
	const ModuleData *md = m_moduleData;
	if (obj != 0)
		TheGameLogic->destroyObject(obj);
	m_workerID = INVALID_ID;
	m_workerWaitCounter = (unsigned int)md->m_08;
	int zero = 0;
	myObj->maskObject(zero != 0);
	myObj->Rva0028CDEB((struct ObjectStatusMask *)&Rva00391F4E(zero, 3, 0x3c));
	myObj->setSelectable(true);
	g_Va009FF0F8->m_10->addObjectToPathfindMap(myObj);
}
