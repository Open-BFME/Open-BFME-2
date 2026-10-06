// cl: /MD
//
// AIReturnTheRingTactic::findRingBearer retail 0x005AB45B 94B (WorldBuilder name;
// same stats lookup, findObjectByID and testStatus walk, asserts in
// AIReturnTheRingTactic.cpp).
// Searches ID range from Rva002A8F24 map entry via LeaField for first live
// Object with status 0x5E and stores its ID at +0x5C. Evidence: rowed calls
// rva002A8F24 get findObjectByID testStatus; globals g_00DFEEF8 TheGameLogic;
// caller 0x005AB6A5; offsets +0x24 +0x5C +0x438 from retail.
class Player;
class Object;
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
enum ObjectStatusTypes
{
	STATUS_5E = 0x5e
};
class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
};
class Rva005C4AD1LeaField
{
public:
	void *get() const;
};
class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
extern Rva002A8F24 *g_00DFEEF8;
class AIReturnTheRingTactic
{
public:
	bool findRingBearer();
private:
	char m_pad0[0x24];
	Player *m_player;
	char m_pad1[0x34];
	ObjectID m_found;
};
bool AIReturnTheRingTactic::findRingBearer()
{
	void *tmp = g_00DFEEF8->rva002A8F24(m_player);
	Rva005C4AD1LeaField *fld = *(Rva005C4AD1LeaField **)tmp;
	void *range = fld->get();
	ObjectID *begin = *(ObjectID **)range;
	ObjectID *end = *(ObjectID **)((char *)range + 4);
	for (ObjectID *p = begin; p != end; ++p)
	{
		Object *obj = TheGameLogic->findObjectByID(*p);
		if (!obj)
			continue;
		if (*(unsigned char *)((char *)obj + 0x438) & 1)
			continue;
		if (!obj->testStatus((ObjectStatusTypes)0x5e))
			continue;
		m_found = *p;
		return true;
	}
	return false;
}
