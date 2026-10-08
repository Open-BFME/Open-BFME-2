// cl: /O1 /EHsc /MD /arch:SSE
// HordeMeleeHoldGround.cpp -- per-unit attack-state accessors recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv). WB's debug build names the
// members and asserts !(index<0||index>=m_AttackInfo.size()); retail keeps
// that range check as a guard. m_AttackInfo is a vector of per-unit states at
// +0x08 (WB member name); the state values 2 (rotating) and 3 (arrived) come
// from the accessor names.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

// STLport vector<Int> view.
class AttackInfoVector
{
public:
	UnsignedInt size() const { return m_finish - m_start; }
	Int &operator[](UnsignedInt i) { return m_start[i]; }
	const Int &operator[](UnsignedInt i) const { return m_start[i]; }

private:
	Int *m_start;
	Int *m_finish;
	Int *m_endOfStorage;
};

enum { UNIT_ROTATING = 2, UNIT_ARRIVED = 3 };

class HordeMeleeHoldGround
{
public:
	virtual Bool isUnitRotating(Int index) const;
	virtual void setUnitRotating(Int index);
	virtual void setUnitArrived(Int index);

private:
	unsigned char m_pad04[4];
	AttackInfoVector m_AttackInfo;		// +0x08
};

// HordeMeleeHoldGround::isUnitRotating, retail 0x00583726.
Bool HordeMeleeHoldGround::isUnitRotating(Int index) const
{
	if (index < 0 || index >= m_AttackInfo.size())
		return false;
	return m_AttackInfo[index] == UNIT_ROTATING;
}

// HordeMeleeHoldGround::setUnitRotating, retail 0x00583750.
void HordeMeleeHoldGround::setUnitRotating(Int index)
{
	if (index < 0 || index >= m_AttackInfo.size())
		return;
	m_AttackInfo[index] = UNIT_ROTATING;
}

// HordeMeleeHoldGround::setUnitArrived, retail 0x00583772.
void HordeMeleeHoldGround::setUnitArrived(Int index)
{
	if (index < 0 || index >= m_AttackInfo.size())
		return;
	m_AttackInfo[index] = UNIT_ARRIVED;
}

enum ObjectStatusTypes
{
	RVA_OBJECT_STATUS_1C = 0x1C
};

class Object
{
public:
	Object *rva002931F5(bool flag);
	Bool testStatus(ObjectStatusTypes status) const;
	void rva00295F05(bool value);
};

struct Rva00583794Node
{
	Rva00583794Node *m_next;
	Rva00583794Node *m_prev;
	Object *m_object;
};

struct Rva00583794List
{
	Rva00583794Node *m_head;
};

struct Rva00583794Range
{
	int m_00;
	const Rva00583794List *m_list;
};

template <int N> class Rva00583794Slots : public Rva00583794Slots<N - 1>
{
public:
	virtual void gap(char (*slot)[N]) = 0;
};

template <> class Rva00583794Slots<0>
{
};

class Rva00583794Iface : public Rva00583794Slots<70>
{
public:
	virtual void fill(Rva00583794Range *range) = 0;
};

struct Rva00583794Member04
{
	char m_pad00[0x20];
	void *m_vtable;
};

// The code-pointer table at RVA 0x86FC50 groups 0x00583794 with the matched
// HordeMeleeHoldGround bodies at 0x00583726/0x00583750/0x00583772. That is
// target-table evidence for the family; the exact method and +0x04 member
// identities remain unresolved. The Ghidra boundary is 0x00583794..0x005837F0.
// ?rva00583794@Rva00583794@@QAEXPAVObject@@@Z @0x00583794 92B
class Rva00583794
{
public:
	void rva00583794(Object *object);

private:
	void *m_vtable;
	Rva00583794Member04 *m_member04;
};

void Rva00583794::rva00583794(Object *object)
{
	object->rva002931F5(false);
	Rva00583794Range range;
	((Rva00583794Iface *)&m_member04->m_vtable)->fill(&range);
	for (Rva00583794Node *node = range.m_list->m_head->m_next;
		node != range.m_list->m_head;
		node = node->m_next)
	{
		Object *item = node->m_object;
		if (item != 0 && !item->testStatus(RVA_OBJECT_STATUS_1C))
			item->rva00295F05(0);
	}
}
