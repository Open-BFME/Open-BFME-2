// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB -DBFME_STLP_NODE_ALLOC -Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/MessageStream
// stlport
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

// SelectionXlat.cpp
// Message stream translator
// Author: Michael S. Booth, January 2001

// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ActionManager.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/MessageStream.h"
#include "Common/MiscAudio.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ThingTemplate.h"

#include "GameLogic/Damage.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Squad.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/UpdateModule.h"

#include "GameClient/ControlBar.h"
#include "GameClient/Display.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Keyboard.h"
#include "GameClient/SelectionInfo.h"
#include "GameClient/SelectionXlat.h"
#include "GameClient/TerrainVisual.h"

namespace _STL
{
extern template _Vector_base<Object *, allocator<Object *> >::_Vector_base(
	size_t, const allocator<Object *> &);
}

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Lorenzen changed this to a member of SelectionTranslator, providing external access
// name ly in rebuildholeexposedie, where we decide whether to create GLA Holes when hand-of-Godding
//#if defined(_DEBUG) || defined(_INTERNAL) || defined(_ALLOW_DEBUG_CHEATS_IN_RELEASE)
//static Bool TheHandOfGodSelectionMode = false;
//#endif

#if defined(_DEBUG) || defined(_INTERNAL)
static Bool TheHurtSelectionMode = false;
static Bool TheDebugSelectionMode = false;
#endif

//-----------------------------------------------------------------------------
static Bool currentlyLookingForSelection( )
{
	// This needs to check if we are currently targetting for special weapons fire.
	return TheInGameUI->getGUICommand() == NULL;
}

//-----------------------------------------------------------------------------
Bool areAllSelected( const DrawableList& listToCheck );

//-----------------------------------------------------------------------------
struct SFWRec
{
	SelectionTranslator *translator;
	GameMessage *createTeamMsg;
	Bool dragSelecting;
};


/*friend*/ Bool killThemKillThemAllWrapper( Drawable *draw, void *userData )
{
	SFWRec *info = (SFWRec *)userData;
	info->translator->killThemKillThemAll( draw, info->createTeamMsg );
	return true;
}
