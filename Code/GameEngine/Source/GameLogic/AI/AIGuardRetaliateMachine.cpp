// cl: /MD /GX
//
// ?lookForInnerTarget@AIGuardRetaliateMachine@@QAE_NXZ, retail 0x005455E3,
// 362 bytes (the pinned name: REL32 callee of AIGuardRetaliateReturnState::
// update 0x00545810). Zero Hour AIGuardRetaliate.cpp's lookForInnerTarget,
// BFME2's version: nothing unless the owner (machine +0x14) can attack; the
// team's common target when its template asks for one; else the closest
// object to a copy of the owner's position within 0.3 of the AI data's
// +0xC8 that passes the chain enemy (relationship 1) -> attackable
// (ATTACK_NEW_TARGET, CMD_FROM_AI) -> same map status, then the 0x002611F2
// filter and the reject-kind-130 filter (Zero Hour's RejectBuildings). The
// nemesis id goes to +0x48. A sixth filter (vftable 0x00C172A8) is built and
// never linked, as retail does.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1). Retail updates the unwind state only after the kind mask filter
// is built, so the bitset and mask-filter ctors are declared throw() here.
class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();	// 0x00045411
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second (ZH's PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BF8FF0: +0x08 the object, +0x0C whether its controlling
// player's +0x5C is 1.
class PartitionFilterRejectBuildings : public Rva000421C8
{
public:
	PartitionFilterRejectBuildings(Object *obj);
	virtual bool allow(Object *obj);
	Object *m_obj;
	bool m_flag;
};

// vftable 0x00BF91B0, allow 0x00260FD0: +0x08 the object, +0x0C the attack
// type, +0x10 the command source.
class Rva00260FD0Filter : public Rva000421C8
{
public:
	Rva00260FD0Filter(const Object *obj, int attackType, int source)
		: m_obj(obj), m_attackType(attackType), m_source(source) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
	int m_attackType;
	int m_source;
};

// vftable 0x00C172A8, allow 0x00260E01: no members of its own.
class Rva00260E01Filter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum ObjectID
{
	INVALID_ID = 0
};

struct TeamTemplateInfo
{
	char m_pad000[0x216];
	bool m_attackCommonTarget;	// +0x216
};

struct TeamPrototype
{
	const TeamTemplateInfo *getTemplateInfo() const { return &m_info; }
	TeamTemplateInfo m_info;
};

class Team
{
public:
	Object *getTeamTargetObject();	// 0x003A105B
	char m_pad00[0x30];
	TeamPrototype *m_proto;		// +0x30
};

class Object
{
public:
	bool isAbleToAttack() const;	// 0x00290B73
	char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;			// +0x74
	char m_pad078[0x304 - 0x78];
	Team *m_team;			// +0x304
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

struct TAiData
{
	char m_pad00[0xC8];
	float m_C8;		// +0xC8
};

class AI
{
public:
	char m_pad00[0x18];
	TAiData *m_aiData;	// +0x18
};
extern AI *TheAI;

class AIGuardRetaliateMachine
{
public:
	bool lookForInnerTarget();
private:
	char m_pad00[0x14];
	Object *m_owner;	// +0x14
	char m_pad18[0x48 - 0x18];
	ObjectID m_nemesisID;	// +0x48
};

bool AIGuardRetaliateMachine::lookForInnerTarget()
{
	Object *owner = m_owner;
	if (!owner->isAbleToAttack())
		return false;
	if (owner->m_team->m_proto->getTemplateInfo()->m_attackCommonTarget) {
		Object *teamVictim = owner->m_team->getTeamTargetObject();
		if (teamVictim) {
			m_nemesisID = teamVictim->m_id;
			return true;
		}
	}
	Rva00260EB1Filter f1(owner, 1, false);
	Rva00260FD0Filter f2(owner, 2, 0);
	PartitionFilterRejectBuildings f3(owner);
	Rva0004584D f8(*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
		*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 0x82));
	Rva002611BFFilter filterMapStatus(owner);
	Rva00260E01Filter unused;
	f1.link(f2.link(&filterMapStatus));
	f1.link(&f3);
	f1.link(&f8);
	float visionRange = TheAI->m_aiData->m_C8 * 0.3;
	Coord3D pos;
	pos.x = owner->m_pos.x;
	pos.y = owner->m_pos.y;
	pos.z = owner->m_pos.z;
	Object *target = ThePartitionManager->getClosestObject(&pos, visionRange, 1, &f1);
	if (target) {
		m_nemesisID = target->m_id;
		return true;
	}
	return false;
}
