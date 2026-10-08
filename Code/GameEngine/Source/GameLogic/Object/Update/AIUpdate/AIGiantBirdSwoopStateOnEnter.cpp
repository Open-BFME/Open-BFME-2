// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX
//
// ?onEnter@AIGiantBirdSwoopState@@UAE?AW4StateReturnType@@XZ
// retail 0x0036BDF2, 1039 bytes: slot 4 of the AIGiantBirdSwoopState vtable
// 0x00C17360 (slot 2 returns "AIGiantBirdSwoopState", slot 5 is the rowed
// onExit 0x003692ED).
//
// Donor: BFME 1 AIGiantBirdSwoopState::onEnter (open-bfme-1 ba7ddda7e,
// AIGiantBirdSwoopStateOnEnter.cpp, its 0x002C3020) supplies the control
// flow; GiantBirdAIUpdate.cpp is the retail file literal (lines 0x23F and
// 0x254). Offsets below are read from BFME 2's body: AI +0x258, dead bit
// +0x438, AI flags +0x4B8, victim ID +0x4C0, continue byte +0x4EC, the
// secondary target ID +0x554 and the attack mode +0x55C.
//
// BFME 2 differences (target evidence): the goal-object rejection asks
// Object::isKindOf(0x48); the KindOf 109 / 142 / 11 tests are inline template
// words; setCurrentVictim moves ahead of the mode store; the victim AI's
// partner comes from AI slot 98 (+0x188); and the weapon template's bone
// query 0x002CAAFA tries first, keeping its point unless it lies at or below
// the ground.
//
// ?update@AIGiantBirdSwoopState@@UAE?AW4StateReturnType@@XZ
// retail 0x0036C201, 567 bytes: slot 6 of the same vtable. Donor: BFME 1
// update (its 0x002C3550 banked attempt) supplies the shape; BFME 2 shrinks
// the swoop radius at AI +0x538 by m_scale (scaled by 0.8 each frame), calls
// the target helper below, then either runs the AI move query 0x00368B51 or
// the stationary-victim check (0x002907A1, victim AI getter 0x002627E8,
// isKindOf 0x9B) before moving to m_pos through 0x00368C7A. Within half the
// bounding radius the helper refreshes the goal; inside the anchor (+0x544)
// range or with the +0x534 flag set it snaps to the anchor and succeeds.
//
// ?rva0036C438@AIGiantBirdSwoopState@@QAEX_N@Z
// retail 0x0036C438, 603 bytes: the swoop target helper called only from
// update (twice); the name is invented, the body is BFME 2 evidence only.

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

enum WeaponChoiceCriteria
{
	PREFER_BEST_OVERALL = 0,
	PREFER_MOST_DAMAGE = 2
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum KindOfType
{
	KINDOF_BFME_48 = 0x48,
	KINDOF_BFME_9B = 0x9B
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_3C = 0x3C,
	OBJECT_STATUS_BFME_43 = 0x43
};

class Object;
class Weapon;

Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);

#define GIANTBIRD_CPP "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp"

// The rowed GameLogicRandom-style move helpers' per-mode masks.
extern unsigned char g_00E01EC0[4];
extern unsigned char g_00E01EC8[4];
extern unsigned char g_00E01ED0[4];

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &other);
	virtual ~GeometryInfo();
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
private:
	unsigned char m_pad04[0x10 - 4];
	Real m_boundingCircleRadius; // +0x10
	unsigned char m_pad14[0x5C - 0x14];
};

class BfmeBoundaryGeometry3D
{
public:
	Real bfmeZDeltaToCenter(void) const;
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const;
};
extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;

class ThingTemplate
{
public:
	UnsignedInt testKindOf(Int word, UnsignedInt mask) const { return m_kindOf[word] & mask; }
private:
	unsigned char m_pad000[0x108];
	UnsignedInt m_kindOf[4]; // +0x108
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
	virtual void c28(); virtual void c29(); virtual void c30();
	virtual void *slot31(); // +0x7C
};

template <int N> class GiantBirdSwoopAISlots : public GiantBirdSwoopAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class GiantBirdSwoopAISlots<0>
{
};

struct GiantBirdSwoopAI1F0
{
	unsigned char m_pad00[0x48];
	Real m_height48; // +0x48
};

