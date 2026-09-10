// cl: /O1 /DNDEBUG /MD
//
// SpawnPointProductionExitUpdate::revalidateOccupiers, retail 0x004A3F04,
// 55 bytes. Dedicated TU so SpawnPointProductionExitUpdate.cpp cannot inline
// this into reserveDoorForExit. Count at +0x28, occupier ids at +0xCC.

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class SpawnPointProductionExitUpdate
{
	char pad[0x28];
	int m_spawnPointCount;
	char pad_cc[0xCC - 0x2C];
	ObjectID m_spawnPointOccupier[1];

	void revalidateOccupiers();
};

void SpawnPointProductionExitUpdate::revalidateOccupiers()
{
	for (int i = 0; i < m_spawnPointCount; i++)
	{
		ObjectID id = m_spawnPointOccupier[i];
		if (id)
		{
			if (!TheGameLogic->findObjectByID(id))
				m_spawnPointOccupier[i] = INVALID_OBJECT_ID;
		}
	}
}
