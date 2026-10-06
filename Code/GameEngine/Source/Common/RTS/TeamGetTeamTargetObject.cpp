// cl: /DNDEBUG /MD
//
// Team::getTeamTargetObject, retail 0x003A105B (101 bytes), ported from Zero
// Hour's GameEngine/Source/Common/RTS/Team.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). Callers: the AITNGuard states and
// AIGuardRetaliateMachine.
// BFME 2 deltas (target evidence): the common attack target id is Team
// +0x114; Zero Hour's three stealth testStatus checks are one call to the
// pinned Object::rva002943B2 with the team's controlling player (the rowed
// Team::getControllingPlayer 0x0039D7CF); isEffectivelyDead is Object +0x438
// bit 0 and getContainedBy Object +0x274; Zero Hour's KINDOF_AIRCRAFT test is
// absent.
typedef bool Bool;
typedef unsigned int UnsignedInt;
#define NULL 0

enum ObjectID
{
	INVALID_ID = 0
};

class Player;

class Object
{
public:
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	Bool rva002943B2(const Player *player);
	// Read directly: an inline getContainedBy here would be one more COMDAT
	// copy beside the Zero Hour header views' (ZH offset).
	unsigned char m_pad00[0x274];
	Object *m_containedBy; // +0x274
private:
	unsigned char m_pad278[0x438 - 0x278];
	unsigned char m_privateStatus; // +0x438
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Team
{
public:
	Player *getControllingPlayer() const;
	Object *getTeamTargetObject(void);
private:
	unsigned char m_pad00[0x114];
	ObjectID m_commonAttackTarget; // +0x114
};

// ------------------------------------------------------------------------
Object *Team::getTeamTargetObject(void)
{
	if (m_commonAttackTarget == INVALID_ID) {
		return NULL;
	}
	Object *target = TheGameLogic->findObjectByID(m_commonAttackTarget);
	if (target) {
		if( target->rva002943B2( getControllingPlayer() ) )
		{
			target = NULL;
		}
	}
	if (target && target->isEffectivelyDead()) {
		target = NULL;
	}
	if (target && target->m_containedBy) {
		target = NULL; // target entered a building or vehicle, so stop targeting.
	}
	if (target == NULL) {
		m_commonAttackTarget = INVALID_ID;
	}
	return target;
}
