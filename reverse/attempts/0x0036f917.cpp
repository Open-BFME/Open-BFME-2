// ?rva0036F917@Rva0036F917@@QAEXPBUCoord3D@@_NW4CommandSourceType@@@Z
// partial score=0.93 date=2026-10-07
// cl: /DNDEBUG /MD /GX /O1 /arch:SSE /G7
// ?rva0036F917@Rva0036F917@@QAEXPBUCoord3D@@_NW4CommandSourceType@@@Z, retail 0x0036F917, 231 bytes
// Evidence: leaf with 1 unclaimed caller at 0x00372571; between AICommandInterfaceAttackCommands and AIGroupWaypointMode;
// calls rowed new 0x0002FDA0 plus pinned SimpleObjectIterator ctor 0x0054B7B7 plus rowed insert 0x0054BBB5 plus pinned sort 0x0054C64A
// plus rowed aiTightenToPosition 0x0036EA74 and aiFollowPathAppend 0x0036EF89; __thiscall (reads ecx first); no proven class so honest address name.
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum IterOrderType
{
	ITER_ORDER_1 = 1
};

class Object;
class AICommandInterface;
class AIUpdateInterface;

class SimpleObjectIterator
{
public:
	SimpleObjectIterator();
	virtual ~SimpleObjectIterator();
	virtual Object *first();
	virtual Object *next();
	void insert(int a, float b);
	void sort(IterOrderType order);
private:
	unsigned char m_pad04[0x3C - 4];
};

extern void *__cdecl operator new(unsigned int size);

class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
	void aiTightenToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiFollowPathAppend(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad00[0x20];
	AICommandInterface m_commands;
};

class Object
{
public:
	unsigned char m_pad00[0x04];
	void *m_team; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Real m_x; // +0x38
	Real m_y; // +0x3C
	unsigned char m_pad40[0x108 - 0x40];
	unsigned char m_flags108; // +0x108 bit 2 tested via team?
	unsigned char m_pad109[0x1C8 - 0x109];
	unsigned char m_flags1C8; // +0x1C8 bit 3 tested
	unsigned char m_pad1C9[0x258 - 0x1C9];
	AIUpdateInterface *m_ai; // +0x258
};

struct Rva0036F917Node
{
	Rva0036F917Node *next;
	unsigned char m_pad04[0x08 - 0x04];
	Object *obj; // +0x08
};

class Rva0036F917
{
public:
	void rva0036F917(const Coord3D *pos, bool flag, CommandSourceType cmdSource);
private:
	unsigned char m_pad00[0x04];
	Rva0036F917Node *m_head; // +0x04
};

void Rva0036F917::rva0036F917(const Coord3D *pos, bool flag, CommandSourceType cmdSource)
{
	SimpleObjectIterator *iter = new SimpleObjectIterator;
	for (Rva0036F917Node *node = m_head->next; node != m_head; node = node->next)
	{
		Object *obj = node->obj;
		if ((obj->m_flags1C8 & 8) == 0)
		{
			Real ox = obj->m_x;
			Real oy = obj->m_y;
			Object *team = (Object *)obj->m_team;
			if ((team->m_flags108 & 4) == 0 && obj->m_ai != 0)
			{
				Real dx = ox - pos->x;
				Real dy = oy - pos->y;
				Real distSq = dx * dx + dy * dy;
				iter->insert((int)obj, distSq);
			}
		}
	}
	iter->sort(ITER_ORDER_1);
	for (Object *obj = iter->first(); obj != 0; obj = iter->next())
	{
		AIUpdateInterface *ai = obj->m_ai;
		if (!flag)
			ai->m_commands.aiTightenToPosition(pos, cmdSource);
		else
			ai->m_commands.aiFollowPathAppend(pos, cmdSource);
	}
}
