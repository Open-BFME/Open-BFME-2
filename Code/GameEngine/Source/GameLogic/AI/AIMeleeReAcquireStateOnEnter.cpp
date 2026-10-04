// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ?onEnter@AIMeleeReAcquireState@@UAE?AW4StateReturnType@@XZ, retail
// 0x0034BA9E: slot 4 of the state vftable 0x00C11588 whose name slot
// 0x0033F648 returns "AIMeleeReAcquireState" (slot 5 the base onExit
// 0x0047A69C). BFME1's AIMeleeReAcquireState::update (reference/open-bfme-1,
// AIMeleeReAcquireState_update.cpp) is the donor: BFME2 waits a quarter of
// the logic rate (0x00DBA4E4) since the last acquire, keeps a still-valid
// goal object, else picks the closest object through BFME2's partition
// filter chain (the view AIStructureCreepTactic.cpp documents) with a KindOf
// mask filter (bits 0x59 0x82 0x36 rejected) at its head, and hands the
// result to the machine and the AI (friend_setGoalObject 0x00262B0F).
// State layout: +0x18 the machine, +0x20 the last acquire frame.

class Object;
class Player;
class Weapon;

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

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// vftable 0x00BF8FE4, allow 0x0026109D; the out-of-line ctor 0x00261058.
class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);	// 0x00261058
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

// vftable 0x00C07160, allow 0x00261246: +0x08 and +0x09 two flags (Zero
// Hour's PartitionFilterInsignificantBuildings).
class Rva00261246Filter : public Rva000421C8
{
public:
	Rva00261246Filter(bool allowNonBuildings, bool allowInsignificant)
		: m_allowNonBuildings(allowNonBuildings), m_allowInsignificant(allowInsignificant) {}
	virtual bool allow(Object *obj);
	bool m_allowNonBuildings;
	bool m_allowInsignificant;
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

// vftable 0x00BF8FF0: +0x08 the object, +0x0C whether its controlling
// player's +0x5C is 1; the out-of-line ctor 0x002611F2.
class Rva002611F2 : public Rva000421C8
{
public:
	Rva002611F2(Object *obj);	// 0x002611F2
	virtual bool allow(Object *obj);
	Object *m_obj;
	bool m_flag;
};

// vftable 0x00C122F0, allow 0x00341C54, slot 2 0x00341C30: +0x08 the
// owner, +0x0C its weapon.
class Rva00341C54Filter : public Rva000421C8
{
public:
	Rva00341C54Filter(Object *obj, Weapon *weapon) : m_obj(obj), m_weapon(weapon) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Object *m_obj;
	Weapon *m_weapon;
};

// The 224-bit KindOf mask.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// The three-bit mask builder (first argument unused) over 28 bytes.
class Rva002618A2
{
public:
	Rva002618A2 *rva002618A2(int unused, int b1, int b2, int b3) throw();	// 0x002618A2
	unsigned m_words[7];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum StateExitType
{
	EXIT_NORMAL = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_IS_ATTACKING = 0x1C,
	OBJECT_STATUS_26 = 0x26
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

struct TAiData
{
	char m_pad00[0x94];
	float m_meleeAcquireRadius;	// +0x94
};

class AI
{
public:
	char m_pad00[0x18];
	TAiData *m_aiData;	// +0x18
	const TAiData *getAiData() const { return m_aiData; }
};
extern AI *TheAI;

class GameLogic
{
public:
	unsigned getFrame() const { return m_frame; }
	char m_pad00[0x40];
	unsigned m_frame;	// +0x40
};
extern GameLogic *TheGameLogic;

extern int g_Va00DBA4E4;
#define LogicFramesPerSecond g_Va00DBA4E4

class AIUpdateInterface
{
public:
	void friend_setGoalObject(Object *obj);	// 0x00262B0F
};

class Object
{
public:
	void setStatus(ObjectStatusTypes bit, bool set);	// 0x0023DB0E
	bool testStatus(ObjectStatusTypes bit) const;	// 0x0004E536
	Weapon *getCurrentWeapon(WeaponSlotType *slot);	// 0x0028AEBD
	Player *getControllingPlayer() const;	// 0x0028AFA9
	bool rva002943B2(const Player *player);	// 0x002943B2
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	AIUpdateInterface *getAI() const { return m_ai; }
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x258 - 0x44];
	AIUpdateInterface *m_ai;	// +0x258
	char m_pad25C[0x274 - 0x25C];
	int m_274;			// +0x274
	char m_pad278[0x438 - 0x278];
	unsigned char m_438;		// +0x438 (bit 0: effectively dead)
};

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void s04();
	virtual void s08();
	virtual void s0C();
	virtual void s10();
	virtual void s14();
	virtual void s18();
	virtual void s1C();
	virtual void s20();
	virtual void s24();
	virtual void s28();
	virtual void s2C();
	virtual void s30();
	virtual void s34();
	virtual void setGoalObject(const Object *obj);	// slot 14
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();	// 0x004D7726
	char m_pad04[0x14 - 0x04];
	Object *m_owner;	// +0x14
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	char m_pad04[0x18 - 0x04];
	StateMachine *m_machine;	// +0x18
};

class AIMeleeReAcquireState : public State
{
public:
	virtual StateReturnType onEnter();
private:
	char m_pad1C[0x20 - 0x1C];
	unsigned m_lastAcquireFrame;	// +0x20
};

StateReturnType AIMeleeReAcquireState::onEnter()
{
	if (TheGameLogic->getFrame() - m_lastAcquireFrame < (unsigned)(LogicFramesPerSecond / 4))
		return STATE_FAILURE;

	Object *owner = getMachineOwner();
	owner->setStatus(OBJECT_STATUS_IS_ATTACKING, false);
	Weapon *weapon;
	if ((owner->testStatus(OBJECT_STATUS_26) && owner->m_274 != 0)
		|| (weapon = owner->getCurrentWeapon(0)) == 0 || !getMachine())
		return STATE_FAILURE;

	Object *goal = getMachine()->getGoalObject();
	if (goal && !goal->isEffectivelyDead() && !goal->rva002943B2(owner->getControllingPlayer())) {
		getMachine()->setGoalObject(goal);
		owner->getAI()->friend_setGoalObject(goal);
		m_lastAcquireFrame = TheGameLogic->getFrame();
		return STATE_SUCCESS;
	}

	Object *target;
	{
		Coord3D pos;
		pos.x = owner->getPosition()->x;
		pos.y = owner->getPosition()->y;
		pos.z = owner->getPosition()->z;
		Rva002618A2 kinds;
		target = ThePartitionManager->getClosestObject(&pos, TheAI->getAiData()->m_meleeAcquireRadius * 2.0f, 1,
			Rva0004584D(*(const BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype,
				*(const BfmeFixedStorage0004543D *)kinds.rva002618A2(0, 0x59, 0x82, 0x36))
				.link(&Rva00341C54Filter(owner, weapon))->link(&Rva002611F2(owner))
				->link(&Rva00260FD0Filter(owner, 2, 0))->link(&Rva00261246Filter(true, false))
				->link(&Rva00261058(owner, false)));
	}
	getMachine()->setGoalObject(target);
	owner->getAI()->friend_setGoalObject(target);
	m_lastAcquireFrame = TheGameLogic->getFrame();
	return STATE_SUCCESS;
}
