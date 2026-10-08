// cl: /DNDEBUG /MD
//
// GarrisonObjectGroupOrder slots 8 and 11 (vtable 0x00C6A3C4), the garrison
// twins of AttackObjectGroupOrder's slots 8 and 11 (AttackObjectGroupOrderSlots.cpp):
// the order keeps the target's ObjectID at +0x18 and a Coord3D at +0x1C.
// Slot 8 (retail 0x00546D7C, 41 bytes) refreshes that position from the
// target found through TheGameLogic (rowed findObjectByID 0x00049DC5) and
// returns it. Slot 11 (retail 0x00546DA5, 47 bytes) reports the order:
// 0x42C into the first out argument and, when the target exists, its
// Drawable (getDrawable 0x005508E2) into the second's +4; returns true.
// Slot 5 (retail 0x00546E2E, 160 bytes) drives the Object named by its
// argument into the target: done (true) when there is no target, when the
// target is gone or has bit 0 of +0x438 set (the target ID is then cleared),
// when the Object or its AI is missing, when it already sits in the target,
// or when TheActionManager (canEnterObject 0x0041C2D0) refuses; otherwise,
// while the AI's slot 110 answers true, the enter command (rowed
// AICommandInterface::rva0036EBB8 0x0036EBB8) goes out and it is not done.
// Names by address.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum CanEnterType
{
	CHECK_CAPACITY = 0
};

class Drawable;
class Object;

class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
	void rva0036EBB8(Object *obj, CommandSourceType cmdSource);
};

template <int N> class Rva00546E2ESlots : public Rva00546E2ESlots<N - 1>
{
public:
	virtual void gap(char (*)[N + 1]) = 0;
};
template <> class Rva00546E2ESlots<0>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class AIUpdateInterface : public Rva00546E2ESlots<109>
{
public:
	virtual bool rva00546E2ESlot110() = 0;
	char m_pad04[0x20 - 4];
	AICommandInterface m_commands; // +0x20
};

class Object
{
public:
	Drawable *getDrawable() const;
	ObjectID getID() const { return m_id; }
	char m_pad0[0x38];
	Coord3D m_position; // +0x38
	char m_pad44[0x74 - 0x44];
	ObjectID m_id; // +0x74
	char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
	char m_pad278[0x438 - 0x278];
	unsigned char m_flags438; // +0x438 bit0
};

class BFMEActionManager
{
public:
	bool canEnterObject(const Object *obj, const Object *objectToEnter, CommandSourceType commandSource,
		CanEnterType mode, bool passThrough, bool *outFlag);
};

extern BFMEActionManager *TheActionManager;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class GarrisonObjectGroupOrder
{
public:
	virtual ~GarrisonObjectGroupOrder();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual bool rva00546E2E(ObjectID id);
	virtual void slot06();
	virtual void slot07();
	virtual Coord3D *rva00546D7C(int dummy);
	virtual void slot09();
	virtual void slot10();
	virtual bool rva00546DA5(int *outID, void *out);
private:
	char m_pad04[0x18 - 4];
	ObjectID m_targetID; // +0x18
	Coord3D m_pos; // +0x1C
};

Coord3D *GarrisonObjectGroupOrder::rva00546D7C(int dummy)
{
	Object *found = TheGameLogic->findObjectByID(m_targetID);
	if (found != 0) {
		Coord3D *dst = &m_pos;
		const Coord3D *src = &found->m_position;
		*dst = *src;
	}
	return &m_pos;
}

bool GarrisonObjectGroupOrder::rva00546DA5(int *outID, void *out)
{
	*outID = 0x42C;
	Object *found = TheGameLogic->findObjectByID(m_targetID);
	if (found)
		*(Drawable **)((char *)out + 4) = found->getDrawable();
	return true;
}

bool GarrisonObjectGroupOrder::rva00546E2E(ObjectID id)
{
	if (m_targetID == INVALID_OBJECT_ID)
		return true;
	GameLogic *logic = TheGameLogic;
	Object *target = logic->findObjectByID(m_targetID);
	if (target == 0 || (target->m_flags438 & 1))
	{
		m_targetID = INVALID_OBJECT_ID;
		return true;
	}
	Object *obj = logic->findObjectByID(id);
	if (obj == 0)
		return true;
	AIUpdateInterface *ai = obj->m_ai;
	if (ai == 0)
		return true;
	if (ai->rva00546E2ESlot110())
	{
		Object *container = obj->m_containedBy;
		if (container && container->getID() == m_targetID)
			return true;
		if (!TheActionManager->canEnterObject(obj, target, CMD_FROM_PLAYER, CHECK_CAPACITY, 1, 0))
			return true;
		ai->m_commands.rva0036EBB8(target, CMD_FROM_PLAYER);
	}
	return false;
}
