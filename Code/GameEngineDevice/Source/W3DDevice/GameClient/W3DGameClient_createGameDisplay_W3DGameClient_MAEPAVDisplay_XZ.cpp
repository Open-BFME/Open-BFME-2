// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient
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

// BFME's placement delete for Drawable calls the CRT free import directly.
// The reference pool macro routes it through ::operator delete, which lands at
// a different retail body.  Override it before any transitive include can
// instantiate Drawable's inline pool glue.
#include "Common/GameMemory.h"
#pragma push_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
extern "C" void free(void *);
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return MP_GLUE_ALLOCATE(ARGCLASS); \
	} \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		free(p); \
	} \
protected: \
	inline void *operator new(size_t s) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return ::operator new(s); \
	} \
	inline void operator delete(void *p) \
	{ \
		::operator delete(p); \
	} \
private: \
	virtual MemoryPool *getObjectMemoryPool() \
	{ \
		return ARGCLASS::getClassMemoryPool(); \
	} \
public:
#undef MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE
#define MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(ARGCLASS, ARGPOOLNAME) \
	MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
	GCMP_FIND(ARGCLASS, ARGPOOLNAME)
#include "GameClient/Drawable.h"
#pragma pop_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")

// USER INCLUDES //////////////////////////////////////////////////////////////

#include "Common/GameType.h"
#include "Common/STLTypedefs.h"
#include "Common/SubsystemInterface.h"

#define _SNOW_H_
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Snow.h
class SnowManager : public SubsystemInterface
{
public:
	SnowManager();
	virtual ~SnowManager();
	virtual void init();
	virtual void reset();
	virtual void updateIniSettings();

private:
	unsigned char m_retailData[ 0x60 ];
};

#define _W3DSNOW_H_
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DSnow.h
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
	unsigned char m_retailData[ 0x34 ];
};

typedef char BFMERetailSnowManagerSizeCheck[ sizeof( SnowManager ) == 0x68 ? 1 : -1 ];
typedef char BFMERetailW3DSnowManagerSizeCheck[ sizeof( W3DSnowManager ) == 0x9c ? 1 : -1 ];

#define __TERRAINVISUAL_H_
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/TerrainVisual.h
class TerrainVisual
{
public:
	virtual void anchor();

private:
	unsigned char m_retailData[ 0x0c ];
};

#define __W3DTERRAINVISUAL_H_
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainVisual.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
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
#include "GameClient/GameClient.h"
#include "GameClient/GameFont.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/RayEffect.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "W3DDevice/GameClient/W3DView.h"
#include "W3DDevice/GameClient/W3DWater.h"

// The placement delete is inline in the pool-glue macro.  This TU owns the
// retail shared body, so keep its COMDAT emitted even though no constructor in
// this source has an exception path that ODR-uses it.
void (*bfmeDrawablePlacementDeleteAnchor)(void *, Drawable::DrawableMagicEnum) =
	&Drawable::operator delete;

#define __W3DINGAMEUI_H_
class View;
class RenderObjClass;
class HAnimClass;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DInGameUI.h
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
class BFMERetailFontLibrary : public FontLibrary
{
public:
	BFMERetailFontLibrary();
	virtual void anchor();

private:
	char m_data[ 24 ];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DGameFont.h
class W3DFontLibrary : public BFMERetailFontLibrary
{
protected:
	Bool loadFontData( GameFont *font );
};

#define __KEYBOARD_H_
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Keyboard.h
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
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/GameClient/Win32DIKeyboard.h
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
#include "W3DDevice/GameClient/W3DStatusCircle.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "W3DDevice/GameClient/heightmap.h"
#include "WW3D2/Part_emt.h"
#include "WW3D2/HAnim.h"
#include "WW3D2/HTree.h"
#include "WW3D2/AnimObj.h"  ///< @todo superhack for demo, remove!

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1W3DGameClient@@UAE@XZ present-unmatched
W3DGameClient::~W3DGameClient()
{

}  // end ~W3DGameClient
