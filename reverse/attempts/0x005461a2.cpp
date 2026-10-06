// ?lookForInnerTarget@AITNGuardMachine@@QAE_NXZ
// partial score=0.9218 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// AITNGuardMachine::lookForInnerTarget, retail 0x005461A2 (395 bytes), ported
// from Zero Hour's GameEngine/Source/GameLogic/AI/AITNGuard.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference); called at
// 0x005466C0. Zero Hour's body on BFME 2's layout (target evidence; the rest
// as in AITNGuardStates.cpp): nemesis id +0x48; the team's prototype +0x30
// with m_attackCommonTarget at prototype +0x216; the player's tunnel tracker
// +0x2E8 with its tunnel id list at +0x08; the AI's state machine at AI +0x30
// (getGoalObject is the rowed StateMachine body 0x004D7726); the body
// module's getLastDamageInfo / getLastDamageTimestamp are vslots 15 / 16 and
// m_noEffect is DamageInfo +0x78; AbleToAttackType 4 (tunnel network guard)
// and CMD_FROM_AI 2 go to the pinned Object::getAbleToAttackSpecificObject.
#include <list>

typedef bool Bool;
typedef unsigned int UnsignedInt;
#define NULL 0

enum ObjectID
{
	INVALID_ID = 0
};
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};
enum AbleToAttackType
{
	ATTACK_TUNNEL_NETWORK_GUARD = 4
};
enum CommandSourceType
{
	CMD_FROM_AI = 2
};
enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT = 1,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};

class Object;

struct DamageInfoInput
{
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
};
struct DamageInfo
{
	DamageInfoInput in;
	unsigned char m_pad0C[0x78 - 0x0C];
	struct
	{
		Bool m_noEffect; // +0x78
	} out;
};

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class BodyModuleInterface : public VSlots<15>
{
public:
	virtual const DamageInfo *getLastDamageInfo() const = 0;
	virtual UnsignedInt getLastDamageTimestamp() const = 0;
};

class StateMachine
{
public:
	Object *getGoalObject();
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

class AIUpdateInterface
{
public:
	Object *getGoalObject() { return m_stateMachine->getGoalObject(); }
private:
	unsigned char m_pad00[0x30];
	StateMachine *m_stateMachine; // +0x30
};

struct TeamTemplateInfo
{
	unsigned char m_pad00[0x16];
	Bool m_attackCommonTarget; // +0x16 (prototype +0x216)
};
class TeamPrototype
{
public:
	const TeamTemplateInfo *getTemplateInfo(void) const { return &m_teamTemplate; }
private:
	unsigned char m_pad00[0x200];
	TeamTemplateInfo m_teamTemplate; // +0x200
};
class Team
{
public:
	const TeamPrototype *getPrototype(void) { return m_proto; }
	Object *getTeamTargetObject();
	void rva0039D84A(Object *target);
	void setTeamTargetObject(Object *target) { rva0039D84A(target); }
private:
	unsigned char m_pad00[0x30];
	TeamPrototype *m_proto; // +0x30
};

class TunnelTracker
{
public:
	Object *getCurNemesis();
	void updateNemesis(const Object *target);
	const _STL::list<ObjectID> *getContainerList() const { return &m_tunnelIDs; }
private:
	unsigned char m_pad00[0x08];
	_STL::list<ObjectID> m_tunnelIDs; // +0x08
};

class Player
{
public:
	TunnelTracker *getTunnelSystem() { return m_tunnelSystem; }
private:
	unsigned char m_pad00[0x2E8];
	TunnelTracker *m_tunnelSystem; // +0x2E8
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	Team *getTeam() { return m_team; }
	Player *getControllingPlayer() const;
	Relationship getRelationship(const Object *that) const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attackType, const Object *obj, CommandSourceType commandSource) const;
	// Read directly: inline getAI / getBodyModule here would be more COMDAT
	// copies beside the Zero Hour header views' (ZH offsets).
	unsigned char m_pad00[0x74];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x254 - 0x78];
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
	Team *m_team; // +0x304
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

struct TAiData
{
	unsigned char m_pad00[0x40];
	UnsignedInt m_guardEnemyScanRate; // +0x40
};
class AI
{
public:
	const TAiData *getAiData() const { return m_aiData; }
private:
	unsigned char m_pad00[0x18];
	TAiData *m_aiData; // +0x18
};
extern AI *TheAI;

class AITNGuardMachine : public StateMachine
{
public:
	Bool lookForInnerTarget(void);
	void setNemesisID(ObjectID id) { m_nemesisToAttack = id; }
private:
	unsigned char m_pad18[0x48 - 0x18];
	ObjectID m_nemesisToAttack; // +0x48
};

//--------------------------------------------------------------------------------------
Bool AITNGuardMachine::lookForInnerTarget(void)
{
	Object* owner = getOwner();

	// Check if team auto targets same victim.
	Object *teamVictim = NULL;
	if (owner->getTeam()->getPrototype()->getTemplateInfo()->m_attackCommonTarget)
	{
		teamVictim = owner->getTeam()->getTeamTargetObject();
		if (teamVictim)
		{
			setNemesisID(teamVictim->getID());
			return true;	// Transitions to AITNGuardInnerState.
		}
	}

	// Find tunnel network to defend.
	// Scan my tunnels.
	Player *ownerPlayer = getOwner()->getControllingPlayer();
	if (!ownerPlayer) return false; // should never happen, but hey.  jba.
	TunnelTracker *tunnels = ownerPlayer->getTunnelSystem();
	if (tunnels==NULL) return false;
	if (tunnels->getCurNemesis()) {
		setNemesisID(tunnels->getCurNemesis()->getID());
		return true;	// Transitions to AITNGuardInnerState.
	}
	const _STL::list<ObjectID> *allTunnels = tunnels->getContainerList();
	for( _STL::list<ObjectID>::const_iterator iter = allTunnels->begin(); iter != allTunnels->end(); iter++ ) {
		Object *currentTunnel = TheGameLogic->findObjectByID( *iter );
		if( currentTunnel ) {
			// Check for attacking.
			if (currentTunnel->m_ai) {
				Object *victim = currentTunnel->m_ai->getGoalObject();
				if (owner->getRelationship(victim) == ENEMIES) {
					setNemesisID(victim->getID());
					return true;
				}
			}
			// check for attacked.
			BodyModuleInterface *body = currentTunnel->m_body;
			if (body) {
				const DamageInfo *info = body->getLastDamageInfo();
				if (info) {
					if (info->out.m_noEffect) {
						continue;
					}
					if (body->getLastDamageTimestamp() + TheAI->getAiData()->m_guardEnemyScanRate > TheGameLogic->getFrame()) {
						// winner.
						ObjectID attackerID = info->in.m_sourceID;
						Object *attacker = TheGameLogic->findObjectByID(attackerID);

						if( attacker )
						{
							if (owner->getRelationship(attacker) != ENEMIES) {
								continue;
							}
							CanAttackResult result = getOwner()->getAbleToAttackSpecificObject(ATTACK_TUNNEL_NETWORK_GUARD, attacker, CMD_FROM_AI);
							if( result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING )
							{
								setNemesisID(attackerID);
								owner->getTeam()->setTeamTargetObject(attacker);
								tunnels->updateNemesis(attacker);
								return true;	// Transitions to AITNGuardInnerState.
							}
						}
					}
				}
			}
		}
	}

	return false;
}
