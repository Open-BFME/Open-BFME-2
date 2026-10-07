// cl: /Ireference/shims/bfme2_ascii_native_ini /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /EHsc /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/controlbarvtables /Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// ?newControlBarScheme@ControlBarSchemeManager@@QAEPAVControlBarScheme@@VAsciiString@@@Z
// retail 0x0032053E, 201 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarScheme.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
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
/* ControlBarSchemeManager::m_controlBarSchemeFieldParseTable: defined by its owning unit */

// used to parse the anim types that each animation part of a scheme can have
static const LookupListRec AnimTypeNames[] = 
{
	{ "SLIDE_RIGHT", ControlBarSchemeAnimation::CB_ANIM_SLIDE_RIGHT },
	{ NULL, 0	}
};

static void animSlideRight( ControlBarSchemeAnimation *anim );

// BFME's ControlBarScheme inserts a fifth button-border colour after
// m_borderSystemColor, so every member from m_commandBarBorderColor on sits
// four bytes later than the Zero Hour header puts it (retail init reads the
// communicator images at +0x54..+0x60, the chat rectangle at +0x120 and the
// command marker at +0x154).
struct BfmeControlBarSchemeInitView
{
	AsciiString m_name;
	ICoord2D m_ScreenCreationRes;
	AsciiString m_side;
	Image *m_buttonQueueImage;
	Image *m_rightHUDImage;					///< +0x14
	Color m_buildUpClockColor;				///< +0x18
	Color m_borderBuildColor;				///< +0x1c
	Color m_borderActionColor;
	Color m_borderUpgradeColor;
	Color m_borderSystemColor;
	Color m_bfmeBorderFifthColor;			///< +0x2c
	Color m_commandBarBorderColor;			///< +0x30
	Image *m_optionsButtonEnable;			///< +0x34
	Image *m_optionsButtonHightlited;
	Image *m_optionsButtonPushed;
	Image *m_optionsButtonDisabled;
	Image *m_idleWorkerButtonEnable;		///< +0x44
	Image *m_idleWorkerButtonHightlited;
	Image *m_idleWorkerButtonPushed;
	Image *m_idleWorkerButtonDisabled;
	Image *m_buddyButtonEnable;				///< +0x54
	Image *m_buddyButtonHightlited;
	Image *m_buddyButtonPushed;
	Image *m_buddyButtonDisabled;
	Image *m_beaconButtonEnable;			///< +0x64
	Image *m_beaconButtonHightlited;
	Image *m_beaconButtonPushed;
	Image *m_beaconButtonDisabled;
	Image *m_genBarButtonIn;				///< +0x74
	Image *m_genBarButtonOn;
	Image *m_toggleButtonUpIn;				///< +0x7c
	Image *m_toggleButtonUpOn;
	Image *m_toggleButtonUpPushed;
	Image *m_toggleButtonDownIn;
	Image *m_toggleButtonDownOn;
	Image *m_toggleButtonDownPushed;
	Image *m_generalButtonEnable;			///< +0x94
	Image *m_generalButtonHightlited;
	Image *m_generalButtonPushed;
	Image *m_generalButtonDisabled;
	Image *m_uAttackButtonEnable;			///< +0xa4
	Image *m_uAttackButtonHightlited;
	Image *m_uAttackButtonPushed;
	Image *m_minMaxButtonEnable;			///< +0xb0
	Image *m_minMaxButtonHightlited;
	Image *m_minMaxButtonPushed;
	Image *m_genArrow;						///< +0xbc
	ICoord2D m_moneyUL;						///< +0xc0
	ICoord2D m_moneyLR;
	ICoord2D m_minMaxUL;
	ICoord2D m_minMaxLR;
	ICoord2D m_generalUL;
	ICoord2D m_generalLR;
	ICoord2D m_uAttackUL;					///< +0xf0
	ICoord2D m_uAttackLR;
	ICoord2D m_optionsUL;
	ICoord2D m_optionsLR;
	ICoord2D m_workerUL;
	ICoord2D m_workerLR;
	ICoord2D m_chatUL;						///< +0x120
	ICoord2D m_chatLR;
	ICoord2D m_beaconUL;
	ICoord2D m_beaconLR;
	ICoord2D m_powerBarUL;
	ICoord2D m_powerBarLR;
	Image *m_expBarForeground;				///< +0x150
	Image *m_commandMarkerImage;			///< +0x154
};

// ControlBar's BFME border-colour and arrow slots, written inline by retail.
struct BfmeControlBarSchemeInitBar
{
	unsigned char m_unreconstructed_000[ 0x294 ];
	Color m_commandBarBorderColor;			///< retail this+0x294
	unsigned char m_unreconstructed_298[ 0x2bc - 0x298 ];
	const Image *m_genArrow;				///< retail this+0x2bc
};

// updateBuildUpClockColor and the five-colour updateCommanBarBorderColors,
// under the names their matched bodies carry (0x0049D010, 0x0049D020).
class Rva0049D010DwordSlot
{
public:
	void set(Int value);
};

class Gen_0049D020
{
public:
	void bfmeSet(Int build, Int action, Int upgrade, Int system, Int fifth);
};

// addAnimation

// addImage

// Retail ControlBarScheme::drawForeground (0x004AD4C0) is implemented in ControlBarScheme_drawBackground.cpp.

// Retail ControlBarScheme::drawBackground (0x004AD600) is implemented in ControlBarScheme_drawBackground.cpp.

//
// Parse the Image Part of the command bar
//-----------------------------------------------------------------------------
// Body in ControlBarScheme_parseImagePart.asm (exact 172B retail @ 0x4AE920).
// Retail inlines addImage + STLport list node alloc; C++ emits call-shaped list insert.

//
// parse the animating part of the control bar scheme
//-----------------------------------------------------------------------------
// Body in ControlBarScheme_parseAnimatingPart.asm (exact 219B retail @ 0x4AEA00).
// Retail inlines addAnimation+addImage + STLport list node alloc; C++ cannot match.

//
// Create a new control bar and return it.  Link it into our control bar list
//-----------------------------------------------------------------------------
// Verified retail body at 0x004AEB20 (267 bytes); INI parser is the named caller.
ControlBarScheme *ControlBarSchemeManager::newControlBarScheme( AsciiString name )
{
	ControlBarScheme *cbScheme = 	findControlBarScheme(name);
	if(cbScheme)
	{
		DEBUG_ASSERTCRASH(false,("We're overwriting a previous control bar scheme %s",name.str()));
		cbScheme->reset();
		cbScheme->m_name.set( name );
		cbScheme->m_name.toLower();
		return cbScheme;		
	}

	cbScheme = NEW ControlBarScheme;

	if( !cbScheme  || name.isEmpty() )
	{
		DEBUG_ASSERTCRASH(FALSE,("Could not create controlbar %s", name.str()));
		return NULL;
	}

	cbScheme->m_name.set( name );
	cbScheme->m_name.toLower();

	m_schemeList.push_back(cbScheme);
		
	return cbScheme;
}

//-----------------------------------------------------------------------------
// Body in ControlBarScheme_setControlBarSchemeByPlayer.asm (exact 590B retail).

//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
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

