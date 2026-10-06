// ?rva0049CF25@Rva0049CF25@@QAEXXZ
// partial score=0.9 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ?rva0049CF25@Rva0049CF25@@QAEXXZ @0x0049CF25 121B.
// Walk the list at +0x28. Kind 3 asks the object's player, then the gate
// at player+0x60. A miss increments the hit counter at +0x98 through the
// slot at player+0x738. Slot 22 on the walker at +0x20 yields the next node.

struct Rva002A7557In;

class Rva002A7461
{
public:
	bool rva002A7557(Rva002A7557In *in, int flag);
};

class Rva0037E421
{
public:
	int rva0037EE4C(Rva002A7557In *in, int key, int zero);
	void *rva0037E421(int index);
};

class Player
{
public:
	char m_pad[0x60];
	Rva002A7461 m_gate;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

struct Node
{
	char m_pad[4];
	int m_kind;
	Rva002A7557In *m_in;
	char m_padC[4];
	int m_key;
};

struct Hit
{
	char m_pad[0x98];
	int m_count;
};

class Walk
{
public:
	virtual Node *s0();
	virtual Node *s1();
	virtual Node *s2();
	virtual Node *s3();
	virtual Node *s4();
	virtual Node *s5();
	virtual Node *s6();
	virtual Node *s7();
	virtual Node *s8();
	virtual Node *s9();
	virtual Node *s10();
	virtual Node *s11();
	virtual Node *s12();
	virtual Node *s13();
	virtual Node *s14();
	virtual Node *s15();
	virtual Node *s16();
	virtual Node *s17();
	virtual Node *s18();
	virtual Node *s19();
	virtual Node *s20();
	virtual Node *s21();
	virtual Node *s22(Node *n);

private:
	int m_gap;
};

class Rva0049CF25
{
public:
	void rva0049CF25();

private:
	char m_pad0[8];
	Object *m_obj;
	char m_padC[0x20 - 0xC];
	Walk m_walk;
	Node *m_node;
};

void Rva0049CF25::rva0049CF25()
{
	Node *n = m_node;
	if (n == 0)
		return;
	Walk *w = &m_walk;
	do {
		if (n->m_kind == 3) {
			Object *obj = m_obj;
			if (obj != 0) {
				Player *player = obj->getControllingPlayer();
				if (player != 0 && player->m_gate.rva002A7557(n->m_in, 1) == 0) {
					Rva0037E421 *slot = (Rva0037E421 *)((char *)player + 0x738);
					if (slot != 0) {
						int id = slot->rva0037EE4C(n->m_in, n->m_key, 0);
						Hit *hit = (Hit *)slot->rva0037E421(id);
						if (hit != 0)
							hit->m_count++;
					}
				}
			}
		}
		n = w->s22(n);
	} while (n != 0);
}
