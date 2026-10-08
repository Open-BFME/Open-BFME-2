// cl: /O1
//
// ?rva00295FA9@Object@@QAEXPAV1@@Z @0x00295FA9 188B.
// Object thiscall (one Object* arg, ret 4): if containedBy (+0x274) is set
// and its template carries 0x2000, emit the holder-entry float pair through
// matched Rva001E46E1 0x1E48CF plus Rva001E415F 0x1E415F; else gate on
// pinned getRelationship 0x28D156 plus current-weapon checks (pinned
// getCurrentWeapon 0x28AEBD, matched byte field 0x2C9400, pinned Weapon
// 0x2CB933) into banked 0x295A84, then emit the same pair for self.
//
// Target evidence (game.dat, read-only, capstone): frameless thiscall
// (esi=this), mid-function push ebx on the containedBy-null path only,
// x87 float return from 0x1E48CF (fstp immediately after), double built on
// stack from that float plus LogicFrames 0x00DBA4E4, double 0.0 via fldz
// for the 0x2CB933 call. Object layout: template +0x04 (flag 0x2000 at
// +0x115), containedBy +0x274; Weapon +0x04 byte field. The 0x1E48CF arg
// is this, the 0x1E415F args are (float, LogicFrames). Identity unproven:
// honest address-derived names; neighbour range bodies reuse this TU.
typedef int Int;
typedef bool Bool;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

struct ThingTemplate
{
	unsigned char m_pad00[0x114];
	unsigned int m_flags114;
};

struct Rva0028AC4EEntry
{
};

class Object;

class Rva001E46E1
{
public:
	float rva001E48CF(Object *o);
};

class Rva001E415F
{
public:
	void rva001E415F(float f, int i);
};

class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};

class Weapon
{
public:
	bool rva002CB933(Object *a, void *b, float f, int e);

public:
	unsigned char m_pad00[4];
	Rva002C9400ByteField *m_4;
};

extern int g_Va00DBA4E4;

class AIUpdateInterface;
struct Rva00295F05ContainView;
enum ObjectStatusTypes
{
	RVA_OBJECT_STATUS_1C = 0x1C
};

class Object
{
public:
	const Rva0028AC4EEntry *rva0028AC4E() const;
	Relationship getRelationship(const Object *other) const;
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	void rva00295A84(Object *other);
	void rva00295FA9(Object *other);
	void rva00295F05(Bool force);
	Object *rva002931F5(Bool checkProducer);
	Bool testStatus(ObjectStatusTypes status) const;
	void rva00295CA6();

private:
	unsigned char m_pad00[4];
	ThingTemplate *m_template;
	unsigned char m_pad08[0x258 - 0x08];
	AIUpdateInterface *m_ai;
	Rva00295F05ContainView *m_containView;
	unsigned char m_pad260[0x274 - 0x260];
	Object *m_containedBy;
	unsigned char m_pad278[0x438 - 0x278];
	unsigned char m_flags438;
};

// Target-side view used by 0x00295F05. The vslot offset is 0x1C4 (slot
// 113); the second helper is the already matched AIUpdateInterface method
// at 0x002632C7. This does not assert a donor class layout.
template <int N> class Rva00295F05AISlots : public Rva00295F05AISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <> class Rva00295F05AISlots<0>
{
};

class AIUpdateInterface : public Rva00295F05AISlots<113>
{
public:
	virtual Bool rva00295F05Guard();
	Int rva002632C7() const;
};

class Pathfinder
{
public:
	Bool rva002ED313(Object *object);
};

struct Rva00295F05ContainView
{
	unsigned char m_pad00[0x5C];
	Bool m_busy;
};

extern void *g_00DFF0F8;

// ?rva00295FA9@Object@@QAEXPAV1@@Z
void Object::rva00295FA9(Object *other)
{
	Object *cont = m_containedBy;
	if (cont != 0)
	{
		if ((cont->m_template->m_flags114 & 0x2000) != 0)
		{
			const Rva0028AC4EEntry *holder = cont->rva0028AC4E();
			if (holder != 0)
			{
				float f = ((Rva001E46E1 *)holder)->rva001E48CF(this);
				((Rva001E415F *)holder)->rva001E415F(f, g_Va00DBA4E4);
			}
		}
		return;
	}
	if (getRelationship(other) != ENEMIES)
		return;
	Weapon *w = getCurrentWeapon(0);
	if (w != 0 && w->m_4->get() && w->rva002CB933(this, other, 0.0f, 1))
		rva00295A84(other);
	const Rva0028AC4EEntry *e = rva0028AC4E();
	if (e != 0)
	{
		float f = ((Rva001E46E1 *)e)->rva001E48CF(this);
		((Rva001E415F *)e)->rva001E415F(f, g_Va00DBA4E4);
	}
}

// ?rva00295F05@Object@@QAEX_N@Z, retail 0x00295F05, 164 bytes.
// The matched caller at 0x00583794 passes zero while visiting the objects in
// a HordeMeleeHoldGround list. The body gates on the AI vslot at +0x1C4,
// object status 0x1C, containment state, a related object, and the pathfinder
// member at TheAI+0x10 before the final Object helper. These offsets and
// calls come from BFME2's body; GeneralsMD Object.cpp was reviewed for the
// shared Object behavior but does not supply this BFME2 helper by name.
void Object::rva00295F05(Bool force)
{
	AIUpdateInterface *ai = m_ai;
	if (ai != 0 && ai->rva00295F05Guard())
		return;
	if ((m_flags438 & 1) != 0)
		return;
	if (testStatus(RVA_OBJECT_STATUS_1C) && force == 0)
		return;
	if (m_containView != 0 && m_containView->m_busy)
		return;

	Object *related = rva002931F5(false);
	if (related != 0)
	{
		AIUpdateInterface *relatedAI = related->m_ai;
		if (relatedAI != 0 && (unsigned char)relatedAI->rva002632C7() != 0)
			return;
	}

	Pathfinder *pathfinder = *(Pathfinder **)((unsigned char *)g_00DFF0F8 + 0x10);
	if (!pathfinder->rva002ED313(this))
	{
		if (related == 0)
			return;
		unsigned int flags = related->m_template->m_flags114;
		if ((((unsigned char *)&flags)[1] & 0x40) == 0 || (flags & 0x800000) != 0)
			return;
	}
	rva00295CA6();
}
