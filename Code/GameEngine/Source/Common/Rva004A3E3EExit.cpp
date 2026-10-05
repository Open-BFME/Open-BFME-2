// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
//
// ?rva004A3E3E@Rva004A3E3E@@QAEXPAVObject@@H@Z @0x004A3E3E 198B ret 8.
// Spawn-point exitObjectViaDoor. this is the subobject at +0x20, so the
// bone init is the parent and the creation object is the dword at parent+8.
// The free occupier slot supplies the coord, the angle, and the id store.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};

enum DisabledType
{
	DISABLED_HELD = 3
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
	void setOrientation(float angle);
};

class Object
{
public:
	int rva0028B511() const;
	void rva0028B4CE(PathfindLayerEnum layer);
	void setDisabled(DisabledType type);
	char m_pad[0x74];
	int m_id;
};

class BFMEPathfinderMapShim
{
public:
	void addObjectToPathfindMap(Object *object);
};

class AI
{
public:
	char m_pad[0x10];
	BFMEPathfinderMapShim *m_pathfinder;
};

extern AI *TheAI;

class Rva004A3E3E;

class SpawnPointProductionExitUpdate
{
	friend class Rva004A3E3E;

private:
	void initializeBonePositions();
};

class Rva004A3E3E
{
public:
	void rva004A3E3E(Object *newObj, int exitDoor);
	char m_pad[4];
	bool m_bonesInitialized;
	char m_pad2[3];
	int m_spawnPointCount;
	Coord3D m_worldCoordSpawnPoints[10];
	float m_worldAngleSpawnPoints[10];
	int m_spawnPointOccupier[10];
};

void Rva004A3E3E::rva004A3E3E(Object *newObj, int)
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
	newObj->rva0028B4CE((PathfindLayerEnum)creationObject->rva0028B511());
	TheAI->m_pathfinder->addObjectToPathfindMap(newObj);
	newObj->setDisabled(DISABLED_HELD);
}
