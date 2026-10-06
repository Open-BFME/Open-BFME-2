// cl: /O1 /DNDEBUG /MD
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
#define NULL 0
#define INVALID_STATE_ID 999999
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
class ExitInterface
{
public:
	virtual Bool isExitBusy() const = 0;
	virtual ExitDoorType reserveDoorForExit(const ThingTemplate *objType, Object *specificObject) = 0;
	virtual void exitObjectViaDoor(Object *newObj, ExitDoorType exitDoor) = 0;
};
class ContainModuleInterface : public VSlots<17>
{
public:
	virtual void onObjectWantsToEnterOrExit(Object *obj, ObjectEnterExitType wants) = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0;
	virtual void slot27() = 0; virtual void slot28() = 0;
	virtual ExitInterface *getContainExitInterface() = 0;
};
class AIUpdateInterface : public VSlots<106>
{
public:
	virtual AIFreeToExitType getAiFreeToExit(const Object *exiter) const = 0;
};
class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
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
class State;
class StateMachine : public VSlots<14>
{
public:
	virtual void setGoalObject(const Object *obj) = 0;
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	inline StateID getCurrentStateID() const;
private:
	State *m_currentState; // +0x04
	unsigned char m_pad08[0x14 - 0x08];
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
	StateID getID() const { return m_ID; }
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
	StateID m_ID; // +0x04
	unsigned char m_pad08[0x18 - 0x08];
	StateMachine *m_machine; // +0x18
};
// ?StateMachine::getCurrentStateID absent-from-retail
inline StateID StateMachine::getCurrentStateID() const
{
	return m_currentState ? m_currentState->getID() : INVALID_STATE_ID;
}
extern Bool g_00E03624;
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
class AIExitState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	ObjectID m_entryToClear; // +0x20
	Bool m_bfmeFlag24; // +0x24
};

StateReturnType AIExitState::onEnter()
{
	m_entryToClear = INVALID_ID;

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
	if (m_entryToClear != INVALID_ID)
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
		if (goalAI && goalAI->getAiFreeToExit(obj) == WAIT_TO_EXIT)
			return STATE_CONTINUE;

		ExitInterface* goalExitInterface = goal->getContain() ? goal->getContain()->getContainExitInterface() : NULL;
		if( goalExitInterface == NULL )
			return STATE_FAILURE;

		if( goalExitInterface->isExitBusy() )
			return STATE_CONTINUE;// Just wait a sec.

		ExitDoorType exitDoor = goalExitInterface ? goalExitInterface->reserveDoorForExit(obj->getTemplate(), obj) : DOOR_NONE_NEEDED;
		if (exitDoor == DOOR_NONE_AVAILABLE)
			return STATE_FAILURE;

		g_00E03624 = m_bfmeFlag24;
		goalExitInterface->exitObjectViaDoor(obj, exitDoor);
		g_00E03624 = false;
		if( getMachine()->getCurrentStateID() != getID() )
			return STATE_CONTINUE;// Not sucess, because exitViaDoor has changed us to FollowPath, and if we say Success, our machine will think FollowPath succeeded
		else
			return STATE_SUCCESS;
	}
	else
	{
		return STATE_FAILURE;
	}
}
