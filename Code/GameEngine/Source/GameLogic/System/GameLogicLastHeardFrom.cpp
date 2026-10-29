// cl: /DNDEBUG /MD
// platformsdk
//
// GameLogic::lastHeardFrom, retail 0x0023CF1C, 35 bytes.
// Dedicated TU so GameLogicProcessProgress.cpp cannot see this body.
// Timeout stamp array sits at this+0x130; MAX_SLOTS is 8.

#include <windows.h>

#include "../../Common/GameLogicObjectLookupView.h"

void GameLogic::lastHeardFrom(int playerId)
{
	if (playerId < 0 || playerId >= 8)
		return;
	m_progressCompleteTimeout[playerId] = timeGetTime();
}
