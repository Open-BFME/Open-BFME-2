// cl: /DNDEBUG /MD
//
// AIWanderState::onExit, retail 0x0034A323 (65 bytes): slot 5 of vtable
// 0x00C12A70, whose slot-2 name getter returns AIWanderState. It starts with
// the Zero Hour body (chain to AIFollowWaypointPathState::onExit, rowed
// 0x0034A0D7); BFME2 then clears model condition 4*32+2 on the owner
// (Object+0x10C words, notifier 0x0028AE6D) and passes 0 to the owner AI's
// vslot 142 (+0x238) without a null check.
template <int N> class AIWanderStateAISlots : public AIWanderStateAISlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIWanderStateAISlots<0>
{
};
// AIUpdateInterface: vslot 142 (+0x238) takes one argument.
#include "../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../Include/GameClient/ModelConditionFlags.h"
class Object
{
public:
	void rva0028AE6D();
	static __forceinline AIUpdateInterface *getAI(const Object *object) { return object->m_ai; }
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
	unsigned char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai; // +0x258
};
#include "../../../Include/Common/StateMachineClass.h"
#include "../../../Include/GameLogic/AIInternalMoveToState.h"
class AIFollowWaypointPathState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};
class AIWanderState : public AIFollowWaypointPathState
{
public:
	virtual void onExit(StateExitType status);
};
void AIWanderState::onExit(StateExitType status)
{
	AIFollowWaypointPathState::onExit(status);
	Object *obj = getMachineOwner();
	if (obj)
	{
		obj->clearModelConditionState(4 * 32 + 2);
		Object::getAI(obj)->chooseLocomotorSet(0);
	}
}
