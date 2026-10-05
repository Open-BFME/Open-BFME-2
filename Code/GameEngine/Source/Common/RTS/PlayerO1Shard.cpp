// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
//
// Shard of Player.cpp for three bodies retail builds size-optimised (/O1):
// Player::onPowerBrownOutChange 0x2AB8D0, grantScience 0x2AD85E and
// findNaturalCommandCenter 0x2AC60A. Under the home TU's default flags the
// three compile with speed-ordered branches; with /O1 each is a unique exact
// byte match. The home file's other rows need its default flags, and a
// per-function #pragma optimize there would stage 112 unmarked definitions.
//
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: Player.cpp /////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: Player.cpp
//
// Created:   Steven Johnson, October 2001
//
// Desc:      @todo
//
//-----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_SCIENCE_AVAILABILITY_NAMES

#include "Common/ActionManager.h"
#include "Common/BuildAssistant.h"
#include "Common/CRCDebug.h"
#include "Common/DisabledTypes.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/MessageStream.h"
#include "Common/MiscAudio.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/PlayerTemplate.h"
#include "Common/ProductionPrerequisite.h"
#include "Common/Radar.h"
#include "Common/ResourceGatheringManager.h"
#include "Common/Team.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/TunnelTracker.h"
#include "Common/Upgrade.h"
#include "Common/WellKnownKeys.h"
#include "Common/Xfer.h"
#include "Common/BitFlagsIO.h"
#include "Common/SpecialPower.h"

#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/Eva.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameText.h"

#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/AISkirmishPlayer.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/Object.h"
#include "GameLogic/Scripts.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/SidesList.h"
#include "GameLogic/Squad.h"
#include "GameLogic/RankInfo.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/AutoDepositUpdate.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Module/BattlePlanUpdate.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/VictoryConditions.h"

#include "GameNetwork/GameInfo.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//Grey for neutral.  
#define NEUTRAL_PLAYER_COLOR 0xffffffff

namespace {

// BFME's AIPlayer query slots precede their recovered Zero Hour positions by one entry.
class BFMEAIPlayerVirtuals
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual Bool isSkirmishAI() = 0;
	virtual Player *getAiEnemy() = 0;
	virtual Bool checkBridges(Object *unit, Waypoint *way) = 0;
};

struct BFMEPlayerAIView
{
	char data[0x220];
	BFMEAIPlayerVirtuals *ai;
};

} // namespace

// ------------------------------------------------------------------------------------------------
class ClosestKindOfData
{
public:

	ClosestKindOfData( void );

	//In
	KindOfMaskType m_setKindOf;
	KindOfMaskType m_clearKindOf;
	Object *m_source;

	//Out
	Object *m_closest;
	Real m_closestDistSq;

};

// ------------------------------------------------------------------------------------------------
// ??0ClosestKindOfData@@QAE@XZ present-unmatched

// iterateObjects callbacks defined static in Player.cpp (DIR32 operands, masked)
// BFME tests KINDOF_POWERED inline on the template's KindOf bits: the template
// pointer at Object+0x04, byte +0x110, bit 0x80.
struct BfmePowerDisableTemplateView
{
	unsigned char m_padding[0x110];
	unsigned char m_kindOf110;
};

struct BfmePowerDisableObjectView
{
	void *m_vtbl;
	const BfmePowerDisableTemplateView *m_template;
};

// Player.cpp's doPowerDisable (0x002AAB8D, 47B): powered objects follow the
// player's brown-out state; BFME's object iterator expects a nonzero return to
// keep walking.
int doPowerDisable( Object *obj, void *userData )
{
	Bool *brownOut = (Bool*)userData;

	// Only do things that need power
	if( obj && (((const BfmePowerDisableObjectView *)obj)->m_template->m_kindOf110 & 0x80) )
	{
		if( *brownOut )
			obj->setDisabled( DISABLED_UNDERPOWERED );
		else
			obj->clearDisabled( DISABLED_UNDERPOWERED );
	}
	return 1;
}
void doFindCommandCenter(Object* obj, void* userData);

// ?onPowerBrownOutChange@Player@@QAEX_N@Z @0x002AB8D0
void Player::onPowerBrownOutChange( Bool brownOut )
{
	// Everything that changes due to Player's power supply goes in here.
	if( brownOut )
		disableRadar();
	else
		enableRadar(); //This doesn't give radar necessarily, it just removes the restriction

	iterateObjects( (ObjectIterateFunc)doPowerDisable, &brownOut );// This function is so cool.
}

// ?grantScience@Player@@QAE_NW4ScienceType@@@Z @0x002AD85E
Bool Player::grantScience(ScienceType science)
{
	if (!TheScienceStore->isScienceGrantable(science))
	{
		DEBUG_CRASH(("Cannot grant science %s, since it is marked as nonGrantable.\n",TheScienceStore->getInternalNameForScience(science).str()));
		return false;	// it's not grantable, so tough, can't have it, even via this method.
	}

	return addScience(science);
}

// ?findNaturalCommandCenter@Player@@QAEPAVObject@@XZ @0x002AC60A
Object* Player::findNaturalCommandCenter()
{
	// BFME allocates only eight bytes here -- retail opens with `sub esp,8` --
	// so this finder pairs with a two-field block, not the seven-field
	// PlayerObjectFindInfo the other finders in this file share.
	// doFindCommandCenter reads only .player and .obj, which are the two
	// that overlay.
	struct { Player* player; Object* obj; } info;
	info.player = this;
	info.obj = NULL;
	iterateObjects(doFindCommandCenter, &info);
	return info.obj;
}

// BuildListInfo::setTemplateName is a header inline the size-optimised Player
// unit leaves out of line (retail 0x001DBC2D, called from 0x001DC54A).
extern void (BuildListInfo::*const g_bfmeBuildListSetTemplateNameAnchor)(AsciiString);
void (BuildListInfo::*const g_bfmeBuildListSetTemplateNameAnchor)(AsciiString) = &BuildListInfo::setTemplateName;
