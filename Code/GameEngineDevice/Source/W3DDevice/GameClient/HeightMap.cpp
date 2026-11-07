// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Link view first: Vector4(x,y,z,w) stays inline without emitting an SSE
// copy that competes with retail's integer-move owner (0x006D8A30).
// The TU's /O1 setting also compiles multilist.h's inline members for size.
#include "multilist.h"
#include "../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
// stlport

// rendobj.h: this unit holds the retail rows of Set_Alpha and the four
// _bfme_ro_flag11x setters; every other unit only declares them.
#define BFME_RO_DEFINE_FLAGS

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
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

// FILE: Heightmap.cpp ////////////////////////////////////////////////
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
// File name: Heightmap.cpp
//
// Created:   Mark W., John Ahlquist, April/May 2001
//
// Desc:      Draw the terrain and scorchmarks in a scene.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//         Includes                                                      
//-----------------------------------------------------------------------------


// Retail owns the snapshot-aware outlined texture-stage setter separately.
#include "../../../../../reference/shims/bfme_mapper_apply_link/dx8wrapper.h"
#include "W3DDevice/GameClient/heightmap.h"

#ifndef USE_FLAT_HEIGHT_MAP // Flat height map uses flattened textures. jba. [3/20/2003]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assetmgr.h>
#include <texture.h>
#include <tri.h>
#include <colmath.h>
#include <coltest.h>
#include <rinfo.h>
#include <camera.h>
#include <d3dx8core.h>
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"

#include "GameClient/TerrainVisual.h"
#include "GameClient/View.h"
#include "GameClient/Water.h"

#include "GameLogic/AIPathfind.h"
#include "GameLogic/TerrainLogic.h"
#include "W3DDevice/GameClient/TerrainTex.h"
#include "W3DDevice/GameClient/W3DDynamicLight.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DTerrainTracks.h"
#include "W3DDevice/GameClient/W3DBibBuffer.h"
#include "W3DDevice/GameClient/W3DTreeBuffer.h"
#include "W3DDevice/GameClient/W3DPropBuffer.h"
#include "W3DDevice/GameClient/W3DRoadBuffer.h"
#include "W3DDevice/GameClient/W3DBridgeBuffer.h"
#include "W3DDevice/GameClient/W3DWaypointBuffer.h"
#include "W3DDevice/GameClient/W3DCustomEdging.h"
#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "W3DDevice/GameClient/W3DWater.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/Light.h"
#include "WW3D2/Scene.h"
#include "W3DDevice/GameClient/W3DPoly.h"
#include "W3DDevice/GameClient/W3DCustomScene.h"

#include "Common/PerfTimer.h"
#include "Common/UnitTimings.h" //Contains the DO_UNIT_TIMINGS define jba.		 

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#define no_OPTIMIZED_HEIGHTMAP_LIGHTING	01
// Doesn't work well.  jba.

const Bool HALF_RES_MESH = false;

HeightMapRenderObjClass *TheHeightMap = NULL;
//-----------------------------------------------------------------------------
//         Private Data                                                     
//-----------------------------------------------------------------------------
#define SC_DETAIL_BLEND ( SHADE_CNST(ShaderClass::PASS_LEQUAL, ShaderClass::DEPTH_WRITE_ENABLE, ShaderClass::COLOR_WRITE_ENABLE, ShaderClass::SRCBLEND_ONE, \
	ShaderClass::DSTBLEND_ZERO, ShaderClass::FOG_DISABLE, ShaderClass::GRADIENT_MODULATE, ShaderClass::SECONDARY_GRADIENT_DISABLE, ShaderClass::TEXTURING_ENABLE, \
	ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_ENABLE, ShaderClass::DETAILCOLOR_SCALE, ShaderClass::DETAILALPHA_DISABLE) )

