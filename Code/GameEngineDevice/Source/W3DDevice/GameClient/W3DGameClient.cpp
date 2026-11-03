// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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

// FILE: W3DGameClient.cpp /////////////////////////////////////////////////
//
// W3DImplementaion of the GameClient.  If there were a client/server
// architecture, this game interface could be thought of as the "client"
// that the user uses to interact with the logic of the game world which
// would be known as the "server"
//
// Author: Colin Day, April 2001
//
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include <stdlib.h>

// USER INCLUDES //////////////////////////////////////////////////////////////

#include "Common/GameType.h"
#include "Common/STLTypedefs.h"
#include "Common/SubsystemInterface.h"

#define _SNOW_H_
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Snow.h
class SnowManager : public SubsystemInterface
{
public:
	SnowManager();
	virtual ~SnowManager();
	virtual void init();
	virtual void reset();
	virtual void updateIniSettings();

private:
	unsigned char m_retailData[ 0x6c ];
};

#define _W3DSNOW_H_
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DSnow.h
class W3DSnowManager : public SnowManager
{
public:
	W3DSnowManager();
	virtual ~W3DSnowManager();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void updateIniSettings();

private:
	unsigned char m_retailData[ 0x3c ];
};

// Retail extents 0x74/0xB0: createSnowManager's operator new (0x0004C5F8, matched) pushes 0xB0.
typedef char BFMERetailSnowManagerSizeCheck[ sizeof( SnowManager ) == 0x74 ? 1 : -1 ];
typedef char BFMERetailW3DSnowManagerSizeCheck[ sizeof( W3DSnowManager ) == 0xb0 ? 1 : -1 ];

#define __TERRAINVISUAL_H_
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/TerrainVisual.h
class TerrainVisual
{
public:
	virtual void anchor();

private:
	unsigned char m_retailData[ 0x0c ];
};

#define __W3DTERRAINVISUAL_H_
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainVisual.h
class W3DTerrainVisual : public TerrainVisual
{
public:
	W3DTerrainVisual();
	virtual ~W3DTerrainVisual();

private:
	unsigned char m_retailData[ 0x10 ];
};

typedef char BFMERetailTerrainVisualSizeCheck[ sizeof( TerrainVisual ) == 0x10 ? 1 : -1 ];
typedef char BFMERetailW3DTerrainVisualSizeCheck[ sizeof( W3DTerrainVisual ) == 0x20 ? 1 : -1 ];

#define _IN_GAME_UI_H_
class Drawable;
typedef std::list< Drawable * > DrawableList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	virtual void anchor();

private:
	char m_data[ 0x13a8 ];
};

#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/ModuleFactory.h"
#include "Common/RandomValue.h"
#include "Common/GlobalData.h"
#include "Common/GameLOD.h"
#include "GameClient/Drawable.h"
// This unit searches Open-BFME-1's sweep shims; take this repository's
// GameClient.h shadow, which has no ZH inline findDrawableByID (retail's is
// the out-of-line hash lookup in GameClientDrawableTOC.cpp).
#include "../../../../../reference/shims/sweep/GameClient/GameClient.h"
#define __GAMEFONT_H_
class GameFont;
#include "GameClient/ParticleSys.h"
#include "GameClient/RayEffect.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "W3DDevice/GameClient/W3DView.h"
#include "W3DDevice/GameClient/W3DWater.h"

#define __W3DINGAMEUI_H_
class View;
class RenderObjClass;
class HAnimClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DInGameUI.h
class W3DInGameUI : public InGameUI
{
public:
	W3DInGameUI();
	virtual ~W3DInGameUI();
	virtual void init();
	virtual void update();
	virtual void reset();
	virtual void draw();

protected:
	virtual View *createView();
	virtual void drawSelectionRegion();
	virtual void drawMoveHints( View *view );
	virtual void drawAttackHints( View *view );
	virtual void drawPlaceAngle( View *view );

private:
	enum { MAX_RETAIL_MOVE_HINTS = 25 };
	RenderObjClass *m_moveHintRenderObj[ MAX_RETAIL_MOVE_HINTS ];
	HAnimClass *m_moveHintAnim[ MAX_RETAIL_MOVE_HINTS ];
	RenderObjClass *m_buildingPlacementAnchor;
	RenderObjClass *m_buildingPlacementArrow;
};

