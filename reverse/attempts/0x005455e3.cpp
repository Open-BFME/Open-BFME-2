// ?lookForInnerTarget@AIGuardRetaliateMachine@@QAE_NXZ
// partial score=0.9 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?lookForInnerTarget@AIGuardRetaliateMachine@@QAE_NXZ @0x005455E3 362B
// BFME1 donor AIGuardRetaliate.cpp lookForInnerTarget with retail offsets: owner +0x14,
// team +0x304 template +0x30 flag +0x216 victim id +0x74 to +0x48, pos +0x38, id +0x74.
// Filter chain mirrors AIClosestObjectQueries.cpp: relationship BFBC90 attack BF91B0
// buildings Rva002611F2 kindMask BitSet 0x82 kindFilter mapStatus BF91BC trailing C172A8
// linked in donor order then PartitionManager getClosestObject via the rowed pin.
// Retail stores the relationship vptr first so it is assigned manually through the
// g_ data extern; its empty dtor keeps the EH state without emitting code. Buildings
// is a 16B box view (the rowed ctor writes the real layout) so it stays out of the
// unwind states. The trailing filter is never read; volatile pins its dead stores.
// Evidence: pinned name rowed callees caller 0x00545810 donor line 386.
class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);
	Rva000421C8 *m_next;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct PartitionFilterRelationship
{
	const void *m_vptr;
	Rva000421C8 *m_next;
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

struct AttackPossibleFilter
{
	const void *m_vptr;
	Rva000421C8 *m_next;
	const Object *m_obj;
	int m_flags;
	int m_match;
};

class Rva002611F2 : public Rva000421C8
{
public:
	Rva002611F2(Object *obj);
	virtual bool allow(Object *obj);
	Object *m_obj;
	bool m_flag;
};

struct Rva002611BFFilter
{
	const void *m_vptr;
	Rva000421C8 *m_next;
	const Object *m_obj;
};

struct TrailingRepoFilter
{
	const void *volatile m_vptr;
	Rva000421C8 *volatile m_next;
};

class BfmeFixedStorage0004543D
{
	char m_bytes[28];
};

struct Rva00045411BitSet : public BfmeFixedStorage0004543D
{
	Rva00045411BitSet(int unused, int bit);
};

class Rva0004584D
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual void dummy();
	int m_04;
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;
extern const void *const g_00BFBC90[];
extern const void *const g_00BF91B0[];
extern const void *const g_00BF91BC[];
extern const void *const g_00C172A8[];
extern const double g_00C6A028;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Team
{
public:
	Object *rva003A105B();
	char m_pad00[0x30];
	const char *m_template30;
};

class Object
{
public:
	bool isAbleToAttack() const;
	char m_pad00[0x38];
	Coord3D m_pos38;
	char m_pad44[0x74 - 0x44];
	int m_id74;
	char m_pad78[0x304 - 0x78];
	Team *m_team304;
};

struct AIGuardData
{
	char m_pad00[0xC8];
	float m_guardInnerRangeC8;
};

class AI
{
public:
	char m_pad00[0x18];
	AIGuardData *m_aiData18;
};
extern AI *g_Va009FF0F8;

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc, Rva000421C8 *filters);
};
extern PartitionManager *ThePartitionManager;

class AIGuardRetaliateMachine
{
public:
	bool lookForInnerTarget();
private:
	char m_pad00[0x14];
	Object *m_owner14;
	char m_pad18[0x48 - 0x18];
	int m_targetID48;
};

// ?lookForInnerTarget@AIGuardRetaliateMachine@@QAE_NXZ present-unmatched
bool AIGuardRetaliateMachine::lookForInnerTarget()
{
	Object *owner = m_owner14;
	if (!owner->isAbleToAttack())
		return false;
	Team *team = owner->m_team304;
	const char *teamTemplate = team->m_template30;
	if (teamTemplate[0x216]) {
		Object *teamVictim = team->rva003A105B();
		if (teamVictim) {
			m_targetID48 = teamVictim->m_id74;
			return true;
		}
	}
	int center = 1;
	PartitionFilterRelationship relationship;
	relationship.m_next = 0;
	relationship.m_vptr = g_00BFBC90;
	relationship.m_obj = owner;
	relationship.m_flags = center;
	relationship.m_match = false;
	AttackPossibleFilter attack;
	attack.m_next = 0;
	attack.m_vptr = g_00BF91B0;
	attack.m_obj = owner;
	attack.m_flags = 2;
	attack.m_match = 0;
	Rva002611F2 buildings(owner);
	Rva00045411BitSet kindMask(0, 0x82);
	Rva0004584D kindFilter(g_defaultStorage009FEFA4, kindMask);
	Rva002611BFFilter mapStatus;
	mapStatus.m_next = 0;
	mapStatus.m_vptr = g_00BF91BC;
	mapStatus.m_obj = owner;
	TrailingRepoFilter trailing;
	trailing.m_next = 0;
	trailing.m_vptr = g_00C172A8;
	((Rva000421C8 *)&relationship)->link(((Rva000421C8 *)&attack)->link((Rva000421C8 *)&mapStatus));
	((Rva000421C8 *)&relationship)->link((Rva000421C8 *)&buildings);
	((Rva000421C8 *)&relationship)->link((Rva000421C8 *)&kindFilter);
	AI *ai = g_Va009FF0F8;
	float visionRange = ai->m_aiData18->m_guardInnerRangeC8 * g_00C6A028;
	Coord3D pos;
	pos.x = owner->m_pos38.x;
	pos.y = owner->m_pos38.y;
	pos.z = owner->m_pos38.z;
	Object *target = ThePartitionManager->getClosestObject(&pos, visionRange, center, (Rva000421C8 *)&relationship);
	if (target) {
		m_targetID48 = target->m_id74;
		return true;
	}
	return false;
}
