// BFME 2: forwards Zero Hour's GameLogic/GameLogic.h to the registered view of the class, whose
// out-of-line findObjectByID (0x00049DC5) and frame at +0x40 are what this TU's rows read.
#pragma once
#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_
#include "Common/GameCommon.h"
#include "Common/GameType.h"
#include "Common/Snapshot.h"
#include "Common/STLTypedefs.h"
#include "Common/ObjectStatusTypes.h"
#include "GameNetwork/NetworkDefs.h"
#include "GameLogic/Module/UpdateModule.h"
#include "../../../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
#endif
