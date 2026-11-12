// cl: /O1 /DNDEBUG /MD /arch:SSE
// platformsdk
//
// AITNGuardReturnState::onEnter ported from Zero Hour's AITNGuard.cpp.
// Target evidence: slot 4 of retail vtable 0xC6A1F0 at 0x005465E5.
// The local noinline helper preserves the banked caller's register allocation;
// Its target 0x00545F80 (129B) keeps the end iterator in EDI across lookups;
// caching end reproduces that lifetime and both bodies byte-match.
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

#include <windows.h>
#include "../../Common/GameLogicObjectLookupView.h"

class Object;
class Player;
#include "../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
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
		const_iterator(ObjectIDListNode *objectIDListNode) : _M_node(objectIDListNode) {}
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
#include "../../../Include/Common/Player.h"
#include "../../../Include/GameLogic/Module/ExitInterface.h"
template <int N> class VSlotsC : public VSlotsC<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlotsC<0>
{
};
#include "../../../Include/GameLogic/Module/ContainModule.h"
#include "../Object/object.h"
#include "../../../Include/GameLogic/TAiData.h"
#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;
extern GameLogic *TheGameLogic;
int GetGameLogicRandomValue(int low, int high, char *file, int line);
#define AITNGUARD_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AITNGuard.cpp"

static __declspec(noinline) Object *findBestTunnel(Player *ownerPlayer, const Coord3D *pos)
{
	if (!ownerPlayer) return NULL; // should never happen, but hey.  jba.
	TunnelTracker *tunnels = ownerPlayer->m_tunnelSystem;
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
#include "../../../Include/Common/StateMachineClass.h"
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
	unsigned char m_pad20[0x54 - 0x20];
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
	getMachineOwner()->getAI()->friend_setGoalObject(bestTunnel);

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
#include "../../../Include/GameLogic/AITNGuardMachine.h"
class AITNGuardIdleState : public State
{
public:
	virtual StateReturnType update();
protected:
	AITNGuardMachine *getGuardMachine() { return (AITNGuardMachine *)getMachine(); }
private:
	UnsignedInt m_nextEnemyScanTime; // +0x20
};

StateReturnType AITNGuardIdleState::update( void )
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (now < m_nextEnemyScanTime)
		return STATE_SLEEP(m_nextEnemyScanTime - now);

	m_nextEnemyScanTime = now + TheAI->getAiData()->m_guardEnemyScanRate;

	getMachineOwner()->getAI()->friend_setGoalObject(NULL);	// friend_setGoalObject(NULL)

	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->getAIUpdateInterface();
	// Check to see if we have created a crate we need to pick up.
	if (ai->getCrateID() != INVALID_OBJECT_ID)
	{
		getMachine()->setState(AI_TN_GUARD_GET_CRATE);
		return STATE_SLEEP(m_nextEnemyScanTime - now);
	}

	// if anyone is in the inner area, return success.
	if (getGuardMachine()->lookForInnerTarget())
	{
		AITNGuardMachine *machine = getGuardMachine();
		Object *nemesis = TheGameLogic->findObjectByID(static_cast<ObjectID>(machine->getNemesisID()));
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
