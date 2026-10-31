// cl: /DNDEBUG /MD /EHsc
//
// ?rva0049C8E9@GiveUpgradeUpdate@@QAEEXZ, retail 0x0049c8e9, 19 bytes. Banked partial (score 0.7894736842) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
//
// GiveUpgradeUpdate's helper 0x0049C73A, run by its slot 14 (0x0049C8E9,
// vftable 0x00851220; xfer 0x0049C41C, pool key 0x0049C471). Without a
// +0x40 target and with the module data's +0xE0 flag: mark +0x89, then the
// first alive allied (relationship flag 2) object other than this one that
// the 0x00261130 filter accepts for the upgrade TheUpgradeCenter finds for
// this object's +0x284 mask, anywhere (100000; BFME2's partition filter
// chain, the view AIStructureCreepTactic.cpp documents), whose template lacks
// +0x118 bit 22 and that is not status 0x42, gets status 0x42 (with its rider,
// from Object::rva002931F5 or the +0x78 object whose template lacks +0x108
// bit 7, unless that one is status 0x42 or 2) and is handed with the data's
// +0x38 to the +0x20 member's slot 0.
class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(class Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(class Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const class Object *obj) : m_obj(obj) {}
	virtual bool allow(class Object *obj);
	const class Object *m_obj;
};

// vftable 0x00C51150, allow 0x00261130: +0x08 an upgrade.
class Rva00261130Filter : public Rva000421C8
{
public:
	Rva00261130Filter(const void *upgrade) : m_upgrade(upgrade) {}
	virtual bool allow(class Object *obj);
	const void *m_upgrade;
};

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags, +0x0C whether a hit allows.
class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(class Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(class Object *obj);
	virtual int getPlayerMask();
	class Player *m_player;
	bool m_match;
	int m_flags;
};


#include "../../../../../Libraries/Include/Lib/Coord3D.h"

struct BfmeWideResult
{
	class Object *next() throw();	// 0x00045623
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

// TheUpgradeCenter's lookup: the first upgrade whose bit the mask has.
class Rva0026F0F0
{
public:
	void *rva0026F0F0(const void *mask);	// 0x0026F0F0
};
// TheUpgradeCenter is only an alias of the owned global TheUpgradeCenter (ledger names column); this unit reads the owner through its own view type.
class UpgradeCenter;
extern UpgradeCenter *TheUpgradeCenter;

#include "../../../Common/GameLogicObjectLookupView.h"

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA0049C73A_2 = 2,
	OS_3 = 3,
	OS_42 = 0x42,
	OBJECT_STATUS_RVA0049C73A_66 = 0x42
};

class ThingTemplate
{
public:
	char m_pad000[0x108];
	unsigned m_kindOf;		// +0x108 (bit 7 tested)
	char m_pad10C[0x118 - 0x10C];
	unsigned m_118;		// +0x118 (bit 22 tested)
};

class UpgradeTemplate;
class Provider31;
class AIUpdate;
class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
	Object *rva002931F5(bool flag);
	Player *getControllingPlayer() const; // 0x0028AFA9
	bool testStatus(ObjectStatusTypes bit) const; // 0x0004E536
	const Coord3D *getPosition() const { return &m_pos; }
	bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	char m_pad00[0x4];
	const ThingTemplate *m_template; // +0x04 +0x04
	char m_pad08[0x30];
	Coord3D m_pos; // +0x38 +0x38
	char m_pad44[0x34];
	ObjectID m_78; // +0x78 +0x78
	char m_pad7C[0x1D4];
	Provider31 *m_prov250; // +0x250
	char m_pad254[0x4];
	AIUpdate *m_ai; // +0x258
	char m_pad25C[0x18];
	int m_int274; // +0x274
	char m_pad278[0xC];
	unsigned m_284[32]; // +0x284 +0x284 the upgrade mask
	char m_pad304[0x134];
	unsigned char m_b438; // +0x438
	char m_pad439[0x3];
};

extern GameLogic *TheGameLogic;

class Rva0044ECCE
{
public:
	virtual ~Rva0044ECCE();

	unsigned char m_pad[0x38 - 4];
	int m_38; // +0x38
	unsigned char m_pad3C[0xC8 - 0x3C];
};

class __declspec(novtable) GiveUpgradeUpdateModuleData : public Rva0044ECCE
{
public:
	virtual ~GiveUpgradeUpdateModuleData();