class AIUpdateInterface : public GiantBirdSwoopAISlots<98>
{
public:
	virtual AIUpdateInterface *slot98() = 0; // +0x188
	virtual void s099() = 0; virtual void s100() = 0; virtual void s101() = 0;
	virtual void s102() = 0; virtual void s103() = 0; virtual void s104() = 0;
	virtual void s105() = 0; virtual void s106() = 0; virtual void s107() = 0;
	virtual void s108() = 0; virtual void s109() = 0; virtual void s110() = 0;
	virtual void s111() = 0; virtual void s112() = 0; virtual void s113() = 0;
	virtual void s114() = 0; virtual void s115() = 0; virtual void s116() = 0;
	virtual void s117() = 0; virtual void s118() = 0; virtual void s119() = 0;
	virtual void s120() = 0; virtual void s121() = 0; virtual void s122() = 0;
	virtual void s123() = 0; virtual void s124() = 0; virtual void s125() = 0;
	virtual void s126() = 0; virtual void s127() = 0; virtual void s128() = 0;
	virtual void s129() = 0; virtual void s130() = 0; virtual void s131() = 0;
	virtual void s132() = 0; virtual void s133() = 0; virtual void s134() = 0;
	virtual void s135() = 0; virtual void s136() = 0; virtual void s137() = 0;
	virtual void s138() = 0; virtual void s139() = 0; virtual void s140() = 0;
	virtual void s141() = 0;
	virtual void setLocomotorSet(Int set) = 0; // slot 142, +0x238

	Bool testFlag(Int bit) const { return (m_flags4B8 >> bit) & 1; }
	void setCurrentVictim(const Object *victim);
	Object *getCurrentVictim() const;
	Bool findNearestLabeledContactPointOnTarget(Object *target, Coord3D *pointOut,
		const Coord3D *callerPos, Bool skipCollideTest);

	unsigned char m_pad004[0x1F0 - 4];
	GiantBirdSwoopAI1F0 *m_1F0; // +0x1F0
	unsigned char m_pad1F4[0x4B8 - 0x1F4];
	UnsignedInt m_flags4B8; // +0x4B8
	unsigned char m_pad4BC[4];
	ObjectID m_victimID4C0; // +0x4C0
	unsigned char m_pad4C4[0x4EC - 0x4C4];
	unsigned char m_continue4EC; // +0x4EC
	unsigned char m_pad4ED[0x534 - 0x4ED];
	unsigned char m_flag534; // +0x534
	unsigned char m_pad535[3];
	Real m_swoopRadius538; // +0x538
	unsigned char m_pad53C[0x544 - 0x53C];
	Coord3D m_anchor544; // +0x544
	unsigned char m_pad550[4];
	ObjectID m_targetID554; // +0x554
	unsigned char m_pad558[4];
	Int m_mode55C; // +0x55C
};

// The rowed GiantBird AI move helper (receiver is the AI).
class Rva00368C7A
{
public:
	Int rva00368B51(Real distance, Bool flag);
	void rva00368C7A(Real distance, const Coord3D *position, Int a);
	void rva003681F2(const Coord3D *position, const unsigned char *mask, Int a, Int b);
};

