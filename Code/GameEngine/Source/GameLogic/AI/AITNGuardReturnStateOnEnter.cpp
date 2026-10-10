// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// AITNGuardReturnState::onEnter ported from Zero Hour's AITNGuard.cpp.
// Target evidence: slot 4 of retail vtable 0xC6A1F0 at 0x005465E5.
// The local noinline helper preserves the banked caller's register allocation;
// Its target 0x00545F80 (129B) keeps the end iterator in EDI across lookups;
// caching end reproduces that lifetime and both bodies byte-match.
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
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
class Player;
class AIUpdateInterface
{
public:
	void rva00262B0F(int obj);
	ObjectID getCrateID() const { return m_crateID; }
private:
	unsigned char m_pad00[0x238];
	ObjectID m_crateID; // +0x238
};
struct Coord3D
{
	Real x, y, z;
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
class ExitInterface
{
public:
	virtual bool isExitBusy() const = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void exitObjectInAHurry(Object *obj) = 0;	// +0x14
};
template <int N> class VSlotsC : public VSlotsC<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlotsC<0>
{
};
class ContainModuleInterface : public VSlotsC<29>
{
public:
	virtual ExitInterface *getContainExitInterface() = 0;	// +0x74
};
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() { return m_ai; }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	Player *getControllingPlayer() const;
	ContainModuleInterface *getContain() const { return m_contain; }
	Object *getContainedBy() { return m_containedBy; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x250 - 0x78];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
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
	unsigned char m_pad00[0x40];
	UnsignedInt m_guardEnemyScanRate; // +0x40
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
extern GameLogic *TheGameLogic;
int GetGameLogicRandomValue(int low, int high, char *file, int line);
#define AITNGUARD_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AITNGuard.cpp"

static __declspec(noinline) Object *findBestTunnel(Player *ownerPlayer, const Coord3D *pos)
{
	if (!ownerPlayer) return NULL; // should never happen, but hey.  jba.
	TunnelTracker *tunnels = ownerPlayer->getTunnelSystem();
	Object *bestTunnel = NULL;
	Real bestDistSqr = 0;
	const ObjectIDList *allTunnels = tunnels->getContainerList();
	ObjectIDList::const_iterator end = allTunnels->end();
	for( ObjectIDList::const_iterator iter = allTunnels->begin(); iter != end; iter++ ) {
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

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
typedef UnsignedInt StateID;
class StateMachine : public VSlots<8>
{
public:
	virtual StateReturnType setState(StateID newStateID) = 0;	// +0x20
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void setGoalObject(const Object *obj) = 0;
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad04[0x14 - 0x04];
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
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIEnterState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
};
class AITNGuardReturnState : public AIEnterState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x54 - 0x1C];
	UnsignedInt m_nextReturnScanTime; // +0x54
};

StateReturnType AITNGuardReturnState::onEnter( void )
{
	UnsignedInt now = TheGameLogic->getFrame();
	m_nextReturnScanTime = now + GetGameLogicRandomValue(0, TheAI->getAiData()->m_guardEnemyReturnScanRate, AITNGUARD_FILE, 508);

	// Find tunnel network to enter.
	// Scan my tunnels.
	Object *bestTunnel = findBestTunnel(getMachineOwner()->getControllingPlayer(), getMachineOwner()->getPosition());
	if (bestTunnel==NULL) return STATE_FAILURE;

	getMachine()->setGoalObject(bestTunnel);
	getMachineOwner()->getAI()->rva00262B0F((int)bestTunnel);

	return AIEnterState::onEnter();
}

// AITNGuardIdleState::update, retail 0x0054665B (258 bytes), the slot after
// onEnter (0x00545CAF) in its table: Zero Hour's AITNGuard.cpp body. The
// guard machine's inner-target scan is the unrowed 0x005461A2 (pinned from
// this call); findBestTunnel is this unit's EAX/EBX-passing static.
enum
{
	AI_TN_GUARD_GET_CRATE = 5004
};
inline StateReturnType STATE_SLEEP(UnsignedInt frames) { return (StateReturnType)frames; }
class AITNGuardMachine : public StateMachine
{
public:
	Bool lookForInnerTarget(void);
	ObjectID getNemesisID() const { return m_nemesisID; }
private:
	unsigned char m_pad18[0x48 - 0x18];
	ObjectID m_nemesisID; // +0x48
};
class AITNGuardIdleState : public State
{
public:
	virtual StateReturnType update();
protected:
	AITNGuardMachine *getGuardMachine() { return (AITNGuardMachine *)getMachine(); }
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	UnsignedInt m_nextEnemyScanTime; // +0x20
};

StateReturnType AITNGuardIdleState::update( void )
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (now < m_nextEnemyScanTime)
		return STATE_SLEEP(m_nextEnemyScanTime - now);

	m_nextEnemyScanTime = now + TheAI->getAiData()->m_guardEnemyScanRate;

	getMachineOwner()->getAI()->rva00262B0F(NULL);	// friend_setGoalObject(NULL)

	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAIUpdateInterface();
	// Check to see if we have created a crate we need to pick up.
	if (ai->getCrateID() != INVALID_ID)
	{
		getMachine()->setState(AI_TN_GUARD_GET_CRATE);
		return STATE_SLEEP(m_nextEnemyScanTime - now);
	}

	// if anyone is in the inner area, return success.
	if (getGuardMachine()->lookForInnerTarget())
	{
		AITNGuardMachine *machine = getGuardMachine();
		Object *nemesis = TheGameLogic->findObjectByID(machine->getNemesisID());
		if (nemesis == NULL)
			return STATE_SLEEP(0);
		if (machine->getOwner()->getContainedBy()) {
			Object *bestTunnel = findBestTunnel(owner->getControllingPlayer(), nemesis->getPosition());
			ExitInterface* goalExitInterface = bestTunnel->getContain() ? bestTunnel->getContain()->getContainExitInterface() : NULL;
			if( goalExitInterface == NULL )
				return STATE_FAILURE;

			if( goalExitInterface->isExitBusy() )
				return STATE_SLEEP(0);// Just wait a sec.
			goalExitInterface->exitObjectInAHurry(getMachineOwner());
			return STATE_SLEEP(0);
		}
		return STATE_SUCCESS;	// Transitions to AITNGuardInnerState.
	}

	if (!owner->getContainedBy() && findBestTunnel(owner->getControllingPlayer(), owner->getPosition())) {
		return STATE_FAILURE;	 // go to AITNGuardReturnState, & enter a tunnel.
	}

	return STATE_SLEEP(m_nextEnemyScanTime - now);
}
