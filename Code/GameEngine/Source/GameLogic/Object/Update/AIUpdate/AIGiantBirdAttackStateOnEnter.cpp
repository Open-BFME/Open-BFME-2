// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii
//
// ?onEnter@AIGiantBirdAttackState@@UAE?AW4StateReturnType@@XZ
// retail 0x003699CA, 1059 bytes: slot 4 of the vtable 0x00C173C0 whose slot-2
// name getter returns "AIGiantBirdAttack" (slot 3 is the rowed xfer
// 0x0036937A, slot 6 the update 0x00369DED). The class name is BFME 1's
// (AIGiantBirdAttackState, its ctor 0x002BE400 passes the same name string).
//
// Structure: WorldBuilder's GiantBirdAIUpdate.cpp body (its 0x00F2E710, line
// 0x37B) supplies the control flow; offsets, vtable slots and callees are read
// from BFME 2's retail body (AI +0x258, dead bit +0x438, AI flags +0x4B8,
// victim ID +0x4C0, rider ID +0x4C4, swoop radius +0x538, attack mode +0x55C,
// contain +0x250, contained-by +0x274, team +0x304). Retail's contained-item
// list query (contain slot 70) has no destructor where WorldBuilder's had one.
//
// ?update@AIGiantBirdAttackState@@UAE?AW4StateReturnType@@XZ
// retail 0x00369DED, 182 bytes: slot 6 of the same vtable. WorldBuilder's
// matching body (0x00F2EFF0) gives the order: dead owner, AI and AI flag bit 3
// fail; a missing or dead victim (AI +0x4C0) succeeds; a ready weapon fires at
// the victim and sets model-condition bit 155 (word +0x11C of the bits at
// +0x10C) through the inline set-and-notify; an out-of-ammo weapon succeeds.
//
// ?onExit@AIGiantBirdAttackState@@UAEXW4StateExitType@@@Z
// retail 0x0036939B, 111 bytes: slot 5 of the same vtable. The base
// State::onExit, then the inverse of the update's bit: condition 155 cleared
// and notified, AI flag bit 5 cleared (rowed 0x0036940A), the current weapon
// reloaded (Weapon::reloadAmmo 0x002CE1E9), the pinned Object::rva0028ACEE with
// the owner's position and 1, and AI +0x558 (set by onEnter) reset.

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include "../../../../Common/GameLogicObjectLookupView.h"

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_28 = 0x28
};

enum ModelConditionFlagType
{
	MODELCONDITION_BFME_06 = 0x06,
	MODELCONDITION_BFME_80 = 0x80,
	MODELCONDITION_BFME_AC = 0xAC
};

enum StateExitType
{
	EXIT_NORMAL = 0
};

enum WeaponStatus
{
	READY_TO_FIRE = 0,
	OUT_OF_AMMO = 3
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Object;
class Team;
class Matrix3D;
class ThingTemplate;

Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);

#define GIANTBIRD_CPP "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp"

#define GIANTBIRD_MAX(a, b) ((a) > (b) ? (a) : (b))

extern GameLogic *TheGameLogic;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

struct CreateMask
{
	UnsignedInt m_bits[4];
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, Bool b);
};
extern ThingFactory *TheThingFactory;

// ThingFactory's template lookup by name (rowed 0x002D06CA).
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

class FXList
{
public:
	Bool rva001E2EF1() const;
	void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, Real primarySpeed,
		const Coord3D *secondary) const;
};

// FXList's static doFXPos (rowed 0x00094C29), expanded in place here.
static __forceinline void giantBirdDoFXPos(const FXList *fx, const Coord3D *primary,
	const Matrix3D *primaryMtx, Real primarySpeed, const Coord3D *secondary)
{
	if (fx && !fx->rva001E2EF1())
		fx->doFXPos(primary, primaryMtx, primarySpeed, secondary);
}

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
};

class WeaponTemplate
{
public:
	Real getWeaponSpeed() const { return m_speed68; }
	const FXList *getFireFX() const { return m_fireFX[0]; }
	Bool getFlag157() const { return m_flag157; }
private:
	unsigned char m_pad000[0x68];
	Real m_speed68; // +0x68
	unsigned char m_pad06C[0xA4 - 0x6C];
	const FXList *m_fireFX[1]; // +0xA4
	unsigned char m_pad0A8[0x157 - 0xA8];
	Bool m_flag157; // +0x157
};

