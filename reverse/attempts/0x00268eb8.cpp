// ?getNextMoodTarget@AIUpdateInterface@@QAEPAVObject@@_N0@Z
// partial score=0.97 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// BANK for ?getNextMoodTarget@AIUpdateInterface@@QAEPAVObject@@_N0@Z, retail
// 0x00268EB8 (1710 bytes). Intended home: a new
// Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_getNextMoodTarget.cpp
// (includes below are written for that directory). Compiles to 1708 bytes; all
// control flow, calls and the early-exit / epilogue layout match. Left: the
// frame is 0x2C instead of 0x30 (retail keeps the slot-44 status temporary in
// its own slot [ebp-0x3C] and puts the partition filter below the shared
// position/delta Coord3D), m_attackInfo is loaded into ECX before the
// player-type select, and retail holds the 0x2000 kind mask in EBX for the
// closing tests.

#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_10 = 0x10,
	OBJECT_STATUS_17 = 0x17,
	OBJECT_STATUS_25 = 0x25,
	OBJECT_STATUS_26 = 0x26,
	OBJECT_STATUS_32 = 0x32,
	OBJECT_STATUS_3A = 0x3A,
	OBJECT_STATUS_44 = 0x44,
	OBJECT_STATUS_46 = 0x46,
	OBJECT_STATUS_4A = 0x4A
};
enum AttitudeType
{
	AI_PASSIVE = -1,
	AI_NORMAL = 0
};
enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0
};
enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};
enum CommandSourceType
{
	CMD_FROM_AI = 2
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class Object;
class Player;
class Module;
class AttackPriorityInfo;
class PartitionFilter;
extern GameLogic *TheGameLogic;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual Bool allow(Object *objOther) = 0;
private:
	Rva000421C8 *m_next; // +0x04
};

// vftable 0x00BF91F0 (allow 0x00263077): built only for human players.
class Rva00263077Filter : public Rva000421C8
{
public:
	Rva00263077Filter(const Object *obj) : m_obj(obj) {}
	virtual Bool allow(Object *objOther);
private:
	const Object *m_obj; // +0x08
};

class TAiData
{
public:
	unsigned char m_pad00[0x67];
	Bool m_attackUsesLineOfSight; // +0x67
	Bool m_attackIgnoreInsignificantBuildings; // +0x68
};

class AI
{
public:
	const TAiData *getAiData() const { return m_aiData; }
	Object *findClosestEnemy(const Object *me, Real range, UnsignedInt qualifiers, const AttackPriorityInfo *info, PartitionFilter *optionalFilter, Int extra);
	static Real getAdjustedVisionRangeForObject(const Object *obj, Int factors);
	static Bool rva002FE193(Object *owner, Object *nemesis);
private:
	unsigned char m_pad00[0x18];
	TAiData *m_aiData; // +0x18
};
extern AI *TheAI;

class GlobalData
{
public:
	unsigned char m_pad000[0xE9C];
	Bool m_debugAI_E9C; // +0xE9C
};
extern GlobalData *TheWritableGlobalData;

class TerrainLogic
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03(); virtual void t04(); virtual void t05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
};
extern TerrainLogic *TheTerrainLogic;

class View
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
	virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void drawCircle(const Coord3D *center, Real radius, Int color);
};
extern View *TheTacticalView;

Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);
#define GameLogicRandomValueAt(lo, hi) GetGameLogicRandomValue((lo), (hi), "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\AIUpdate.cpp", 0x200a)
NameKeyType Rva0045EE2CGet();

class StancesBehavior
{
public:
	Int rva0045ED4B() const;
};

class Rva0028B7AELeaGetter
{
public:
	void *get() const;
};

struct DamageInfoView
{
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
};

class BodyModuleView
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03(); virtual void b04();
	virtual void b05(); virtual void b06(); virtual void b07(); virtual void b08(); virtual void b09();
	virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14();
	virtual const DamageInfoView *getLastDamageInfo() const; // slot 15
};

struct ObjectStatusBitsView
{
	ObjectStatusBitsView();
	UnsignedInt m_bits;
};

class ContainRiderView
{
public:
	virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03(); virtual void r04();
	virtual void r05(); virtual void r06(); virtual void r07(); virtual void r08(); virtual void r09();
	virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13(); virtual void r14();
	virtual void r15(); virtual void r16(); virtual void r17(); virtual void r18(); virtual void r19();
	virtual void r20(); virtual void r21(); virtual void r22(); virtual void r23(); virtual void r24();
	virtual void r25(); virtual void r26(); virtual void r27(); virtual void r28(); virtual void r29();
	virtual void r30(); virtual void r31(); virtual void r32(); virtual void r33(); virtual void r34();
	virtual void r35(); virtual void r36(); virtual void r37(); virtual void r38(); virtual void r39();
	virtual void r40(); virtual void r41(); virtual void r42(); virtual void r43(); virtual void r44();
	virtual void r45(); virtual void r46(); virtual void r47(); virtual void r48(); virtual void r49();
	virtual void r50(); virtual void r51(); virtual void r52(); virtual void r53(); virtual void r54();
	virtual void r55(); virtual void r56(); virtual void r57(); virtual void r58(); virtual void r59();
	virtual void r60();
	virtual Bool slot61();
};

