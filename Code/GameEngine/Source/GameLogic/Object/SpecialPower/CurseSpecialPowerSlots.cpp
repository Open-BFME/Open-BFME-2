// cl: /DNDEBUG /MD /EHsc
//
// CurseSpecialPower's slot 17 (0x004CCEEE; SpecialAbilityUpdate's slot 17
// first), its per-target curse (0x004CCE85) and the kind filter's implicit
// copy constructor the slot emits (0x004CCE4C), beside the matched
// CurseSpecialPower ctor 0x004CCD7F and pool key 0x004CCDEB.
//
//   0x004CCEEE  with no +0x40 target, curse every alive object of kind 90
//               relationship 1 to the owner within the special power
//               template's radius of +0x44 (BFME2's partition filter chain,
//               the view AIStructureCreepTactic.cpp documents) and, when any
//               was, FXList::doFXPos the module data's +0xC8 there; with one,
//               curse the object 0x00049DC5 finds for it and do the same FX
//   0x004CCE85  skip the owner, objects whose template lacks +0x110 bit 26,
//               non-enemies and status 3 or 2; then Object::rva0028B701 of
//               the data's +0xD0 and FXList::doFXObj of its +0xCC
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

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
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

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second. Its implicit copy constructor is
// 0x004CCE4C.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();	// 0x00045411
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

// Inherited mask resolves to the real implementation in
// ActionManagerSpecialPowerChecks.cpp (retail 0x0036CC7A).

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

enum ObjectID
{
	INVALID_ID = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA004CCE85_2 = 2,
	OBJECT_STATUS_RVA004CCE85_3 = 3
};

enum Relationship
{
	ENEMIES = 0
};

class Matrix3D;
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);	// 0x000B2235
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx,
		float speed, const Coord3D *secondary);	// 0x00094C29
};

class ThingTemplate
{
public:
	char m_pad000[0x110];
	unsigned m_110;		// +0x110 (bit 26 tested)
};

class Object
{
public:
	Relationship getRelationship(const Object *that) const;	// 0x0028D156
	bool testStatus(ObjectStatusTypes bit) const;	// 0x0004E536
	void rva0028B701(float amount);	// 0x0028B701
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;	// 0x00288609
};

class SpecialPowerTemplate : public Overridable
{
public:
	float getRadius() const
	{
		return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_54;
	}
	char m_pad00[0x54];
	float m_54;	// +0x54
};

class CurseSpecialPowerModuleData
{
public:
	char m_pad00[0xC8];
	const FXList *m_C8;	// +0xC8
	const FXList *m_CC;	// +0xCC
	float m_D0;		// +0xD0
};

class SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();	// slot 17 (0x0045108D)
	const SpecialPowerTemplate *rva005F6B0B() const;	// 0x005F6B0B: module data +0x38
protected:
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class CurseSpecialPower : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
	void rva004CCE85(Object *obj);
private:
	const CurseSpecialPowerModuleData *getCurseSpecialPowerModuleData() const
	{
		return (const CurseSpecialPowerModuleData *)m_moduleData;
	}
	char m_pad0C[0x40 - 0x0C];
	ObjectID m_40;		// +0x40
	Coord3D m_44;		// +0x44
};

void CurseSpecialPower::rva004CCE85(Object *obj)
{
	Object *owner = m_object;
	const CurseSpecialPowerModuleData *data = getCurseSpecialPowerModuleData();
	if (obj == owner)
		return;
	if (!(obj->m_template->m_110 & 0x04000000))
		return;
	if (owner->getRelationship(obj) != ENEMIES)
		return;
	if (obj->testStatus(OBJECT_STATUS_RVA004CCE85_3))
		return;
	if (obj->testStatus(OBJECT_STATUS_RVA004CCE85_2))
		return;
	obj->rva0028B701(data->m_D0);
	FXList::doFXObj(data->m_CC, obj, 0);
}

void CurseSpecialPower::triggerAbilityEffect()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	const CurseSpecialPowerModuleData *data = getCurseSpecialPowerModuleData();
	Object *owner = m_object;
	if (m_40 == INVALID_ID) {
		const SpecialPowerTemplate *power = rva005F6B0B();
		if (!power)
			return;
		float radius = power->getRadius();
		Rva0004584D kind(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 90),
			*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&m_44, radius, 0,
			Rva0026119DFilter().link(Rva0004584D(kind).link(&Rva00260EB1Filter(owner, 1, false))), 0);
		Object *other = hits.next();
		if (other) {
			do {
				rva004CCE85(other);
			} while ((other = hits.next()) != 0);
			FXList::doFXPos(data->m_C8, &m_44, 0, 0.0f, 0);
		}
	} else {
		Object *target = TheGameLogic->findObjectByID(m_40);
		if (target) {
			rva004CCE85(target);
			FXList::doFXPos(data->m_C8, &m_44, 0, 0.0f, 0);
		}
	}
}
