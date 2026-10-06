// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch W. As in VslotSmallBodiesA-V, each class and
// method is address-derived unless the ledger already names it, and models
// only what its body touches. Meanings are not recovered.

// The game's own fprintf (pinned _fprintf), not the CRT import.
struct _iobuf;
typedef struct _iobuf FILE;
extern "C" int __cdecl fprintf(FILE *stream, const char *format, ...);

typedef int Int;
typedef unsigned int UnsignedInt;

class Object;
class Weapon;
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum ObjectID
{
	INVALID_ID = 0
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class GameLogic
{
public:
	Object *getFirstObject();
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *obj);
	char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	void setReceivingDifficultyBonus(bool b);
	char m_pad00[0x8C];
	Object *m_next8C; // +0x8C
};

// 0x003400F9 (AI state tables): logs "CritterDesync: ComputePath3" to the
// file at VA 0x00DFEFF0 while the flag at VA 0x00E03745 is set, then sets
// +0x49 and answers true.
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
class Rva003400F9
{
public:
	bool rva003400F9();
private:
	char m_pad00[0x49];
	bool m_49;
};
bool Rva003400F9::rva003400F9()
{
	if (g_00E03745 && g_00DFEFF0)
		fprintf((FILE *)g_00DFEFF0, "CritterDesync: ComputePath3");
	m_49 = true;
	return true;
}

// 0x003412A5 (AI state tables): whether the owner's current weapon (pinned
// Object::getCurrentWeapon) has a template whose rowed byte getter is set or
// whose +0x78 is not negative.
class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};
struct Rva003412A5Template : public Rva002C9400ByteField
{
	char m_pad00[0x78];
	Int m_78;
};
class Weapon
{
public:
	Int m_00;
	Rva003412A5Template *m_04;
};
struct Rva003412A5Machine
{
	char m_pad00[0x14];
	Object *m_owner14;
};
class Rva003412A5
{
public:
	bool rva003412A5();
private:
	char m_pad00[0x18];
	Rva003412A5Machine *m_18;
};
bool Rva003412A5::rva003412A5()
{
	Object *owner = m_18->m_owner14;
	WeaponSlotType slot;
	const Weapon *w = owner->getCurrentWeapon(&slot);
	if (w && (w->m_04->get() || w->m_04->m_78 >= 0))
		return true;
	return false;
}

// 0x00347AAC: an onExit override that chains to the rowed
// AIInternalMoveToState::onExit, then destroys the owner AI's path and
// clears its +0x198/+0x19C words and +0x3BA flag.
class AIUpdateInterface
{
public:
	void destroyPath();
	char m_pad00[0x198];
	Int m_198;
	Int m_19C;
	char m_pad1A0[0x21A];
	bool m_3BA;
};
struct Rva00347AACOwner
{
	char m_pad00[0x258];
	AIUpdateInterface *m_ai258;
};
struct Rva00347AACMachine
{
	char m_pad00[0x14];
	Rva00347AACOwner *m_owner14;
};
class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
	char m_pad04[0x14];
	Rva00347AACMachine *m_machine18;
};
class Rva00347AAC : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};
void Rva00347AAC::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	AIUpdateInterface *ai = m_machine18->m_owner14->m_ai258;
	if (ai)
	{
		ai->destroyPath();
		ai->m_198 = 0;
		ai->m_19C = 0;
		ai->m_3BA = false;
	}
}

// 0x003AFD22: appends an unlinked node (flag +0x74) to the list with head
// +0x14, tail +0x18 and count +0x10 (links +0x64 next, +0x68 prev).
struct Rva003AFD22Node
{
	char m_pad00[0x64];
	Rva003AFD22Node *m_next;
	Rva003AFD22Node *m_prev;
	char m_pad6C[0x08];
	bool m_linked;
};
class Rva003AFD22
{
public:
	void rva003AFD22(Rva003AFD22Node *node);
	void rva003AFD5C(Rva003AFD22Node *node);
private:
	char m_pad00[0x10];
	Int m_count;
	Rva003AFD22Node *m_head;
	Rva003AFD22Node *m_tail;
};
void Rva003AFD22::rva003AFD22(Rva003AFD22Node *node)
{
	if (node->m_linked)
		return;
	if (!m_head)
		m_head = node;
	if (m_tail)
	{
		m_tail->m_next = node;
		node->m_prev = m_tail;
	}
	else
		node->m_prev = 0;
	m_tail = node;
	node->m_next = 0;
	node->m_linked = true;
	m_count++;
}