class Weapon
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }
	WeaponStatus getStatus() const;
	void reloadAmmo(const Object *sourceObj);
private:
	void *m_vtbl;
	const WeaponTemplate *m_template; // +4
};

class ModuleData
{
public:
	const AsciiString &getObjectName3C() const { return m_name3C; }
private:
	unsigned char m_pad00[0x3C];
	AsciiString m_name3C; // +0x3C
};

class Module
{
public:
	const ModuleData *getModuleData() const { return m_moduleData; }
private:
	void *m_vtbl;
	const ModuleData *m_moduleData; // +4
};

// What contain slot 31 hands back for the victim's container.
class GiantBirdAttackContainRider
{
public:
	virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03();
	virtual void r04(); virtual void r05(); virtual void r06(); virtual void r07();
	virtual void r08(); virtual void r09(); virtual void r10(); virtual void r11();
	virtual void r12(); virtual void r13();
	virtual void slot14(Object *obj); // +0x38
};

struct GiantBirdAttackItemNode
{
	GiantBirdAttackItemNode *m_next;
	GiantBirdAttackItemNode *m_prev;
	Object *m_object;
};

struct GiantBirdAttackItemList
{
	GiantBirdAttackItemNode *m_head;
};

struct GiantBirdAttackItems
{
	void *m_owner;
	const GiantBirdAttackItemList *m_list;
};

class ContainModuleInterface
{
public:
	virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
	virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
	virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
	virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
	virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
	virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23();
	virtual void c24(); virtual void c25(); virtual void c26(); virtual void c27();
	virtual UnsignedInt getContainMax() const; // +0x70
	virtual void c29(); virtual void c30();
	virtual GiantBirdAttackContainRider *slot31(); // +0x7C
	virtual void c32(); virtual void c33(); virtual void c34(); virtual void c35();
	virtual void c36(); virtual void c37(); virtual void c38();
	virtual void addToContain(Object *obj); // +0x9C
	virtual void c40(); virtual void c41(); virtual void c42(); virtual void c43();
	virtual void c44(); virtual void c45(); virtual void c46(); virtual void c47();
	virtual void c48(); virtual void c49(); virtual void c50(); virtual void c51();
	virtual void c52(); virtual void c53(); virtual void c54(); virtual void c55();
	virtual void c56(); virtual void c57(); virtual void c58(); virtual void c59();
	virtual void c60(); virtual void c61(); virtual void c62(); virtual void c63();
	virtual void c64(); virtual void c65(); virtual void c66(); virtual void c67();
	virtual void c68();
	virtual UnsignedInt getContainCount(Int a) const; // +0x114
	virtual void getContainedItems(GiantBirdAttackItems *items); // +0x118
};

template <int N> class GiantBirdAttackAISlots : public GiantBirdAttackAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class GiantBirdAttackAISlots<0>
{
};

class AIUpdateInterface : public GiantBirdAttackAISlots<98>
{
public:
	virtual AIUpdateInterface *slot98() = 0; // +0x188

	Bool testFlag(Int bit) const { return (m_flags4B8 >> bit) & 1; }
	Real getSwoopRadius() const { return m_swoopRadius538; }
	Object *getCurrentVictim() const;
	Bool findNearestLabeledContactPointOnTarget(Object *target, Coord3D *pointOut,
		const Coord3D *callerPos, Bool skipCollideTest);

	unsigned char m_pad004[0x4B8 - 4];
	UnsignedInt m_flags4B8; // +0x4B8
	unsigned char m_pad4BC[4];
	ObjectID m_victimID4C0; // +0x4C0
	ObjectID m_riderID4C4; // +0x4C4
	unsigned char m_pad4C8[0x538 - 0x4C8];
	Real m_swoopRadius538; // +0x538
	unsigned char m_pad53C[0x558 - 0x53C];
	Bool m_entered558; // +0x558
	unsigned char m_pad559[3];
	Int m_mode55C; // +0x55C
};

// The AI flag-bit setter chain (0x0036940A clears or sets AI flag bit 5).
class Rva0036748E
{
public:
	void rva0036940A(bool flag);
};

class BfmeVec3EJ;
class Gen_000E5A50
{
public:
	Real bfmeDistanceSquared(const BfmeVec3EJ *pos) const;
};

