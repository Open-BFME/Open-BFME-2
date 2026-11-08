// cl: /DNDEBUG /MD
// platformsdk
//
// AIExitState::onEnter, retail 0x00341B11 (61 bytes), onExit, retail
// 0x0035118A (63 bytes), and update, retail 0x00341B4E (171 bytes): slots 4,
// 5 and 6 of vtable 0x00C115E8, whose slot-2
// name getter returns AIExitState (slot 3 is the rowed AIExitState::xfer
// 0x00341ACD). Ported from Zero Hour's GameEngine/Source/GameLogic/AI/
// AIStates.cpp (GeneralsMD tree vendored under reference/open-bfme-1/inputs/
// reference).
// BFME2 difference (target evidence): update publishes the state's version-2
// Bool (+0x24, unnamed; see AIStatesXfer.cpp) in the global byte 0x00E03624
// for the duration of exitObjectViaDoor, then clears it; onExit ends by
// clearing the machine's goal object (StateMachine vslot 14, the rowed
// locked-guarded setGoalObject 0x004D750F).
// BFME2 layout (target evidence): object template +4, id +0x74, contain
// +0x250 (onObjectWantsToEnterOrExit vslot 17, getContainExitInterface vslot
// 29), AI +0x258 (getAiFreeToExit vslot 106); ExitInterface isExitBusy,
// reserveDoorForExit and exitObjectViaDoor are its vslots 0..2; state id +4,
// machine current state +4 (INVALID_STATE_ID 999999), m_entryToClear +0x20.
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
#define INVALID_STATE_ID 999999
#include <windows.h>
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../Include/Common/StateMachine.h"
enum ObjectEnterExitType
{
	WANTS_TO_ENTER = 0,
	WANTS_TO_EXIT = 1,
	WANTS_NEITHER = 2
};
enum AIFreeToExitType
{
	FREE_TO_EXIT = 0,
	NOT_FREE_TO_EXIT = 1,
	WAIT_TO_EXIT = 2
};
enum ExitDoorType
{
	DOOR_NONE_AVAILABLE = -1,
	DOOR_NONE_NEEDED = 0
};
class Object;
class ThingTemplate;
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
#include "../../../Include/GameLogic/Module/ExitInterface.h"
#include "../../../Include/GameLogic/Module/ContainModule.h"
#include "../../../Include/GameLogic/Module/AIUpdate.h"
class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	__declspec(dllimport) __forceinline ObjectID getID() const { return m_id; }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x250 - 0x78];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
};
#include "../../../Include/Common/StateMachineClass.h"
// Shared one-byte flag at retail VA 0x00E03624. Exit states publish their
// saved flag around exitObjectViaDoor and clear it afterwards. The retail
// .data zero-fill and byte operands prove bool storage; original name unknown.
Bool BfmeAIExitDoorFlag = false;
extern GameLogic *TheGameLogic;
class AIExitState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	ObjectID m_entryToClear; // +0x20
	Bool m_bfmeFlag24; // +0x24
};

StateReturnType AIExitState::onEnter()
{
	m_entryToClear = INVALID_OBJECT_ID;

	Object* obj = getMachineOwner();
	Object* goal = getMachineGoalObject();
	if (goal)
	{
		ContainModuleInterface* contain = goal->getContain();
		if (contain)
		{
			contain->onObjectWantsToEnterOrExit(obj, WANTS_TO_EXIT);
			m_entryToClear = goal->getID();
		}
		return STATE_CONTINUE;
	}
	else
	{
		return STATE_FAILURE;
	}
}

void AIExitState::onExit( StateExitType status )
{
	// use this, rather than getMachineGoalObject, in case the goal
	// is killed while we were waiting...
	if (m_entryToClear != INVALID_OBJECT_ID)
	{
		Object* goal = TheGameLogic->findObjectByID(m_entryToClear);
		if (goal)
		{
			ContainModuleInterface* contain = goal->getContain();
			if (contain)
			{
				contain->onObjectWantsToEnterOrExit(getMachineOwner(), WANTS_NEITHER);
			}
		}
	}
	getMachine()->setGoalObject(NULL);
}

StateReturnType AIExitState::update()
{
	// update the goal position to coincide with the GoalObject
	Object* obj = getMachineOwner();
	Object* goal = getMachineGoalObject();
	if (goal)
	{
		AIUpdateInterface* goalAI = goal->getAI();
		if (goalAI && goalAI->vslot106(obj) == WAIT_TO_EXIT)
			return STATE_CONTINUE;

		ExitInterface* goalExitInterface = goal->getContain() ? goal->getContain()->getContainExitInterface() : NULL;
		if( goalExitInterface == NULL )
			return STATE_FAILURE;

		if( goalExitInterface->isExitBusy() )
			return STATE_CONTINUE;// Just wait a sec.

		ExitDoorType exitDoor = goalExitInterface ? goalExitInterface->reserveDoorForExit(obj->getTemplate(), obj) : DOOR_NONE_NEEDED;
		if (exitDoor == DOOR_NONE_AVAILABLE)
			return STATE_FAILURE;

		BfmeAIExitDoorFlag = m_bfmeFlag24;
		goalExitInterface->exitObjectViaDoor(obj, exitDoor);
		BfmeAIExitDoorFlag = false;
		StateMachine *machine = getMachine();
		if( (machine->m_currentState ? (StateID)machine->m_currentState->m_id : (StateID)INVALID_STATE_ID) != (StateID)m_id )
			return STATE_CONTINUE;// Not sucess, because exitViaDoor has changed us to FollowPath, and if we say Success, our machine will think FollowPath succeeded
		else
			return STATE_SUCCESS;
	}
	else
	{
		return STATE_FAILURE;
	}
}