// Object +0x10C model condition words (ModelConditionFlags), as in GiantBirdStateSlots.cpp.
class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	Bool isDead() const { return (m_privateStatus & 1) != 0; }
	Bool testStatusBit38() const { return (m_status94 >> 6) & 1; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Object *getContainedBy() const { return m_containedBy; }
	ContainModuleInterface *getContain() const { return m_contain; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	const Coord3D *getPosition() const { return &m_position; }

	Bool isKindOf(KindOfType kindOf) const;
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool chooseBestWeaponForTarget(const Object *target, WeaponChoiceCriteria criteria,
		CommandSourceType cmdSource);
	const Weapon *getCurrentWeapon(WeaponSlotType *slot = 0) const;
	Object *adjustVictim(Object *owner, Int a, Int b);
	Bool getWorldspaceBestContactPoint(Coord3D *pointOut, const Coord3D *callerPos,
		const char *preferredPoint, Int pref, Int seed, Bool skipCollideTest) const;
	Bool rva002907A1();
	void rva0028AE6D();
	__forceinline void clearModelConditionBit(int bit)
	{
		if (m_conditionBits.test(bit) != 0)
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
	__forceinline void setModelConditionBit(int bit)
	{
		if (m_conditionBits.test(bit) == 0)
		{
			m_conditionBits.set(bit);
			rva0028AE6D();
		}
	}


private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +4
	unsigned char m_pad008[0x38 - 8];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x94 - 0x78];
	UnsignedInt m_status94; // +0x94
	unsigned char m_pad098[0xA8 - 0x98];
	GeometryInfo m_geometryInfo; // +0xA8
	unsigned char m_pad104[0x10C - 0x104];
	Rva0010CBits m_conditionBits; // +0x10C
	unsigned char m_pad158[0x250 - (0x10C + sizeof(Rva0010CBits))];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[4];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
	unsigned char m_pad278[0x438 - 0x278];
	unsigned char m_privateStatus; // +0x438
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class BfmeVec3EJ;
class Gen_000E5A50
{
public:
	Real bfmeDistanceSquared(const BfmeVec3EJ *pos) const;
};

class Rva002627E8
{
public:
	Real rva002627E8() const;
};

class Rva002CAAFA
{
public:
	Bool rva002CAAFA(Object *victim, Coord3D *pos);
};

class WeaponTemplate
{
public:
	Int getClipSize() const { return m_clipSizeE4; }
private:
	unsigned char m_pad000[0xE4];
	Int m_clipSizeE4; // +0xE4
};

class Weapon
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }
	Bool rva002C969D(const void *a, Int b);
private:
	void *m_vtbl;
	const WeaponTemplate *m_template; // +4
};

class StateMachine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void setGoalObject(const Object *object); // +0x38

	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
	void setGoalPosition(const Coord3D *pos);

private:
	unsigned char m_pad04[0x14 - 4];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit();
	virtual StateReturnType update();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	StateMachine *getMachine() const { return m_machine; }
	unsigned char m_pad04[0x18 - 4];
	StateMachine *m_machine; // +0x18
};

class AIGiantBirdSwoopState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
	void rva0036C438(Bool force);
private:
	unsigned char m_pad1C[4];
	ObjectID m_targetID; // +0x20
	Coord3D m_pos; // +0x24
	Bool m_enabled; // +0x30
	unsigned char m_pad31[7];
	Real m_scale; // +0x38
};

