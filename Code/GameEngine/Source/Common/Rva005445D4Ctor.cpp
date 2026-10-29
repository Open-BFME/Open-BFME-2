// cl: /MD
// ??0Rva005445D4@@QAE@PAVStateMachine@@@Z, retail 0x005445D4, 37 bytes.
// Derived State ctor via rowed/pinned State hash ctor 0x004D73FC with hash
// 0x90B65C1D then zero of +0x20/+0x24 then vtable 0x00869A20. Evidence:
// vtable store at [this]; base StateCtor hash pin; caller 0x005449DD in
// FUN_009448a1; prev 0x005440CD same dir.
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


// The retail table at RVA 0x00869A20: 17 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GTurretAIIdleState@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Rva005445F9Get@@YAHXZ")();
void __identifier("?xfer@Rva005445D4@@UAEXPAVXfer@@@Z")();
void __identifier("?onEnter@AIDockProcessDockState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?onExit@AIDockProcessDockState@@UAEXW4StateExitType@@@Z")();
void __identifier("?update@AIDockProcessDockState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00C69A20[17] = {
	(const void *)&__identifier("??_GTurretAIIdleState@@UAEPAXI@Z"), // slot 0 0x004D8507
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?Rva005445F9Get@@YAHXZ"), // slot 2 0x005445F9
	(const void *)&__identifier("?xfer@Rva005445D4@@UAEXPAVXfer@@@Z"), // slot 3 0x00544AD2
	(const void *)&__identifier("?onEnter@AIDockProcessDockState@@UAE?AW4StateReturnType@@XZ"), // slot 4 0x00544646
	(const void *)&__identifier("?onExit@AIDockProcessDockState@@UAEXW4StateExitType@@@Z"), // slot 5 0x00544670
	(const void *)&__identifier("?update@AIDockProcessDockState@@UAE?AW4StateReturnType@@XZ"), // slot 6 0x00544B96
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 7 0x000B3FD0
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 8 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 9 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 11 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 12 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 13 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 14 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 15 0x0047A699
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 16 0x000B3FD0
};

Rva005445D4::Rva005445D4(StateMachine *machine) : State(machine, 0x90B65C1Du)
{
	m_20 = 0;
	m_24 = 0;
	*(const void **)this = g_00C69A20;
}