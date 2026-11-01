// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?GetDefaultStartingBattleMessage@StrategicInGameUI@@YA?AVUnicodeString@@H@Z @0x005D012E 46B: starting battle message fetch.
// Evidence: selects STRATEGICHUD StartingAutoResolve vs StartingRTS by flag==1 then rowed TheGameText fetch slot 0x3C with 0 exists; sret via hidden out pointer; callers in 0x005D015C.
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

// WorldBuilder StrategicInGameUI::GetDefaultStartingBattleMessage, WB VA 0x015B8C10 (strings lead, score 2.0).
namespace StrategicInGameUI {
UnicodeString GetDefaultStartingBattleMessage(int autoResolve)
{
	const char *msg = "STRATEGICHUD:StartingAutoResolveBattleMessage";
	if (autoResolve != 1)
		msg = "STRATEGICHUD:StartingRTSBattleMessage";
	return TheGameText->fetch(msg, 0);
}
}
