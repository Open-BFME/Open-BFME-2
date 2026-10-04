// cl: /O1 /DNDEBUG /MD
// ?rva00290DBB@Object@@QAEXPAURva002A9B58@@0@Z @0x00290DBB 103B
// Neighbours rva00290D42 and findSpecialPowerModuleInterface; unlocks 0x0039D97E 0x003BD884 0x002AEA9F.
// Evidence: null-guarded dual Rva002A9B58 calls 0x002A9B58 0x002A9B35; +0x250 iface slot 0x118 list; self-recursion on node +8; callers 0x00290E0F 0x002AEBF8 0x0039D9C9 0x003BD8F9.
struct Rva002A7588In;
struct Rva002A9B58
{
	void rva002A9B58(Rva002A7588In *p);
	void rva002A9B35(Rva002A7588In *p);
};
struct Out
{
	void *a;
	void *b;
};
struct Object;
struct Node
{
	Node *next;
	void *unk4;
	Object *obj;
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
	void rva00290DBB(Rva002A9B58 *a, Rva002A9B58 *b);
	unsigned char m_pad00[0x250];
	Iface *m_250;
};
void Object::rva00290DBB(Rva002A9B58 *a, Rva002A9B58 *b)
{
	if (!a)
		return;
	if (!b)
		return;
	a->rva002A9B58((Rva002A7588In *)this);
	b->rva002A9B35((Rva002A7588In *)this);
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
		Object *o = cur->obj;
		if (o)
			o->rva00290DBB(a, b);
		cur = cur->next;
	} while (cur != *(Node **)out.b);
}
