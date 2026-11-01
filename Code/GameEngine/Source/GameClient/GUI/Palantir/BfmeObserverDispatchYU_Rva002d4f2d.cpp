// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/Palantir
//
// BFME2 literal fix: retail's two statics name "NonCommand_MultiplayerOptions"
// (VA 0x00C02D90, the observer-active arm) and "NonCommand_Options" (VA
// 0x00C02D7C, the inactive arm); the donor carried BFME1's "NonCommand_Objectives"
// and "NonCommand_PlayerStatus". Only the literals differ; the body is byte-equal.
//
// Open-BFME5: the observer-dependent command dispatch at retail 0x0058EDB0,
// 228 bytes.  Same two-static shape as 0x0058ECA0, but the selector is a live
// observer plus a predicate call rather than a flag bit.

// The two function-local statics are real AsciiStrings: retail constructs them
// through the StringBase C-string ctor (0x00037BA0) and registers atexit
// cleanups 0x007B79BF / 0x007B79B5 (ecx=static, jmp ??1AsciiString 0x0048BA39),
// which this unit emits as _$E2 / _$E3.
#include "ascii_string.h"

#include "../../../Common/GameLogicObjectLookupView.h"

// The global at 0x012F33F8 is the ControlBar singleton; only the accessor
// spellings the method pins carry are declared here.
class GameWindow;
#include "../../../../Include/GameClient/ControlBar.h"
extern GameLogic *TheGameLogic;				// retail 0x012F0898
extern ControlBar *TheControlBar;			// retail 0x012F33F8

// ?bfmeApplyYU@@YGXH@Z -- placeholder owner; WorldBuilder names the body
// Palantir::Impl::HandleOverOptionsButton (WB va 0xf45eb0, assert line 1704).
// The C++ below stays under the placeholder spelling until the rename commit
// can prove a mangle; renaming changes only the linker label, not bytes.
void __stdcall bfmeApplyYU(int unused)
{
	AsciiString *name;

	if (TheGameLogic != 0 && TheGameLogic->isInMultiplayerGame())
	{
		static AsciiString s_bfmeObjectivesYU("NonCommand_MultiplayerOptions");

		name = &s_bfmeObjectivesYU;
	}
	else
	{
		static AsciiString s_bfmeOtherYU("NonCommand_Options");

		name = &s_bfmeOtherYU;
	}

	const CommandButton *entry = TheControlBar->findCommandButton(*name);

	if (entry != 0)
		TheControlBar->rva004C1B60(0, (void *)entry);
}
