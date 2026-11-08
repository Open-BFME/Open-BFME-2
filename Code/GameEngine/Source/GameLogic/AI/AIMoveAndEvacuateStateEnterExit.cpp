// cl: /DNDEBUG /MD
//
// AIMoveAndEvacuateState::onEnter, retail 0x0034EB7E (106 bytes), and
// AIMoveAndEvacuateState::onExit, retail 0x00349FD0 (37 bytes): slots 4 and
// 5 of vtable 0x00C12C28, whose slot-2 name getter returns
// AIMoveAndEvacuateState (slot 6 is the rowed update 0x00353C27). Ported from
// Zero Hour's GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference).
// BFME2 layout (target evidence): machine lock byte +0x38, machine goal
// position +0x24, owner position +0x38; state goal +0x20, adjusts-destination
// +0x48 (setAdjustsDestination logs "CritterDesync" under the global log flag)
// and m_origin +0x4C. getGoalObject and setGoalPosition are pinned StateMachine
// callees; the base onEnter/onExit are pinned AIInternalMoveToState bodies.
typedef bool Bool;
typedef float Real;
#include "../../../Include/Common/StateMachine.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
#include "../Object/object.h"
#include "../../../Include/Common/StateMachineClass.h"
class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
protected:
	__declspec(dllimport) __forceinline void setAdjustsDestination(Bool b)
	{
		if (b)
		{
			if (g_00E03745)
			{
				FprintfTarget *log = (FprintfTarget *)theLogicRandomLogFile;
				if (log)
					fprintf(log, "CritterDesync: setAdjustDestination(TRUE) 49");
			}
		}
		else
		{
			if (g_00E03745)
			{
				FprintfTarget *log = (FprintfTarget *)theLogicRandomLogFile;
				if (log)
					fprintf(log, "CritterDesync: setAdjustDestination(FALSE) 56");
			}
		}
		m_adjustsDestination = b;
	}
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	Bool m_adjustsDestination; // +0x48
};
class AIMoveAndEvacuateState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
private:
	Coord3D m_origin; // +0x4C
};

StateReturnType AIMoveAndEvacuateState::onEnter()
{
	Object *obj = getMachineOwner();

	getMachine()->m_locked = true;		// This state is not user interruptable.

	m_origin = *obj->getPosition();
	setAdjustsDestination(true);

	// if we have a goal object, move to it, otherwise move to goal position
	if (getMachine()->getGoalObject())
		m_goalPosition = *getMachine()->getGoalObject()->getPosition();
	else
		m_goalPosition = *getMachine()->getGoalPosition();
	return AIInternalMoveToState::onEnter();
}

void AIMoveAndEvacuateState::onExit( StateExitType status )
{
	getMachine()->m_locked = false;
	getMachine()->setGoalPosition(&m_origin); // In case we follow with a AIMoveAndDeleteState.
	AIInternalMoveToState::onExit( status );
}
