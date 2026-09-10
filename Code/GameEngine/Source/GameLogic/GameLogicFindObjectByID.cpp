// cl: /O1 /DNDEBUG /MD
//
// GameLogic::findObjectByID, retail 0x00049DC5, 37 bytes.
// Dedicated TU. Null ObjectID returns null; otherwise hashtable find at
// this+0xB4 and the Object* lives at the node +8.

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

Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}
