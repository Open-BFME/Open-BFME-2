// cl: /MD
// ?rva00431B76@Rva00431B76@@QAEXXZ @0x00431B76 103B: thiscall guarded emit via MessageStream slot 0x48 then helper new 8B with vtable 0x0083C97C plus final Rva00575674 call. Evidence: chain lane calls rowed 0x00431955; MessageStreamSubsystem global 0x00A00950; rowed appendPixel 0x0030F9D8 appendInteger 0x0030F936 new 0x0002FDA0 rva00575674 0x00575674; vtables g_00C3C97C.
struct ICoord2D
{
	int m_x;
	int m_y;
};

class GameMessage
{
public:
	void appendPixelArgument(const ICoord2D &v);
	void appendIntegerArgument(int v);
};

class MessageStream
{
public:
	virtual void _d00(); virtual void _d01(); virtual void _d02(); virtual void _d03();
	virtual void _d04(); virtual void _d05(); virtual void _d06(); virtual void _d07();
	virtual void _d08(); virtual void _d09(); virtual void _d10(); virtual void _d11();
	virtual void _d12(); virtual void _d13(); virtual void _d14(); virtual void _d15();
	virtual void _d16(); virtual void _d17();
	virtual GameMessage *createMessage(int type);
	virtual GameMessage *v19(int a, int b);
};

extern MessageStream *MessageStreamSubsystem;
extern const void *const g_00C3C97C[];

struct Rva00431B76Helper
{
	void *m_vptr;
	void *m_parent;
};

class Object;
class Rva00575674
{
public:
	void rva00575674(Object *o);
};

class Rva00431955
{
public:
	bool rva00431955();
};

class Rva00431B76
{
	void *m_00;
	void *m_04;
	int m_08;
	ICoord2D m_0C;
	int m_14;
	int m_18;
public:
	void rva00431B76();
};

void *__cdecl operator new(unsigned int size);

void Rva00431B76::rva00431B76()
{
	if (((Rva00431955 *)this)->rva00431955())
		return;
	GameMessage *msg = MessageStreamSubsystem->createMessage(m_08);
	msg->appendPixelArgument(m_0C);
	msg->appendIntegerArgument(m_14);
	msg->appendIntegerArgument(m_18);
	void *mem = operator new(8);
	Rva00431B76Helper *h;
	if (mem != 0)
	{
		h = (Rva00431B76Helper *)mem;
		h->m_parent = m_04;
		h->m_vptr = (void *)g_00C3C97C;
	}
	else
	{
		h = 0;
	}
	Rva00575674 *q = (Rva00575674 *)((char *)m_04 + 8);
	q->rva00575674((Object *)h);
}
