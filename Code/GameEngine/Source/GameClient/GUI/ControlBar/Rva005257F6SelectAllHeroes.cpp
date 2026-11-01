// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ob2
// Donor: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/BfmeCommandLookupYI.cpp, recompiled /O1.
// Target: complete 117B entry at RVA 005257F6, between a preceding RET
// and the next body at 0052586B. Retail independently names the literal
// NonCommand_SelectAllHeroes and loads the established TheControlBar global.
// Static string VA E0495C occupies one pointer before its guard at E04960;
// its registered destructor at 7B9220 tail-calls releaseBuffer at 36410.
// Original callback name and parameter meaning remain unknown.

#include "ascii_string.h"

class CommandButton;
class GameWindow;

#include "../../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;

// ?rva005257F6@@YGXH@Z
void __stdcall rva005257F6(int unused)
{
    if (TheControlBar == 0)
        return;

    static AsciiString name("NonCommand_SelectAllHeroes");
    const CommandButton *entry = TheControlBar->findCommandButton(name);
    if (entry != 0)
        TheControlBar->rva004C1B60(0, (void *)entry);
}
