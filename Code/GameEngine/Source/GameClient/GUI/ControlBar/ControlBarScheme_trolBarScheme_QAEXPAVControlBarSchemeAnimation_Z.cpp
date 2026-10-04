// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -D_STLP_USE_STATIC_LIB -DBFME_STLP_NODE_ALLOC -EHsc -Ireference/open-bfme-1/inputs/reference/shims/ini -Ireference/open-bfme-1/inputs/reference/shims/controlbarvtables -Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/ControlBar
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

const FieldParse ControlBarSchemeManager::m_controlBarSchemeFieldParseTable[] = 
{

	{ "ImagePart",						ControlBarSchemeManager::parseImagePart,			NULL, NULL },
	{ "AnimatingPart",				ControlBarSchemeManager::parseAnimatingPart,	NULL, NULL },
	{ "ScreenCreationRes",		INI::parseICoord2D,						NULL, offsetof( ControlBarScheme, m_ScreenCreationRes ) },
	{ "Side",									INI::parseAsciiString,				NULL, offsetof( ControlBarScheme, m_side ) },
	{ "QueueButtonImage",			INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_buttonQueueImage ) },
	{ "RightHUDImage",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_rightHUDImage ) },
	{ "BuildUpClockColor",		INI::parseColorInt,						NULL, offsetof( ControlBarScheme, m_buildUpClockColor ) },
	{ "ButtonBorderBuildColor",			INI::parseColorInt,						NULL, offsetof( ControlBarScheme, m_borderBuildColor ) },
	{ "CommandBarBorderColor",			INI::parseColorInt,						NULL, offsetof( ControlBarScheme, m_commandBarBorderColor ) },
	{ "ButtonBorderActionColor",		INI::parseColorInt,						NULL, offsetof( ControlBarScheme, m_borderActionColor ) },
	{ "ButtonBorderUpgradeColor",		INI::parseColorInt,						NULL, offsetof( ControlBarScheme, m_borderUpgradeColor ) },
	{ "ButtonBorderSystemColor",		INI::parseColorInt,						NULL, offsetof( ControlBarScheme, m_borderSystemColor ) },
	{ "OptionsButtonEnable",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_optionsButtonEnable ) },
	{ "OptionsButtonHightlited",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_optionsButtonHightlited ) },
	{ "OptionsButtonPushed",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_optionsButtonPushed ) },
	{ "OptionsButtonDisabled",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_optionsButtonDisabled ) },
	{ "IdleWorkerButtonEnable",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_idleWorkerButtonEnable ) },
	{ "IdleWorkerButtonHightlited",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_idleWorkerButtonHightlited ) },
	{ "IdleWorkerButtonPushed",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_idleWorkerButtonPushed ) },
	{ "IdleWorkerButtonDisabled",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_idleWorkerButtonDisabled ) },
	{ "BuddyButtonEnable",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_buddyButtonEnable ) },
	{ "BuddyButtonHightlited",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_buddyButtonHightlited ) },
	{ "BuddyButtonPushed",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_buddyButtonPushed ) },
	{ "BuddyButtonDisabled",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_buddyButtonDisabled) },
	{ "BeaconButtonEnable",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_beaconButtonEnable ) },
	{ "BeaconButtonHightlited",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_beaconButtonHightlited ) },
	{ "BeaconButtonPushed",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_beaconButtonPushed ) },
	{ "BeaconButtonDisabled",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_beaconButtonDisabled ) },
	{ "GenBarButtonIn",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_genBarButtonIn ) },
	{ "GenBarButtonOn",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_genBarButtonOn ) },
	{ "ToggleButtonUpIn",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_toggleButtonUpIn ) },
	{ "ToggleButtonUpOn",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_toggleButtonUpOn ) },
	{ "ToggleButtonUpPushed",		INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_toggleButtonUpPushed ) },
	{ "ToggleButtonDownIn",			INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_toggleButtonDownIn ) },
	{ "ToggleButtonDownOn", 		INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_toggleButtonDownOn ) },
	{ "ToggleButtonDownPushed",	INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_toggleButtonDownPushed ) },

	{ "GeneralButtonEnable",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_generalButtonEnable ) },
	{ "GeneralButtonHightlited",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_generalButtonHightlited ) },
	{ "GeneralButtonPushed",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_generalButtonPushed ) },
	{ "GeneralButtonDisabled",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_generalButtonDisabled ) },

	{ "UAttackButtonEnable",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_uAttackButtonEnable ) },
	{ "UAttackButtonHightlited",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_uAttackButtonHightlited ) },
	{ "UAttackButtonPushed",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_uAttackButtonPushed ) },

	{ "GenArrow",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_genArrow) },

	{ "MinMaxButtonEnable",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_minMaxButtonEnable ) },
	{ "MinMaxButtonHightlited",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_minMaxButtonHightlited ) },
	{ "MinMaxButtonPushed",				INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_minMaxButtonPushed ) },

	{ "MinMaxUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_minMaxUL ) },
	{ "MinMaxLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_minMaxLR ) },

	{ "GeneralUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_generalUL ) },
	{ "GeneralLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_generalLR ) },

	{ "UAttackUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_uAttackUL ) },
	{ "UAttackLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_uAttackLR ) },

	{ "OptionsUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_optionsUL ) },
	{ "OptionsLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_optionsLR ) },

	{ "WorkerUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_workerUL ) },
	{ "WorkerLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_workerLR ) },

	{ "ChatUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_chatUL ) },
	{ "ChatLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_chatLR ) },

	{ "BeaconUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_beaconUL ) },
	{ "BeaconLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_beaconLR ) },

	{ "PowerBarUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_powerBarUL ) },
	{ "PowerBarLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_powerBarLR ) },

	{ "MoneyUL", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_moneyUL ) },
	{ "MoneyLR", 		INI::parseICoord2D,				NULL, offsetof( ControlBarScheme, m_moneyLR ) },

	{ "CommandMarkerImage",		INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_commandMarkerImage) },
	{ "ExpBarForegroundImage",		INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_expBarForeground) },
	{ "PowerPurchaseImage",			INI::parseMappedImage,				NULL, offsetof( ControlBarScheme, m_powerPurchaseImage) },

	{ NULL,										NULL,													NULL, 0 }  // keep this last

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
