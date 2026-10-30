// FILE: command_source_type.h ////////////////////////////////////////////////////////////////////
// Canonical BFME 2 CommandSourceType. Home and body come from BFME 1's
// game/GameEngine/Source/GameLogic/command_source_type.h (reference/open-bfme-1,
// pin 337e4b48e8): PLAYER=0, SCRIPT=1 and AI=2 have independent BFME evidence;
// values 3-4 follow Zero Hour Common/GameCommon.h.
//
// BFME 2 units already include the BFME 1 file by its reference path
// (ActionManager.cpp, AIGroupBroadcastOrders.cpp, AIUpdateInterface*.cpp, ...);
// this is that file's Code/ mirror, so those includes repoint to it. Zero Hour
// declares the same type in Common/GameCommon.h, which BFME 2 units include for
// other content, so that header is not its home.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

enum CommandSourceType
{
    CMD_FROM_PLAYER = 0,
    CMD_FROM_SCRIPT = 1,
    CMD_FROM_AI = 2,
    CMD_FROM_DOZER = 3,
    CMD_DEFAULT_SWITCH_WEAPON = 4
};
