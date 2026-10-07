// cl: /DNDEBUG /MD /GX
//
// RadiateFearUpdate::update (0x0049C21E, slot 0 of its UpdateModuleInterface
// vftable 0x00850FB0; ctor 0x0049C106 installs it). Asleep for good once the
// object is effectively dead or its upgrade (the UpgradeMux at +0x20, slot 0)
// is not active. With any of the module data's +0x10/+0x11/+0x12 flags,
// every object other than this one the controlling player's relationship
// flag 4 accepts within the data's +0x14 radius (BFME2's partition filter
// chain, the view AIStructureCreepTactic.cpp documents) that the data's
// +0x1C object filter accepts gets 0x0028EC68 (6, 4 and 5 respectively;
// this object; the data's +0x18). Sleeps the +0x18 delay plus ID mod 5.
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

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
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

class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);	// 0x00362437
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	void rva0028EC68(int a, void *b, int c);	// 0x0028EC68
	void applyFrom(int a, Object *source, const int &c) { rva0028EC68(a, source, c); }
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	const Coord3D *getPosition() const { return &m_pos; }
	int getID() const { return m_74; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x74 - 0x44];
	int m_74;		// +0x74 the ID
	char m_pad078[0x438 - 0x78];
	unsigned char m_438;	// +0x438
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	Object *getObject() const { return m_object; }
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
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
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	char m_pad14[0x20 - 0x14];
};
class UpgradeMux
{
public:
	virtual bool rvaUpgradeMuxSlot0() const = 0;
private:
	unsigned int m_executed;
};

struct RadiateFearUpdateModuleData
{
	unsigned char m_pad00[0x10];
	bool m_10;		// +0x10
	bool m_11;		// +0x11
	bool m_12;		// +0x12
	float m_14;		// +0x14 the radius
	int m_18;		// +0x18 the delay
	Rva2225E0Filter m_1C;	// +0x1C the object filter
};

class RadiateFearUpdate : public UpdateModule, public UpgradeMux
{
public:
	virtual UpdateSleepTime update();
private:
	const RadiateFearUpdateModuleData *getRadiateFearUpdateModuleData() const
	{
		return (const RadiateFearUpdateModuleData *)m_moduleData;
	}
};

UpdateSleepTime RadiateFearUpdate::update()
{
	Object *obj = m_object;
	const RadiateFearUpdateModuleData *data = getRadiateFearUpdateModuleData();
	if (obj->isEffectivelyDead())
		return UPDATE_SLEEP_FOREVER;
	if (!rvaUpgradeMuxSlot0())
		return UPDATE_SLEEP_FOREVER;
	if (data->m_10 || data->m_11 || data->m_12) {
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(getObject()->getPosition(), data->m_14, 0,
			Rva00261409Filter(m_object->getControllingPlayer(), true, 4).link(&Rva002611BFFilter(m_object)), 0);
		Object *other;
		while ((other = hits.next()) != 0) {
			if (((Rva2225E0Filter &)data->m_1C).accepts(other, obj->getControllingPlayer())) {
				if (data->m_10)
					other->applyFrom(6, m_object, data->m_18);
				if (data->m_11)
					other->applyFrom(4, m_object, data->m_18);
				if (data->m_12)
					other->applyFrom(5, m_object, data->m_18);
			}
		}
	}
	return (UpdateSleepTime)(obj->getID() % 5 + data->m_18);
}
