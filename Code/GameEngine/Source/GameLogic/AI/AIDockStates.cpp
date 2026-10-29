// cl: /DNDEBUG /MD
//
// AIDock state bodies ported from Zero Hour's GameEngine/Source/GameLogic/AI/
// AIDock.cpp (GeneralsMD tree vendored under reference/open-bfme-1/inputs/
// reference). Vtables are named by their slot-2 name getters:
//  - AIDockApproachState::update, retail 0x00544348 (28 bytes): slot 6 of
//    0x00C69AB0 (AIDockApproachState), over the pinned base
//    AIInternalMoveToState::update 0x00347460.
//  - AIDockProcessDockState::onEnter, retail 0x00544646 (42 bytes), and
//    update, retail 0x00544B96 (109 bytes): slots 4 and 6 of 0x00C69A20
//    (AIDockProcessDockState).
//  - AIDockProcessDockState::setNextDockActionFrame, retail 0x005445FF
//    (71 bytes), and findMyDrone, retail 0x00544B41 (85 bytes): the two
//    helpers those slots call.
//  - AIDockApproachState::onExit, retail 0x005441AF (91 bytes): slot 5 of
//    0x00C69AB0, over the rowed base AIInternalMoveToState::onExit.
//  - AIDockWaitForClearanceState::onEnter, update and onExit, retail
//    0x0054420A (14 bytes), 0x00544218 (115 bytes) and 0x0054428B (65 bytes):
//    slots 4-6 of 0x00C69940 (AIDockWaitForClearanceState); m_enterFrame
//    +0x20, and the timeout's LOGICFRAMES_PER_SECOND is the rowed int global
//    BfmeLogicFramesPerSecond. The update's flag-to-result 'and al, 0xFE' needs /G7, which
//    the unit's other bodies accept unchanged.
//  - AIDockProcessDockState::onExit, retail 0x00544670 (10 bytes): slot 5 of
//    0x00C69A20; the inline StateMachine::unlock clears +0x38.
// BFME2 layout (target evidence): m_nextDockActionFrame +0x20, m_droneID
// +0x24; AI +0x258 with getSupplyTruckAIInterface at AI vslot 95 (+0x17C) and
// getActionDelayForDock at its vslot 19 (+0x4C); DockUpdateInterface
// isClearToEnter at vslot 3 (+0x0C), onApproachReached at vslot 8 (+0x20),
// action at vslot 12 (+0x30), cancelDock at vslot 13 (+0x34) and isDockOpen at
// vslot 14 (+0x38). BFME 2's DroneInfo has
// no found flag (owner, drone); its findDrone callback is the rowed
// Rva00544B13Callback.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
#include <stddef.h>
#include "../../Common/GameLogicObjectLookupView.h"
// The AIDock view shared by every unit of retail's AIDock translation unit
// (Zero Hour's GameEngine/Source/GameLogic/AI/AIDock.cpp). BFME 2 layout
// (target evidence): StateMachine owner +0x14 and lock flag +0x38,
// AIDockMachine approach position +0x3C; State machine +0x18, a 0x20-byte base;
// AIInternalMoveToState goal position +0x20 and adjustsDestination +0x48 in a
// 0x4C-byte object; Object id +0x74 and AI +0x258.
enum StateExitType
{
	EXIT_NORMAL = 0,
	EXIT_RESET
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
class Object;
class StateMachine;
struct State;
struct StateConditionInfo
{
	void *m_test;
	StateID m_toStateID;
	void *m_userData;
};
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class SupplyTruckAIInterface : public VSlots<19>
{
public:
	virtual UnsignedInt getActionDelayForDock(Object *dock) = 0;
};
class AIUpdateInterface : public VSlots<95>
{
public:
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface() = 0;
	void ignoreObstacle(const Object *obj);
};
// Slots 0-16 keep Zero Hour's DockUpdateInterface order; 17-19 are BFME 2's.
class DockUpdateInterface
{
public:
	virtual Bool isClearToApproach(const Object *docker) const = 0;
	virtual Bool reserveApproachPosition(Object *docker, Coord3D *position, Int *index) = 0;
	virtual Bool advanceApproachPosition(Object *docker, Coord3D *position, Int *index) = 0;
	virtual Bool isClearToEnter(const Object *docker) const = 0;
	virtual Bool isClearToAdvance(const Object *docker, Int dockerIndex) const = 0;
	virtual void getEnterPosition(Object *docker, Coord3D *position) = 0;
	virtual void getDockPosition(Object *docker, Coord3D *position) = 0;
	virtual void getExitPosition(Object *docker, Coord3D *position) = 0;
	virtual void onApproachReached(Object *docker) = 0;
	virtual void onEnterReached(Object *docker) = 0;
	virtual void onDockReached(Object *docker) = 0;
	virtual void onExitReached(Object *docker) = 0;
	virtual Bool action(Object *docker, Object *drone) = 0;
	virtual void cancelDock(Object *docker) = 0;
	virtual Bool isDockOpen() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual Bool slot18() = 0;
	virtual Bool slot19() = 0;
};
class ExitInterface : public VSlots<8>
{
public:
	virtual Coord3D *slot08() = 0;
};
class Player
{
public:
	int iterateObjects(int (*func)(Object *, void *), void *userData) const;
};
class Object
{
public:
	ObjectID getID() const { return m_id; }
	AIUpdateInterface *getAI() { return m_ai; }
	static __forceinline AIUpdateInterface *getAI(const Object *object) { return object->m_ai; }
	Player *getControllingPlayer() const;
	DockUpdateInterface *getDockUpdateInterface();
	ExitInterface *getObjectExitInterface() const;
	unsigned char m_pad00[0x74];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
};
class StateMachine
{
public:
	StateMachine(Object *owner, UnsignedInt nameKey, Bool flag);
	virtual ~StateMachine();
	void defineState(StateID id, State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions = NULL);
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	void unlock() { m_locked = false; }
	// LINK: same-body helper under a TU-unique name (identical inlined
	// bytes). This TU's unlock copy loses to the first-in-order copy (no
	// retail address); the onExit call inlines it but still emits the
	// loser COMDAT. Rebinding there emits only this unique (trivially kept)
	// copy. No flags touched.
	void bfme_unlock() { m_locked = false; }
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x38 - 0x18];
	Bool m_locked; // +0x38
	unsigned char m_pad39[0x3C - 0x39];
};
class TurretStateMachine : public StateMachine
{
public:
	Object *getGoalObject();
};
class AIDockMachine : public StateMachine
{
public:
	AIDockMachine(Object *owner);
	virtual ~AIDockMachine();
	// condition 0x005440F6, the only entry of the .rdata table 0x00869C78
	// (Zero Hour's ableToAdvance: wait-for-clearance -> advance-position)
	static Bool ableToAdvance(State *thisState, void *userData);
	int m_approachPosition;	// +0x3C dock approach slot (-1: none)
};
struct State
{
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	virtual void slot07();
	virtual Bool isIdle() const;
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	StateMachine *m_machine; // +0x18
	bool m_tail1C;
	unsigned char m_pad1D[0x20 - 0x1D];
};
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual ~AIInternalMoveToState();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	Bool m_adjustsDestination; // +0x48
	unsigned char m_pad49[0x4C - 0x49];
};
class Rva005447ED : public AIInternalMoveToState
{
public:
	Rva005447ED(StateMachine *machine);
	virtual StateReturnType onEnter();
};
class AIDockApproachState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};
class Rva00544095 : public State
{
public:
	Rva00544095(StateMachine *machine);
private:
	unsigned char m_pad20[0x24 - 0x20];
};
class AIDockWaitForClearanceState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	UnsignedInt m_enterFrame; // +0x20
};
class Rva005442CC : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};
class Rva00544810 : public AIInternalMoveToState
{
public:
	Rva00544810(StateMachine *machine);
};
class Rva0054482D : public AIInternalMoveToState
{
public:
	Rva0054482D(StateMachine *machine);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};
