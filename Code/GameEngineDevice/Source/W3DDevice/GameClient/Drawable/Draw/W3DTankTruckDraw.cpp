// cl: /D__PLACEMENT_VEC_NEW_INLINE /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/stlp_nodealloc /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankTruckDraw.cpp); this unit had no counterpart under Code/.
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

// FILE: W3DTankTruckDraw.cpp 
// Draw TankTrucks.  Actually, this draws quad cannon which has both treads and wheels.
// Author: Mark Wilczynski, August 2002

#include "../../../../../../../reference/shims/bfme_wwmath_floor_link/wwmath.h"
#include <stdlib.h>
#include <math.h>

#include "Common/Thing.h"
#include "Common/ThingFactory.h"
#include "Common/GameAudio.h"
#include "Common/GlobalData.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameClient/Drawable.h"
#include "GameClient/ParticleSys.h"
#include "W3DDevice/GameClient/W3DGameClient.h"
#include "W3DDevice/GameClient/Module/W3DTankTruckDraw.h"
#include "WW3D2/matinfo.h"
// bfme link decl-only begin
template <> DynamicVectorClass<Render2DClass *>::~DynamicVectorClass();
// bfme link decl-only end

//#define SHOW_TANK_DEBRIS
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// The unrowed Zero Hour constructor that stood here emitted this unit's two
// rows through its tread array: TreadObjectInfo's implicit constructor
// (0x000CDFB1, taken by ??_H) and, with it, RenderObjClass::Material_Override's
// (0x000636B3). TreadObjectInfo is a protected nested type, so the anchor is a
// static member of a derived helper that is never instantiated (precedent:
// TerrainTrackEdgeInfoO1.cpp). Not retail code.
struct BfmeTankTruckTreadAnchor : public W3DTankTruckDraw
{
	static void anchor(void);
};
// ?anchor@BfmeTankTruckTreadAnchor@@ absent-from-retail
void BfmeTankTruckTreadAnchor::anchor(void)
{
	TreadObjectInfo treads[MAX_TREADS_PER_TANK];
	(void)treads;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// W3DTankTruckDraw::tossEmitters: defined in W3DTankTruckDrawTossEmitters.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
void W3DTankTruckDraw::setFullyObscuredByShroud(Bool fullyObscured)
{
	if (fullyObscured != getFullyObscuredByShroud())
	{
		if (fullyObscured)
			tossEmitters();
		else
			createEmitters();
	}
	W3DModelDraw::setFullyObscuredByShroud(fullyObscured);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**

 * Start creating debris from the tank treads
 */
// createEmitters is owned by W3DTankTruckDrawCreateEmitters.cpp.
// The ZH donor definition here was not retail and shadowed that native body.


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**
 * Stop creating debris from the tank treads
 */
// W3DTankTruckDraw::enableEmitters: defined in W3DTankTruckDrawTossEmitters.cpp (its row's unit).
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**Update uv coordinates on each tread object to simulate movement*/
// W3DTankTruckDraw::updateTreadPositions: retail body not identified (0x000CDFC8, once rowed
// under this name, is W3DTankDraw::updateTreadPositions; see W3DTankTruckDrawUpdateTreadPositions.cpp).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/** Map behavior states into W3D animations. */
//-------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
void W3DTankTruckDraw::loadPostProcess( void )
{

	// extend base class
	W3DModelDraw::loadPostProcess();

	// toss any existing ones (no need to re-create; we'll do that on demand)
	tossEmitters();

}  // end loadPostProcess

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0TreadObjectInfo@W3DTankDraw@@QAE@XZ=??0TreadObjectInfo@W3DTankTruckDraw@@QAE@XZ")
