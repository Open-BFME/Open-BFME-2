// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
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
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};

enum DisabledType
{
	DISABLED_HELD = 3
};

enum ExitDoorType
{
	DOOR_1 = 0
};

#include "../../../../Common/Thing/thing.h"

class Object
{
public:
	int rva0028B511() const;
	void setLayer(PathfindLayerEnum layer);
	void setDisabled(DisabledType type);
	char m_pad[0x74];
	int m_id;
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

class SpawnPointProductionExitUpdate
{
public:
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor);

private:
	void initializeBonePositions();
	bool m_bonesInitialized;								// +0x04 (vtable at +0x00)
	char m_pad2[3];
	int m_spawnPointCount;
	Coord3D m_worldCoordSpawnPoints[10];
	float m_worldAngleSpawnPoints[10];
	int m_spawnPointOccupier[10];
};

void SpawnPointProductionExitUpdate::exitObjectViaDoor(Object *newObj, ExitDoorType)
{
	if (m_bonesInitialized == 0)
		((SpawnPointProductionExitUpdate *)((char *)this - 0x20))->initializeBonePositions();

	Object *creationObject = *(Object **)((char *)this - 0x18);
	if (creationObject == 0)
		return;

	int positionIndex;
	for (positionIndex = 0; positionIndex < m_spawnPointCount; ++positionIndex)
	{
		if (m_spawnPointOccupier[positionIndex] == 0)
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
