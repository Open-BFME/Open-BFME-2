// cl: /MD
// ?rva00431AEC@Rva00431AEC@@QAEHPAVGameMessage@@@Z @0x00431AEC 138B: bool method checking GameMessage+0x10 for 4 or 0xe then building Rva00431920 via ctor 0x00431920 plus final Rva00575674 call. Evidence: chain lane calls rowed 0x00431920; rowed getArgument 0x0030F4EA new 0x0002FDA0 rva00575674 0x00575674.
struct ICoord2D
{
	int m_x;
	int m_y;
};

union GameMessageArgumentType
{
	int integer;
	float real;
	int boolean;
	int objectID;
	struct Pix { int x; int y; } pixel;
};

class GameMessage
{
public:
	const GameMessageArgumentType *getArgument(int argIndex) const;
private:
	char m_pad[0x10];
	int m_10;
};

class Rva00431920
{
public:
	Rva00431920(void *a, int b, ICoord2D *c, int d, int e);
};

class Object;
class Rva00575674
{
public:
	void rva00575674(Object *o);
};

class Rva00431AEC
{
	void *m_00;
	void *m_04;
public:
	int rva00431AEC(GameMessage *msg);
};

void *__cdecl operator new(unsigned int size);
inline void *__cdecl operator new(unsigned int, void *p) { return p; }

int Rva00431AEC::rva00431AEC(GameMessage *msg)
{
	int t = *(int *)((char *)msg + 0x10);
	if (t != 4 && t != 0x0e)
		return 0;
	const GameMessageArgumentType *a0 = msg->getArgument(0);
	ICoord2D tmp;
	tmp.m_x = a0->pixel.x;
	tmp.m_y = a0->pixel.y;
	ICoord2D pos = tmp;
	const GameMessageArgumentType *a1 = msg->getArgument(1);
	int v1 = a1->integer;
	const GameMessageArgumentType *a2 = msg->getArgument(2);
	int v2 = a2->integer;
	void *mem = operator new(0x1c);
	Rva00431920 *h;
	if (mem != 0)
	{
		int type2 = *(int *)((char *)msg + 0x10);
		h = new (mem) Rva00431920(m_04, type2, &pos, v1, v2);
	}
	else
		h = 0;
	Rva00575674 *q = (Rva00575674 *)((char *)m_04 + 8);
	q->rva00575674((Object *)h);
	return 1;
}
