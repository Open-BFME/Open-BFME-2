// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// CallHelpOnDamage::onDamage (0x004BB547, slot 0 of its DamageModuleInterface
// vftable 0x00859FD0, the +0x10 subobject; deleting dtor 0x004BB4B5 heads the
// primary vftable). Field names are the module data's INI table at 0x00859F70.
// On a listed damage type once CallDelay has passed: every object of the
// owner's player (0x00260E2A) that ValidObjects (0x002614EC) and 0x0026185B
// accept within CallRadius (BFME2's partition filter chain, the view
// AIStructureCreepTactic.cpp documents) gets AI command 0x003C7653 at the
// attacker (MoveToAttacker, when 0x00049DC5 finds it) or the owner.
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

// vftable 0x00BFAD04, allow 0x00260E2A, slot 2 0x00260E1E: +0x08 a player.
class Rva00260E2AFilter : public Rva000421C8
{
public:
	Rva00260E2AFilter(Player *player) : m_player(player) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
};

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

// vftable 0x00C59EA8, allow 0x0026185B: +0x08 a flag.
class Rva0026185BFilter : public Rva000421C8
{
public:
	Rva0026185BFilter(bool flag) : m_flag(flag) {}
	virtual bool allow(Object *obj);
	bool m_flag;
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

enum ObjectID
{
	INVALID_ID = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 1
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const void *parms) = 0;
	void rva003C7653(Object *obj, CommandSourceType cmdSource);	// 0x003C7653
};

// What precedes the AICommandInterface subobject (+0x20).
class Rva004BB547AIBase
{
public:
	virtual void rva004BB547AIBaseAnchor();
private:
	char m_pad04[0x1C];
};

class AIUpdateInterface : public Rva004BB547AIBase, public AICommandInterface
{
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	const Coord3D *getPosition() const { return &m_pos; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	unsigned char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
	unsigned char m_pad044[0x258 - 0x44];
	AIUpdateInterface *m_ai;	// +0x258
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
	unsigned getFrame() const { return m_frame; }
	char m_pad00[0x40];
	unsigned m_frame;	// +0x40
};
extern GameLogic *TheGameLogic;

struct DamageInfo
{
	char m_pad00[0x08];
	ObjectID m_sourceID;	// +0x08
	char m_pad0C[0x10 - 0x0C];
	int m_damageType;	// +0x10
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
class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo) = 0;
};
class DamageModule : public BehaviorModule, public BehaviorModuleInterface, public DamageModuleInterface
{
};

struct CallHelpOnDamageModuleData
{
	unsigned char m_pad00[0x08];
	unsigned m_damageTypes;		// +0x08 DamageTypes
	float m_callRadius;		// +0x0C CallRadius
	unsigned m_callDelay;		// +0x10 CallDelay
	bool m_moveToAttacker;		// +0x14 MoveToAttacker
	struct { int m_value; } m_validObjects;	// +0x18 ValidObjects
};

class CallHelpOnDamage : public DamageModule
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
private:
	const CallHelpOnDamageModuleData *getCallHelpOnDamageModuleData() const
	{
		return (const CallHelpOnDamageModuleData *)m_moduleData;
	}
	unsigned m_nextCallFrame;	// +0x14
};

void CallHelpOnDamage::onDamage(DamageInfo *damageInfo)
{
	const CallHelpOnDamageModuleData *data = getCallHelpOnDamageModuleData();
	if (!(data->m_damageTypes & (1 << (damageInfo->m_damageType - 1))))
		return;
	unsigned now = TheGameLogic->getFrame();
	if (now <= m_nextCallFrame)
		return;

	Object *target;
	if (!data->m_moveToAttacker || (target = TheGameLogic->findObjectByID(damageInfo->m_sourceID)) == 0)
		target = m_object;

	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(getObject()->getPosition(), data->m_callRadius, 1,
		Rva00260E2AFilter(m_object->getControllingPlayer())
			.link(&Rva002614ECFilter(&data->m_validObjects, m_object->getControllingPlayer(), true))
			->link(&Rva0026185BFilter(true)), 0);
	Object *other;
	while ((other = hits.next()) != 0) {
		AIUpdateInterface *ai = other->getAIUpdateInterface();
		if (ai)
			ai->rva003C7653(target, CMD_FROM_PLAYER);
	}
	m_nextCallFrame = now + data->m_callDelay;
}
