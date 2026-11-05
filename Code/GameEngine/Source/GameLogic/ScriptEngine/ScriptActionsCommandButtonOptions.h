// ScriptActions' read of CommandButton option bit 5 (the "needs a target
// position" option) in the commandButtonOnNearest family (0x003BD905,
// 0x003C10D8 and siblings). Retail tests the shifted value (shr eax,5;
// test al,1), the shape of a bool-returning inline; a direct `& 0x20` compiles
// to a byte test instead. Shared so the units keep one definition when they
// merge into ScriptActions.cpp.
#ifndef SCRIPTACTIONS_COMMANDBUTTON_OPTIONS_H
#define SCRIPTACTIONS_COMMANDBUTTON_OPTIONS_H

#include "../../../Include/GameClient/CommandButton.h"

static inline bool needsTargetPosition(const CommandButton *button)
{
	return (button->getOptions() >> 5) & 1;
}

#endif