// Retail .data 0x009B4140 holds 0x0051581B at load: SC_DETAIL_BLEND with primary gradient 6
// (a BFME 2 mode, as W3DBibBuffer.cpp's detailAlphaShader has), laid out in BFME 2's shader
// bits: cull mode at bit 20 and the post-detail color function at bits 21-24
// (reference/shims/bfmeshader/shader.h). This unit compiles against Zero Hour's shader.h,
// whose SHADE_CNST puts them at bits 19 and 20, so those two fields are shifted here.
#define BFME2_SC_DETAIL_BLEND ( SHADE_CNST(ShaderClass::PASS_LEQUAL, ShaderClass::DEPTH_WRITE_ENABLE, ShaderClass::COLOR_WRITE_ENABLE, ShaderClass::SRCBLEND_ONE, 	ShaderClass::DSTBLEND_ZERO, ShaderClass::FOG_DISABLE, (ShaderClass::PriGradientType)6, ShaderClass::SECONDARY_GRADIENT_DISABLE, ShaderClass::TEXTURING_ENABLE, 	ShaderClass::ALPHATEST_DISABLE, ShaderClass::CULL_MODE_DISABLE, ShaderClass::DETAILCOLOR_DISABLE, ShaderClass::DETAILALPHA_DISABLE) 	| (ShaderClass::CULL_MODE_ENABLE << 20) | (ShaderClass::DETAILCOLOR_SCALE << 21) )

// Not static: BaseHeightMapInitHeightData.cpp reads it too.
ShaderClass detailOpaqueShader(BFME2_SC_DETAIL_BLEND);

#define DEFAULT_MAX_FRAME_EXTRABLEND_TILES		256	//default number of terrain tiles rendered per call (must fit in one VB)
#define DEFAULT_MAX_MAP_EXTRABLEND_TILES		2048	//default size of array allocated to hold all map extra blend tiles.
#define DEFAULT_MAX_BATCH_SHORELINE_TILES		512	//maximum number of terrain tiles rendered per call (must fit in one VB)
#define DEFAULT_MAX_MAP_SHORELINE_TILES		4096	//default size of array allocated to hold all map shoreline tiles.

#define ADJUST_FROM_INDEX_TO_REAL(k) ((k-m_map->getBorderSizeInline())*MAP_XY_FACTOR)
inline Int IABS(Int x) {	if (x>=0) return x; return -x;};

//-----------------------------------------------------------------------------
//         Private Functions                                               
//-----------------------------------------------------------------------------

//=============================================================================
// HeightMapRenderObjClass::freeIndexVertexBuffers
//=============================================================================
/** Frees the w3d resources used to draw the terrain. */
//=============================================================================
//=============================================================================
// HeightMapRenderObjClass::freeMapResources
//=============================================================================
/** Frees the w3d resources used to draw the terrain. */
//=============================================================================
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameClient/HeightMapRenderObjClass_freeMapResources.cpp

//=============================================================================
// HeightMapRenderObjClass::doTheDynamicLight
//=============================================================================
/** Calculates the diffuse lighting as affected by dynamic lighting. */
//=============================================================================
//=============================================================================
// HeightMapRenderObjClass::getXWithOrigin
//=============================================================================
/** Gets the x index that corresponds to the data.  For example, if the columns
are shifted by 3, index 3 is actually the first row of polygons, or 0.  Yes it
is confusing, but it makes sliding the map 10x faster.  */
//=============================================================================
//=============================================================================
// HeightMapRenderObjClass::getYWithOrigin
//=============================================================================
/** Gets the y index that corresponds to the data.  For example, if the rows
are shifted by 3, index 3 is actually the first row of polygons, or 0.  Yes it
is confusing, but it makes sliding the map 10x faster.  */
//=============================================================================
//=============================================================================
// HeightMapRenderObjClass::updateVB
//=============================================================================
/** Update a rectangular block of the given Vertex Buffer. 
data is expected to be an array same dimensions as current heightmap
mapped into this VB.
*/
//=============================================================================
//=============================================================================
// HeightMapRenderObjClass::updateVBForLight
//=============================================================================


//=============================================================================
// HeightMapRenderObjClass::doPartialUpdate
//=============================================================================
//=============================================================================
// HeightMapRenderObjClass::updateBlock
//=============================================================================
/** Updates a block of vertices from [x0,y0 to x1,y1]
The vertex coordinates and texture coordinates, as well as static lighting are updated.
*/


//-----------------------------------------------------------------------------
//         Public Functions                                                
//-----------------------------------------------------------------------------

//=============================================================================
// HeightMapRenderObjClass::~HeightMapRenderObjClass
//=============================================================================
/** Destructor. Releases w3d assets. */
//=============================================================================
// byte-exact reconstruction: Code/GameEngine/Source/Common/HeightMapRenderObjClassDestructorThunk.cpp
//=============================================================================
// HeightMapRenderObjClass::HeightMapRenderObjClass
//=============================================================================
/** Constructor. Mostly nulls out the member variables. */
//=============================================================================


