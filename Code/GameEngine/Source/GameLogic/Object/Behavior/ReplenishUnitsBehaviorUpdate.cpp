// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ?update@ReplenishUnitsBehavior@@UAE?AW4UpdateSleepTime@@XZ, retail
// 0x0048438A: slot 0 of ReplenishUnitsBehavior's UpdateModuleInterface
// vftable 0x00C49F68 (ctor 0x00484227). BFME2 only (BFME1 keeps just the
// upgrade part): asleep for good unless the +0x20 upgrade interface reports
// active (slot 0) and the object is alive; with the data's +0x139 flag the
// object's +0x250 interface must name a +0x08 for the 0x00260F77 filter
// (slot 31). When the data's +0x11C radius is zero or no enemy (0x00260EB1
// with 1) alive, not this object and passing 0x00261058 lies within it,
// the closest object within the data's +0x118 that is of the controlling
// player, has the data's +0x124 status and not status 0x32, is alive, not
// this object and passes 0x00260F77, goes to 0x004842DD. Sleeps for the
// data's +0x134. All scans go through BFME2's partition filter chain (the
// view AIStructureCreepTactic.cpp documents).
//
// 0x004842DD: replenish the target: the data's +0x120 FX on it, and when the
// data's +0x124 status mask has bit 39 its DetachableRiderUpdate module (if
// any) gets 0x004AE8FA.
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

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFBC90, allow 0x00260EB1: +0x08 the object, +0x0C
// relationship flags, +0x10 whether a hit allows.
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

// vftable 0x00BF8FE4, allow 0x0026109D; the out-of-line ctor 0x00261058.
class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);	// 0x00261058
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

// vftable 0x00BFAD04, allow 0x00260E2A, slot 2 0x00260E1E: +0x08 a player.
class Rva00260E2AFilter : public Rva000421C8
{
public:
	Rva00260E2AFilter(Player *player) : m_player(player) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
};

// vftable 0x00C49F14, allow 0x00260F77: +0x08 what to compare, +0x0C
// whether a hit allows.
class Rva00260F77Filter : public Rva000421C8
{
public:
	Rva00260F77Filter(void *what, bool match) : m_what(what), m_match(match) {}
	virtual bool allow(Object *obj);
	void *m_what;
	bool m_match;
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA0048438A_50 = 0x32
};

// A 128-bit ObjectStatusMaskType; 0x0023DA79 clears it and sets one bit.
struct ObjectStatusMask
{
	ObjectStatusMask() {}
	bool test(int bit) const { return (m_bits[bit >> 5] >> (bit & 31)) & 1; }
	ObjectStatusMask *Rva0023DA79(int reserved, ObjectStatusTypes bit) throw();	// 0x0023DA79
	unsigned m_bits[4];
};

// vftable 0x00C17968; the out-of-line ctor 0x003685CF: status must / must not.
class Rva003685CF : public Rva000421C8
{
public:
	Rva003685CF(const ObjectStatusMask &must, const ObjectStatusMask &mustNot) throw();	// 0x003685CF
	virtual bool allow(Object *obj);
	ObjectStatusMask m_must;
	ObjectStatusMask m_mustNot;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);	// 0x000B2235
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);	// 0x00148E1A
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
public:
	virtual void moduleSlot();
};

class DetachableRiderUpdate
{
public:
	void rva004AE8FA();	// 0x004AE8FA
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

// What Object +0x250 holds: slot 31 names the 0x00260F77 filter's subject.
class Rva0048438AInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void *slot31();
};

class Object
{
	friend class ReplenishUnitsBehavior;
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	const Coord3D *getPosition() const { return &m_pos; }
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x250 - 0x44];
	Rva0048438AInterface *m_250;	// +0x250
	char m_pad254[0x438 - 0x254];
	unsigned char m_438;	// +0x438 (bit 0: effectively dead)
protected:
	Module *findModule(NameKeyType key) const;	// 0x0028B6D6
};

struct ReplenishUnitsBehaviorModuleData
{
	char m_pad00[0x118];
	float m_118;			// +0x118 the replenish radius
	float m_11C;			// +0x11C the enemy check radius
	const FXList *m_120;		// +0x120 the replenish FX
	ObjectStatusMask m_124;		// +0x124 the status a target needs
	UpdateSleepTime m_134;		// +0x134 the sleep
	char m_pad138;
	bool m_139;			// +0x139
};

class ModuleData;

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	char m_pad14[0x20 - 0x14];
};

class UpgradeMux
{
public:
	virtual bool isUpgradeActive() const = 0;
};

class ReplenishUnitsBehavior : public UpdateModule, public UpgradeMux
{
public:
	virtual UpdateSleepTime update();
	void rva004842DD(Object *target);
private:
	const ReplenishUnitsBehaviorModuleData *getReplenishUnitsBehaviorModuleData() const
	{
		return (const ReplenishUnitsBehaviorModuleData *)m_moduleData;
	}
};

void ReplenishUnitsBehavior::rva004842DD(Object *target)
{
	const ReplenishUnitsBehaviorModuleData *data = getReplenishUnitsBehaviorModuleData();
	if (data->m_120)
		FXList::doFXObj(data->m_120, target, 0);
	if (data->m_124.test(39)) {
		static NameKeyType key = TheNameKeyGenerator->nameToKey("DetachableRiderUpdate");
		Module *rider = target->findModule(key);
		if (rider)
			((DetachableRiderUpdate *)rider)->rva004AE8FA();
	}
}

UpdateSleepTime ReplenishUnitsBehavior::update()
{
	Object *obj = m_object;
	const ReplenishUnitsBehaviorModuleData *data = getReplenishUnitsBehaviorModuleData();
	ReplenishUnitsBehavior *self = this;
	if (self->isUpgradeActive() && !obj->isEffectivelyDead()) {
		void *subject = 0;
		if (data->m_139) {
			Rva0048438AInterface *provider = obj->m_250;
			subject = provider ? provider->slot31() : 0;
			if (!subject)
				return UPDATE_SLEEP_FOREVER;
		}
		if (data->m_11C == 0.0f || ThePartitionManager->getClosestObject(obj->getPosition(), data->m_11C, 0,
				Rva00260EB1Filter(obj, 1, false).link(Rva0026119DFilter().link(Rva002611BFFilter(obj).link(
					&Rva00261058(obj, false))))) == 0) {
			Object *target = ThePartitionManager->getClosestObject(obj->getPosition(), data->m_118, 0,
				Rva00260E2AFilter(obj->getControllingPlayer()).link(
					Rva003685CF(data->m_124, *ObjectStatusMask().Rva0023DA79(0, OBJECT_STATUS_RVA0048438A_50)).link(
						Rva0026119DFilter().link(Rva002611BFFilter(obj).link(&Rva00260F77Filter(subject, true))))));
			if (target)
				self->rva004842DD(target);
		}
		return data->m_134;
	}
	return UPDATE_SLEEP_FOREVER;
}
