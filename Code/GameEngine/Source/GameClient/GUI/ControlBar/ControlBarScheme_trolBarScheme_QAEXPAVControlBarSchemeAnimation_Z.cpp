// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -D_STLP_USE_STATIC_LIB -DBFME_STLP_NODE_ALLOC -EHsc -Ireference/open-bfme-1/inputs/reference/shims/ini -Ireference/open-bfme-1/inputs/reference/shims/controlbarvtables -Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/ControlBar /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
#define BFME_STLP_NODE_ALLOC 1
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

// FILE: ControlBarScheme.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Apr 2002
//
//	Filename: 	ControlBarScheme.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	Contains all the Command bar goodness in terms of how it looks
//						For instrucitons on how to use, please see it's .h file
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#define _STLP_NO_EXCEPTIONS 1	// Open-BFME7: this TU was built with STLport exceptions off (STLport helpers inline as in retail)
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Player.h"
#include "Common/PlayerTemplate.h"
#include "Common/Recorder.h"
#include "GameClient/ControlBarScheme.h"
#include "GameClient/Display.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Image.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetPushButton.h"
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
enum{
	COMMAND_BAR_SIZE_OFFSET = 0
};

// The retail table at RVA 0x0080CD88: 68 entries and the null terminator, read from
// game.dat. BFME inserts ButtonBorderAlteredColor and moves members, so the
// offsets are retail's own rather than the Zero Hour header's offsetof values.
// ImagePart and AnimatingPart parse through the rowed factories at 0x00320158
// (ControlBarRva00320158.cpp) and 0x003201A9 (ControlBarRva003201A9.cpp).
class Rva003200BC;
void Rva00320158Parse(INI *ini, Rva003200BC *holder);
void Rva003201A9Parse(INI *ini, void *holder);

const FieldParse ControlBarSchemeManager::m_controlBarSchemeFieldParseTable[] = 
{
	{ "ImagePart", (INIFieldParseProc)Rva00320158Parse, NULL, 0x0 },
	{ "AnimatingPart", (INIFieldParseProc)Rva003201A9Parse, NULL, 0x0 },
	{ "ScreenCreationRes", INI::parseICoord2D, NULL, 0x4 },
	{ "Side", INI::parseAsciiString, NULL, 0xC },
	{ "QueueButtonImage", INI::parseMappedImage, NULL, 0x10 },
	{ "RightHUDImage", INI::parseMappedImage, NULL, 0x14 },
	{ "BuildUpClockColor", INI::parseColorInt, NULL, 0x18 },
	{ "ButtonBorderBuildColor", INI::parseColorInt, NULL, 0x1C },
	{ "CommandBarBorderColor", INI::parseColorInt, NULL, 0x30 },
	{ "ButtonBorderActionColor", INI::parseColorInt, NULL, 0x20 },
	{ "ButtonBorderUpgradeColor", INI::parseColorInt, NULL, 0x24 },
	{ "ButtonBorderSystemColor", INI::parseColorInt, NULL, 0x28 },
	{ "ButtonBorderAlteredColor", INI::parseColorInt, NULL, 0x2C },
	{ "OptionsButtonEnable", INI::parseMappedImage, NULL, 0x34 },
	{ "OptionsButtonHightlited", INI::parseMappedImage, NULL, 0x38 },
	{ "OptionsButtonPushed", INI::parseMappedImage, NULL, 0x3C },
	{ "OptionsButtonDisabled", INI::parseMappedImage, NULL, 0x40 },
	{ "IdleWorkerButtonEnable", INI::parseMappedImage, NULL, 0x44 },
	{ "IdleWorkerButtonHightlited", INI::parseMappedImage, NULL, 0x48 },
	{ "IdleWorkerButtonPushed", INI::parseMappedImage, NULL, 0x4C },
	{ "IdleWorkerButtonDisabled", INI::parseMappedImage, NULL, 0x50 },
	{ "BuddyButtonEnable", INI::parseMappedImage, NULL, 0x54 },
	{ "BuddyButtonHightlited", INI::parseMappedImage, NULL, 0x58 },
	{ "BuddyButtonPushed", INI::parseMappedImage, NULL, 0x5C },
	{ "BuddyButtonDisabled", INI::parseMappedImage, NULL, 0x60 },
	{ "BeaconButtonEnable", INI::parseMappedImage, NULL, 0x64 },
	{ "BeaconButtonHightlited", INI::parseMappedImage, NULL, 0x68 },
	{ "BeaconButtonPushed", INI::parseMappedImage, NULL, 0x6C },
	{ "BeaconButtonDisabled", INI::parseMappedImage, NULL, 0x70 },
	{ "GenBarButtonIn", INI::parseMappedImage, NULL, 0x74 },
	{ "GenBarButtonOn", INI::parseMappedImage, NULL, 0x78 },
	{ "ToggleButtonUpIn", INI::parseMappedImage, NULL, 0x7C },
	{ "ToggleButtonUpOn", INI::parseMappedImage, NULL, 0x80 },
	{ "ToggleButtonUpPushed", INI::parseMappedImage, NULL, 0x84 },
	{ "ToggleButtonDownIn", INI::parseMappedImage, NULL, 0x88 },
	{ "ToggleButtonDownOn", INI::parseMappedImage, NULL, 0x8C },
	{ "ToggleButtonDownPushed", INI::parseMappedImage, NULL, 0x90 },
	{ "GeneralButtonEnable", INI::parseMappedImage, NULL, 0x94 },
	{ "GeneralButtonHightlited", INI::parseMappedImage, NULL, 0x98 },
	{ "GeneralButtonPushed", INI::parseMappedImage, NULL, 0x9C },
	{ "GeneralButtonDisabled", INI::parseMappedImage, NULL, 0xA0 },
	{ "UAttackButtonEnable", INI::parseMappedImage, NULL, 0xA4 },
	{ "UAttackButtonHightlited", INI::parseMappedImage, NULL, 0xA8 },
	{ "UAttackButtonPushed", INI::parseMappedImage, NULL, 0xAC },
	{ "GenArrow", INI::parseMappedImage, NULL, 0xBC },
	{ "MinMaxButtonEnable", INI::parseMappedImage, NULL, 0xB0 },
	{ "MinMaxButtonHightlited", INI::parseMappedImage, NULL, 0xB4 },
	{ "MinMaxButtonPushed", INI::parseMappedImage, NULL, 0xB8 },
	{ "MinMaxUL", INI::parseICoord2D, NULL, 0xD0 },
	{ "MinMaxLR", INI::parseICoord2D, NULL, 0xD8 },
	{ "GeneralUL", INI::parseICoord2D, NULL, 0xE0 },
	{ "GeneralLR", INI::parseICoord2D, NULL, 0xE8 },
	{ "UAttackUL", INI::parseICoord2D, NULL, 0xF0 },
	{ "UAttackLR", INI::parseICoord2D, NULL, 0xF8 },
	{ "OptionsUL", INI::parseICoord2D, NULL, 0x100 },
	{ "OptionsLR", INI::parseICoord2D, NULL, 0x108 },
	{ "WorkerUL", INI::parseICoord2D, NULL, 0x110 },
	{ "WorkerLR", INI::parseICoord2D, NULL, 0x118 },
	{ "ChatUL", INI::parseICoord2D, NULL, 0x120 },
	{ "ChatLR", INI::parseICoord2D, NULL, 0x128 },
	{ "BeaconUL", INI::parseICoord2D, NULL, 0x130 },
	{ "BeaconLR", INI::parseICoord2D, NULL, 0x138 },
	{ "PowerBarUL", INI::parseICoord2D, NULL, 0x140 },
	{ "PowerBarLR", INI::parseICoord2D, NULL, 0x148 },
	{ "MoneyUL", INI::parseICoord2D, NULL, 0xC0 },
	{ "MoneyLR", INI::parseICoord2D, NULL, 0xC8 },
	{ "CommandMarkerImage", INI::parseMappedImage, NULL, 0x154 },
	{ "ExpBarForegroundImage", INI::parseMappedImage, NULL, 0x150 },
	{ NULL, NULL, NULL, 0 }  // keep this last
};

