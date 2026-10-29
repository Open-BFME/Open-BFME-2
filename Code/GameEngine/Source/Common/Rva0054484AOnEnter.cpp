// cl: /MD
// ?onEnter@Rva0054484A@@UAE?AW4StateReturnType@@XZ, retail 0x00544480, 170 bytes.
// Virtual slot 4 (offset 0x10, onEnter) of vtable 0x00869BA0, class of ??0Rva0054484A@@QAE@PAVStateMachine@@@Z.
// Gets TurretStateMachine goal via rowed getGoalObject 0x004D7726, finds BEC via rowed Object::getDockUpdateInterface 0x0028BCB4, checks slot 0x38, notifies slot 0x34 with owner, calls slot 0x18 with owner and goalPosition, loads AI at owner+0x258, checks slot 0x48, regets goal and calls rowed ignoreObstacle 0x00268D88, CritterDesync log via theLogicRandomLogFile and fprintf when g_00E03745 set, clears adjustsDestination at +0x48, sets machine+0x38 to 1, tail-chains to pinned base onEnter 0x0034C146. Evidence: vslot slot 4; ctor TU Rva0054484ACtor; sibling Rva005447EDOnEnter tri pattern plus 0x0054467a stash adjustsDestination.
#include "../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
#include <stddef.h>
#include "GameLogicObjectLookupView.h"
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


extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

StateReturnType Rva0054484A::onEnter()
{
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	DockUpdateInterface *bec;
	if (goal == 0 || (bec = goal->getDockUpdateInterface()) == 0)
		return STATE_FAILURE;
	if (!bec->isDockOpen()) {
		bec->cancelDock(m_machine->getOwner());
		return STATE_FAILURE;
	}
	bec->getDockPosition(m_machine->getOwner(), &m_goalPosition);
	AIUpdateInterface *ai = m_machine->getOwner()->m_ai;
	if (ai != 0) {
		if (bec->slot18()) {
			Object *goal2 = ((TurretStateMachine *)m_machine)->getGoalObject();
			ai->ignoreObstacle(goal2);
			if (g_00E03745) {
				void *log = theLogicRandomLogFile;
				if (log != 0)
					fprintf(log, "CritterDesync: setAdjustDestination(FALSE) 1");
			}
			m_adjustsDestination = false;
		}
	}
	m_machine->m_locked = true;
	return AIInternalMoveToState::onEnter();
}