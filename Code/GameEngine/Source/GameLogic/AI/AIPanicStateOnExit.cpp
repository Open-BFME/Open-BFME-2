// cl: /DNDEBUG /MD
//
// AIPanicState::onExit, retail 0x0034A4DB (45 bytes).
// Identity: slot 5 of vtable 0x00C12B70 (installed by the unrowed ctor at
// 0x00342D31), whose slot 2 is the rowed name getter 0x00342D3B returning the
// literal AIPanicState; the body is the Zero Hour AIStates.cpp
// AIPanicState::onExit (clear the panicking model condition on the machine
// owner, then chain to AIInternalMoveToState::onExit, rowed at 0x003473A4).
// BFME2 delta: the condition is bit 2*32+13 of the Object+0x10C words (byte
// +0x115 mask 0x20) with the pinned notifier 0x0028AE6D.
enum ModelConditionFlagType
{
	MODELCONDITION_PANICKING = 2 * 32 + 13
};
#include "../../../Include/GameClient/ModelConditionFlags.h"
class Object
{
public:
	void rva0028AE6D();
	__forceinline void clearModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x10C];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
};
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"
#include "../../../Include/GameLogic/AIInternalMoveToState.h"
class AIPanicState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};
void AIPanicState::onExit(StateExitType status)
{
	Object *obj = getMachineOwner();
	obj->clearModelConditionState(MODELCONDITION_PANICKING);
	AIInternalMoveToState::onExit(status);
}
