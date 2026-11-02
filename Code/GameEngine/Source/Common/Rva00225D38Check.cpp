// cl: /DNDEBUG /MD /EHsc
// ?rva00225D38@GameEngine@@AAE_NXZ @0x00225D38 48B frame-period check using
// FramesPerSecond at 0x00DBA4E8 and LogicFramesPerSecond at 0x00DBA4E4 plus
// member m_clientFramePeriod at +0x34. Evidence: same +0x34 and globals as
// GameEngineFrameTiming rows; ten callers use result as condition.

extern int BfmeClientFramesPerSecond;
extern int BfmeLogicFramesPerSecond;

#define FramesPerSecond BfmeClientFramesPerSecond
#define LogicFramesPerSecond BfmeLogicFramesPerSecond

#include "../../Include/Common/GameEngine.h"

bool GameEngine::rva00225D38(void)
{
	int counter = FramesPerSecond / LogicFramesPerSecond;
	int six = 6;
	if (counter < six)
		return m_34 == six / counter;
	return m_34 == 1;
}
