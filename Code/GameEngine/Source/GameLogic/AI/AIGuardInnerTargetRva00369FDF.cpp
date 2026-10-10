// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /I. /ICode/Libraries/Include/Lib
// Native complete boundary 00369FDF..0036A3E9. Loading the ordinary owner
// member via a local slot pointer preserves retail's owner/receiver spill
// lifetime around the position copy. No storage-type inference is claimed.
// BF1/ZH guide the behavior; target bytes and WB F356C0 establish this variant.
// ?lookForInnerTarget@Rva00369FDFGuardMachine@@QAE_NXZ, retail 0x00369FDF
// (1034 bytes): the pinned name, REL32 callee of the second guard machine's
// idle state update (Rva0036A979GuardIdleState::update 0x0036A979). Zero
// Hour AIGuard.cpp's AIGuardMachine::lookForInnerTarget is the body
// (WorldBuilder twin 0x00F356C0, callgraph lead), on the second guard
// machine layout (owner +0x14, target +0x3C, team +0x40, area +0x44,
// position +0x48, flag +0x60, nemesis +0x68, guard mode +0x6C).
// BFME2 differences read from retail: the owner's own AI goal wins when it
// is an enemy; the guard position also follows a guarded team (Team
// 0x0039E5B9); the area scan only marks the closest-object query stale
// instead of returning; a non-flagged owner (0x0028AFBB) first asks
// AI::findClosestEnemy with its attack info then without it for a player
// with +0x33D set and keeps a hit only inside the area; a victim with
// template kind bit +0x115/0x20 is adjusted (pinned Object::adjustVictim);
// and with no target an area with the +0x60 flag is scanned again at range
// 99999 for enemies inside it.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members.
// Retail updates the unwind state only after the status mask filter is
// built, so the status bitset and mask-filter ctors are declared throw().
#include <string.h>
#include "Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"

class Object;
class Player;
class Team;
class PartitionFilter;
class AttackPriorityInfo;

extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;

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


class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

template <int N> class BitFlags
{
	unsigned char m_bytes[28];
};
extern BitFlags<116> KINDOFMASK_NONE;

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit);	// 0x00045411
	unsigned int m_bits[7];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second (ZH's PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
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

class PolygonTrigger;

// The PolygonTrigger test 0x00261723 is rowed under this address-named view.
class Arg00261723;
class Rva00261723
{
public:
	bool rva00261723(Arg00261723 *arg);	// 0x00261723
};

// vftable 0x00C07184, allow 0x00261723: +0x08 the polygon trigger (Zero
// Hour's PartitionFilterPolygonTrigger).
class Rva00261723Filter : public Rva000421C8
{
public:
	Rva00261723Filter(const PolygonTrigger *trigger) : m_trigger(trigger) {}
	virtual bool allow(Object *obj);
	bool allowNow(Object *obj) { return ((Rva00261723 *)this)->rva00261723((Arg00261723 *)obj); }
	const PolygonTrigger *m_trigger;
};

// vftable 0x00C172A8, allow 0x00260E01: no members of its own.
class Rva00260E01Filter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF8FE4, allow 0x0026109D: +0x08 a player, +0x0C whether a hit
// allows (built inline here; the out-of-line ctor 0x00261058 takes an object).
class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Player *player, bool flag) : m_player(player), m_flag(flag) {}
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

// A 128-bit ObjectStatusMaskType; 0x0023DA79 clears it and sets one bit.
class BfmeObject872Header
{
	unsigned int m_words[4];
};

class Rva0023DA79 : public BfmeObject872Header
{
public:
	Rva0023DA79 *rva0023DA79(int base, int bit) throw();	// 0x0023DA79
};

struct Rva00369FDFStatusNone : public BfmeObject872Header
{
	Rva00369FDFStatusNone() { memset(this, 0, sizeof(*this)); }
};

// vftable 0x00C17968; the out-of-line ctor 0x003685CF: status must / must not.
class Rva003685CF : public Rva000421C8
{
public:
	Rva003685CF(const BfmeObject872Header &must, const BfmeObject872Header &mustNot) throw();	// 0x003685CF
	virtual bool allow(Object *obj);
	BfmeObject872Header m_must;
	BfmeObject872Header m_mustNot;
};

struct Rva0030B719Shape
{
	float getRadius() const;	// 0x0030B719
};

