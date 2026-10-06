// ?Rva00525E07@Holder00525E07@@QAEXPBVAsciiString@@H@Z
// partial score=0.95 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// Range-27 object name max-update walk.
// ?Rva00525E07@Holder00525E07@@QAEXPBVAsciiString@@H@Z @0x00525E07 78B
// Thiscall (name, value): walks the node list at (this+0x10)+0x10 while
// nodes differ from its head. Per node resolves rowed GameLogic
// findObjectByID 0x00049DC5 on the +8 id; on a hit compares the
// AsciiString at [obj+4]+0x64 through rowed StringBase compare 0x000069D6
// and raises the node's +0x10 max to value on equality. Views TU-local;
// callee names are the rowed ones.
#include "ascii_string.h"

enum ObjectID
{
	OBJECTID_NONE = 0
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

struct Node00525E07
{
	Node00525E07 *m_next;
	char m_pad[4];
	int m_8;
	char m_padC[4];
	int m_10;
};

struct List00525E07
{
	Node00525E07 *m_head;
};

struct Holder00525E07
{
	char m_pad[0x10];
	int m_10;
	void Rva00525E07(const AsciiString *name, int value);
};

void Holder00525E07::Rva00525E07(const AsciiString *name, int value)
{
	List00525E07 *list = (List00525E07 *)(m_10 + 0x10);
	Node00525E07 *head = list->m_head;
	Node00525E07 *node = head->m_next;
	if (node != head)
	{
		int b = value;
		do
		{
			Object *o = TheGameLogic->findObjectByID((ObjectID)node->m_8);
			if (o != 0)
			{
				AsciiString *s = (AsciiString *)*(int *)((char *)o + 4);
				s = (AsciiString *)((char *)s + 0x64);
				if (((const StringBase<char> *)s)->compare(*(const StringBase<char> *)name) == 0)
				{
					if (b > node->m_10)
						node->m_10 = b;
				}
			}
			node = node->m_next;
		} while (node != list->m_head);
	}
}