class ContainView
{
public:
	virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03(); virtual void c04();
	virtual void c05(); virtual void c06(); virtual void c07(); virtual void c08(); virtual void c09();
	virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14();
	virtual void c15(); virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
	virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23(); virtual void c24();
	virtual void c25(); virtual void c26(); virtual void c27(); virtual void c28(); virtual void c29();
	virtual void c30();
	virtual ContainRiderView *slot31();
	virtual void c32(); virtual void c33(); virtual void c34();
	virtual void c35(); virtual void c36(); virtual void c37(); virtual void c38(); virtual void c39();
	virtual void c40(); virtual void c41(); virtual void c42(); virtual void c43();
	virtual ObjectStatusBitsView slot44(const Object *passenger);
	virtual void c45();
	virtual Bool slot46();
};

class ThingTemplate
{
public:
	unsigned char m_pad000[0x109];
	unsigned char m_kind109; // +0x109
	unsigned char m_pad10A[0x10F - 0x10A];
	unsigned char m_kind10F; // +0x10F
	unsigned char m_pad110[0x114 - 0x110];
	UnsignedInt m_kind114; // +0x114
};

class Team;
class TeamPrototype
{
public:
	unsigned char m_pad000[0x216];
	Bool m_attackCommonTarget; // +0x216
};
class Team
{
public:
	Object *getTeamTargetObject();
	unsigned char m_pad00[0x30];
	TeamPrototype *m_proto; // +0x30
};

class Player
{
public:
	Int getPlayerType() const { return m_playerType; }
private:
	unsigned char m_pad00[0x5C];
	Int m_playerType; // +0x5C
};

class Weapon
{
public:
	Bool isWithinAttackRange(const Object *source, const Object *target, Real extra, Int flag) const;
};

class AIUpdateInterface;
class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	Bool testStatus(ObjectStatusTypes bit) const;
	Player *getControllingPlayer() const;
	Module *findModule(NameKeyType key) const;
	Int rva0028F4EF();
	Bool rva002943B2(const Player *player);
	Int rva0028AF97();
	Object *adjustVictim(Object *owner, Int flag, Int extra);
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType t, const Object *target, CommandSourceType src) const;
	Real rva00263763(const void *other) const;
	Bool isAbleToAttack() const;
	Real rva002615E3(const Coord3D *pos) const;
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	Bool isDestroyed() const { return (m_privateStatus & 8) != 0; }
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0xB8 - 0x44];
	Real m_boundingRadius; // +0xB8
	unsigned char m_pad0BC[0x124 - 0xBC];
	UnsignedInt m_124; // +0x124 (bit 26: holding fire)
	unsigned char m_pad128[0x134 - 0x128];
	UnsignedInt m_134; // +0x134 (bit 13: no auto-acquire)
	unsigned char m_pad138[0x250 - 0x138];
	ContainView *m_contain; // +0x250
	BodyModuleView *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
	unsigned char m_pad278[0x304 - 0x278];
	Team *m_team; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_privateStatus; // +0x438
};

struct AIUpdateModuleData
{
	unsigned char m_pad00[0x18];
	Int m_moodAttackCheckRate; // +0x18
	UnsignedInt m_autoAcquireEnemiesWhenIdle; // +0x1C
	unsigned char m_pad20[0x25 - 0x20];
	Bool m_25; // +0x25
	unsigned char m_pad26[0x28 - 0x26];
	Real m_28; // +0x28
};

class Rva00268EB8SlotView
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07();
	virtual Bool slot08();
	virtual Int slot09();
};

// A flag word bit read as Rva0045F3F8Finish.cpp reads Object +0x124 (the
// shifted word truncated to a byte keeps retail's shr / test al,1).
static __forceinline Bool testBit(UnsignedInt value, Int bit)
{
	return ((unsigned char)(value >> bit)) & 1;
}

template <int N> class VirtualSlots : public VirtualSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class VirtualSlots<0>
{
};

class AIUpdateSlots93 : public VirtualSlots<93>
{
public:
	virtual Rva00268EB8SlotView *slot93();
};

