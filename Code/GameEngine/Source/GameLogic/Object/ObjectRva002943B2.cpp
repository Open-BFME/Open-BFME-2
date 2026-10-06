// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002943B2@Object@@QAE_NPBVPlayer@@@Z @0x002943B2 191B.
// Object gate: scan dword-field array at +0x84 via the rowed get for the
// slot-60 veto, chain via rva002933CD/testStatus 0x11/rva0028F518/testStatus
// 0x0F, Player +0x5C gate via rva0028C1CC, template +0x113 flag, then
// Rva00373EC6 +0x38/+0x3C via ThePlayerList getNthPlayer and Player
// getRelationship. Evidence: thiscall ret 4 bool al; callees rowed 0x2B224B
// 0x2933CD 0x4E536 0x28F518 0x28C1CC 0x28F4BC 0x2A7A29 0x2AC3E0; ThePlayerList
// 0x009FEEE8; chain from 0x28F4BC.
// LEVER over the 0.97 bank: inverting the four head-guard polarities, so each
// guard's TRUE edge falls through and only its FALSE edge jumps to the high
// result block, is what puts retail's `mov al,1` at the LOW address. The bank
// concluded that block order was unreachable from source after collapsing the
// guards with ||, an explicit veto bool, and nesting; none of those invert the
// JUMP polarity of each guard, which is the lever that matters. rva002933CD is
// rowed returning int (QAEHXZ), so the (unsigned char) cast is what produces the
// `test al,al` retail has instead of a full `test eax,eax`.
// ?rva002931F5@Object@@QAEPAV1@_N@Z, retail 0x002931F5, 84 bytes.
// Object helper: if own template dword +0x114 carries 0x2000 return this;
// else if containedBy (+0x274) template carries it return containedBy;
// else if bool arg set look up producerID (+0x78) via TheGameLogic
// findObjectByID (rowed 0x00049DC5) and return producer if its template
// carries it, else null. Evidence: Object offsets template +0x04
// (Object_isAbleToAttack/ObjectScriptStatus), producer +0x78
// (ObjectSetProducer), containedBy +0x274 (Object_isAbleToAttack),
// TheGameLogic at 0x00DFE78C; callers 0x002933CD (chain + testStatus
// 0x5F/0x60) and 0x00293926 (isKindOf gate) prove Object owner.

typedef bool Bool;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum ObjectID
{
	INVALID_ID = 0
};

enum KindOfType
{
	KINDOF_DUMMY = 0
};

enum ObjectStatusTypes
{
	STATUS_0F = 0x0F,
	STATUS_11 = 0x11,
	STATUS_5F = 0x5F,
	STATUS_60 = 0x60
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

struct ThingTemplate
{
	unsigned char m_pad[0x114];
	unsigned int m_flags114;
};

class Object;

class Rva002B224BDwordField
{
public:
	int get() const;
};

class Rva00373EC6
{
public:
	char m_pad[0x38];
	int m_nth;
	int m_flag3C;
};

class Player
{
public:
	Relationship getRelationship(const Player *other) const;
	char m_pad[0x5C];
	int m_val5C;
};

class PlayerList
{
public:
	Player *getNthPlayer(int i);
};

extern PlayerList *ThePlayerList;

class Rva002943B2Elem
{
public:
	virtual bool v00();
	virtual bool v01();
	virtual bool v02();
	virtual bool v03();
	virtual bool v04();
	virtual bool v05();
	virtual bool v06();
	virtual bool v07();
	virtual bool v08();
	virtual bool v09();
	virtual bool v10();
	virtual bool v11();
	virtual bool v12();
	virtual bool v13();
	virtual bool v14();
	virtual bool v15();
	virtual bool v16();
	virtual bool v17();
	virtual bool v18();
	virtual bool v19();
	virtual bool v20();
	virtual bool v21();
	virtual bool v22();
	virtual bool v23();
	virtual bool v24();
	virtual bool v25();
	virtual bool v26();
	virtual bool v27();
	virtual bool v28();
	virtual bool v29();
	virtual bool v30();
	virtual bool v31();
	virtual bool v32();
	virtual bool v33();
	virtual bool v34();
	virtual bool v35();
	virtual bool v36();
	virtual bool v37();
	virtual bool v38();
	virtual bool v39();
	virtual bool v40();
	virtual bool v41();
	virtual bool v42();
	virtual bool v43();
	virtual bool v44();
	virtual bool v45();
	virtual bool v46();
	virtual bool v47();
	virtual bool v48();
	virtual bool v49();
	virtual bool v50();
	virtual bool v51();
	virtual bool v52();
	virtual bool v53();
	virtual bool v54();
	virtual bool v55();
	virtual bool v56();
	virtual bool v57();
	virtual bool v58();
	virtual bool v59();
	virtual bool v60();
};

class Object;

class GameLogic
{
public:
	class Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	Object *rva002931F5(Bool checkProducer);
	Bool rva00293926(KindOfType kind);
	int rva002933CD();
	void *rva0029439D();
	bool rva002943B2(const Player *other);
	Bool isKindOf(KindOfType kind) const;
	Bool testStatus(ObjectStatusTypes bit) const;
	void *rva0028C197() const;
	Bool rva0028F518();
	Bool rva0028C1CC() const;
	Rva00373EC6 *rva0028F4BC();

private:
	unsigned char m_pad00[4];
	ThingTemplate *m_template;
	unsigned char m_pad08[0x78 - 0x08];
	ObjectID m_producerID;
	unsigned char m_pad7C[0x84 - 0x7C];
	Rva002B224BDwordField *m_field84;
	unsigned char m_pad88[0x274 - 0x88];
	Object *m_containedBy;
};

bool Object::rva002943B2(const Player *other)
{
	Rva002B224BDwordField *field = m_field84;
	if (field != 0)
	{
		Rva002943B2Elem **pp = (Rva002943B2Elem **)field->get();
		for (;;)
		{
			Rva002943B2Elem *e = *pp;
			if (e == 0)
				break;
			if (e->v60())
			{
				++pp;
				continue;
			}
			return false;
		}
	}
	if ((unsigned char)rva002933CD() == 0)
	{
		if (testStatus(STATUS_11) == 0)
		{
			if (rva0028F518())
				goto player_gate;
			if (!testStatus(STATUS_0F))
				return false;
		player_gate:
			if (other == 0 || other->m_val5C != 1)
				goto template_gate;
			if (rva0028C1CC())
				return false;
		}
		else
			return false;
	}
	else
		return false;
template_gate:
	if ((m_template->m_pad[0x113] & 1) == 0)
		return true;
	Rva00373EC6 *r = rva0028F4BC();
	if (r == 0)
		return true;
	if (r->m_flag3C == 0)
		return true;
	Player *pl = ThePlayerList->getNthPlayer(r->m_nth);
	if (pl == 0)
		return true;
	if (pl->getRelationship(other) == ENEMIES)
		return false;
	_ReadWriteBarrier();
	return true;
}
