// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP=
// ?rva004F971E@Rva004F971E@@QAEXXZ retail 0x004F971E..0x004F99CC (686 bytes)
// under the pinned placeholder spelling. WorldBuilder twin 0x12ED000 is
// LivingWorldAutoResolveBattle::chooseTargets (LivingWorldAutoResolveBattle.cpp
// asserts at lines 670..765); the ready loop of 0x004FA10F calls it.
// Per side: clear each unit's target reference (+0x20); queue the units that
// can attack (0x0059AE94) and whose combat chain (thing +0x2C through
// 0x0033A674) yields a target priority; file the units that can be attacked
// (0x0059ADB9) into per-type (thing +0x5C4) and per-side target lists. Then each
// side's attackers are spread over the other side's targets: a quotient and a
// remainder per target; an attacker that finds no list entry under its quota
// asks its chain for the next priority (0x00418EEB) and is queued again.
// Locals: list<Rva005F8F96> lists[8][2] and two 16-byte priority queues built
// through the EH vector constructor iterator; queue push 0x004F941E and pop
// 0x004F81DB; list push_back 0x005CD018 and pop_front 0x004F7DBE; reference
// holders 0x004F6943 / 0x004F692B / 0x004F6966 released through 0x0007DEEF.
// The battle keeps its two unit vectors at +0x0C (12-byte stride).

typedef unsigned int size_t;

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
};

struct Ints004F6943
{
	int m_00;
	int m_04;
};

struct Out00418CC8;
struct Rva004F9018Element;

struct Rva004F6943
{
	TargetRef00217D4C *m_00;
	int m_04;
	int m_08;
	Rva004F6943(const TreeHintRef00217D4C &ref, const Ints004F6943 &v);
	~Rva004F6943()
	{
		if (m_00)
			ReleaseTreeHintRef00217D4C(m_00);
	}
};

struct Rva004F692B
{
	TargetRef00217D4C *m_00;
	int m_04;
	Rva004F692B(const Rva004F692B &other);
	~Rva004F692B()
	{
		if (m_00)
			ReleaseTreeHintRef00217D4C(m_00);
	}
};

struct Rva004F6966
{
	TargetRef00217D4C *m_00;
	int m_04;
	int m_08;
	Rva004F6966(const Rva004F6966 &other);
	~Rva004F6966()
	{
		if (m_00)
			ReleaseTreeHintRef00217D4C(m_00);
	}
};

// List element: the target unit reference and its attacker count.
struct Rva005F8F96
{
	TargetRef00217D4C *m_unit;
	int m_count;
};

class Rva005CD018Obj;

namespace _STL
{
template <class _Tp> class allocator { };

struct _List_node_base
{
	_List_node_base *_M_next;
	_List_node_base *_M_prev;
};

template <class _Tp> struct _List_node : public _List_node_base
{
	_Tp _M_data;
};

template <class _Tp, class _Alloc = allocator<_Tp> > class list
{
public:
	list();
	~list();
	void push_back(const _Tp &x);
	// The target lists file holders through the folded list<Rva005CD018Obj*>
	// push_back spelling at 0x005CD018.
	void push_back(const Rva004F692B &x)
	{
		((list<Rva005CD018Obj *> *)this)->push_back((Rva005CD018Obj *const &)x);
	}
	void pop_front();
	bool empty() const { return _M_node->_M_next == _M_node; }
	_Tp &front() { return ((_List_node<_Tp> *)_M_node->_M_next)->_M_data; }

	_List_node_base *_M_node;
};
}

typedef _STL::list<Rva005F8F96> TargetList;

class Rva004F941E
{
public:
	void rva004F941E(const Rva004F9018Element &e);
};

class Rva004F81DBQueue
{
public:
	void pop();
};

// The 16-byte priority queue of attackers: vector of 12-byte holders plus the
// comparator byte.
class Rva00524306
{
public:
	Rva00524306();
	~Rva00524306();

	bool empty() const { return m_start == m_finish; }
	const Rva004F6966 &top() const { return *m_start; }
	void push(const Rva004F6943 &e) { ((Rva004F941E *)this)->rva004F941E((const Rva004F9018Element &)e); }
	void pop() { ((Rva004F81DBQueue *)this)->pop(); }

	Rva004F6966 *m_start;
	Rva004F6966 *m_finish;
	Rva004F6966 *m_endOfStorage;
	bool m_compare;
};

class LivingWorldAutoResolveCombatChain
{
public:
	bool getHighestPriorityTarget(Out00418CC8 *out);
};

