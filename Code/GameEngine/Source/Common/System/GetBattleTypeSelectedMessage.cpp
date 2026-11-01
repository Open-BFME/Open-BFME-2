// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?GetBattleTypeSelectedMessage@@YA?AVUnicodeString@@H@Z @0x005D0100 46B: battle message fetch.
// Evidence: selects STRATEGICHUD SelectedAutoResolve vs SelectedRTS by flag==1 then rowed TheGameText fetch slot 0x3C with 0 exists; sret via hidden out pointer; callers in 0x005D015C 0x005D08FD.
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

UnicodeString GetBattleTypeSelectedMessage(int autoResolve)
{
	const char *msg = "STRATEGICHUD:SelectedAutoResolveBattleMessage";
	if (autoResolve != 1)
		msg = "STRATEGICHUD:SelectedRTSBattleMessage";
	return TheGameText->fetch(msg, 0);
}