// 0x003AFD5C: unlinks a linked node from that list.
void Rva003AFD22::rva003AFD5C(Rva003AFD22Node *node)
{
	if (!node->m_linked)
		return;
	if (node->m_next)
		node->m_next->m_prev = node->m_prev;
	if (node->m_prev)
		node->m_prev->m_next = node->m_next;
	if (node == m_head)
		m_head = node->m_next;
	if (node == m_tail)
		m_tail = node->m_prev;
	node->m_prev = 0;
	node->m_next = 0;
	node->m_linked = false;
	m_count--;
}

// 0x003BCC37: the rowed Object 0x0028B238 with the argument on every object
// of TheGameLogic, then the byte at +0x1A4D5 of the object at VA 0x00DFE16C.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;
class Rva003BCC37
{
public:
	void rva003BCC37(bool b);
};
void Rva003BCC37::rva003BCC37(bool b)
{
	for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->m_next8C)
		obj->setReceivingDifficultyBonus(b);
	*(bool *)((char *)TheScriptEngine + 0x1A4D5) = b;
}

// 0x00406B39 and 0x004059F6: ids drawn once each from the counter at VA
// 0x00DFEE18.
__declspec(selectany) Int g_00DFEE18 = 0;
class Rva00406B39
{
public:
	Int rva00406B39();
	Int rva004059F6();
};
Int Rva00406B39::rva00406B39()
{
	static Int s_id = g_00DFEE18++;
	return s_id;
}
Int Rva00406B39::rva004059F6()
{
	static Int s_id = g_00DFEE18++;
	return s_id;
}

// 0x00428D66: 0 for the argument's +0x10 ids 1000-1999, 29-34, 1701, 2009
// and 2029; else 1.
struct Rva00428D66Arg
{
	char m_pad00[0x10];
	Int m_10;
};
class Rva00428D66
{
public:
	Int rva00428D66(const Rva00428D66Arg *arg);
};
Int Rva00428D66::rva00428D66(const Rva00428D66Arg *arg)
{
	Int id = arg->m_10;
	if ((id >= 1000 && id <= 1999) || id == 30 || id == 29 || id == 2009 || id == 2029
		|| id == 1701 || id == 31 || id == 32 || id == 34 || id == 33)
		return 0;
	return 1;
}

// 0x00479B0A: when the +0x9E0 member's pinned 0x00588BF3 accepts this
// object and the argument, virtual slot 18 then the pinned 0x00478C2C on the
// +0x20 member with the argument.
class Rva0047A040Base9E0
{
public:
	void *rva00588BF3(void *owner, Object *obj);
};
class Rva00478C2C
{
public:
	void rva00478C2C(Object *obj, void *p);
};
class Rva00479B0A
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	void rva00479B0A(Object *obj);
private:
	char m_pad04[0x1C];
	Rva00478C2C m_20;
	char m_pad21[0x9BF];
	Rva0047A040Base9E0 m_9E0;
};
void Rva00479B0A::rva00479B0A(Object *obj)
{
	if (m_9E0.rva00588BF3(this, obj))
	{
		v18();
		m_20.rva00478C2C(obj, 0);
	}
}

// 0x004835FB: destroys the object whose id is held at +0x08 through
// TheGameLogic and forgets the id (the argument is unused).
class Rva004835FB
{
public:
	void rva004835FB(Int unused);
private:
	Int m_00;
	Int m_04;
	ObjectID m_08;
};
void Rva004835FB::rva004835FB(Int)
{
	if (m_08)
	{
		GameLogic *logic = TheGameLogic;
		Object *obj = logic->findObjectByID(m_08);
		if (obj)
		{
			logic->destroyObject(obj);
			m_08 = INVALID_ID;
		}
	}
}

// 0x00483B10 (interface at +0x20 of an UpdateModule): virtual slot 13 of
// the complete object, then the rowed UpdateModule::setWakeFrame for the
// object at the frames left until the +0x24 frame.
class UpdateModule
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	const void *m_moduleData; // +0x04
	Object *m_object; // +0x08
	char m_pad0C[0x14];
};
class Rva00483B10Iface
{
public:
	virtual void rva00483B10(Int unused) = 0;
};
class Rva00483B10 : public UpdateModule, public Rva00483B10Iface
{
public:
	void rva00483B10(Int unused);
private:
	UnsignedInt m_24;
};
void Rva00483B10::rva00483B10(Int)
{
	UnsignedInt now = TheGameLogic->m_frame;
	v13();
	setWakeFrame(m_object, (UpdateSleepTime)(m_24 - now));
}
