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
	void EatNextClickMessage(GameMessage *msg);
};

extern "C" const void *const __identifier("??_7Rva004318FC@@6B@")[];

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

#include <new>

int Rva00431F0C::rva00431F0C(GameMessage *msg)
{
	int messageType = msg->m_10;
	if (messageType == 6 || messageType == 0x10)
	{
		if (messageType != m_08)
		{
			((Rva00431A4D *)m_04)->EatNextClickMessage(msg);
			void *mem = operator new(8);
			Rva00431F0CHelper *h;
			if (mem != 0)
			{
				h = (Rva00431F0CHelper *)mem;
				h->m_parent = m_04;
				h->m_vptr = (void *)__identifier("??_7Rva004318FC@@6B@");
			}
			else
			{
				h = 0;
			}
			Rva00575674 *dispatcher = (Rva00575674 *)((char *)m_04 + 8);
			dispatcher->rva00575674((Object *)h);
			return 1;
		}
	}
	return 0;
}
