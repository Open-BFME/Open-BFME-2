// cl: /O1 /DNDEBUG /MD /arch:SSE /EHsc
//
// AITNGuard (tunnel-network guard) state bodies ported from Zero Hour's
// GameEngine/Source/GameLogic/AI/AITNGuard.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). Vtables are named by their slot-2
// name getters:
//  - AITNGuardInnerState::onExit, retail 0x00545BB7 (51 bytes): slot 5 of
//    0x00C6A140; attack sub-state +0x2C.
//  - AITNGuardOuterState::onExit, retail 0x00545BEA (51 bytes): slot 5 of
//    0x00C6A198; attack sub-state +0x28.
//  - AITNGuardReturnState::update, retail 0x00545C4D (93 bytes): slot 6 of
//    0x00C6A1F0, over the pinned AIEnterState::update 0x0035455A.
//  - AITNGuardAttackAggressorState::onExit, retail 0x00545CF7 (76 bytes):
//    slot 5 of 0x00C6A298; attack sub-state +0x28.
//  - AITNGuardAttackAggressorState::update, retail 0x0054684E (93 bytes):
//    slot 6 of 0x00C6A298; while the attack machine is in FIRE_WEAPON (state
//    id 103; INVALID_STATE_ID 999999 when it has no state) the player's
//    tunnel tracker gets updateNemesis (pinned 0x004F5935, Zero Hour's body:
//    take the target when there is no nemesis, refresh the timestamp when it
//    is the nemesis).
//  - AITNGuardInnerState::onEnter, retail 0x0054632D (156 bytes), and
//    AITNGuardOuterState::onEnter, retail 0x005464CE (169 bytes): slots 4 of
//    0x00C6A140 and 0x00C6A198; Zero Hour's bodies (exit conditions +0x20 with
//    the give-up frame at +0x24 from TAiData +0x3C, new AIAttackState through
//    the rowed ctor; guard mode at machine +0x4C). Retail keeps TheGameLogic
//    in a register across the nemesis lookup, so it is read once into a local.
//  - AITNGuardOuterState::update, retail 0x00546577 (110 bytes): slot 6 of
//    0x00C6A198; Zero Hour's body. The team's prototype is +0x30 and its
//    template info's m_attackCommonTarget lands at prototype +0x216 (the split
//    between prototype and embedded template info is not established; it is
//    modelled as info at +0x200).
//  - AITNGuardAttackAggressorState::onEnter, retail 0x0054675D (241 bytes):
//    slot 4 of 0x00C6A298; Zero Hour's body (body module +0x254, vslot 15
//    getLastDamageInfo, source id +8).
//  - AITNGuardIdleState::onEnter, retail 0x00545CAF (72 bytes): slot 4 of
//    0x00C6A038 (AITNGuardIdleState); Zero Hour's randomised first scan (AITNGuard.cpp
//    line 586; TAiData m_guardEnemyScanRate +0x40, m_nextEnemyScanTime +0x20),
//    then the AI's friend_setGoalObject(NULL) (rowed opaque
//    AIUpdateInterface::rva00262B0F).
//  - AITNGuardInnerState::update, retail 0x005463C9 (261 bytes): slot 6 of
//    0x00C6A140; Zero Hour's body, with the guard machine read once into a
//    local for the nemesis and owner lookups (retail keeps it in a register
//    across the call). TunnelNetworkScan is the rowed file
//    helper 0x00545DEE, which takes the owner in ECX (__fastcall, see
//    AITNGuardScan.cpp).
// BFME2 layout (target evidence): the attack sub-state is deleted with a
// global-scope delete (vslot 0 with flag 0, then ::operator delete); owner
// team +0x304, object id +0x74, player tunnel tracker +0x2E8, guard machine
// nemesis id +0x48. setTeamTargetObject is the rowed Team::rva0039D84A;
// Team::getTeamTargetObject (0x003A105B) and TunnelTracker::getCurNemesis
// (0x004F5684) are pinned ZH-shaped bodies.
typedef bool Bool;
typedef unsigned int UnsignedInt;
#define NULL 0
enum ObjectID
{
	INVALID_ID = 0
};
enum StateExitType
{
	EXIT_NORMAL = 0,
	EXIT_RESET = 1
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
class Object;
class AIUpdateInterface;
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
	void rva0039D84A(Object *target);
	void setTeamTargetObject(Object *target) { rva0039D84A(target); }
	Object *getTeamTargetObject();
private:
	unsigned char m_pad00[0x30];
	TeamPrototype *m_proto; // +0x30
};
class TunnelTracker
{
public:
	Object *getCurNemesis();
	void updateNemesis(const Object *target);
};
class Player
{
public:
	TunnelTracker *getTunnelSystem() { return m_tunnelSystem; }
private:
	unsigned char m_pad00[0x2E8];
	TunnelTracker *m_tunnelSystem; // +0x2E8
};
struct DamageInfoInput
{
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
};
struct DamageInfo
{
	DamageInfoInput in;
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
};
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	ObjectID getID() const { return m_id; }
	Team *getTeam() { return m_team; }
	Player *getControllingPlayer() const;
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
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
struct TAiData
{
	unsigned char m_pad00[0x3C];
	UnsignedInt m_guardChaseUnitFrames; // +0x3C
	UnsignedInt m_guardEnemyScanRate; // +0x40
};
int GetGameLogicRandomValue(int low, int high, char *file, int line);
#define AITNGUARD_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AITNGuard.cpp"
class AIUpdateInterface
{
public:
	void rva00262B0F(int goal); // friend_setGoalObject
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
extern GameLogic *TheGameLogic;
typedef UnsignedInt StateID;
enum
{
	INVALID_STATE_ID = 999999
};
class State;
class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13();
	virtual void setGoalObject(const Object *obj);
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	inline StateID getCurrentStateID() const;
private:
	State *m_currentState; // +0x04
	unsigned char m_pad08[0x14 - 0x08];
	Object *m_owner; // +0x14
};
class AttackStateMachine : public StateMachine
{
public:
	enum
	{
		FIRE_WEAPON = 103
	};
};
class AITNGuardMachine : public StateMachine
{
public:
	void setNemesisID(ObjectID id) { m_nemesisToAttack = id; }
	ObjectID getNemesisID() const { return m_nemesisToAttack; }
	int getGuardMode() const { return m_guardMode; }
private:
	unsigned char m_pad18[0x48 - 0x18];
	ObjectID m_nemesisToAttack; // +0x48
	int m_guardMode; // +0x4C
};
enum
{
	GUARDMODE_NORMAL = 0,
	GUARDMODE_GUARD_WITHOUT_PURSUIT = 1
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
	StateID getID() const { return m_ID; }
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	StateID m_ID; // +0x04
	unsigned char m_pad08[0x18 - 0x08];
	StateMachine *m_machine; // +0x18
};
// ?StateMachine::getCurrentStateID absent-from-retail
inline StateID StateMachine::getCurrentStateID() const
{
	return m_currentState ? m_currentState->getID() : (StateID)INVALID_STATE_ID;
}
class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const = 0;
};
class TunnelNetworkExitConditions : public AttackExitConditionsInterface
{
public:
	UnsignedInt m_attackGiveUpFrame; // +0x04 (state +0x24)
	virtual Bool shouldExit(const StateMachine *machine) const;
};
class AIAttackState : public State
{
public:
	AIAttackState(StateMachine *machine, Bool follow, Bool attackingObject, Bool forceAttacking, AttackExitConditionsInterface *attackParameters);
private:
	unsigned char m_pad1C[0x50 - 0x1C]; // sizeof(AIAttackState) 0x50 (the operator new size)
};
class AIEnterState : public State
{
public:
	virtual StateReturnType update();
};
class AITNGuardInnerState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	AITNGuardMachine *getGuardMachine() { return (AITNGuardMachine *)getMachine(); }
	unsigned char m_pad1C[0x20 - 0x1C];
	TunnelNetworkExitConditions m_exitConditions; // +0x20
	Bool m_scanForEnemy; // +0x28
	AIAttackState *m_attackState; // +0x2C
};
class AITNGuardOuterState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	AITNGuardMachine *getGuardMachine() { return (AITNGuardMachine *)getMachine(); }
	unsigned char m_pad1C[0x20 - 0x1C];
	TunnelNetworkExitConditions m_exitConditions; // +0x20
	AIAttackState *m_attackState; // +0x28
};
class AITNGuardReturnState : public AIEnterState
{
public:
	virtual StateReturnType update();
private:
	AITNGuardMachine *getGuardMachine() { return (AITNGuardMachine *)getMachine(); }
};
class AITNGuardIdleState : public State
{
public:
	virtual StateReturnType onEnter();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	UnsignedInt m_nextEnemyScanTime; // +0x20
};
class AITNGuardAttackAggressorState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	AITNGuardMachine *getGuardMachine() { return (AITNGuardMachine *)getMachine(); }
	unsigned char m_pad1C[0x20 - 0x1C];
	TunnelNetworkExitConditions m_exitConditions; // +0x20
	AIAttackState *m_attackState; // +0x28
};