//-------------------------------------------------------------------------------------------------
StateReturnType AIGiantBirdSwoopState::onEnter()
{
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAI();
	Object *victim = 0;
	if (ai == 0 || owner->isDead())
		return STATE_FAILURE;

	ai->m_flags4B8 &= ~0x38;
	ai->m_victimID4C0 = INVALID_OBJECT_ID;
	m_scale = 0.4f;

	if (m_targetID == INVALID_OBJECT_ID)
	{
		owner->chooseBestWeaponForTarget(0, PREFER_BEST_OVERALL, CMD_FROM_AI);
		m_pos = *m_machine->getGoalPosition();
		ai->m_victimID4C0 = INVALID_OBJECT_ID;
		{
			GeometryInfo geometry(owner->getGeometryInfo());
			m_pos.z += ((const BfmeBoundaryGeometry3D *)&geometry)->bfmeZDeltaToCenter();
		}
	}
	else
	{
		if (m_machine->getGoalObject() != 0 &&
			(victim = m_machine->getGoalObject()) != 0 &&
			victim->isKindOf(KINDOF_BFME_48))
		{
			victim = 0;
			m_machine->setGoalObject(victim);
		}
		if (victim == 0)
		{
			if (ai->m_targetID554 != INVALID_OBJECT_ID)
			{
				victim = TheGameLogic->findObjectByID(ai->m_targetID554);
				m_scale = 1.0f;
			}
			if (victim == 0)
				return STATE_FAILURE;
		}
		if (victim->isDead())
			return STATE_FAILURE;

		if (victim->getTemplate()->testKindOf(3, 0x2000))
		{
			ai->m_targetID554 = victim->getID();
			victim = victim->adjustVictim(owner, 1, 0);
		}
		else
		{
			Object *container = victim->getContainedBy();
			if (container != 0)
			{
				ContainModuleInterface *contain = container->getContain();
				if (contain != 0 && contain->slot31())
					ai->m_targetID554 = container->getID();
			}
			else
				ai->m_targetID554 = INVALID_OBJECT_ID;
		}

		if (victim == 0 || victim->isDead())
			return STATE_FAILURE;

		ai->m_victimID4C0 = victim->getID();
		owner->chooseBestWeaponForTarget(victim, PREFER_MOST_DAMAGE, CMD_FROM_AI);
		Weapon *weapon = (Weapon *)owner->getCurrentWeapon();
		if (weapon == 0)
			return STATE_FAILURE;

		ai->m_flags4B8 &= ~0x10;
		if (weapon->rva002C969D(owner, (Int)victim) &&
			(victim->getTemplate()->testKindOf(4, 0x4000) || victim->testStatus(OBJECT_STATUS_BFME_43)))
			ai->m_flags4B8 |= 0x110;
		else if (victim->getTemplate()->testKindOf(0, 0x800))
			ai->m_flags4B8 = (ai->m_flags4B8 & ~0x100) | 0x20;
		else if (weapon->getTemplate()->getClipSize() > 1 && !victim->testStatusBit38())
			ai->m_flags4B8 |= 8;

		ai->setCurrentVictim(victim);
		ai->m_mode55C = 2;
		AIUpdateInterface *victimAI = victim->getAI();
		AIUpdateInterface *other = victimAI ? victimAI->slot98() : 0;
		if (other != 0)
		{
			if (other->getCurrentVictim() == owner)
			{
				if (GetGameLogicRandomValue(11, 23, GIANTBIRD_CPP, 0x23F) <= 17)
				{
					ai->m_mode55C = 0;
					other->m_mode55C = 1;
				}
				else
				{
					ai->m_mode55C = 1;
					other->m_mode55C = 0;
				}
			}
		}

		if (!((Rva002CAAFA *)weapon->getTemplate())->rva002CAAFA(victim, &m_pos) ||
			!(m_pos.z > TheTerrainLogic->getGroundHeight(m_pos.x, m_pos.y, 0)))
		{
			const Coord3D *ownerPos = owner->getPosition();
			if (!ai->findNearestLabeledContactPointOnTarget(victim, &m_pos, ownerPos, false))
			{
				victim->getWorldspaceBestContactPoint(&m_pos, ownerPos, 0, 1,
					GetGameLogicRandomValue(0, 12345678, GIANTBIRD_CPP, 0x254), false);
			}
		}

		if (ai->m_mode55C != 2)
		{
			GiantBirdSwoopAI1F0 *terrain = ai->m_1F0;
			if (terrain != 0)
			{
				m_pos.z = TheTerrainLogic->getGroundHeight(m_pos.x, m_pos.y, 0) + terrain->m_height48;
				m_machine->setGoalPosition(&m_pos);
			}
		}
	}

	if (m_enabled)
		ai->setLocomotorSet(4);
	else if (ai->m_mode55C == 0)
		ai->setLocomotorSet(3);
	else
		ai->setLocomotorSet(6);

	if (ai->testFlag(2) || ai->testFlag(3))
		((Rva00368C7A *)ai)->rva003681F2(&m_pos, g_00E01EC8, 0, 0);
	else if (m_enabled)
		((Rva00368C7A *)ai)->rva003681F2(&m_pos, g_00E01ED0, 0, 0);
	else
		((Rva00368C7A *)ai)->rva003681F2(&m_pos, g_00E01EC0, 0, 0);

	return ai->m_continue4EC ? STATE_CONTINUE : STATE_FAILURE;
}

