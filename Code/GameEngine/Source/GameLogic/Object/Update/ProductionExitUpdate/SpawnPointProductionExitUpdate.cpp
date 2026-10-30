// cl: /DNDEBUG /MD /GX
// FILE: SpawnPointProductionExitUpdate.cpp /////////////////////////////////////////////////////////
// Hand off produced units to this module so it can exit them into the world at named bones.
//
// Target facts: the module is 0xF4 bytes. UpdateModule's three vptrs sit at +0x00/+0x0C/+0x10
// and the exit interface's at +0x20 (vtable 0x0085256C: slot 1 reserveDoorForExit 0x004A3F3B,
// slot 2 exitObjectViaDoor 0x004A3E3E). The bone flag is at +0x24, the live point count at
// +0x28, ten Coord3D points at +0x2C, ten angles at +0xA4 and ten occupier ids at +0xCC. Both
// interface methods take the +0x20 sub-object as `this` and reach the module's private helpers
// through this-0x20.
// Donor (Zero Hour SpawnPointProductionExitUpdate.cpp) facts: the member and method names, and
// the shape of reserveDoorForExit.
////////////////////////////////////////////////////////////////////////////////////////////////////

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

//-------------------------------------------------------------------------------------------------
ExitDoorType SpawnPointProductionExitUpdate::reserveDoorForExit( const ThingTemplate* objType, Object *specificObject )
{
	if( !m_bonesInitialized )
		initializeBonePositions();

	if( !m_bonesInitialized )
		return DOOR_NONE_AVAILABLE; // Init failure

	revalidateOccupiers();

	for( int positionIndex = 0; positionIndex < m_spawnPointCount; positionIndex++ )
	{
		if( m_spawnPointOccupier[positionIndex] == INVALID_OBJECT_ID )
			return DOOR_1;
	}

	return DOOR_NONE_AVAILABLE;
}
