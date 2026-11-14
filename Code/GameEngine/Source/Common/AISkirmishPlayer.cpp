// cl: /MD /GX
// ??1Rva004EF41D@@UAE@XZ @0x004EF41D 56B derived dtor with EH.
// Evidence: stores vtable 0x00C62AF8 at [this], calls rowed AIPlayer::clearTeamsInQueue 0x004F05D6, calls rowed base ??1Rva004F07E6 0x004F07E6, EH prolog handler 0x00792BB5, caller 0x004EF638, chain from 0x004F07E6.
#include "../../Include/GameLogic/AIPlayerClass.h"
class AISkirmishPlayer : public AIPlayer
{
public:
	virtual ~AISkirmishPlayer();
};
#include <new>
AISkirmishPlayer::~AISkirmishPlayer()
{
	((AIPlayer *)this)->clearTeamsInQueue();
}
