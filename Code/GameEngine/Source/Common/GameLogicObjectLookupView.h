#pragma once

// BFME 2's native lookup at 0x00049DC5 uses the ObjectID enum and a map
// receiver at +0xB4. The provider's existing accessed prefix is shared here;
// complete GameLogic and map extents remain unreconstructed. Pointer-only
// callers do not construct these views or depend on their sizeof.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;

struct ObjectIdNode
{
	char pad[8];
	Object *object;
};

class ObjectIdMap
{
public:
	ObjectIdNode *find(const ObjectID &id);
};

class GameLogic
{
	char pad[0xB4];
	ObjectIdMap m_map;

public:
	Object *findObjectByID(ObjectID id);
};