//=============================================================================
// HeightMapRenderObjClass::adjustTerrainLOD
//=============================================================================
/** Adjust the terrain Level Of Detail.  If adj > 0 , increases LOD 1 step, if 
adj < 0 decreases it one step, if adj==0, then just sets up for the current LOD */
//=============================================================================
//=============================================================================
// HeightMapRenderObjClass::ReleaseResources
//=============================================================================
/** Releases all w3d assets, to prepare for Reset device call. */
//=============================================================================
//=============================================================================
// HeightMapRenderObjClass::ReAcquireResources
//=============================================================================
/** Reallocates all W3D assets after a reset.. */
//=============================================================================
//=============================================================================
// HeightMapRenderObjClass::reset
//=============================================================================
/** Updates the macro noise/lightmap texture (pass 3) */
//=============================================================================
//=============================================================================
// HeightMapRenderObjClass::oversizeTerrain
//=============================================================================
/** Sets the terrain oversize amount. */
//=============================================================================


//=============================================================================
// HeightMapRenderObjClass::initHeightData
//=============================================================================
/** Allocate a heightmap of x by y vertices and fill with initial height values.
Also allocates all rendering resources such as vertex buffers, index buffers, 
shaders, and materials.*/
//=============================================================================

//=============================================================================
// HeightMapRenderObjClass::On_Frame_Update
//=============================================================================
/** Updates the diffuse color values in the vertices as affected by the dynamic lights.*/
//=============================================================================
//=============================================================================
// HeightMapRenderObjClass::staticLightingChanged
//=============================================================================
/** Notification that all lighting needs to be recalculated. */
//=============================================================================


//=============================================================================
// HeightMapRenderObjClass::updateCenter
//=============================================================================
/** Updates the positioning of the drawn portion of the height map in the 
heightmap.  As the view slides around, this determines what is the actually
rendered portion of the terrain.  Only a 96x96 section is rendered at any time, 
even though maps can be up to 1024x1024.  This function determines which subset
is rendered. */
//=============================================================================
//=============================================================================
// HeightMapRenderObjClass::Render
//=============================================================================
/** Renders (draws) the terrain. */
//=============================================================================
//DECLARE_PERF_TIMER(Terrain_Render)



///Performs additional terrain rendering pass, blending in the black shroud texture.
//=============================================================================
// HeightMapRenderObjClass::renderExtraBlendTiles
//=============================================================================
// Set_Transform(Matrix3D) is import-inlined, so no local body emits Matrix4(Vector4 x4);
// the anchor retains this unit's row copy (0x6A34E) and is not retail code.
#pragma inline_depth(0)
// ?_bfmeHeightMapMatrix4RowsCtorAnchor absent-from-retail
void _bfmeHeightMapMatrix4RowsCtorAnchor(Matrix4x4 *matrix4x4, const Vector4 *rows)
{
	matrix4x4->Matrix4x4::Matrix4x4(rows[0], rows[1], rows[2], rows[3]);
}

// The bit setters BFME_RO_DEFINE_FLAGS defines (rows Set_Alpha 0x6CF6F and
// _bfme_ro_flag110/112/114/116) were emitted through the vtable of the unrowed
// Zero Hour constructor; qualified calls keep them emitted. Not retail code.
// ?_bfmeHeightMapRenderObjFlagsAnchor absent-from-retail
void _bfmeHeightMapRenderObjFlagsAnchor(RenderObjClass *robj, int onoff)
{
	robj->RenderObjClass::Set_Alpha(onoff);
	robj->RenderObjClass::_bfme_ro_flag110(onoff);
	robj->RenderObjClass::_bfme_ro_flag112(onoff);
	robj->RenderObjClass::_bfme_ro_flag114(onoff);
	robj->RenderObjClass::_bfme_ro_flag116(onoff);
}
#pragma inline_depth()

// The unrowed Zero Hour Render body was this unit's only caller of the inline
// RTS3DScene::getCustomPassMode, whose row (0x0026FF4F) this copy matches; taking
// its address keeps the inline emitted.
CustomScenePassModes (RTS3DScene::*_bfmeInlineAnchor_HeightMap_0)(void) = &RTS3DScene::getCustomPassMode;
#endif