// used to parse the anim types that each animation part of a scheme can have
static const LookupListRec AnimTypeNames[] = 
{
	{ "SLIDE_RIGHT", ControlBarSchemeAnimation::CB_ANIM_SLIDE_RIGHT },
	{ NULL, 0	}
};

static void animSlideRight( ControlBarSchemeAnimation *anim );

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

void ControlBarScheme::updateAnim (ControlBarSchemeAnimation * anim)
{
	switch(anim->m_animType)
	{
		case ControlBarSchemeAnimation::CB_ANIM_SLIDE_RIGHT:
		{
			animSlideRight( anim );
			break;
		}
		default:
		{
			DEBUG_ASSERTCRASH(FALSE,("We tried to animate but not animate function was found %d", anim->m_animType));
		}
	}
}

static void animSlideRight( ControlBarSchemeAnimation *anim )
{
	if(!anim->m_animImage || (anim->m_animDuration == 0))
		return;

	UnsignedInt currentFrame = anim->getCurrentFrame();
	ICoord2D startPos = anim->getStartPos();
	// if we're at the end, bring us to the beginning
	if(currentFrame == anim->m_animDuration)
	{
		anim->m_animImage->m_position.x = startPos.x;
		anim->m_animImage->m_position.y = startPos.y;
		anim->setCurrentFrame( 0 );
		return;
	}
	else if(currentFrame == 0)
	{
		// if we're at the beginning, save off the start position
		startPos.x = anim->m_animImage->m_position.x;
		startPos.y = anim->m_animImage->m_position.y;
		anim->setStartPos(startPos);
	}
	
	// now lets animate this bad boy!
	
	// now increment the frame
	currentFrame++;
	anim->setCurrentFrame(currentFrame);

	// now lets find what position we should be at.
	anim->m_animImage->m_position.x = startPos.x + (((anim->m_finalPos.x - startPos.x) * currentFrame) / anim->m_animDuration);


}
