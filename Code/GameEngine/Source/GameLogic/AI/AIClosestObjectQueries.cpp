// cl: /O1 /MD /GX /arch:SSE
//
// ai.cpp holds the donor-flag ports; these are built with BFME2 flags.
//
// Members of the AI singleton (TheAI, 0x00DFF0F8) that query the partition
// manager through a filter chain.
//
//   0x002FDBC4  the closest object to `me` within range that passes six
//               filters (the 0x002611F2 one first; the 0x002619C1 one only
//               with flag bit 0), never `me` itself; called by 0x003423C8
//               with flags 2 and twice the owner's vision range
//   0x002FDC9A  AI::findClosestRepulsor (the pinned name; Zero Hour's
//               AI.cpp): nothing unless the AI data enables repulsors (+0x64),
//               else the closest object to `me` passing the repulsor filter
//               and the 0x00261058 one, from the 2D centre
//   0x002FEEAD  Zero Hour's AI::findClosestEnemy qualifier chain made a
//               count: with CAN_ATTACK (2) nothing unless `me` can attack;
//               live map enemies, then (by qualifier) not buildings unless
//               ATTACK_BUILDINGS (8), within attack range (0x10), line of
//               sight (1), possible to attack (2), free of fog for the
//               controlling player's index (0x20), significant (4), and the
//               stealth filter last. With CAN_ATTACK and status 0x25 the
//               +0x274 object's +0x250 interface (slot 55) may name the one
//               target, counted 1 when the chain accepts it; otherwise the
//               number of hits within range from the 2D centre. Called by
//               0x00458BE1 with 0x20.
//
// BFME2's partition filters (the view AIStructureCreepTactic.cpp documents):
// a vptr, the +0x04 link to the next filter of a chain (PartitionFilter::link
// 0x00625790 appends its argument and returns this), then each filter's own
// members. Names are address-derived: after the out-of-line ctor, else after
// allow (slot 1). Slot 0 of each vftable is the shared deleting dtor
// 0x00395A19. The inline destructors only restore the base vftable, which cl
// drops when nothing follows.
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
	bool allows(Object *obj);	// 0x00625720
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF8FE4, allow 0x0026109D: +0x08 the object's controlling player
// (or none), +0x0C a flag.
class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