class AIUpdateInterface : public VirtualSlots<111>
{
public:
	virtual Bool isAttacking() const; // slot 111
	Object *getNextMoodTarget(Bool calledByAI, Bool calledDuringIdle);
	AttitudeType getAttitude() const;
	UnsignedInt getMoodMatrixValue() const;
	Object *getObject() const { return m_object; }
	const AIUpdateModuleData *getAIUpdateModuleData() const { return m_moduleData; }
	const AIUpdateModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad00C[0x34 - 0x0C];
	Int m_34; // +0x34
	unsigned char m_pad038[0x70 - 0x38];
	const AttackPriorityInfo *m_attackInfo; // +0x70
	unsigned char m_pad074[0x1A4 - 0x74];
	ObjectID m_1a4; // +0x1A4 (a target ID taken first)
	unsigned char m_pad1A8[0x21C - 0x1A8];
	UnsignedInt m_nextMoodCheckTime; // +0x21C
	unsigned char m_pad220[0x3BC - 0x220];
	Bool m_randomlyOffsetMoodCheck; // +0x3BC
	unsigned char m_pad3BD[0x3CC - 0x3BD];
	Bool m_3cc; // +0x3CC (retaliate against the last damage source)
};

Object *AIUpdateInterface::getNextMoodTarget(Bool calledByAI, Bool calledDuringIdle)
{
	Object *obj = getObject();
	Real rangeToFindWithin;
	if (obj->isEffectivelyDead())
		return 0;
	if (obj->isDestroyed() || obj->testStatus(OBJECT_STATUS_46) ||
		(obj->m_ai && obj->m_ai->m_34) || obj->testStatus(OBJECT_STATUS_17) || obj->testStatus(OBJECT_STATUS_26) ||
		obj->testStatus(OBJECT_STATUS_4A) || testBit(obj->m_124, 26) || testBit(obj->m_134, 13))
		return 0;

	Bool humanControlled = obj->testStatus(OBJECT_STATUS_44) || obj->getControllingPlayer()->getPlayerType() == 0;

	if (obj->getTemplate()->m_kind109 & 0x40)
	{
		Rva00268EB8SlotView *view = ((AIUpdateSlots93 *)this)->slot93();
		if (view && (view->slot09() != -1 || view->slot08()))
			return 0;
	}

	if (m_1a4)
	{
		Object *forced = TheGameLogic->findObjectByID(m_1a4);
		if (forced && !(forced->m_privateStatus & 1) && !forced->testStatus(OBJECT_STATUS_32))
			return forced;
		m_1a4 = (ObjectID)0;
	}

	const AIUpdateModuleData *d = getAIUpdateModuleData();
	if (calledDuringIdle && !(d->m_autoAcquireEnemiesWhenIdle & 1))
		return 0;
	if (isAttacking() && (d->m_autoAcquireEnemiesWhenIdle & 8))
		return 0;

	if (obj->m_containedBy)
	{
		if (!d->m_25 && !obj->testStatus(OBJECT_STATUS_25))
		{
			ContainView *contain = obj->m_contain;
			if (!contain || !contain->slot46())
				return 0;
		}
		if (testBit(obj->m_containedBy->m_124, 26))
			return 0;
	}

	if (calledDuringIdle)
	{
		if (obj->rva0028F4EF() == 1)
		{
			StancesBehavior *stances = (StancesBehavior *)obj->findModule(Rva0045EE2CGet());
			if (stances && stances->rva0045ED4B() == 3)
				return 0;
		}
		else if (obj->rva002943B2(0) && !(getAIUpdateModuleData()->m_autoAcquireEnemiesWhenIdle & 2))
		{
			Object *container = obj->m_containedBy;
			if (!container)
				return 0;
			if (!testBit(container->m_contain->slot44(obj).m_bits, 1))
				return 0;
		}
	}

	if (obj->testStatus(OBJECT_STATUS_10))
		return 0;

	UnsignedInt now = TheGameLogic->getFrame();
	if (calledByAI)
	{
		Team *team = obj->m_team;
		if (team && team->m_proto->m_attackCommonTarget)
		{
			Object *teamVictim = team->getTeamTargetObject();
			if (teamVictim && getAttitude() >= AI_NORMAL)
				return teamVictim;
		}
		if (now < m_nextMoodCheckTime)
			return 0;
		Int checkRate = d->m_moodAttackCheckRate;
		m_nextMoodCheckTime = now + checkRate;
		if (m_randomlyOffsetMoodCheck)
		{
			Int halfRate = checkRate >> 1;
			m_nextMoodCheckTime += GameLogicRandomValueAt(-halfRate, halfRate);
			m_randomlyOffsetMoodCheck = false;
		}
	}

	rangeToFindWithin = AI::getAdjustedVisionRangeForObject(obj, 3);
	if (rangeToFindWithin <= 0.0f)
		return 0;
	if (obj->m_containedBy)
		rangeToFindWithin += obj->m_containedBy->m_boundingRadius;

	UnsignedInt moodMatrixVal = getMoodMatrixValue();
	if ((moodMatrixVal & 2) && (moodMatrixVal & 0x200))
	{
		BodyModuleView *body = obj->m_body;
		if (!body)
			return 0;
		return TheGameLogic->findObjectByID(body->getLastDamageInfo()->m_sourceID);
	}
	if (moodMatrixVal & 0x2000)
		return 0;

	if ((obj->getTemplate()->m_kind114 & 0x2000) && obj->testStatus(OBJECT_STATUS_3A))
	{
		ContainView *contain = obj->m_contain;
		if (contain)
		{
			ContainRiderView *rider = contain->slot31();
			if (rider && !rider->slot61())
				return 0;
		}
	}

	UnsignedInt flags = 2;
	if (TheAI->getAiData()->m_attackUsesLineOfSight && (obj->getTemplate()->m_kind10F & 8))
		flags = 3;
	if (TheAI->getAiData()->m_attackIgnoreInsignificantBuildings)
		flags |= 4;
	if (d->m_autoAcquireEnemiesWhenIdle & 0x10)
		flags |= 8;
	if (calledByAI && obj->getControllingPlayer() && obj->getControllingPlayer()->getPlayerType() == 0)
		flags |= 0x20;
	flags |= 0x40;
	if (humanControlled)
		flags |= 0x10;
	if (obj->getControllingPlayer()->getPlayerType() == 1)
		flags |= 0x80;

	Object *target = 0;
	if (m_3cc && calledByAI && calledDuringIdle)
	{
		BodyModuleView *body = obj->m_body;
		if (body)
		{
		const DamageInfoView *info = body->getLastDamageInfo();
		if (info)
		{
			const Weapon *weapon = obj->getCurrentWeapon(0);
			Object *attacker = TheGameLogic->findObjectByID(info->m_sourceID);
			if (attacker && weapon && obj->getAbleToAttackSpecificObject(ATTACK_NEW_TARGET, attacker, CMD_FROM_AI))
			{
				if (obj->rva00263763(attacker) < 1.0f)
				{
					m_3cc = false;
					target = attacker;
				}
				if (weapon->isWithinAttackRange(obj, attacker, 0.0f, 1))
					target = attacker;
				if (target)
					goto found;
			}
		}
		}
	}

	{
		Object *nemesis = TheGameLogic->findObjectByID((ObjectID)obj->rva0028AF97());
		target = nemesis ? nemesis->adjustVictim(obj, 1, 0) : 0;
		if (target)
		{
			if (target->rva002615E3(obj->getPosition()) > rangeToFindWithin * rangeToFindWithin)
				target = 0;
			if (target)
				goto found;
		}
	}

	if (TheWritableGlobalData->m_debugAI_E9C)
	{
		Coord3D pos;
		pos.x = obj->getPosition()->x;
		pos.y = obj->getPosition()->y;
		pos.z = obj->getPosition()->z;
		pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);
		TheTacticalView->drawCircle(&pos, rangeToFindWithin, 0xFF00FF00);
	}
	{
		Rva00263077Filter filter(obj);
		const AttackPriorityInfo *info = m_attackInfo;
		target = TheAI->findClosestEnemy(obj, rangeToFindWithin, flags, info,
			obj->getControllingPlayer()->getPlayerType() == 0 ? (PartitionFilter *)&filter : 0, 0);
	}
	if (target)
	{
found:
		if (!(obj->getTemplate()->m_kind114 & 0x2000) && (target->getTemplate()->m_kind114 & 0x2000))
			target = target->adjustVictim(obj, 0, 0);
	}
	if (calledByAI && humanControlled && target && !AI::rva002FE193(obj, target))
		return 0;
	if (!obj->isAbleToAttack())
		return 0;
	if (!target)
		return 0;
	if (testBit(*(const UnsignedInt *)((const Rva0028B7AELeaGetter *)obj)->get(), 7))
	{
		if (!AI::rva002FE193(obj, target))
		{
			Real maxRange = d->m_28;
			if (maxRange > 0.0f)
			{
				Coord3D delta;
				delta.x = target->getPosition()->x;
				delta.y = target->getPosition()->y;
				delta.z = target->getPosition()->z;
				delta.x -= obj->getPosition()->x;
				delta.y -= obj->getPosition()->y;
				delta.z -= obj->getPosition()->z;
				if (delta.length() > maxRange)
					return 0;
			}
		}
	}
	if ((obj->getTemplate()->m_kind114 & 0x2000) && target->m_containedBy &&
		(target->m_containedBy->getTemplate()->m_kind114 & 0x2000))
		target = target->m_containedBy;
	return target;
}