class PolygonTrigger
{
public:
	float getRadius() const { return m_shape.getRadius(); }
	void getCenterPoint(Coord3D *pOutCoord) const;	// 0x002E38F3
private:
	char m_pad00[0x08];
	Rva0030B719Shape m_shape;	// +0x08
};

class StateMachine
{
public:
	Object *getGoalObject();	// 0x004D7726
};

class AIUpdateInterface
{
public:
	StateMachine *getStateMachine() { return m_stateMachine; }
	const AttackPriorityInfo *getAttackInfo() const { return m_attackInfo; }
private:
	char m_pad00[0x30];
	StateMachine *m_stateMachine;	// +0x30
	char m_pad34[0x70 - 0x34];
	const AttackPriorityInfo *m_attackInfo;	// +0x70
};

struct TeamTemplateInfo
{
	char m_pad000[0x216];
	bool m_attackCommonTarget;	// +0x216
};

struct TeamPrototype
{
	const TeamTemplateInfo *getTemplateInfo() const { return &m_info; }
	TeamTemplateInfo m_info;
};

class Team
{
public:
	Object *getTeamTargetObject();	// 0x003A105B
	void rva0039E5B9(Coord3D *pos);	// 0x0039E5B9
	TeamPrototype *getPrototype() { return m_proto; }
private:
	char m_pad00[0x30];
	TeamPrototype *m_proto;	// +0x30
};

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);	// 0x0039F761
};
extern TeamFactory *TheTeamFactory;

class Player
{
public:
	char m_pad000[0x33D];
	bool m_33d;	// +0x33D
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class ThingTemplate
{
public:
	bool isKindOf6D() const { return (m_kindOf[0x0D] & 0x20) != 0; }
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[0x1C];	// +0x108
};

class Object
{
public:
	bool isAbleToAttack() const;	// 0x00290B73
	Relationship getRelationship(const Object *that) const;	// 0x0028D156
	Player *getControllingPlayer() const;	// 0x0028AFA9
	bool rva0028AFBB() const;	// 0x0028AFBB
	Object *adjustVictim(Object *owner, int flag, int extra);	// 0x0028CCB9

	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() { return m_ai; }
	Team *getTeam() { return m_team; }
private:
	void *m_vtable;
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;	// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;	// +0x74
	char m_pad078[0x258 - 0x78];
	AIUpdateInterface *m_ai;	// +0x258
	char m_pad25C[0x304 - 0x25C];
	Team *m_team;	// +0x304
};

struct TAiData
{
	char m_pad00[0x40];
	unsigned int m_guardEnemyScanRate;	// +0x40
};

class AI
{
public:
	Object *findClosestEnemy(const Object *me, float range, unsigned int qualifiers,
		const AttackPriorityInfo *info, PartitionFilter *optionalFilter, int extra);	// 0x002FFFA3
	const TAiData *getAiData() const { return m_aiData; }
private:
	char m_pad00[0x18];
	TAiData *m_aiData;	// +0x18
};
extern AI *TheAI;

// GameLogic's trigger-area change frame at +0x180, beside the canonical
// view's frame at +0x40.
struct Rva00369FDFTriggerFrameView
{
	char m_pad000[0x180];
	unsigned int m_frameObjectsChangedTriggerAreas;	// +0x180
};

enum
{
	GUARDMODE_GUARD_FLYING_UNITS_ONLY = 2
};

class AIGuardMachine
{
public:
	static float getStdGuardRange(const Object *obj);	// 0x00542C2A
};

class Rva00369FDFGuardMachine : public AIGuardMachine
{
public:
	bool lookForInnerTarget();
private:
	Object *getOwner() { return m_owner; }
	Object *findTargetToGuardByID() { return TheGameLogic->findObjectByID(m_targetToGuard); }
	Team *findTeamToGuardByID() { return TheTeamFactory->findTeamByID(m_teamToGuard); }
	const Coord3D *getPositionToGuard() const { return &m_positionToGuard; }
	const PolygonTrigger *getAreaToGuard() const { return m_areaToGuard; }
	int getGuardMode() const { return m_guardMode; }
	void setNemesisID(ObjectID id) { m_nemesisToAttack = id; }

