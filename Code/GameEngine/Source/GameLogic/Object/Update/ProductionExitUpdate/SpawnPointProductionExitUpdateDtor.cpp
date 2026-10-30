// cl: /DNDEBUG /MD /GX
//
// ??1SpawnPointProductionExitUpdate@@MAE@XZ, retail 0x004A3B35, 90 bytes.
// Destructor for SpawnPointProductionExitUpdate (ctor rowed at 0x004A3C1B in
// SpawnPointProductionExitUpdateCtor.cpp, vtable 0x0085259C with slot 0 ??_G
// at 0x004A3CCE which calls this body).
//
// Shape follows the ctor TU's MI layout (UpdateModule 0x20 over three bases
// plus trailing SpawnB4 vptr at +0x20): the body reinstalls the four vptrs
// at +0/+0x0C/+0x10/+0x20, destroys the Coord3D array m_spawnPoints[10] at
// +0x2C through the rowed ehvec dtor iterator 0x00629110 (count 0xA, stride
// 0xC, element dtor rowed ??1Coord3D@@QAE@XZ at 0x000B3FD0), then calls the
// pinned UpdateModule base dtor ??1UpdateModule@@UAE@XZ at 0x0024A797.
// /GX for the EH prologue plus the two state stores (and-early, or-late).
// BFME1 donor SpawnPointProductionExitUpdateDestructor.cpp proves the array
// at +0x2C and the 4-vptr teardown; BFME2 revalidate occupier TU pins count
// at +0x28 and occupiers at +0xCC.

#define COORD3D_VIEW_DTOR
#include "../../../../../../Libraries/Include/Lib/Coord3DCtorView.h"
#include "../../../../Common/Thing/thing.h"
#include "../../../../Common/GameLogicObjectLookupView.h"

class Thing;
class ModuleData;
class Object;
class ThingTemplate;

enum { MAX_SPAWN_POINTS = 10 };

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheGameLogic;

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};

enum DisabledType
{
	DISABLED_HELD = 3
};

class Object
{
public:
	int rva0028B511() const;
	void setLayer(PathfindLayerEnum layer);
	void setDisabled(DisabledType type);
	char m_pad[0x74];
	ObjectID m_id;
};

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *object);
};

class AI
{
public:
	char m_pad[0x10];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

enum ExitDoorType
{
	DOOR_NONE_AVAILABLE = -1,
	DOOR_1 = 0
};

class SpawnB1
{
public:
	virtual void spawnAnchor1() {}
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class SpawnB2
{
public:
	virtual void spawnAnchor2() {}
};

class SpawnB3
{
public:
	virtual void spawnAnchor3() {}
protected:
	char m_pad[0x0C];
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModule : public SpawnB1, public SpawnB2, public SpawnB3
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);
};

// +0x20: the exit interface (ExitInterface; slot 0 is not recovered here, and the
// placeholder name keeps its vtable apart from the other units' ExitInterface views).
class SpawnB4
{
public:
	virtual void spawnAnchor4() {}
	virtual ExitDoorType reserveDoorForExit(const ThingTemplate *objType, Object *specificObject) = 0;
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor) = 0;
};

class SpawnPointProductionExitUpdate : public UpdateModule, public SpawnB4
{
public:
	SpawnPointProductionExitUpdate(Thing *thing, const ModuleData *moduleData);

	virtual NameKeyType getModuleNameKey() const;

	virtual ExitDoorType reserveDoorForExit(const ThingTemplate *objType, Object *specificObject);
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor);

protected:
	virtual ~SpawnPointProductionExitUpdate();

private:
	void initializeBonePositions();
	void revalidateOccupiers();

	bool m_bonesInitialized;								// +0x24
	int m_spawnPointCount;									// +0x28
	Coord3D m_worldCoordSpawnPoints[MAX_SPAWN_POINTS];		// +0x2C
	float m_worldAngleSpawnPoints[MAX_SPAWN_POINTS];		// +0xA4
	ObjectID m_spawnPointOccupier[MAX_SPAWN_POINTS];		// +0xCC
};


SpawnPointProductionExitUpdate::~SpawnPointProductionExitUpdate()
{
}
