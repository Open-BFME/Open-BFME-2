// cl: /O1 /G7 /MD
// ?enumerateRegisteredClaimants@TerrainResourceManager@@QAEXHPAVCb00359D42@@@Z @0x00359D42 87B: iterate circular list at +0x14 over BfmePod12-like entries (id+8 float+0xc byte+0x10); findObjectByID via TheGameLogic; mask test 1<<Player+0x54; virtual slot0 cb(id float byte); callers 0x004E7A85 0x004E7E3A; ret 8.
// ?TheGameLogic@@3PAVGameLogic@@A present-unmatched
enum ObjectID
{
	OBJECTID_NONE = 0
};

class Player
{
public:
	int m_00[21];
	int m_side;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Cb00359D42
{
public:
	virtual void cb(int id, float val, char b);
};

struct Entry00359D42
{
	Entry00359D42 *m_next;
	Entry00359D42 *m_prev;
	int m_id;
	float m_val;
	char m_b;
	char m_pad[3];
};

class TerrainResourceManager
{
public:
	void enumerateRegisteredClaimants(int mask, Cb00359D42 *cb);
private:
	int m_00[5];
	Entry00359D42 *m_list;
};

void TerrainResourceManager::enumerateRegisteredClaimants(int mask, Cb00359D42 *cb)
{
	Entry00359D42 *head = m_list;
	Entry00359D42 *cur = head->m_next;
	if (cur == head)
		return;
	do {
		Object *obj = TheGameLogic->findObjectByID((ObjectID)cur->m_id);
		if (obj != 0) {
			Player *pl = obj->getControllingPlayer();
			if (mask & (1 << pl->m_side))
				cb->cb(cur->m_id, cur->m_val, cur->m_b);
		}
		cur = cur->m_next;
	} while (cur != head);
}
