// ?onEnter@AITNGuardReturnState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9728 date=2026-10-05
// ?onEnter@AITNGuardReturnState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /arch:SSE
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
// BFME2 layout (target evidence): the attack sub-state is deleted with a
// global-scope delete (vslot 0 with flag 0, then ::operator delete); owner
// team +0x304, object id +0x74, player tunnel tracker +0x2E8, guard machine
// nemesis id +0x48. setTeamTargetObject is the rowed Team::rva0039D84A;
// Team::getTeamTargetObject (0x003A105B) and TunnelTracker::getCurNemesis
// (0x004F5684) are pinned ZH-shaped bodies.
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;
struct Coord3D
{
	Real x, y, z;
};
#define NULL 0
enum ObjectID
{
	INVALID_ID = 0
};
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
class Object;
class Team
{
public:
	void rva0039D84A(Object *target);
	void setTeamTargetObject(Object *target) { rva0039D84A(target); }
	Object *getTeamTargetObject();
};
struct ObjectIDListNode
{
	ObjectIDListNode *m_next;
	ObjectIDListNode *m_prev;
	ObjectID m_data; // +8
};
struct ObjectIDList
{
	struct const_iterator
	{
		ObjectIDListNode *_M_node;
		const_iterator(ObjectIDListNode *n) : _M_node(n) {}
		const ObjectID &operator*() const { return _M_node->m_data; }
		const_iterator &operator++() { _M_node = _M_node->m_next; return *this; }
		const_iterator operator++(int) { const_iterator tmp = *this; _M_node = _M_node->m_next; return tmp; }
		bool operator!=(const const_iterator &o) const { return _M_node != o._M_node; }
	};
	const_iterator begin() const { return const_iterator(m_node->m_next); }
	const_iterator end() const { return const_iterator(m_node); }
	ObjectIDListNode *m_node; // sentinel
};
class TunnelTracker
{
public:
	Object *getCurNemesis();
	const ObjectIDList *getContainerList() const { return &m_tunnelIDs; }
private:
	unsigned char m_pad00[0x08];
	ObjectIDList m_tunnelIDs; // +0x08
};
class Player
{
public:
	TunnelTracker *getTunnelSystem() { return m_tunnelSystem; }
private:
	unsigned char m_pad00[0x2E8];
	TunnelTracker *m_tunnelSystem; // +0x2E8
};
class AIUpdateInterface
{
public:
	void rva00262B0F(Object *obj);
	void friend_setGoalObject(Object *obj) { rva00262B0F(obj); }
};
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() { return m_ai; }
	ObjectID getID() const { return m_id; }
	Team *getTeam() { return m_team; }
	Player *getControllingPlayer() const;
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x258 - 0x78];
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
	unsigned char m_pad00[0x44];
	UnsignedInt m_guardEnemyReturnScanRate; // +0x44
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
int GetGameLogicRandomValue(int low, int high, char *file, int line);
#define AITNGUARD_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AITNGuard.cpp"
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class StateMachine : public VSlots<14>
{
public:
	virtual void setGoalObject(const Object *obj) = 0;
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
};
class AITNGuardMachine : public StateMachine
{
public:
	void setNemesisID(ObjectID id) { m_nemesisToAttack = id; }
private:
	unsigned char m_pad18[0x48 - 0x18];
	ObjectID m_nemesisToAttack; // +0x48
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
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIAttackState : public State
{
};
class AIEnterState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
};
class AITNGuardInnerState : public State
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x2C - 0x1C];
	AIAttackState *m_attackState; // +0x2C
};
class AITNGuardOuterState : public State
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x28 - 0x1C];
	AIAttackState *m_attackState; // +0x28
};
class AITNGuardReturnState : public AIEnterState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	AITNGuardMachine *getGuardMachine() { return (AITNGuardMachine *)getMachine(); }
	unsigned char m_pad1C[0x54 - 0x1C];
	UnsignedInt m_nextReturnScanTime; // +0x54
};
class AITNGuardAttackAggressorState : public State
{
public:
	virtual void onExit(StateExitType status);
private:
	unsigned char m_pad1C[0x28 - 0x1C];
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

// Not inlined in retail: AITNGuardIdleState::update calls it twice more (not yet
// ported here), so noinline stands in for those callers.
static __declspec(noinline) Object *findBestTunnel(Player *ownerPlayer, const Coord3D *pos)
{
	if (!ownerPlayer) return NULL; // should never happen, but hey.  jba.
	TunnelTracker *tunnels = ownerPlayer->getTunnelSystem();
	Object *bestTunnel = NULL;
	Real bestDistSqr = 0;
	const ObjectIDList *allTunnels = tunnels->getContainerList();
	for( ObjectIDList::const_iterator iter = allTunnels->begin(); iter != allTunnels->end(); iter++ ) {
		// For each ID, look it up and change its team.  We all get captured together.
		Object *currentTunnel = TheGameLogic->findObjectByID( *iter );
		if( currentTunnel ) {
			Real dx = currentTunnel->getPosition()->x-pos->x;
			Real dy = currentTunnel->getPosition()->y-pos->y;
			Real distSqr = dx*dx+dy*dy;
			if (bestTunnel==NULL || distSqr<bestDistSqr) {
				bestDistSqr = distSqr;
				bestTunnel = currentTunnel;
			}
		}
	}
	return bestTunnel;
}

StateReturnType AITNGuardReturnState::onEnter( void )
{
	UnsignedInt now = TheGameLogic->getFrame();
	m_nextReturnScanTime = now + GetGameLogicRandomValue(0, TheAI->getAiData()->m_guardEnemyReturnScanRate, AITNGUARD_FILE, 508);

	// Find tunnel network to enter.
	// Scan my tunnels.
	Object *bestTunnel = findBestTunnel(getMachineOwner()->getControllingPlayer(), getMachineOwner()->getPosition());
	if (bestTunnel==NULL) return STATE_FAILURE;

	getMachine()->setGoalObject(bestTunnel);
	getMachineOwner()->getAI()->friend_setGoalObject(bestTunnel);

	return AIEnterState::onEnter();
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