	char m_pad00[0x14];
	Object *m_owner;	// +0x14
	char m_pad18[0x3C - 0x18];
	ObjectID m_targetToGuard;	// +0x3C
	unsigned int m_teamToGuard;	// +0x40
	const PolygonTrigger *m_areaToGuard;	// +0x44
	Coord3D m_positionToGuard;	// +0x48
	char m_pad54[0x60 - 0x54];
	bool m_rescanArea;	// +0x60
	char m_pad61[0x68 - 0x61];
	ObjectID m_nemesisToAttack;	// +0x68
	int m_guardMode;	// +0x6C
};

bool Rva00369FDFGuardMachine::lookForInnerTarget()
{
	Object **ownerSlot = &m_owner;
	Object *owner = *ownerSlot;
	if (!owner->isAbleToAttack())
		return false;

	Object *goal = owner->getAI()->getStateMachine()->getGoalObject();
	if (goal && goal->getRelationship(owner) == ENEMIES)
	{
		setNemesisID(goal->getID());
		return true;
	}

	Object *teamVictim = 0;
	if (owner->getTeam()->getPrototype()->getTemplateInfo()->m_attackCommonTarget)
	{
		teamVictim = owner->getTeam()->getTeamTargetObject();
		if (teamVictim)
		{
			setNemesisID(teamVictim->getID());
			return true;
		}
	}

	Object *targetToGuard = findTargetToGuardByID();
	Team *teamToGuard = findTeamToGuardByID();
	Coord3D pos;
	if (targetToGuard)
		pos = *targetToGuard->getPosition();
	else if (teamToGuard)
		teamToGuard->rva0039E5B9(&pos);
	else
		pos = *getPositionToGuard();

	Object *target = 0;
	const PolygonTrigger *area = getAreaToGuard();
	float visionRange = AIGuardMachine::getStdGuardRange(owner);
	{
		Rva00260EB1Filter f1(owner, 1, false);
		Rva00261723Filter f2(area);
		bool checkClosest = true;
		if (area)
		{
			unsigned int scanRate = TheAI->getAiData()->m_guardEnemyScanRate;
			unsigned int changed = ((const Rva00369FDFTriggerFrameView *)TheGameLogic)->m_frameObjectsChangedTriggerAreas;
			unsigned int checkFrame = scanRate + changed;
			if (TheGameLogic->getFrame() < checkFrame)
				checkClosest = false;
			f1.link(&f2);
			visionRange = area->getRadius();
			area->getCenterPoint(&pos);
		}
		Rva00260E01Filter f3;
		if (getGuardMode() == GUARDMODE_GUARD_FLYING_UNITS_ONLY)
			f1.link(&f3);
		Rva0026119DFilter f4;
		f1.link(&f4);
		Rva0004584D f5(*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
			*(const BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 0x36));
		Rva00369FDFStatusNone none;
		Rva003685CF f6(none, *Rva0023DA79().rva0023DA79(0, 0x3C));
		Rva00261058 f7(owner->getControllingPlayer(), false);
		f1.link(&f5);
		f1.link(&f6);
		f1.link(&f7);

		if (checkClosest)
		{
			if (!owner->rva0028AFBB())
			{
				target = TheAI->findClosestEnemy(owner, visionRange, 0x4A, owner->getAI()->getAttackInfo(), 0, 0);
				if (!target && owner->getControllingPlayer() && owner->getControllingPlayer()->m_33d)
					target = TheAI->findClosestEnemy(owner, visionRange, 0x4A, 0, 0, 0);
			}
			if (!target || (area && !f2.allowNow(target)))
				target = ThePartitionManager->getClosestObject(&pos, visionRange, 1, &f1);
		}
	}

	if (target && target->getTemplate()->isKindOf6D())
		target = target->adjustVictim(owner, 0, 0);
	if (target)
	{
		setNemesisID(target->getID());
		return true;
	}

	if (area && m_rescanArea)
	{
		Rva00260EB1Filter f1(owner, 1, false);
		Rva00261723Filter f2(area);
		f1.link(&f2);
		Rva0026119DFilter f4;
		f1.link(&f4);
		Rva0004584D f5(*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
			*(const BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 0x36));
		f1.link(&f5);
		Rva00260E01Filter f3;
		if (getGuardMode() == GUARDMODE_GUARD_FLYING_UNITS_ONLY)
			f1.link(&f3);
		target = ThePartitionManager->getClosestObject(&pos, 99999.0f, 1, &f1);
		if (target)
		{
			setNemesisID(target->getID());
			return true;
		}
	}
	return false;
}
