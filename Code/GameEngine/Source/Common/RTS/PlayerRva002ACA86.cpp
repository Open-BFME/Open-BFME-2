// cl: /MD /GX-
// ?rva002ACA86@Player@@QAEXHPBVGameMessage@@@Z @0x002ACA86 117B: Player GameMessage ObjectID fill.
// Evidence: prev PlayerRva002AC673 next PlayerRva002ACD09 same flags; +0x708 10-slot array
// matches Rva002AA191 m_entries; callees Clear 0x004D6C29 getArgument 0x0030F4EA
// findObjectByID 0x00049DC5 Find 0x002AA1BF Add 0x004D6C7C TheGameLogic; caller 0x00377BD7.
class Object;
enum ObjectID
{
	OBJECTID_INVALID = 0
};

union GameMessageArgumentType
{
	ObjectID m_objectID;
	int m_int;
};

class GameMessage
{
public:
	const GameMessageArgumentType *getArgument(int index) const;
private:
	char m_pad[0x18];
	unsigned char m_argCount;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Rva004D6C29
{
public:
	void rva004D6C29();
};

class Rva004D6C7C
{
public:
	void rva004D6C7C(const Object *obj);
};

class Rva002AA191
{
public:
	void rva002AA1BF(void *arg);
};

class Player
{
public:
	void rva002ACA86(int index, const GameMessage *msg);
private:
	char m_pad[0x708];
	void *m_array[10];
};

void Player::rva002ACA86(int index, const GameMessage *msg)
{
	if (index < 0 || index >= 10)
		return;
	void **slot = &m_array[index];
	((Rva004D6C29 *)*slot)->rva004D6C29();
	unsigned char count = *(const unsigned char *)((const char *)msg + 0x18);
	if (count <= 0)
		return;
	int i = 0;
	unsigned int left = count;
	while (true) {
		const GameMessageArgumentType *arg = msg->getArgument(i);
		Object *obj = TheGameLogic->findObjectByID(arg->m_objectID);
		if (obj) {
			((Rva002AA191 *)this)->rva002AA1BF(obj);
			((Rva004D6C7C *)*slot)->rva004D6C7C(obj);
		}
		++i;
		--left;
		if (left == 0)
			break;
	}
}
