// cl: /MD /GX
// ??1Rva004F07E6@@UAE@XZ @0x004F07E6 51B AIPlayer-like dtor with EH.
// Evidence: stores vtable at [this] twice (0x00C62DC8 then 0x00BBB554 via the canonical Snapshot table), calls rowed AIPlayer::clearTeamsInQueue 0x004F05D6, EH prolog with handler 0x00792CB5 and Unwind@00b92bad, callers 0x004EF443/0x004F111F, prev/next flags.
#include "../../../Include/GameLogic/AIPlayerClass.h"
AIPlayer::~AIPlayer()
{
	clearTeamsInQueue();
}