// The owner's model-condition bits at +0x10C (bit 155 is word +0x11C).
class GiantBirdAttackConditionBits
{
public:
	UnsignedInt test(Int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(Int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(Int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	UnsignedInt m_words[19];
};

class Thing
{
public:
	const Matrix3D *getTransformMatrix() const { return (const Matrix3D *)m_transform; }
	Drawable *getDrawable() const;
	void setTransformMatrix(const Matrix3D *mx);
private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +4
	unsigned char m_transform[0x30]; // +8
};

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }
	Bool isDead() const { return (m_privateStatus & 1) != 0; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Object *getContainedBy() const { return m_containedBy; }
	ContainModuleInterface *getContain() const { return m_contain; }
	const Coord3D *getPosition() const { return &m_position; }
	Team *getTeam() const { return m_team; }
	Real getDistanceSquared(const Coord3D *pos) const
	{
		return ((const Gen_000E5A50 *)this)->bfmeDistanceSquared((const BfmeVec3EJ *)pos);
	}

	Bool testStatus(ObjectStatusTypes bit) const;
	const Weapon *getCurrentWeapon(WeaponSlotType *slot = 0) const;
	Bool getWorldspaceBestContactPoint(Coord3D *pointOut, const Coord3D *callerPos,
		const char *preferredPoint, Int pref, Int seed, Bool skipCollideTest) const;
	void rva0028FC8F();
	void fireCurrentWeapon(const Coord3D *pos);
	void fireCurrentWeapon(Object *victim, Int id);
	void setSpecialModelConditionState(ModelConditionFlagType flag, UnsignedInt frames);
	void rva0028AE6D();
	__forceinline void setModelConditionBit(Int bit)
	{
		if (m_conditionBits.test(bit) == 0)
		{
			m_conditionBits.set(bit);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionBit(Int bit)
	{
		if (m_conditionBits.test(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
	void rva0028ACEE(const Coord3D *pos, Int value);
protected:
	Module *findModule(NameKeyType key) const;
	friend class AIGiantBirdAttackState;

private:
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	GiantBirdAttackConditionBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x250 - (0x10C + sizeof(GiantBirdAttackConditionBits))];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[4];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
	unsigned char m_pad278[0x304 - 0x278];
	Team *m_team; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_privateStatus; // +0x438
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
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
	virtual StateReturnType update();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 4];
	StateMachine *m_machine; // +0x18
};

class AIGiantBirdAttackState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[4];
	ObjectID m_targetID; // +0x20
};

//-------------------------------------------------------------------------------------------------
StateReturnType AIGiantBirdAttackState::onEnter()
{
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAI();
	if (ai == 0)
		return STATE_FAILURE;

	ai->m_entered558 = true;
	if (owner->isDead())
		return STATE_FAILURE;

	if (ai->testFlag(3))
		return STATE_CONTINUE;

	if (m_targetID == INVALID_OBJECT_ID)
	{
		owner->rva0028FC8F();
		owner->fireCurrentWeapon(owner->getPosition());
		return STATE_SUCCESS;
	}

	Object *victim = TheGameLogic->findObjectByID(ai->m_victimID4C0);
	if (victim == 0 || victim->isDead())
		return STATE_SUCCESS;

	Coord3D pos;
	if (!ai->findNearestLabeledContactPointOnTarget(victim, &pos, owner->getPosition(), false))
	{
		victim->getWorldspaceBestContactPoint(&pos, owner->getPosition(), 0, 1,
			GetGameLogicRandomValue(0, 12345678, GIANTBIRD_CPP, 0x37B), false);
	}

	Real range = GIANTBIRD_MAX(8.5f, ai->getSwoopRadius() * 3.0f);
	if (owner->getDistanceSquared(&pos) > range * range)
		return STATE_FAILURE;

	if (ai->testFlag(4))
	{
		Object *container = victim->getContainedBy();
		if (container != 0)
		{
			ContainModuleInterface *victimContain = container->getContain();
			if (victimContain != 0)
			{
				GiantBirdAttackContainRider *rider = victimContain->slot31();
				if (rider != 0)
					rider->slot14(victim);
			}
		}

		ContainModuleInterface *contain = owner->getContain();
		GiantBirdAttackItems items;
		contain->getContainedItems(&items);
		Int count = 0;
		GiantBirdAttackItemNode *head = items.m_list->m_head;
		for (GiantBirdAttackItemNode *node = head->m_next; node != head; )
		{
			Object *item = node->m_object;
			node = node->m_next;
			if (!item->testStatus(OBJECT_STATUS_BFME_28))
			{
				++count;
				break;
			}
		}
		if (count == 0)
		{
			contain->addToContain(victim);
			ai->m_riderID4C4 = victim->getID();
		}

		if (victim->getContainedBy() == owner)
		{
			const Weapon *weapon = owner->getCurrentWeapon();
			if (weapon != 0 && weapon->getTemplate() != 0 && weapon->getTemplate()->getFlag157())
			{
				const FXList *fx = weapon->getTemplate()->getFireFX();
				Drawable *draw = owner->getDrawable();
				if (fx != 0 && draw != 0)
				{
					Real speed = weapon->getTemplate()->getWeaponSpeed();
					const Matrix3D *mtx = draw->getTransformMatrix();
					giantBirdDoFXPos(fx, victim->getPosition(), mtx, speed, victim->getPosition());
				}
			}
			ai->m_flags4B8 |= 0x40;
			return STATE_SUCCESS;
		}

		owner->rva0028FC8F();
		owner->fireCurrentWeapon(victim->getPosition());
		return STATE_FAILURE;
	}

	owner->rva0028FC8F();
	owner->fireCurrentWeapon(victim, victim->getID());

	if (victim->isDead() && ai->testFlag(5))
	{
		ai->m_flags4B8 &= ~0x20;
		ContainModuleInterface *contain = owner->getContain();
		if (contain != 0 && contain->getContainCount(0) < contain->getContainMax())
		{
			AsciiString name("");
			static NameKeyType key = TheNameKeyGenerator->nameToKey("CreateObjectDie");
			Module *module = victim->findModule(key);
			if (module != 0)
				name = module->getModuleData()->getObjectName3C();
			const ThingTemplate *tmplate =
				(const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&name);
			if (tmplate != 0)
			{
				CreateMask mask;
				memset(&mask, 0, sizeof(mask));
				Object *created = TheThingFactory->newObject(tmplate, victim->getTeam(), &mask, false);
				if (created != 0)
				{
					created->setTransformMatrix(owner->getTransformMatrix());
					contain->addToContain(created);
					ai->m_flags4B8 |= 0x40;
					ai->m_riderID4C4 = created->getID();
				}
			}
		}
	}
	else
	{
		AIUpdateInterface *victimAI = victim->getAI() ? victim->getAI()->slot98() : 0;
		if (victimAI != 0)
		{
			victim->setSpecialModelConditionState(MODELCONDITION_BFME_AC, 5);
			victim->setSpecialModelConditionState(MODELCONDITION_BFME_80, 5);
			if (victimAI->getCurrentVictim() == owner && ai->m_mode55C == 1 &&
				victimAI->m_mode55C == 0)
			{
				victim->fireCurrentWeapon(owner, owner->getID());
				victim->setSpecialModelConditionState(MODELCONDITION_BFME_06, 5);
			}
		}
	}
	return STATE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------
StateReturnType AIGiantBirdAttackState::update()
{
	Object *owner = getMachineOwner();
	if (owner->isDead())
		return STATE_FAILURE;

	AIUpdateInterface *ai = owner->getAI();
	if (ai == 0)
		return STATE_FAILURE;
	if (!ai->testFlag(3))
		return STATE_FAILURE;

	Object *victim = TheGameLogic->findObjectByID(ai->m_victimID4C0);
	if (victim == 0 || victim->isDead())
		return STATE_SUCCESS;

	const Weapon *weapon = owner->getCurrentWeapon();
	if (weapon == 0)
		return STATE_FAILURE;

	if (weapon->getStatus() == READY_TO_FIRE)
	{
		owner->rva0028FC8F();
		owner->fireCurrentWeapon(victim, victim->getID());
		owner->setModelConditionBit(155);
	}
	else if (weapon->getStatus() == OUT_OF_AMMO)
	{
		return STATE_SUCCESS;
	}
	return STATE_CONTINUE;
}

//-------------------------------------------------------------------------------------------------
void AIGiantBirdAttackState::onExit(StateExitType status)
{
	State::onExit(status);
	Object *owner = getMachineOwner();
	owner->clearModelConditionBit(155);
	AIUpdateInterface *ai = owner->getAI();
	if (ai)
		reinterpret_cast<Rva0036748E *>(ai)->rva0036940A(false);

	Weapon *weapon = const_cast<Weapon *>(owner->getCurrentWeapon());
	if (weapon)
		weapon->reloadAmmo(owner);

	owner->rva0028ACEE(owner->getPosition(), 1);
	if (ai)
		ai->m_entered558 = false;
}
