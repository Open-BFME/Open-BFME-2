// cl: /O1 /DNDEBUG /MD
//
// ?onCollide@HordeMemberCollide@@UAEXPAVObject@@PBVCoord3D@@1@Z, retail
// 0x004BC3CF, 301 bytes: slot 0 of the collide vtable 0x00C5A5B8, the
// secondary table directly before the HordeMemberCollide behavior vtable
// 0x00C5A5D0 (installed at +0x10 by the matched ctor 0x004BC389). Its
// remaining slots are CollideModule's defaults (0x005CB9FF and four
// 0x0047A699), the ZH CollideModuleInterface shape, so the slot is
// onCollide, compiled with that subobject as this (owner at this-8).
//
// When the owner rides in a container whose contain slot 31 (+0x7C) yields a
// horde record with a nonzero id in slot 91 (+0x16C): touching the record's
// own object, or an object riding inside it, hands the toucher to slot 89
// (+0x164). Otherwise, unless slot 88 (+0x160) already accepts the record's
// object, an allied (relationship 2) toucher -- or its container when
// rva002931BA says so -- carrying template kind bit 109 and whose own horde
// record accepts that object (slot 88) and passes slot 87 (+0x15C) has that
// object handed to slot 89. Slot names stay positional: the record's class is
// not established.

class Coord3D;
class ModuleData;
class Player;

typedef int ObjectID;
enum Relationship { ENEMIES, NEUTRAL, ALLIES };

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};

class Object;

class Rva004BC3CFHordeRecord : public VSlots<87>
{
public:
	virtual bool slot87();                    // +0x15C
	virtual bool slot88(Object *obj);         // +0x160
	virtual void slot89(Object *obj);         // +0x164
	virtual void slot90();                    // +0x168
	virtual ObjectID slot91();                // +0x16C
};

class ContainModuleInterface : public VSlots<31>
{
public:
	virtual Rva004BC3CFHordeRecord *slot31(); // +0x7C
};

class ThingTemplate
{
public:
	unsigned int testKindOf(int k) const { return m_kindOf[k >> 5] & (1U << (k & 31)); }
private:
	unsigned char m_pad00[0x108];
	unsigned int m_kindOf[8];                 // +0x108
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	Object *getContainedBy() const { return m_containedBy; }
	ContainModuleInterface *getContain() const { return m_contain; }
	Relationship getRelationship(const Object *that) const;
	bool rva002931BA();
private:
	void *m_vtable;
	const ThingTemplate *m_template;          // +0x04
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id;                            // +0x74
	unsigned char m_pad78[0x250 - 0x78];
	ContainModuleInterface *m_contain;        // +0x250
	unsigned char m_pad254[0x274 - 0x254];
	Object *m_containedBy;                    // +0x274
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData;           // +0x04
	Object *m_object;                         // +0x08
};

class BehaviorModuleInterface { public: virtual void behaviorModuleInterfaceAnchor(); };

class CollideModuleInterface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
};

class HordeMemberCollide : public BehaviorModule, public BehaviorModuleInterface, public CollideModuleInterface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
};

// ?onCollide@HordeMemberCollide@@UAEXPAVObject@@PBVCoord3D@@1@Z @0x004BC3CF
void HordeMemberCollide::onCollide(Object *other, const Coord3D *, const Coord3D *)
{
	if (!other)
		return;

	Object *me = getObject();
	Object *container = me->getContainedBy();
	if (!container)
		return;
	ContainModuleInterface *contain = container->getContain();
	if (!contain)
		return;
	Rva004BC3CFHordeRecord *record = contain->slot31();
	if (!record)
		return;
	if (!record->slot91())
		return;

	if (other->getID() == record->slot91())
	{
		record->slot89(other);
		return;
	}

	Object *recordObject = TheGameLogic->findObjectByID(record->slot91());
	if (record->slot88(recordObject))
		return;

	Object *otherContainer = other->getContainedBy();
	if (otherContainer && otherContainer->getID() == record->slot91())
	{
		record->slot89(other);
		return;
	}

	Object *target = other;
	if (other->rva002931BA())
		target = other->getContainedBy();
	if (!target)
		return;
	if (!target->getTemplate()->testKindOf(109))
		return;
	if (me->getRelationship(target) != ALLIES)
		return;

	Rva004BC3CFHordeRecord *otherRecord = 0;
	if (target->getContain())
		otherRecord = target->getContain()->slot31();
	if (!otherRecord->slot88(recordObject))
		return;
	if (!otherRecord->slot87())
		return;
	record->slot89(recordObject);
}
