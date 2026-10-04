// ?rva0049C8E9@GiveUpgradeUpdate@@QAEEXZ
// partial score=0.7894736842 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
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

// vftable 0x00C51150, allow 0x00261130: +0x08 an upgrade.
class Rva00261130Filter : public Rva000421C8
{
public:
	Rva00261130Filter(const void *upgrade) : m_upgrade(upgrade) {}
	virtual bool allow(Object *obj);
	const void *m_upgrade;
};

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags, +0x0C whether a hit allows.
class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

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

// TheUpgradeCenter's lookup: the first upgrade whose bit the mask has.
struct Rva0026F0F0
{
	void *rva0026F0F0(const void *mask);	// 0x0026F0F0
};
extern Rva0026F0F0 *TheUpgradeCenter;

enum ObjectID
{
	INVALID_ID = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA0049C73A_2 = 2,
	OBJECT_STATUS_RVA0049C73A_66 = 0x42
};

class ThingTemplate
{
public:
	char m_pad000[0x108];
	unsigned m_108;		// +0x108 (bit 7 tested)
	char m_pad10C[0x118 - 0x10C];
	unsigned m_118;		// +0x118 (bit 22 tested)
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	bool testStatus(ObjectStatusTypes bit) const;	// 0x0004E536
	void setStatus(ObjectStatusTypes bit, bool flag);	// 0x0023DB0E
	Object *rva002931F5(bool flag);		// 0x002931F5
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;				// +0x38
	char m_pad044[0x78 - 0x44];
	ObjectID m_78;				// +0x78
	char m_pad07C[0x284 - 0x7C];
	unsigned m_284[32];			// +0x284 the upgrade mask
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

struct GiveUpgradeUpdateModuleData
{
	char m_pad00[0x38];
	int m_38;		// +0x38
	char m_pad3C[0xE0 - 0x3C];
	bool m_E0;		// +0xE0
};

// What sits at +0x20: slot 0 takes the data's +0x38 and the object.
class Rva0049C73AHandler
{
public:
	virtual void rva0049C73ASlot0(int what, Object *obj, int a, int b, int c);
};

class GiveUpgradeUpdate
{
public:
	void rva0049C73A();
	unsigned char rva0049C8E9();
	void rva00450AE9CallView();
private:
	const GiveUpgradeUpdateModuleData *getGiveUpgradeUpdateModuleData() const
	{
		return (const GiveUpgradeUpdateModuleData *)m_moduleData;
	}
	void *m_vtable;
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	char m_pad0C[0x20 - 0x0C];
	Rva0049C73AHandler m_20;	// +0x20
	char m_pad24[0x40 - 0x24];
	ObjectID m_40;			// +0x40
	char m_pad44[0x89 - 0x44];
	bool m_89;			// +0x89
};

void GiveUpgradeUpdate::rva0049C73A()
{
	ObjectID target = m_40;
	const GiveUpgradeUpdateModuleData *data = getGiveUpgradeUpdateModuleData();
	if (target != INVALID_ID || !data->m_E0)
		return;
	Object *obj = m_object;
	m_89 = true;
	const void *upgrade = TheUpgradeCenter->rva0026F0F0(obj->m_284);
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
			Object *p = TheGameLogic->findObjectByID(other->m_78);
			if (p && !(p->m_template->m_108 & 0x80))
				rider = p;
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
    rva0049C73A();
    rva00450AE9CallView();
    return 0;
}