// vftable 0x00BF8FF0: +0x08 the object, +0x0C whether its controlling
// player's +0x5C is 1.
class Rva002611F2 : public Rva000421C8
{
public:
	Rva002611F2(Object *obj);
	virtual bool allow(Object *obj);
	Object *m_obj;
	bool m_flag;
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

// vftable 0x00C07190, allow 0x002614DF.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C07150, allow 0x002619C1.
class Rva002619C1Filter : public Rva000421C8
{
public:
	Rva002619C1Filter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C07178, allow 0x00261BFB: the repulsor filter of
// AI::findClosestRepulsor (ZH's PartitionFilterRepulsor).
class Rva00261BFBFilter : public Rva000421C8
{
public:
	Rva00261BFBFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C071B4, allow 0x002FE13D, getPlayerMask 0x002FE108: the live
// map enemies of +0x08 (ZH's PartitionFilterLiveMapEnemies, AI.cpp-local).
class Rva002FE13DFilter : public Rva000421C8
{
public:
	Rva002FE13DFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
};

// vftable 0x00C071C0, allow 0x002FE371: within +0x08's attack range (ZH's
// PartitionFilterWithinAttackRange, AI.cpp-local).
class Rva002FE371Filter : public Rva000421C8
{
public:
	Rva002FE371Filter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BF91B0, allow 0x00260FD0: +0x08 the object, +0x0C the attack
// type, +0x10 the command source (ZH's PartitionFilterPossibleToAttack).
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

// vftable 0x00C07160, allow 0x00261246: two flags (ZH's
// PartitionFilterInsignificantBuildings).
class Rva00261246Filter : public Rva000421C8
{
public:
	Rva00261246Filter(bool a, bool b) : m_a(a), m_b(b) {}
	virtual bool allow(Object *obj);
	bool m_a;
	bool m_b;
};

// vftable 0x00C0716C, allow 0x00261353: +0x08 a player index (ZH's
// PartitionFilterFreeOfFog).
class Rva00261353Filter : public Rva000421C8
{
public:
	Rva00261353Filter(int playerIndex) : m_playerIndex(playerIndex) {}
	virtual bool allow(Object *obj);
	int m_playerIndex;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Player
{
public:
	char m_pad00[0x54];
	int m_playerIndex;	// +0x54
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA002FEEAD_37 = 0x25
};

// What the +0x274 object keeps at +0x250: slot 55 may name `me`'s target.
class Rva002FEEADInterface
{
public:
#define RVA002FEEAD_SLOT(n) virtual void slot##n();
	RVA002FEEAD_SLOT(00) RVA002FEEAD_SLOT(01) RVA002FEEAD_SLOT(02) RVA002FEEAD_SLOT(03)
	RVA002FEEAD_SLOT(04) RVA002FEEAD_SLOT(05) RVA002FEEAD_SLOT(06) RVA002FEEAD_SLOT(07)
	RVA002FEEAD_SLOT(08) RVA002FEEAD_SLOT(09) RVA002FEEAD_SLOT(10) RVA002FEEAD_SLOT(11)
	RVA002FEEAD_SLOT(12) RVA002FEEAD_SLOT(13) RVA002FEEAD_SLOT(14) RVA002FEEAD_SLOT(15)
	RVA002FEEAD_SLOT(16) RVA002FEEAD_SLOT(17) RVA002FEEAD_SLOT(18) RVA002FEEAD_SLOT(19)
	RVA002FEEAD_SLOT(20) RVA002FEEAD_SLOT(21) RVA002FEEAD_SLOT(22) RVA002FEEAD_SLOT(23)
	RVA002FEEAD_SLOT(24) RVA002FEEAD_SLOT(25) RVA002FEEAD_SLOT(26) RVA002FEEAD_SLOT(27)
	RVA002FEEAD_SLOT(28) RVA002FEEAD_SLOT(29) RVA002FEEAD_SLOT(30) RVA002FEEAD_SLOT(31)
	RVA002FEEAD_SLOT(32) RVA002FEEAD_SLOT(33) RVA002FEEAD_SLOT(34) RVA002FEEAD_SLOT(35)
	RVA002FEEAD_SLOT(36) RVA002FEEAD_SLOT(37) RVA002FEEAD_SLOT(38) RVA002FEEAD_SLOT(39)
	RVA002FEEAD_SLOT(40) RVA002FEEAD_SLOT(41) RVA002FEEAD_SLOT(42) RVA002FEEAD_SLOT(43)
	RVA002FEEAD_SLOT(44) RVA002FEEAD_SLOT(45) RVA002FEEAD_SLOT(46) RVA002FEEAD_SLOT(47)
	RVA002FEEAD_SLOT(48) RVA002FEEAD_SLOT(49) RVA002FEEAD_SLOT(50) RVA002FEEAD_SLOT(51)
	RVA002FEEAD_SLOT(52) RVA002FEEAD_SLOT(53) RVA002FEEAD_SLOT(54)
#undef RVA002FEEAD_SLOT
	virtual bool slot55(Object *me, Object **target);
};

class Object
{
public:
	bool isAbleToAttack() const;	// 0x00290B73
	Player *getControllingPlayer() const;	// 0x0028AFA9
	bool testStatus(ObjectStatusTypes bit) const;	// 0x0004E536
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x250 - 0x44];
	Rva002FEEADInterface *m_250;	// +0x250
	char m_pad254[0x274 - 0x254];
	Object *m_274;		// +0x274
};

enum DistanceCalculationType
{
	FROM_CENTER_3D = 0,
	FROM_CENTER_2D = 1
};

struct BfmeWideHit
{
	Object *m_object;
	float m_distance;
};

struct BfmeWidePayload
{
	BfmeWideHit *m_begin;
	BfmeWideHit *m_end;
};

struct BfmeWideResult
{
	int size() const { return m_value->m_end - m_value->m_begin; }
	~BfmeWideResult();	// 0x0004AA28
	BfmeWidePayload *m_value;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

struct TAiData
{
	char m_pad00[0x64];
	bool m_enableRepulsors;	// +0x64
};

class AI
{
public:
	Object *rva002FDBC4(const Object *me, float range, unsigned int flags);
	Object *findClosestRepulsor(const Object *me, float range);
	int rva002FEEAD(Object *me, float range, unsigned int qualifiers);

private:
	char m_pad00[0x18];
	TAiData *m_aiData;	// +0x18
};

Object *AI::rva002FDBC4(const Object *me, float range, unsigned int flags)
{
	Rva002611F2 first((Object *)me);
	Rva00260EB1Filter relationship(me, 4, false);
	Rva0026119DFilter alive;
	Rva002611BFFilter second(me);
	Rva002619C1Filter optional(me);
	Rva002614DFFilter last(me);
	first.link(relationship.link(alive.link(second.link(&last))));
	if (flags & 1)
		first.link(&optional);
	Object *obj = ThePartitionManager->getClosestObject(&me->m_pos, range, FROM_CENTER_2D, &first);
	if (obj == me)
		obj = 0;
	return obj;
}

Object *AI::findClosestRepulsor(const Object *me, float range)
{
	if (!m_aiData->m_enableRepulsors)
		return 0;
	return ThePartitionManager->getClosestObject(&me->m_pos, range, FROM_CENTER_2D,
		Rva00261BFBFilter(me).link(&Rva00261058((Object *)me, false)));
}

int AI::rva002FEEAD(Object *me, float range, unsigned int qualifiers)
{
	if ((qualifiers & 2) && !me->isAbleToAttack())
		return 0;
	Rva002FE13DFilter filterObvious(me);
	Rva002FE371Filter filterWithinAttackRange(me);
	Rva002611F2 filterBldgs(me);
	Rva00261058 filterStealth(me, false);
	Rva002619C1Filter filterLOS(me);
	Rva00260FD0Filter filterAttack(me, 2, 0);
	Rva00261246Filter filterInsignificant(true, false);
	Rva00261353Filter filterFogged(me->getControllingPlayer()->m_playerIndex);
	if (!(qualifiers & 8))
		filterObvious.link(&filterBldgs);
	if (qualifiers & 0x10)
		filterObvious.link(&filterWithinAttackRange);
	if (qualifiers & 1)
		filterObvious.link(&filterLOS);
	if (qualifiers & 2)
		filterObvious.link(&filterAttack);
	if (qualifiers & 0x20)
		filterObvious.link(&filterFogged);
	if (qualifiers & 4)
		filterObvious.link(&filterInsignificant);
	filterObvious.link(&filterStealth);
	if ((qualifiers & 2) && me->testStatus(OBJECT_STATUS_RVA002FEEAD_37)) {
		Object *container = me->m_274;
		if (container) {
			Rva002FEEADInterface *iface = container->m_250;
			Object *target;
			if (iface && iface->slot55(me, &target)) {
				if (!target)
					return 0;
				return filterObvious.allows(target) ? 1 : 0;
			}
		}
	}
	return ThePartitionManager->iterateObjectsInRange(&me->m_pos, range, FROM_CENTER_2D,
		&filterObvious, 0).size();
}