void AITNGuardInnerState::onExit( StateExitType status )
{
	if (m_attackState)
	{
		m_attackState->onExit(status);
		::delete m_attackState;
		m_attackState = NULL;
	}
}

void AITNGuardOuterState::onExit( StateExitType status )
{
	if (m_attackState)
	{
		m_attackState->onExit(status);
		::delete m_attackState;
		m_attackState = NULL;
	}
}

StateReturnType AITNGuardReturnState::update( void )
{
	Player *ownerPlayer = getMachineOwner()->getControllingPlayer();
	if (getMachineOwner()->getTeam()) {
		Object *teamVictim = getMachineOwner()->getTeam()->getTeamTargetObject();
		if (teamVictim)	{
			getGuardMachine()->setNemesisID(teamVictim->getID());
			return STATE_FAILURE; // Fail to return goes to inner attack state.
		}
	}
	// Check tunnel for target.
	TunnelTracker *tunnels = NULL;
	if (ownerPlayer) {
		tunnels = ownerPlayer->getTunnelSystem();
	}

	if (tunnels) {
		Object *nemesis = tunnels->getCurNemesis();
		if (nemesis) {
			getGuardMachine()->setNemesisID(nemesis->getID());
			return STATE_FAILURE; // Fail to return goes to inner attack state.
		}
	}

	// Just let the return movement finish.
	StateReturnType ret = AIEnterState::update();
	if (ret==STATE_CONTINUE) return STATE_CONTINUE;
	return STATE_SUCCESS;
}