#define __W3DGAMEFONT_H_
class FontLibrary
{
public:
	FontLibrary();
	virtual ~FontLibrary();

private:
	char m_data[ 0x28 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DGameFont.h
class W3DFontLibrary : public FontLibrary
{
public:
	W3DFontLibrary() {}
	virtual ~W3DFontLibrary();
};

#define __KEYBOARD_H_
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Keyboard.h
class Keyboard : public SubsystemInterface
{
public:
	Keyboard();
	virtual ~Keyboard();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual Bool getCapsState() = 0;

private:
	unsigned char m_retailData[ 0xe14 ];
};

#define __WIN32DIKEYBOARD_H_
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/GameClient/Win32DIKeyboard.h
class DirectInputKeyboard : public Keyboard
{
public:
	DirectInputKeyboard();
	virtual ~DirectInputKeyboard();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual Bool getCapsState();

private:
	unsigned char m_retailData[ 8 ];
};

typedef char BFMERetailKeyboardSizeCheck[ sizeof( Keyboard ) == 0xe1c ? 1 : -1 ];
typedef char BFMERetailDirectInputKeyboardSizeCheck[ sizeof( DirectInputKeyboard ) == 0xe24 ? 1 : -1 ];

#include "W3DDevice/GameClient/W3DGameClient.h"
// This unit only uses the static color operation, not an instance layout.
// Its dirty byte is the existing data-ledger owner at RVA 0x009E207C.
extern unsigned char g_trackDirty;
class W3DStatusCircle
{
public:
	static void setColor(Int red, Int green, Int blue)
	{
		g_trackDirty = true;
		m_diffuse = blue + (green << 8) + (red << 16);
	}
	static Int m_diffuse;
};
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "W3DDevice/GameClient/heightmap.h"
#include "WW3D2/Part_emt.h"
#include "WW3D2/HAnim.h"
#include "WW3D2/HTree.h"
#include "WW3D2/AnimObj.h"  ///< @todo superhack for demo, remove!
// bfme link decl-only begin
template <> DynamicVectorClass<Render2DClass *>::~DynamicVectorClass();
// bfme link decl-only end

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** Initialize resources for the w3d game client */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** Per frame udpate, note we are extending functionality */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** Reset this device client system.  Note we are extending reset functionality from
	* the device independent client */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** allocate a new drawable using the thing template for initialization.
	* if we want to have the thing manager actually contain the pools of
	* object and drawable storage it seems OK to have it be friends with the
	* GameLogic/Client for those purposes, or we could put the allocation pools
	* in the GameLogic and GameClient themselves */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void W3DGameClient::addScorch(const Coord3D *pos, Real radius, Scorches type)
{
	if (TheTerrainRenderObject) 
	{
		Vector3 loc(pos->x, pos->y, pos->z);
		TheTerrainRenderObject->addScorch(loc, radius, type);
	}
}

//-------------------------------------------------------------------------------------------------
/** create an effect that requires a start and end location */
//-------------------------------------------------------------------------------------------------
class BFMEThingFactory : public ThingFactory
{
public:
	Drawable *newDrawable(const ThingTemplate *tmplate, DrawableStatus statusBits, Int drawableID);
};

void W3DGameClient::createRayEffectByTemplate( const Coord3D *start, 
																		 const Coord3D *end, 
																		 const ThingTemplate* thingTemplate )
{
	Drawable *draw = ((BFMEThingFactory *)TheThingFactory)->newDrawable(thingTemplate, DRAWABLE_STATUS_NONE, -1);

	if( draw )
	{
		Coord3D pos;

		// add to world, the location of the drawable is at the midpoint of laser
		pos.x = (end->x - start->x) * 0.5f + start->x;
		pos.y = (end->y - start->y) * 0.5f + start->y;
		pos.z = (end->z - start->z) * 0.5f + start->z;
		draw->setPosition( &pos );

		// add this ray effect to the list of ray effects
		TheRayEffects->addRayEffect( draw, start, end );
			
	}  // end if

}  // end createRayEffectByTemplate

//-------------------------------------------------------------------------------------------------
/**  Tell all the drawables what time of day it is now */
//-------------------------------------------------------------------------------------------------
class W3DGameClientWaterShim
{
public:
	void setTimeOfDay(TimeOfDay tod);
};

class W3DGameClientShadowShim
{
public:
	void setTimeOfDay(TimeOfDay tod);
};

class W3DGameClientDisplayShim
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void setTimeOfDay(TimeOfDay tod) = 0;
};

// W3DGameClient::setTimeOfDay: defined in W3DGameClient_setTimeOfDay.cpp (its row's unit).
  // end setTimeOfDay


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void W3DGameClient::setTeamColor(Int red, Int green, Int blue)
{

	W3DStatusCircle::setColor(red, green, blue);

}  // end setTeamColor

//-------------------------------------------------------------------------------------------------
/** temporary entry point for adjusting LOD for development testing. */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/**  Tell the terrain that an object moved, so it can knock down trees or crush grass
		or whatever is appropriate. jba. */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// The unrowed Zero Hour constructor and destructor that stood here emitted
// W3DGameClient's vtable, this unit's only emitter of three inline virtuals:
// GameClient::firstDrawable and getDrawableList (GameClientDrawableTOC's
// GameClient vtable takes them) and the createGameDisplay row (0x0008FCAE).
// createGameDisplay is protected, so the anchor is a static member of a derived
// helper that is never instantiated (precedent: TerrainTrackEdgeInfoO1.cpp).
// Not retail code.
struct BfmeW3DGameClientInlineAnchor : public W3DGameClient
{
	static void anchor(BfmeW3DGameClientInlineAnchor *client);
};
#pragma inline_depth(0)
// ?anchor@BfmeW3DGameClientInlineAnchor@@ absent-from-retail
void BfmeW3DGameClientInlineAnchor::anchor(BfmeW3DGameClientInlineAnchor *client)
{
	client->GameClient::firstDrawable();
	client->GameClient::getDrawableList();
	client->W3DGameClient::createGameDisplay();
}
#pragma inline_depth()
