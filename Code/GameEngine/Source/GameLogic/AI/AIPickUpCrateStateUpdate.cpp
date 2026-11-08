// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Byte-exact reconstruction of ?update@AIPickUpCrateState@@UAE?AW4StateReturnType@@XZ
// at retail 0x0034DEDE (26B).
// Donor: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// (BFME1 matched the same 26B body at 0x00178E10); logic verbatim from
// GeneralsMD AIStates.cpp AIPickUpCrateState::update. ZH hierarchy
// (AIStateMachine.h): AIPickUpCrateState : public AIInternalMoveToState.

#include "../../../Include/Common/StateMachine.h"

#include "../../../Include/GameLogic/AIInternalMoveToState.h"

class AIPickUpCrateState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
private:
	int m_delayCounter; // +0x4C
};

StateReturnType AIPickUpCrateState::update()
{
	/// @todo srj -- find a way to sleep for a number of frames here, if possible

	if (m_delayCounter) {
		m_delayCounter--;
		if (m_delayCounter == 0) {
			return AIInternalMoveToState::onEnter();
		}
		return STATE_CONTINUE;
	}
	// do movement
	StateReturnType status = AIInternalMoveToState::update();

	return status;
}
