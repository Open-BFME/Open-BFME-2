// cl: /MD
// AIPlayer::rva004F48D8 at RVA 0x004F48D8 (79B).
// Slot 18 of the retail AIPlayer table at VA 0x00C62DC8. Calls the rowed
// queueUnits at RVA 0x004F46A9 and slot 26; the timer uses
// BfmeLogicFramesPerSecond multiplied by five.

extern int BfmeLogicFramesPerSecond;

// 0x004F46A9 is rowed as the protected AIPlayer::queueUnits
// (AIPlayerTeamBuild.cpp); this unit's carrier reaches it on the same this.

struct Rva004F48D8Sub
{
	char m_pad[0x338];
	unsigned char m_338;
};

#include "../../../Include/GameLogic/AIPlayerClass.h"

void AIPlayer::rva004F48D8()
{
	if (((const Rva004F48D8Sub *)m_player)->m_338 == 0)
		return;
	if (m_readyToBuildTeam == 0)
	{
		--m_teamTimer;
		if (m_teamTimer <= 0)
		{
			m_readyToBuildTeam = 1;
			m_teamDelay = 0;
		}
	}
	--m_teamDelay;
	if (m_teamDelay >= 1)
		return;
	queueUnits();
	if (m_readyToBuildTeam != 0)
		vslot26();
	m_teamDelay = BfmeLogicFramesPerSecond * 5;
}
