// ?lookForInnerTarget@AITNGuardMachine@@QAE_NXZ
// partial score=0.92 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /GX
// ?lookForInnerTarget@AITNGuardMachine@@QAE_NXZ, 0x005461A2, 395B.
// ZH donor GameEngine/Source/GameLogic/AI/AITNGuard.cpp AITNGuardMachine::lookForInnerTarget.
// Caller 0x005466C0 in AITNGuardOuterState context; machine nemesis +0x48, owner +0x14,
// team +0x304 proto +0x30 template +0x216, tunnel +0x2E8 list +8, AI +0x258 turret +0x30,
// body +0x254 slots 15/16, DamageInfo source +8 noEffect +0x78, AI data +0x18 rate +0x40,
// frame +0x40. Row names rva003A105B/rva0039D84A, pins getRelationship/getAbleToAttack.
#include <list>

typedef bool Bool;
typedef unsigned int UnsignedInt;
#define NULL 0

typedef UnsignedInt ObjectID;
enum
{
	INVALID_ID = 0
};
enum Relationship
{
	ENEMIES = 0
};
enum AbleToAttackType
{
	ATTACK_TUNNEL_NETWORK_GUARD = 4
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};
enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING,
	ATTACKRESULT_POSSIBLE
};

class Object;
class TeamPrototype;
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
	const TeamPrototype *getPrototype(void) const { return m_proto; }
	Object *rva003A105B(void);
	void rva0039D84A(Object *target);
private:
	unsigned char m_pad00[0x30];
	TeamPrototype *m_proto; // +0x30
};
class TunnelTracker
{
public:
	Object *getCurNemesis(void);
	void updateNemesis(const Object *target);
	const std::list<ObjectID> *getContainerList(void) const { return &m_tunnelIDs; }
private:
	unsigned char m_pad00[4];
	std::list<ObjectID> m_tunnelIDs; // +4 (head at +8)
};
class Player
{
public:
	TunnelTracker *getTunnelSystem(void) { return m_tunnelSystem; }
private:
	unsigned char m_pad00[0x2E8];
	TunnelTracker *m_tunnelSystem; // +0x2E8
};
class TurretStateMachine
{
public:
	Object *getGoalObject(void);
};
class AIUpdateInterface
{
public:
	Object *getGoalObject(void) { return m_turret->getGoalObject(); }
private:
	unsigned char m_pad00[0x30];
	TurretStateMachine *m_turret; // +0x30
};
struct DamageInfoInput
{
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
	unsigned char m_pad0C[0x70 - 0x0C];
};
struct DamageInfoOutput
{
	unsigned char m_pad00[8];
	Bool m_noEffect; // +8 (DamageInfo +0x78)
};
struct DamageInfo
{
	DamageInfoInput in;
	DamageInfoOutput out;
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
	virtual const DamageInfo *getLastDamageInfo(void) const = 0;
	virtual UnsignedInt getLastDamageTimestamp(void) const = 0;
};
class Object
{
public:
	ObjectID getID(void) const { return m_id; }
	Team *getTeam(void) { return m_team; }
	AIUpdateInterface *getAI(void) { return m_ai; }
	BodyModuleInterface *getBodyModule(void) const { return m_body; }
	Player *getControllingPlayer(void) const;
	Relationship getRelationship(const Object *that) const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType t, const Object *target, CommandSourceType commandSource) const;
private:
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
	UnsignedInt getFrame(void) const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
struct TAiData
{
	unsigned char m_pad00[0x40];
	UnsignedInt m_guardEnemyScanRate; // +0x40
};
class AI
{
public:
	const TAiData *getAiData(void) const { return m_aiData; }
private:
	unsigned char m_pad00[0x18];
	TAiData *m_aiData; // +0x18
};
extern GameLogic *TheGameLogic;
extern AI *g_Va009FF0F8;
class StateMachine
{
public:
	virtual ~StateMachine(void);
	virtual void slot01(void); virtual void slot02(void); virtual void slot03(void);
	virtual void slot04(void); virtual void slot05(void); virtual void slot06(void);
	virtual void slot07(void); virtual void slot08(void); virtual void slot09(void);
	virtual void slot10(void); virtual void slot11(void); virtual void slot12(void);
	virtual void slot13(void);
	virtual void setGoalObject(const Object *obj);
	Object *getOwner(void) const { return m_owner; }
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
};
class AITNGuardMachine : public StateMachine
{
public:
	void setNemesisID(ObjectID id) { m_nemesisToAttack = id; }
	ObjectID getNemesisID(void) const { return m_nemesisToAttack; }
	Bool lookForInnerTarget(void);
private:
	unsigned char m_pad18[0x48 - 0x18];
	ObjectID m_nemesisToAttack; // +0x48
};

// ?lookForInnerTarget@AITNGuardMachine@@QAE_NXZ present-unmatched
Bool AITNGuardMachine::lookForInnerTarget(void)
{
	Object *owner = getOwner();
	Object *currentTunnel;
	Object *victim;
	BodyModuleInterface *body;

	// Check if team auto targets same victim.
	if (owner->getTeam()->getPrototype()->getTemplateInfo()->m_attackCommonTarget)
	{
		Object *teamVictim = owner->getTeam()->rva003A105B();
		if (teamVictim)
		{
			setNemesisID(teamVictim->getID());
			return true;
		}
	}

	// Find tunnel network to defend.
	// Scan my tunnels.
	Player *ownerPlayer = getOwner()->getControllingPlayer();
	if (!ownerPlayer)
		return false;
	TunnelTracker *tunnels = ownerPlayer->getTunnelSystem();
	if (tunnels == NULL)
		return false;
	if (tunnels->getCurNemesis()) {
		setNemesisID(tunnels->getCurNemesis()->getID());
		return true;
	}
	const std::list<ObjectID> *allTunnels = tunnels->getContainerList();
	for (std::list<ObjectID>::const_iterator iter = allTunnels->begin(); iter != allTunnels->end(); iter++) {
		currentTunnel = TheGameLogic->findObjectByID(*iter);
		if (currentTunnel) {
			// Check for attacking.
			if (currentTunnel->getAI()) {
				victim = currentTunnel->getAI()->getGoalObject();
				if (owner->getRelationship(victim) == ENEMIES) {
					setNemesisID(victim->getID());
					return true;
				}
			}
			// check for attacked.
			body = currentTunnel->getBodyModule();
			if (body) {
				const DamageInfo *info = body->getLastDamageInfo();
				if (info) {
					if (info->out.m_noEffect) {
						continue;
					}
					if (body->getLastDamageTimestamp() + g_Va009FF0F8->getAiData()->m_guardEnemyScanRate > TheGameLogic->getFrame()) {
						// winner.
						ObjectID attackerID = info->in.m_sourceID;
						Object *attacker = TheGameLogic->findObjectByID(attackerID);

						if (attacker)
						{
							if (owner->getRelationship(attacker) != ENEMIES) {
								continue;
							}
							CanAttackResult result = getOwner()->getAbleToAttackSpecificObject(ATTACK_TUNNEL_NETWORK_GUARD, attacker, CMD_FROM_AI);
							if (result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
							{
								setNemesisID(attackerID);
								owner->getTeam()->rva0039D84A(attacker);
								tunnels->updateNemesis(attacker);
								return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}
