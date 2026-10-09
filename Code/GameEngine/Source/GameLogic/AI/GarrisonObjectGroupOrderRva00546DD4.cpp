// cl: /MD
// ?rva00546DD4@GarrisonObjectGroupOrder@@UAEXW4ObjectID@@@Z @0x00546DD4 90B evidence: slot 4 of 0x0086A3C4; calls findObjectByID rowed 0x00049DC5 three times plus AI rva0036EBB8 rowed 0x0036EBB8; uses TheGameLogic; clears +0x18 on null.
// Honest-address slot method via vtable (naming rule).
enum ObjectID
{
	OBJECTID_INVALID = 0
};

enum CommandSourceType
{
	CMDSOURCE_0 = 0
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class AICommandInterface
{
public:
	void rva0036EBB8(Object *target, enum CommandSourceType src);
};

struct AIHolder
{
	unsigned char m_pad[0x20];
	AICommandInterface m_ai;
};

class Object
{
public:
	unsigned char m_pad[0x258];
	AIHolder *m_258;
};

class GroupOrder
{
public:
	GroupOrder();
	virtual ~GroupOrder();
private:
	unsigned char m_pad04[0x18 - 4];
};

class GarrisonObjectGroupOrder : public GroupOrder
{
public:
	// Slot 4 of 0x00C6A3C4, the class's vftable: virtual (SynchronizeGroupOrder's
	// slot 4 0x00546A78 is rowed virtual too).
	virtual void rva00546DD4(enum ObjectID id);
private:
	enum ObjectID m_18;
	int m_1c;
};

void GarrisonObjectGroupOrder::rva00546DD4(enum ObjectID id)
{
	GameLogic *logic = TheGameLogic;
	Object *first = logic->findObjectByID(id);
	enum ObjectID mine = m_18;
	Object *second = logic->findObjectByID(mine);
	if (second == 0 || first == 0)
		return;
	AIHolder *holder = first->m_258;
	if (holder == 0)
		return;
	Object *third = logic->findObjectByID(mine);
	if (third != 0)
		holder->m_ai.rva0036EBB8(third, CMDSOURCE_0);
	else
		m_18 = OBJECTID_INVALID;
}
