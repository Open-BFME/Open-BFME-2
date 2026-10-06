// ?rva00344F57@Rva00344F57@@QAEHXZ
// partial score=0.6 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva00344F57@@QAEHXZ @0x00344F57 287B.
// Int-returning goal evaluation (thiscall, no stack args): rejects a failed
// machine check (-1), a missing goal (-1), a null slot (0) and a null slot
// value (-1), refreshes the goal through the status/flag-resolution pair,
// gates on the banked 0x344EB2 predicate (-2), then scores the 0x113 quirk,
// the 0x28B511/0x663763 range check (-2) and the virtual slot chain into a
// final 0. The pre/post slot selves share one spilled home; ebx trades
// 0x28/0x3C and is restored for the join.
class Object;

template <int N>
class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <>
class VSlots<0>
{
};

class Slot31 : public VSlots<31>
{
public:
	virtual Object *slot31();
};

class SelfVirt : public VSlots<78>
{
public:
	virtual void slot78();
	virtual void g79();
	virtual void g80();
	virtual void g81();
	virtual void g82();
	virtual void g83();
	virtual void g84();
	virtual bool slot85(Object *o);
	virtual void g86();
	virtual void g87();
	virtual void g88();
	virtual void slot89(Object *o);
	virtual void slot90(int v);
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26
};

struct Rva00344F57Flags
{
	char m_pad[0x114];
};

class StateMachine
{
public:
	Object *getGoalObject();

	char m_pad00[0x14];
	Object *m_obj14;
};

class TurretStateMachine
{
public:
	bool rva004D7ADD();
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	Object *rva002931F5(bool flag);
	int rva0028B511() const;
	float rva00263763(const void *arg) const;

	char m_pad00[4];
	Rva00344F57Flags *m_p4;
	char m_pad08[0x74 - 0x8];
	int m_74;
	char m_pad78[0x250 - 0x78];
	void *m_slot250;
};

class Thing : public Object
{
};

class Rva00344F57
{
public:
	int rva00344F57();

	char m_pad00[0x18];
	StateMachine *m_machine;
	char m_pad1C[0x20 - 0x1C];
	int m_20;
};

extern int g_00DBA4E4;
extern void *g_00DFE78C;

bool rva00344EB2Gate(Object *a, Thing *b);

int Rva00344F57::rva00344F57()
{
	Object *self = m_machine->m_obj14;
	Object *refSelf = self;
	if (!((TurretStateMachine *)m_machine)->rva004D7ADD())
		return -1;
	Object *goal = m_machine->getGoalObject();
	if (goal == 0)
		return -1;
	Slot31 *slot = (Slot31 *)self->m_slot250;
	if (slot == 0)
		return 0;
	self = slot->slot31();
	if (self == 0)
		return -1;
	int sel = goal->m_74;
	if (goal->testStatus(OBJECT_STATUS_26)) {
		if (goal->rva002931F5(false) != 0) {
			goal = goal->rva002931F5(false);
			sel = goal->m_74;
		}
	}
	if (rva00344EB2Gate(refSelf, (Thing *)goal))
		return -2;
	if (!((SelfVirt *)self)->slot85((Object *)goal)) {
		int rad = 0x28;
		if ((((Rva00344F57Flags *)goal->m_p4)->m_pad[0x113] & 0x20) != 0 && (refSelf->rva0028B511() != 1))
			rad = 0x3C;
		if (refSelf->rva00263763(goal) >= (float)(rad * rad))
			return -2;
		((SelfVirt *)self)->slot89((Object *)goal);
	}
	((SelfVirt *)self)->slot90(sel);
	int base = *(int *)g_00DBA4E4;
	int *table = (int *)g_00DFE78C;
	m_20 = base * 3 + table[0x40 / 4];
	((SelfVirt *)self)->slot78();
	return 0;
}

bool rva00344EB2Gate(Object *a, Thing *b);
