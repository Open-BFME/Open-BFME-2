// cl: /O1 /MD /GX /arch:SSE
//
// WallUpgradeUpdate members that query the partition manager through a
// filter chain (layout as WallUpgradeUpdateBehaviorCtor.cpp: +0x08 the
// object; +0x28 an ObjectID).
//
//   0x004AB415  while +0x28 is unset, the closest object within 200 of ours
//               (2D centre) that passes the 0x002614DF filter and has kinds
//               7 and 60; its id goes to +0x28 (caller 0x004AB4F2)
//   0x004AB57E  push-out when GeometryUpgrade (0x004B6C8A) grows the wall:
//               every alive object with an AI, other than ours, without
//               status 0x3B, not of kind 2 and passing 0x002614DF within the
//               geometry radius (+0xA8 +0x10) of the geometry centre
//               (0x0028C2DD) that is mobile (0x0028B511 gives 1) and not
//               already clear of the wall is moved three times its centre
//               offset away (Pathfinder::adjustDestination) and faded in
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1).
extern "C" void *memset(void *dst, int value, unsigned int size) throw();

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

// A KindOfMaskType with two kinds set (0x0006EE7A).
struct Rva0006EE7A
{
	Rva0006EE7A(int unused, int bit1, int bit2);
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second (ZH's PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// The 224-bit KindOf mask (unused, bit) constructor 0x00045411.
struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit);	// 0x00045411
	unsigned int m_bits[7];
};

// vftable 0x00BF91BC, allow 0x002611BF: not the given object.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00C17F08, allow 0x0026118B: the object has an AI (+0x258).
class Rva0026118BFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// A 128-bit ObjectStatusMaskType; 0x0023DA79 clears it and sets one bit.
enum ObjectStatusTypes
{
	OBJECT_STATUS_3B = 0x3B
};

struct ObjectStatusMask
{
	ObjectStatusMask() {}
	ObjectStatusMask *Rva0023DA79(int reserved, ObjectStatusTypes bit) throw();	// 0x0023DA79
	unsigned int m_bits[4];
};

struct ObjectStatusMaskNone : ObjectStatusMask
{
	ObjectStatusMaskNone() { memset(this, 0, sizeof(*this)); }
};

class BfmeObject872Header;

// vftable 0x00BFBF00 family: the status must/must-not filter whose ctor is
// 0x002FDF1C (two 16-byte masks).
class Rva002FDF1C : public Rva000421C8
{
public:
	Rva002FDF1C(const BfmeObject872Header &a, const BfmeObject872Header &b) throw();	// 0x002FDF1C
	virtual bool allow(Object *obj);
	ObjectStatusMask m_08;
	ObjectStatusMask m_18;
};

// vftable 0x00C07190, allow 0x002614DF.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
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

struct BfmeWideResultEntry
{
	Object *m_obj;
	int m_04;
};

struct BfmeWideResultData
{
	BfmeWideResultEntry *m_begin;
	BfmeWideResultEntry *m_end;
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	unsigned int count() const { return m_value->m_end - m_value->m_begin; }
	BfmeWideResultData *m_value;
};

class LocomotorSet;

class AIUpdateInterface
{
public:
	char m_pad000[0x1CC];
	char m_locomotorSet[1];	// +0x1CC
	const LocomotorSet &getLocomotorSet() const { return *(const LocomotorSet *)m_locomotorSet; }
};

class Pathfinder
{
public:
	int rva002E9871(const Coord3D *pos);		// 0x002E9871
	bool rva002EDFF9(Object *obj, Coord3D *pos);	// 0x002EDFF9
	bool adjustDestination(Object *obj, const LocomotorSet &locoSet, Coord3D *dest,
		const Coord3D *groupDest);		// 0x002FCFCF
};

class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;	// +0x10
};
extern AI *TheAI;

class Drawable
{
public:
	void fadeIn(unsigned int frames);	// 0x002707A8
};

class Object
{
public:
	void rva0028C2DD(Coord3D *center) const;	// 0x0028C2DD
	int rva0028B511() const;			// 0x0028B511
	void rva0029660C(const Coord3D *pos, int flag);	// 0x0029660C
	Drawable *getDrawable() const;			// 0x005508E2
	char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;			// +0x74
	char m_pad078[0xB8 - 0x78];
	float m_B8;			// +0xB8 (geometry +0xA8, its +0x10 radius)
	char m_pad0BC[0x258 - 0xBC];
	AIUpdateInterface *m_ai;	// +0x258
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

class WallUpgradeUpdate
{
public:
	void rva004AB415();
	void rva004AB57E();
private:
	const void *m_vtable;
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	char m_pad0C[0x28 - 0x0C];
	ObjectID m_28;			// +0x28
};

void WallUpgradeUpdate::rva004AB415()
{
	if (m_28 != INVALID_ID)
		return;
	Object *obj = m_object;
	const Coord3D *pos = &obj->m_pos;
	Object *found = ThePartitionManager->getClosestObject(pos, 200.0f, 1,
		Rva002614DFFilter(obj).link(&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva0006EE7A(0, 7, 60),
			*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)));
	if (found)
		m_28 = found->m_id;
}

void WallUpgradeUpdate::rva004AB57E()
{
	Object *us = m_object;
	float radius = us->m_B8;
	Coord3D center;
	us->rva0028C2DD(&center);
	center.z = us->m_pos.z;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&center, radius, 0,
		Rva002614DFFilter(us).link(&Rva0026119DFilter())->link(&Rva0026118BFilter())
			->link(&Rva002FDF1C(*(BfmeObject872Header *)ObjectStatusMask().Rva0023DA79(0, OBJECT_STATUS_3B),
				*(BfmeObject872Header *)&ObjectStatusMaskNone()))
			->link(&Rva002611BFFilter(us))
			->link(&Rva0004584D(*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
				*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 2))), 2);
	if (hits.count() > 0) {
		for (Object *obj = hits.next(); obj; obj = hits.next()) {
			if (obj->rva0028B511() != 1)
				continue;
			Pathfinder *pathfinder = TheAI->pathfinder();
			Coord3D pos;
			pos.x = obj->m_pos.x;
			pos.y = obj->m_pos.y;
			pos.z = obj->m_pos.z;
			if (pathfinder->rva002E9871(&pos) == 1 && pathfinder->rva002EDFF9(obj, &pos))
				continue;
			AIUpdateInterface *ai = obj->m_ai;
			Coord3D offset;
			offset.x = (center.x - us->m_pos.x) * 3.0f;
			offset.y = (center.y - us->m_pos.y) * 3.0f;
			offset.z = 0.0f;
			pos.x = offset.x + pos.x;
			pos.y = offset.y + pos.y;
			pos.z = offset.z + pos.z;
			pathfinder->adjustDestination(obj, ai->getLocomotorSet(), &pos, 0);
			obj->rva0029660C(&pos, 1);
			if (obj->getDrawable())
				obj->getDrawable()->fadeIn(10);
		}
	}
}
