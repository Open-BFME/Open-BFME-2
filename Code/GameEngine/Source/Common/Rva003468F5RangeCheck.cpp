// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva003468F5@AIChargeTargetState@@AAE_NXZ @0x003468F5 48B: range predicate over TurretStateMachine goal.
// Returns true when the goal object exists and its distSq to the +0x20 point exceeds 2500.0f (50 squared).
// Callees are rowed ?getGoalObject@TurretStateMachine@@QAEPAVObject@@XZ and ?distSq@Rva000CBA20@@QAEMPBVRva000CBA20Point@@@Z.
// Caller AIChargeTargetState::update 0x0034FE6E passes its own this (edi): +0x18 machine, +0x20 point.
// /arch:SSE selects the retail fld/fxch/fcompi/jbe shape (plain /O1 emits fcomp/fnstsw); /O1 keeps push-esi framing.
class Object;
#include "../../Include/GameLogic/Module/TurretStateMachine.h"
#include "../../Include/Common/Rva000CBA20Point.h"
#include "RTS/XYDistanceCallView.h"

// AIChargeTargetState (rowed ctor 0x00343042, onExit, update; the class is
// AIStatesBfmeOnExit.cpp's): its update 0x0034FE6E calls this private test on
// its own this.
class AIChargeTargetState
{
private:
	bool rva003468F5();
	char _pad[0x18];
	TurretStateMachine *m_machine;
	char _pad1C[4];
	Rva000CBA20Point m_point;
};
bool AIChargeTargetState::rva003468F5()
{
	Object *goal = m_machine->getGoalObject();
	if (!goal)
		return false;
	float d = ((Rva000CBA20 *)goal)->distSq(&m_point);
	if (d > 2500.0f)
		return true;
	return false;
}
