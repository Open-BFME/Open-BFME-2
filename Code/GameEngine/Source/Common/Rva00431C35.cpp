// cl: /MD
// FormationTranslator::WaitForSecondButtonDownStateHandler::Restart (WorldBuilder name, FormationTranslator.cpp lines 373..378: re-emits the stored pixel and ints and pushes a new 8B state).
// ?rva00431C35@Rva00431C35@@QAEXPAX@Z @0x00431C35 104B: thiscall method emitting GameMessage via MessageStream slot 0x4c then helper new 8B with vtable 0x0083C97C plus final Rva00575674 call. Evidence: unlock lane; MessageStreamSubsystem global 0x00A00950; rowed appendPixel 0x0030F9D8 appendInteger 0x0030F936 new 0x0002FDA0 rva00575674 0x00575674; vtables g_00C3C97C; callers 0x00431CB7 0x00431E4D 0x004320A4.
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

struct Rva00431C35Helper
{
	void *m_vptr;
	void *m_parent;
};

struct Rva00431C35Param
{
	int m_00;
	int m_04;
	int m_08;
};

class Object;
class Rva00575674
{
public:
	void rva00575674(Object *o);
};

class FormationTranslator
{
public:
	class WaitForSecondButtonDownStateHandler;
};
class FormationTranslator::WaitForSecondButtonDownStateHandler
{
	void *m_00;
	void *m_04;
	int m_08;
	ICoord2D m_0C;
	int m_14;
	int m_18;
public:
	void Restart(void *p);
};

void *__cdecl operator new(unsigned int size);

void FormationTranslator::WaitForSecondButtonDownStateHandler::Restart(void *p)
{
	Rva00431C35Param *par = (Rva00431C35Param *)p;
	int v = par->m_08;
	GameMessage *msg = MessageStreamSubsystem->v19(m_08, v);
	msg->appendPixelArgument(m_0C);
	msg->appendIntegerArgument(m_14);
	msg->appendIntegerArgument(m_18);
	void *mem = operator new(8);
	Rva00431C35Helper *h;
	if (mem != 0)
	{
		h = (Rva00431C35Helper *)mem;
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
