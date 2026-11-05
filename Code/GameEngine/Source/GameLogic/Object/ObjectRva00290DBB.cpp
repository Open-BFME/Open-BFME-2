// cl: /DNDEBUG /MD
// ?rva00290DBB@Object@@QAEXPAVPlayer@@0@Z @0x00290DBB 103B
// Neighbours removeUpgrade and findSpecialPowerModuleInterface; unlocks 0x0039D97E 0x003BD884 0x002AEA9F.
// Evidence: null-guarded dual Player calls 0x002A9B58 0x002A9B35; +0x250 iface slot 0x118 list; self-recursion on node +8; callers 0x00290E0F 0x002AEBF8 0x0039D9C9 0x003BD8F9.
struct Rva002A7588In;
#include "../../../Include/Common/Player.h"
struct Out
{
	void *a;
	void *b;
};
struct Object;
struct Node
{
public:
	Node *next; // +0x00
	char m_pad04[0x4];
	class Object *obj; // +0x08
};
template <int N> class Slots : public Slots<N-1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Slots<0>
{
};
class Iface : public Slots<70>
{
public:
	virtual void getList(Out *out) = 0;
};
class Object
{
public:
	void rva00290DBB(Player *a, Player *b);
	unsigned char m_pad00[0x250];
	Iface *m_250;
};
void Object::rva00290DBB(Player *player, Player *b)
{
	if (!player)
		return;
	if (!b)
		return;
	player->removeCommandPoints((Rva002A7588In *)this);
	b->addCommandPoints((Rva002A7588In *)this);
	Iface *iface = m_250;
	if (!iface)
		return;
	Out out;
	iface->getList(&out);
	Node *head = *(Node **)out.b;
	Node *cur = head->next;
	if (cur == head)
		return;
	do {
		Object *object = cur->obj;
		if (object)
			object->rva00290DBB(player, b);
		cur = cur->next;
	} while (cur != *(Node **)out.b);
}