class Rva0054484A : public AIInternalMoveToState
{
public:
	Rva0054484A(StateMachine *machine);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};
class Rva005445D4 : public State
{
public:
	Rva005445D4(StateMachine *machine);
private:
	int m_20;
	int m_24;
};
class AIDockProcessDockState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	void setNextDockActionFrame();
	UnsignedInt m_nextDockActionFrame; // +0x20
	Object *findMyDrone();
private:
	ObjectID m_droneID; // +0x24
};
class Rva00544884 : public AIInternalMoveToState
{
public:
	Rva00544884(StateMachine *machine);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};
class Rva00544867 : public AIInternalMoveToState
{
public:
	Rva00544867(StateMachine *machine);
	virtual StateReturnType onEnter();
};

extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond;
#define LOGICFRAMES_PER_SECOND BfmeLogicFramesPerSecond

struct DroneInfo
{
	Object *owner;
	Object *drone;
};
int Rva00544B13Callback(void *obj, void *droneInfo);

StateReturnType AIDockApproachState::update( void )
{
	Object *goalObject = getMachineGoalObject();

	// if we have nothing to dock with, fail
	if (goalObject == NULL)
		return STATE_FAILURE;

	// this behavior is an extention of basic MoveTo
	return AIInternalMoveToState::update();
}