//-------------------------------------------------------------------------------------------------
void AIGiantBirdSwoopState::rva0036C438(Bool force)
{
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAI();
	owner->clearModelConditionBit(155);
	if (ai == 0)
		return;
	Object *victim = TheGameLogic->findObjectByID(ai->m_victimID4C0);
	if (victim == 0)
		return;

	Coord3D pos;
	const Weapon *weapon = owner->getCurrentWeapon();
	if (weapon == 0 ||
		!((Rva002CAAFA *)weapon->getTemplate())->rva002CAAFA(victim, &pos) ||
		!(pos.z > TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0)))
	{
		const Coord3D *ownerPos = owner->getPosition();
		if (!ai->findNearestLabeledContactPointOnTarget(victim, &pos, ownerPos, false))
		{
			victim->getWorldspaceBestContactPoint(&pos, ownerPos, 0, 1,
				GetGameLogicRandomValue(0, 12345678, GIANTBIRD_CPP, 0x294), false);
		}
	}

	const Coord3D *goal = &m_pos;
	Coord3D delta;
	delta.x = pos.x - goal->x;
	delta.y = pos.y - goal->y;
	delta.z = pos.z - goal->z;
	Real moved = delta.length();
	delta = pos;
	delta.x -= owner->getPosition()->x;
	delta.y -= owner->getPosition()->y;
	delta.z -= owner->getPosition()->z;
	Real range = delta.length();

	if (ai->m_swoopRadius538 * 4.0f > range)
	{
		owner->setModelConditionBit(155);
	}

	if (moved > 10.0f || force)
	{
		Real near8 = ai->m_swoopRadius538 * 8.0f;
		if (near8 > range || moved > near8 || force)
		{
			m_pos = pos;
			if (ai->m_mode55C == 0)
			{
				GiantBirdSwoopAI1F0 *terrain = ai->m_1F0;
				if (terrain != 0)
				{
					m_pos.z = TheTerrainLogic->getGroundHeight(m_pos.x, m_pos.y, 0) + terrain->m_height48;
					m_machine->setGoalPosition(&m_pos);
				}
			}
			if (ai->testFlag(2) || ai->testFlag(3))
				((Rva00368C7A *)ai)->rva003681F2(&m_pos, g_00E01EC8, 0, 0);
			else
				((Rva00368C7A *)ai)->rva003681F2(&m_pos, g_00E01EC0, 0, 0);
		}
	}
}

//-------------------------------------------------------------------------------------------------
StateReturnType AIGiantBirdSwoopState::update()
{
	Object *owner = getMachineOwner();
	if (owner->isDead())
		return STATE_FAILURE;
	AIUpdateInterface *ai = owner->getAI();
	if (ai == 0)
		return STATE_FAILURE;
	Object *victim = TheGameLogic->findObjectByID(ai->m_victimID4C0);
	if (victim == 0)
		return STATE_SUCCESS;
	if (victim->testStatus(OBJECT_STATUS_BFME_3C))
		return STATE_SUCCESS;
	if (victim->isDead())
		return STATE_SUCCESS;

	Real swoopRadius = (1.0f - m_scale) * ai->m_swoopRadius538;
	m_scale *= 0.8f;
	ai->m_swoopRadius538 = swoopRadius;
	rva0036C438(false);

	if (m_enabled)
	{
		if (((Rva00368C7A *)ai)->rva00368B51(-5.0f, true) == 1)
			return STATE_SUCCESS;
	}
	else
	{
		Bool stationary;
		if (victim->rva002907A1())
		{
			AIUpdateInterface *victimAI = victim->getAI();
			stationary = victimAI != 0 && ((Rva002627E8 *)victimAI)->rva002627E8() <= 0.0f;
		}
		else
			stationary = true;
		if (!owner->isKindOf(KINDOF_BFME_9B) || !stationary)
			((Rva00368C7A *)ai)->rva00368C7A(5.0f, &m_pos, 0);
	}

	if (!ai->m_continue4EC)
		return STATE_FAILURE;

	GeometryInfo geometry(owner->getGeometryInfo());
	Real dx = m_pos.x - owner->getPosition()->x;
	Real dy = m_pos.y - owner->getPosition()->y;
	Real dz = m_pos.z - owner->getPosition()->z;
	Real distSq = dx * dx + dy * dy + dz * dz;
	if (distSq < geometry.getBoundingCircleRadius() * geometry.getBoundingCircleRadius() * 0.5f)
		rva0036C438(true);

	Real range = ai->m_swoopRadius538;
	const Coord3D *src = &ai->m_anchor544;
	Coord3D anchor;
	anchor.x = src->x;
	anchor.y = src->y;
	anchor.z = src->z;
	Bool inside = ((Gen_000E5A50 *)owner)->bfmeDistanceSquared((const BfmeVec3EJ *)&anchor) < range * range;
	if (ai->m_flag534 == 0.0f && !inside)
		return STATE_CONTINUE;
	((Thing *)owner)->setPosition(&anchor);
	return STATE_SUCCESS;
}
