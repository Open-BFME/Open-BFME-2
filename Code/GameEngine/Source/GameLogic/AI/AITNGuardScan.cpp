// cl: /O1 /MD /GX /arch:SSE
//
// ?TunnelNetworkScan@@YIPAVObject@@PAV1@@Z, retail 0x00545DEE, 146 bytes.
// Zero Hour AITNGuard.cpp's file-static TunnelNetworkScan: the closest
// enemy of the owner it may attack and that shares its map status, within
// AITNGuardMachine::getStdGuardRange. Its caller AITNGuardInnerState::update
// (0x005463C9) passes the owner in ECX with nothing on the stack, the
// register convention whole-program optimisation gives a static; __fastcall
// is that convention for a one-pointer argument, so a separately compiled
// caller can reach it. The name is the Zero Hour helper's: the same three
// filters in the same chain, the same range and query, the same caller.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after allow (slot 1), the ctors being inline. Zero
// Hour's analogues: PartitionFilterRelationship(owner, ALLOW_ENEMIES),
// PartitionFilterPossibleToAttack(ATTACK_NEW_TARGET, owner, CMD_FROM_AI),
// PartitionFilterSameMapStatus(owner). BFME2 builds them in reverse.
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

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

class AITNGuardMachine
{
public:
	static float getStdGuardRange(const Object *obj);	// 0x00542C2A
};

Object *__fastcall TunnelNetworkScan(Object *owner)
{
	Rva002611BFFilter filterMapStatus(owner);
	Rva00260FD0Filter f2(owner, 2, 0);
	Rva00260EB1Filter f1(owner, 1, false);
	Rva000421C8 *filters = f1.link(f2.link(&filterMapStatus));
	return ThePartitionManager->getClosestObject(&owner->m_pos,
		AITNGuardMachine::getStdGuardRange(owner), 0, filters);
}