void AIDockProcessDockState::setNextDockActionFrame()
{
	// If we have a SupplyTruck Interface, then we will ask for our specific delay time
	SupplyTruckAIInterface *supplyTruck = getMachineOwner()->getAI()->getSupplyTruckAIInterface();
	if( supplyTruck )
	{
		m_nextDockActionFrame = TheGameLogic->getFrame() + supplyTruck->getActionDelayForDock( getMachineGoalObject() );
		return;
	}

	// The default is that it is simply okay to Action right away
	m_nextDockActionFrame = TheGameLogic->getFrame();
}

StateReturnType AIDockProcessDockState::onEnter( void )
{
	Object *goalObject = getMachineGoalObject();

	DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	// if we have nothing to dock with, fail
	if (dock == NULL)
		return STATE_FAILURE;

	setNextDockActionFrame();

	return STATE_CONTINUE;
}

StateReturnType AIDockProcessDockState::update( void )
{
	Object *goalObject = getMachineGoalObject();

	DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	// if we have nothing to dock with, fail
	if (dock == NULL)
		return STATE_FAILURE;

	// Some dockers can have a delay built in
	if( TheGameLogic->getFrame() < m_nextDockActionFrame )
		return STATE_CONTINUE;
	setNextDockActionFrame();

	Object *drone = findMyDrone();

	// invoke the dock's action until it tells us it is done or the dock becomes closed
	if( dock->isDockOpen() == false || dock->action( getMachineOwner(), drone ) == false )
		return STATE_SUCCESS;

	return STATE_CONTINUE;
}

Object* AIDockProcessDockState::findMyDrone()
{
	//First do the fast cached check.
	Object *drone = TheGameLogic->findObjectByID( m_droneID );
	if( drone )
	{
		return drone;
	}

	//Nope... look for a drone (perhaps we just finished building one after docking?)
	Object *self = getMachineOwner();
	Player *player = self->getControllingPlayer();
	DroneInfo dInfo;
	dInfo.drone = NULL;
	dInfo.owner = self;

	//Iterate the objects in search for a drone with a producer ID of me.
	if( player )
	{
		player->iterateObjects( (int (*)(Object *, void *))Rva00544B13Callback, (void*)&dInfo );
		if( dInfo.drone )
		{
			m_droneID = dInfo.drone->getID();
		}
	}
	return dInfo.drone;
}

void AIDockApproachState::onExit( StateExitType status )
{
	Object *goalObject = getMachineGoalObject();

	DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	// tell the dock we have approached
	if (dock)
	{
		// if we were interrupted, let the dock know we're not coming
		if (status == EXIT_RESET || dock->isDockOpen() == false)
			dock->cancelDock( getMachineOwner() );
		else
			dock->onApproachReached( getMachineOwner() );
	}

	// this behavior is an extention of basic MoveTo
	AIInternalMoveToState::onExit( status );
}

StateReturnType AIDockWaitForClearanceState::onEnter( void )
{
	m_enterFrame = TheGameLogic->getFrame();
	return STATE_CONTINUE;
}

StateReturnType AIDockWaitForClearanceState::update( void )
{
	Object *goalObject = getMachineGoalObject();

	if( goalObject == NULL )
		return STATE_FAILURE;

	DockUpdateInterface *dock = goalObject->getDockUpdateInterface();

	// if we have nothing to dock with, fail
	if (dock == NULL)
		return STATE_FAILURE;

	// fail if the dock is closed
	if( dock->isDockOpen() == false )
	{
		dock->cancelDock( getMachineOwner() );
		return STATE_FAILURE;
	}

	// if the dock says we can enter, our wait is over
	if (dock->isClearToEnter( getMachineOwner() ))
		return STATE_SUCCESS;

	if (m_enterFrame + 30*LOGICFRAMES_PER_SECOND < TheGameLogic->getFrame()) {
		return STATE_FAILURE;
	}
	// continue to wait
	return STATE_CONTINUE;
}

void AIDockWaitForClearanceState::onExit( StateExitType status )
{
	Object *goalObject = getMachineGoalObject();

	DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	// if we were interrupted, let the dock know we're not coming
	if (dock && (dock->isDockOpen() == false || status == EXIT_RESET))
		dock->cancelDock( getMachineOwner() );
}

void AIDockProcessDockState::onExit( StateExitType status )
{
	// unlock the machine
	getMachine()->bfme_unlock();
}