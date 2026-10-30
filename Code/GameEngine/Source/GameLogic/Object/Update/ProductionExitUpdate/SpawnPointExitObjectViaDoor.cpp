// cl: /DNDEBUG /MD /GX
//
// ?exitObjectViaDoor@SpawnPointProductionExitUpdate@@UAEXPAVObject@@W4ExitDoorType@@@Z
// @0x004A3E3E 198B ret 8. Identity: WorldBuilder names
// SpawnPointProductionExitUpdate::exitObjectViaDoor in EA's own
// SpawnPointProductionExitUpdate.cpp. Body provenance: the byte-exact
// placeholder Rva004A3E3E::rva004A3E3E (Rva004A3E3EExit.cpp, retracted).
// Retail's receiver is the ExitUpdateInterface sub-object at module+0x20:
// the bone-init parent is this-0x20 and the creation object the dword at
// this-0x18. The ZH-ported home unit defines this method on the merged
// module layout and therefore cannot host the byte-exact body.

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


void SpawnPointProductionExitUpdate::exitObjectViaDoor(Object *newObj, ExitDoorType)
{
	if (!m_bonesInitialized)
		initializeBonePositions();

	Object *creationObject = m_object;
	if (creationObject == 0)
		return;

	int positionIndex;
	for (positionIndex = 0; positionIndex < m_spawnPointCount; ++positionIndex)
	{
		if (m_spawnPointOccupier[positionIndex] == INVALID_OBJECT_ID)
			break;
	}
	if (positionIndex == m_spawnPointCount)
		return;

	float createAngle = m_worldAngleSpawnPoints[positionIndex];
	const Coord3D *slot = &m_worldCoordSpawnPoints[positionIndex];
	Coord3D createPoint;
	createPoint.x = slot->x;
	createPoint.y = slot->y;
	createPoint.z = slot->z;
	m_spawnPointOccupier[positionIndex] = newObj->m_id;
	((Thing *)newObj)->setPosition(&createPoint);
	((Thing *)newObj)->setOrientation(createAngle);
	newObj->setLayer((PathfindLayerEnum)creationObject->rva0028B511());
	TheAI->m_pathfinder->AddObjectToPathfindMap(newObj);
	newObj->setDisabled(DISABLED_HELD);
}