void AITNGuardAttackAggressorState::onExit( StateExitType status )
{
	Object *obj = getMachineOwner();
	if (m_attackState)
	{
		m_attackState->onExit(status);
		::delete m_attackState;
		m_attackState = NULL;
	}

	if (obj->getTeam())
	{
		obj->getTeam()->setTeamTargetObject(NULL); // clear the target.
	}
}

StateReturnType AITNGuardAttackAggressorState::update( void )
{	
	if (m_attackState->getMachine()->getCurrentStateID() == AttackStateMachine::FIRE_WEAPON) {
		AITNGuardMachine *machine = getGuardMachine();
		Object *nemesis = TheGameLogic->findObjectByID(machine->getNemesisID());
		Player *ownerPlayer = machine->getOwner()->getControllingPlayer();
		TunnelTracker *tunnels = NULL;
		if (ownerPlayer) {
			tunnels = ownerPlayer->getTunnelSystem();
		}
		if (tunnels) tunnels->updateNemesis(nemesis);
	}
	return m_attackState->update();
}

StateReturnType AITNGuardInnerState::onEnter( void )
{
	GameLogic *logic = TheGameLogic;
	Object* nemesis = logic->findObjectByID(getGuardMachine()->getNemesisID()) ;
	if (nemesis == NULL) 
	{
		return STATE_SUCCESS;
	}
	m_exitConditions.m_attackGiveUpFrame = logic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;

	m_attackState = new AIAttackState(getMachine(), false, true, false, &m_exitConditions);

	m_attackState->getMachine()->setGoalObject(nemesis);

	StateReturnType returnVal = m_attackState->onEnter();
	if (returnVal == STATE_CONTINUE) {
		return STATE_CONTINUE;
	}

	// if we had no one to attack, we were successful, so go to the next state.
	return STATE_SUCCESS;
}

StateReturnType AITNGuardOuterState::onEnter( void )
{
	if (getGuardMachine()->getGuardMode() == GUARDMODE_GUARD_WITHOUT_PURSUIT)
	{
		// "patrol" mode does not follow targets outside the guard area.
		return STATE_SUCCESS;
	}

	GameLogic *logic = TheGameLogic;
	Object* nemesis = logic->findObjectByID(getGuardMachine()->getNemesisID()) ;
	if (nemesis == NULL) 
	{
		return STATE_SUCCESS;
	}

	m_exitConditions.m_attackGiveUpFrame = logic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;
	m_attackState = new AIAttackState(getMachine(), false, true, false, &m_exitConditions);
	m_attackState->getMachine()->setGoalObject(nemesis);

	StateReturnType returnVal = m_attackState->onEnter();
	if (returnVal == STATE_CONTINUE) {
		return STATE_CONTINUE;
	}

	// if we had no one to attack, we were successful, so go to the next state.
	return STATE_SUCCESS;
}

Object *__fastcall TunnelNetworkScan(Object *owner);

