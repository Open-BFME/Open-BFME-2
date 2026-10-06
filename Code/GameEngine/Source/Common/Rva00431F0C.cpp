// cl: /MD
// ?rva00431F0C@Rva00431F0C@@QAEHPAVGameMessage@@@Z @0x00431F0C 85B: thiscall int method gating on GameMessage+0x10 == 6 or 0x10 and != this+8 then flag via rowed 0x00431A4D plus helper new 8B vtable 0x0083C97C and final Rva00575674 call. Evidence: chain lane calls just-landed 0x00431A4D; rowed new 0x0002FDA0 rva00575674 0x00575674; vtable g_00C3C97C; prev Rva00431C35 same flags and helper pattern; next Rva00431F61Ctor flag class.
class GameMessage
{
public:
	char m_pad[0x10];
	int m_10;
};

class Rva00431A4D
{
public:
	void rva00431A4D(GameMessage *msg);
};

extern const void *const g_00C3C97C[];

struct Rva00431F0CHelper
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

class Rva00431F0C
{
	void *m_00;
	void *m_04;
	int m_08;
public:
	int rva00431F0C(GameMessage *msg);
};

void *__cdecl operator new(unsigned int size);

int Rva00431F0C::rva00431F0C(GameMessage *msg)
{
	int t = msg->m_10;
	if (t == 6 || t == 0x10)
	{
		if (t != m_08)
		{
			((Rva00431A4D *)m_04)->rva00431A4D(msg);
			void *mem = operator new(8);
			Rva00431F0CHelper *h;
			if (mem != 0)
			{
				h = (Rva00431F0CHelper *)mem;
				h->m_parent = m_04;
				h->m_vptr = (void *)g_00C3C97C;
			}
			else
			{
				h = 0;
			}
			Rva00575674 *q = (Rva00575674 *)((char *)m_04 + 8);
			q->rva00575674((Object *)h);
			return 1;
		}
	}
	return 0;
}