class Rva00418EEB
{
public:
	bool rva00418EEB(void *priority, const void *type);
};

class Rva0033A674
{
public:
	void *rva0033A674();
};

class Rva002BED91
{
public:
	void clear();
};

class AptCommandMap;
template <class T> class AptRef
{
public:
	AptRef &operator=(const AptRef &other);
};

class Rva0059AE94
{
public:
	bool rva0059AE94();
};

class Rva0059ADB9
{
public:
	bool rva0059ADB9();
};

struct AutoResolveThing
{
	unsigned char m_unmodelled000[0x5c4];
	int m_targetType;									///< +0x5C4
};

struct AutoResolveUnit
{
	void *m_vtbl;
	int references;
	unsigned char m_unmodelled08[0x18];
	TargetRef00217D4C *m_target;						///< +0x20
	unsigned char m_unmodelled24[8];
	AutoResolveThing *m_thing;							///< +0x2C

	bool canAttack() { return ((Rva0059AE94 *)this)->rva0059AE94(); }
	bool canBeAttacked() { return ((Rva0059ADB9 *)this)->rva0059ADB9(); }
	void clearTarget() { ((Rva002BED91 *)&m_target)->clear(); }
	void setTarget(const Rva005F8F96 &e)
	{
		((AptRef<AptCommandMap> *)&m_target)->operator=(*(const AptRef<AptCommandMap> *)&e);
	}
	void *getCombatChain() { return ((Rva0033A674 *)m_thing)->rva0033A674(); }
	int getTargetType() { return m_thing->m_targetType; }
};

struct AutoResolveUnitRef
{
	AutoResolveUnit *m_ptr;
	AutoResolveUnit *operator->() const { return m_ptr; }
};

struct AutoResolveUnitVector
{
	AutoResolveUnitRef *m_start;
	AutoResolveUnitRef *m_finish;
	AutoResolveUnitRef *m_endOfStorage;
};

class Rva004F971E
{
public:
	void rva004F971E();

	unsigned char m_players[0xc];
	AutoResolveUnitVector m_units[2];					///< +0x0C
};

void Rva004F971E::rva004F971E()
{
	TargetList lists[8][2];
	Rva00524306 queues[2];
	int targets[2];
	int attackers[2];
	int i;

	for (i = 0; i < 2; ++i)
	{
		attackers[i] = 0;
		targets[i] = 0;
		AutoResolveUnitRef *it = m_units[i].m_start;
		AutoResolveUnitRef *end = m_units[i].m_finish;
		for (; it != end; ++it)
		{
			(*it)->clearTarget();
			if ((*it)->canAttack())
			{
				++attackers[i];
				Ints004F6943 priority;
				priority.m_00 = 7;
				priority.m_04 = 0;
				if (((LivingWorldAutoResolveCombatChain *)(*it)->getCombatChain())->getHighestPriorityTarget((Out00418CC8 *)&priority))
					queues[i].push(Rva004F6943((const TreeHintRef00217D4C &)*it, priority));
			}
			if ((*it)->canBeAttacked())
			{
				++targets[i];
				lists[(*it)->getTargetType()][i].push_back(Rva004F692B((const Rva004F692B &)*it));
			}
		}
	}

	for (i = 0; i < 2; ++i)
	{
		int other = (i == 0);
		if (targets[other] == 0)
			continue;
		int perTarget = attackers[i] / targets[other];
		int extra = attackers[i] % targets[other];
		while (!queues[i].empty())
		{
			Rva004F6966 top(queues[i].top());
			queues[i].pop();
			bool assigned = false;
			while (!assigned && !lists[top.m_04][other].empty())
			{
				Rva005F8F96 &entry = lists[top.m_04][other].front();
				if (entry.m_count < perTarget || (entry.m_count == perTarget && extra > 0))
				{
					assigned = true;
					if (entry.m_count == perTarget)
						--extra;
					++entry.m_count;
					((AutoResolveUnit *)top.m_00)->setTarget(entry);
				}
				else
				{
					lists[top.m_04][other].pop_front();
				}
			}
			if (!assigned)
			{
				Ints004F6943 priority;
				priority.m_00 = 7;
				priority.m_04 = 0;
				if (((Rva00418EEB *)((AutoResolveUnit *)top.m_00)->getCombatChain())->rva00418EEB(&priority, &top.m_04))
					queues[i].push(Rva004F6943((const TreeHintRef00217D4C &)top, priority));
			}
		}
	}
}