	void *m_bufC8; // +0xC8 vector payload stand-in
	unsigned char m_padCC[0xD4 - 0xCC]; // +0xCC..+0xD3 vector tail stand-in
	int m_intD4; // +0xD4
	int m_intD8; // +0xD8
	float m_floatDC; // +0xDC
	bool m_deliverUpgrade; // +0xE0
	unsigned char m_padE1[0xE4 - 0xE1];
};

// What sits at +0x20: slot 0 takes the data's +0x38 and the object.
class Rva0049C73AHandler
{
public:
	virtual void rva0049C73ASlot0(int what, Object *obj, int a, int b, int c);
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
enum NameKeyType
{
	NK_UNKNOWN = 0
};
class SpecialPowerTemplate;
class Waypoint;
class Rva0049C5D9;
class Xfer;

// 0x00450AE9 is the rowed SpecialAbilityUpdate::rva00450AE9 (bool, result
// unused here), called on this unit's own receiver.
class SpecialAbilityUpdate
{
	friend class Rva0049C5D9;
public:
	virtual UpdateSleepTime update();
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate, const Object *targetObj, const Coord3D *targetPos, unsigned int commandOptions, const Waypoint *way);
	bool rva00450AE9();

protected:
	virtual void onExit(bool a, bool b);
	virtual void xfer(Xfer *xfer);

	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	char m_pad0C[0x20 - 0x0C];
	Rva0049C73AHandler m_20;	// +0x20
	char m_pad24[0x40 - 0x24];
	ObjectID m_40;			// +0x40
	char m_pad44[0x88 - 0x44];
};

class GiveUpgradeUpdate : public SpecialAbilityUpdate
{
public:
	virtual NameKeyType getModuleNameKey() const;
	void GetDeliveryTarget();
	unsigned char rva0049C8E9();

protected:
	virtual void xfer(Xfer *xfer);
	const GiveUpgradeUpdateModuleData *getGiveUpgradeUpdateModuleData() const
	{
		return (const GiveUpgradeUpdateModuleData *)m_moduleData;
	}

	bool m_firstFlag;		// +0x88
	bool m_89;			// +0x89
	unsigned char m_pad8A[2];
	float m_value;			// +0x8C
};

void GiveUpgradeUpdate::GetDeliveryTarget()
{
	ObjectID target = m_40;
	const GiveUpgradeUpdateModuleData *data = getGiveUpgradeUpdateModuleData();
	if (target != INVALID_OBJECT_ID || !data->m_deliverUpgrade)
		return;
	Object *obj = m_object;
	m_89 = true;
	const void *upgrade = ((Rva0026F0F0 *)TheUpgradeCenter)->rva0026F0F0(obj->m_284);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(obj->getPosition(), 100000.0f, 0,
		Rva00261409Filter(obj->getControllingPlayer(), true, 2).link(&Rva0026119DFilter())
			->link(&Rva00261130Filter(upgrade))
			->link(&Rva002611BFFilter(obj)), 1);
	Object *other;
	while ((other = hits.next()) != 0) {
		if (other->m_template->m_118 & 0x00400000)
			continue;
		if (other->testStatus(OBJECT_STATUS_RVA0049C73A_66))
			continue;
		Object *rider = other->rva002931F5(false);
		if (!rider && other->m_78) {
			Object *object = TheGameLogic->findObjectByID(other->m_78);
			if (object && !(object->m_template->m_kindOf & 0x80))
				rider = object;
		}
		if (rider) {
			if (rider->testStatus(OBJECT_STATUS_RVA0049C73A_66) || rider->testStatus(OBJECT_STATUS_RVA0049C73A_2))
				continue;
			rider->setStatus(OBJECT_STATUS_RVA0049C73A_66, true);
		}
		other->setStatus(OBJECT_STATUS_RVA0049C73A_66, true);
		m_20.rva0049C73ASlot0(getGiveUpgradeUpdateModuleData()->m_38, other, 0, 0, 0);
		break;
	}
}

// Donor lead: official BFME1 5cc75ddda6455c338a5068307e587a793f96d6b3,
// game/GameEngine/Source/Common/BfmeConv940.cpp. Its nominal prototype is
// not claimed. Native vtable 0x851220 slot 14 and Ghidra boundary 0x49C8E9/19
// call the existing 0x49C73A helper, then 0x450AE9 with the same receiver,
// and return AL=0. No complete return type or original method name is known.
// 0x450AE9 remains unconverted; this declaration records only observed ABI.
unsigned char GiveUpgradeUpdate::rva0049C8E9()
{
    GetDeliveryTarget();
    ((SpecialAbilityUpdate *)this)->rva00450AE9();
    return 0;
}