//--------------------------------------------------------------------------------------
StateReturnType AITNGuardInnerState::update( void )
{
	AITNGuardMachine *machine = getGuardMachine();
	Object* nemesis = TheGameLogic->findObjectByID(machine->getNemesisID()) ;
	Player *ownerPlayer = machine->getOwner()->getControllingPlayer();
	TunnelTracker *tunnels = NULL;
	if (ownerPlayer) {
		tunnels = ownerPlayer->getTunnelSystem();
	}

	Object* owner = getMachineOwner();
	// killed him.
	Object *teamVictim = owner->getTeam()->getTeamTargetObject();
	if (nemesis == NULL)
	{
		if (teamVictim)
		{
			getGuardMachine()->setNemesisID(teamVictim->getID());
			m_exitConditions.m_attackGiveUpFrame = TheGameLogic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;
			return STATE_CONTINUE;
		}

		// Check tunnel.
		if (tunnels) {
			nemesis = tunnels->getCurNemesis();
			if (nemesis) {
				getGuardMachine()->setNemesisID(nemesis->getID());
				m_exitConditions.m_attackGiveUpFrame = TheGameLogic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;
				return STATE_CONTINUE;
			}
		}

		if (m_scanForEnemy) {
			m_scanForEnemy = false; // we just do 1 scan.
			nemesis = TunnelNetworkScan(owner);
			if (nemesis) {
				m_attackState->onExit(EXIT_RESET);
				m_attackState->getMachine()->setGoalObject(nemesis);
				if (tunnels) {
					tunnels->updateNemesis(nemesis);
				}
				StateReturnType returnVal = m_attackState->onEnter();
				return returnVal;
			}
		}
	} else {
		if (nemesis != teamVictim && teamVictim != NULL) {
			tunnels->updateNemesis(nemesis);
			getGuardMachine()->setNemesisID(teamVictim->getID());
		}
	}
	return m_attackState->update();
}

StateReturnType AITNGuardOuterState::update( void )
{
	Object *owner = getMachineOwner();
	Object* goalObj = m_attackState->getMachineGoalObject();
	if (goalObj) 
	{
	}	else {
		Object* nemesis = TheGameLogic->findObjectByID(getGuardMachine()->getNemesisID()) ;
		if (nemesis) {
			goalObj = nemesis;
		}
		// Check if team auto targets same victim.
		Object *teamVictim = NULL;
		if (goalObj == NULL && owner->getTeam()->getPrototype()->getTemplateInfo()->m_attackCommonTarget) 
		{
			teamVictim = owner->getTeam()->getTeamTargetObject();
			if (teamVictim) 
			{	
				goalObj = teamVictim;	
			}
			m_attackState->getMachine()->setGoalObject(goalObj);
			return m_attackState->onEnter();
		}
	}
	
	return m_attackState->update();
}

StateReturnType AITNGuardAttackAggressorState::onEnter( void )
{
	Object *obj = getMachineOwner();
	ObjectID nemID = INVALID_ID;

	if (obj->getBodyModule() && obj->getBodyModule()->getLastDamageInfo()->in.m_sourceID) {
		nemID = obj->getBodyModule()->getLastDamageInfo()->in.m_sourceID;
		getGuardMachine()->setNemesisID(nemID);	 

	}

	AITNGuardMachine *machine = getGuardMachine();
	Object *nemesis = TheGameLogic->findObjectByID(machine->getNemesisID());
	if (nemesis == NULL) 
	{
		return STATE_SUCCESS;
	}

	Player *ownerPlayer = machine->getOwner()->getControllingPlayer();
	TunnelTracker *tunnels = NULL;
	if (ownerPlayer) {
		tunnels = ownerPlayer->getTunnelSystem();
	}
	if (tunnels) tunnels->updateNemesis(nemesis);

	m_exitConditions.m_attackGiveUpFrame = TheGameLogic->getFrame() + TheAI->getAiData()->m_guardChaseUnitFrames;
	m_attackState = new AIAttackState(getMachine(), true, true, false, &m_exitConditions);
	m_attackState->getMachine()->setGoalObject(nemesis);

	StateReturnType returnVal = m_attackState->onEnter();
	if (returnVal == STATE_CONTINUE) {
		return STATE_CONTINUE;
	}

	// if we had no one to attack, we were successful, so go to the next state.
	return STATE_SUCCESS;
}

StateReturnType AITNGuardIdleState::onEnter( void )
{
	// first time thru, use a random amount so that everyone doesn't scan on the same frame,
	// to avoid "spikes". 
	UnsignedInt now = TheGameLogic->getFrame();
	m_nextEnemyScanTime = now + GetGameLogicRandomValue(0, TheAI->getAiData()->m_guardEnemyScanRate, AITNGUARD_FILE, 586);

	getMachineOwner()->getAI()->rva00262B0F(NULL); // friend_setGoalObject(NULL)
	return STATE_CONTINUE;
}
