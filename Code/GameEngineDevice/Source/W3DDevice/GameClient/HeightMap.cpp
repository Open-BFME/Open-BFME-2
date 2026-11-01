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

// Not static: BaseHeightMapInitHeightData.cpp reads it too.
ShaderClass detailOpaqueShader(SC_DETAIL_BLEND);

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
// ?updateBlock@HeightMapRenderObjClass@@UAEHHHHHPAVWorldHeightMap@@PAV?$RefMultiListIterator@VRenderObjClass@@@@@Z present-unmatched
Int HeightMapRenderObjClass::updateBlock(Int x0, Int y0, Int x1, Int y1,  WorldHeightMap *pMap, RefRenderObjListIterator *pLightsIterator)
{	
#ifdef _DEBUG
	DEBUG_ASSERTCRASH(x0>=0,  ("HeightMapRenderObjClass::UpdateBlock parameters extend beyond left edge."));
	DEBUG_ASSERTCRASH(y0>=0,  ("HeightMapRenderObjClass::UpdateBlock parameters extend beyond bottom edge."));
	DEBUG_ASSERTCRASH(x1<m_x, ("HeightMapRenderObjClass::UpdateBlock parameters extend beyond right edge."));
	DEBUG_ASSERTCRASH(y1<m_y, ("HeightMapRenderObjClass::UpdateBlock parameters extend beyond top edge."));
	DEBUG_ASSERTCRASH(x0<=x1, ("HeightMapRenderObjClass::UpdateBlock parameters have inside-out rectangle (on X)."));
	DEBUG_ASSERTCRASH(y0<=y1, ("HeightMapRenderObjClass::UpdateBlock parameters have inside-out rectangle (on Y)."));
#endif
	Invalidate_Cached_Bounding_Volumes();
	if (pMap) {
		REF_PTR_SET(m_stageZeroTexture, pMap->getTerrainTexture());
		REF_PTR_SET(m_stageOneTexture, pMap->getAlphaTerrainTexture());
	}

	Int i,j;
	DX8VertexBufferClass	**pVB;
	Int originX,originY;
	//step through each vertex buffer that needs updating
	for (j=0; j<m_numVBTilesY; j++)
	{
		originY=j*VERTEX_BUFFER_TILE_LENGTH;	//location of this VB on the large full-size heightmap
		Int yMin, yMax;
		yMin = originY;
		if (y0>yMin) yMin = y0;
		yMax = originY+VERTEX_BUFFER_TILE_LENGTH;
		if (y1<yMax) yMax = y1;
		if (yMin >= yMax) {
			continue;
		}
		for (i=0; i<m_numVBTilesX; i++)
		{	
			originX=i*VERTEX_BUFFER_TILE_LENGTH;	//location of this VB on the large full-size heightmap
			Int xMin, xMax;
			xMin = originX;
			if (xMin<x0) xMin = x0;
			xMax = originX+VERTEX_BUFFER_TILE_LENGTH;
			if (xMax>x1) xMax = x1;
			if (xMin >= xMax) {
				continue;
			}
			pVB=m_vertexBufferTiles+j*m_numVBTilesX+i;	//point to correct row/column of vertex buffers 
			char **pData = m_vertexBufferBackup+j*m_numVBTilesX+i;
			updateVB(*pVB, *pData, xMin, yMin, xMax, yMax, originX, originY, pMap, pLightsIterator);
		}
	}

	return 0;
}


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
// ??0HeightMapRenderObjClass@@QAE@XZ present-unmatched
HeightMapRenderObjClass::HeightMapRenderObjClass(void):
m_extraBlendTilePositions(NULL),
m_numExtraBlendTiles(0),
m_numVisibleExtraBlendTiles(0),
m_extraBlendTilePositionsSize(0),
m_vertexBufferTiles(NULL),
m_vertexBufferBackup(NULL),
m_originX(0),
m_originY(0),
m_indexBuffer(NULL),
m_numVBTilesX(0),
m_numVBTilesY(0),
m_numVertexBufferTiles(0),
m_numBlockColumnsInLastVB(0),
m_numBlockRowsInLastVB(0)
{
	TheHeightMap = this;
}


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
#define CENTER_LIMIT 2
#define BIG_JUMP 16
#define WIDE_STEP 32

static Int visMinX, visMinY, visMaxX, visMaxY;
static Bool check(const FrustumClass & frustum, WorldHeightMap *pMap, Int x, Int y) 
{
	if (x<0 || y<0) return(false);
	if (x>= pMap->getXExtent() || y>= pMap->getYExtent()) return(false);
	if (x >= visMinX && y >= visMinY && x <=visMaxX && y <= visMaxY) {
		return(true);
	}
	Int height = pMap->getHeight(x, y);
	Vector3 loc((x-pMap->getBorderSizeInline())*MAP_XY_FACTOR, (y-pMap->getBorderSizeInline())*MAP_XY_FACTOR, height*MAP_HEIGHT_SCALE);
	if (CollisionMath::Overlap_Test(frustum,loc) == CollisionMath::INSIDE) {
		if (x<visMinX) visMinX=x;
		if (x>visMaxX) visMaxX=x;
		if (y<visMinY) visMinY=y;
		if (y>visMaxY) visMaxY=y;
		return(true);
	}
	return(false);
}

static void calcVis(const FrustumClass & frustum, WorldHeightMap *pMap, Int minX, Int minY, Int maxX, Int maxY, Int limit)
{
	if (maxX-minX<2) return;
	if (maxY-minY<2) return;
	if (minX >=visMinX && minY >= visMinY && maxX <=visMaxX && maxY <= visMaxY) {
		return;
	}
	Int midX = (minX+maxX)/2;
	Int midY = (minY+maxY)/2;
	Bool recurse1 = maxX-minX>=limit;
	Bool recurse2 = recurse1;
	Bool recurse3 = recurse1;
	Bool recurse4 = recurse1;	 
	/* boxes are:

			1     2


			3			4 */

	if (check(frustum, pMap, midX, maxY)) {
		recurse1=true;
		recurse2=true;
	}
	if (check(frustum, pMap, midX, minY)) {
		recurse3=true;
		recurse4=true;
	}
	if (check(frustum, pMap, midX, midY)) {
		recurse1=true;
		recurse2=true;
		recurse3=true;
		recurse4=true;
	}
	if (check(frustum, pMap, minX, midY)) {
		recurse1=true;
		recurse3=true;
	}
	if (check(frustum, pMap, maxX, midY)) {
		recurse2=true;
		recurse4=true;
	}
	if (recurse1) {
		calcVis(frustum, pMap, minX, midY, midX, maxY, limit);
	}
	if (recurse2) {
		calcVis(frustum, pMap, midX, midY, maxX, maxY, limit);
	}
	if (recurse3) {
		calcVis(frustum, pMap, minX, minY, midX, midY, limit);
	}
	if (recurse4) {
		calcVis(frustum, pMap, midX, minY, maxX, midY, limit);
	}
}


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

// ?Render@HeightMapRenderObjClass@@ present-unmatched
void HeightMapRenderObjClass::Render(RenderInfoClass & rinfo)
{
	//USE_PERF_TIMER(Terrain_Render)
	
	Int i,j,devicePasses;
	W3DShaderManager::ShaderTypes st;
	Bool doCloud = TheGlobalData->m_useCloudMap;

	Matrix3D tm(Transform);
#if 0 // There is some weirdness sometimes with the dx8 static buffers.
			// This usually fixes terrain flashing.  jba.
	static Int delay = 1;
	delay --;
	if (delay<1) {
		delay = 1;
		static Int ndx = -1;
		ndx++;
		if (ndx>=m_numVertexBufferTiles) {
			ndx = 0;
		}
		DX8VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexBufferTiles[ndx]);
		VERTEX_FORMAT *vb = (VERTEX_FORMAT*)lockVtxBuffer.Get_Vertex_Array();	
		vb = 0;
	}
#endif
	// If there are trees, tell them to draw at the transparent time to draw.
	if (m_treeBuffer) {
		m_treeBuffer->setIsTerrain();
	}


#ifdef DO_UNIT_TIMINGS
#pragma MESSAGE("*** WARNING *** DOING DO_UNIT_TIMINGS!!!!")
	return;
#endif

#ifdef EXTENDED_STATS
	if (DX8Wrapper::stats.m_disableTerrain) {
		return;
	}
#endif

	DX8Wrapper::Set_Light_Environment(rinfo.light_environment);

	// Force shaders to update.
	m_stageTwoTexture->restore();
	DX8Wrapper::Set_Texture(0,NULL);
	DX8Wrapper::Set_Texture(1,NULL);
	ShaderClass::Invalidate();

	//	tm.Scale(ObjSpaceExtent);
	DX8Wrapper::Set_Transform(D3DTS_WORLD,tm);

	//Apply the shader and material

	DX8Wrapper::Set_Index_Buffer(m_indexBuffer,0);

	Bool doMultiPassWireFrame=FALSE;

	if (((RTS3DScene *)rinfo.Camera.Get_User_Data())->getCustomPassMode() == SCENE_PASS_ALPHA_MASK ||
		((SceneClass *)rinfo.Camera.Get_User_Data())->Get_Extra_Pass_Polygon_Mode() == SceneClass::EXTRA_PASS_CLEAR_LINE)
	{
			if (WW3D::Is_Texturing_Enabled())
			{	//first pass where we just fill the z-buffer

				devicePasses=1;	//one pass solid, next in wireframe.
				doMultiPassWireFrame=TRUE;

				if (rinfo.Additional_Pass_Count())
				{
					rinfo.Peek_Additional_Pass(0)->Install_Materials();
					renderTerrainPass(&rinfo.Camera);
					rinfo.Peek_Additional_Pass(0)->UnInstall_Materials();
					return;
				}
			}
			else
			{	//wireframe pass
				//Set to vertex diffuse lighting
				DX8Wrapper::Set_Material(m_vertexMaterialClass);
				//Set shader to non-textured solid color from vertex
				DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaqueSolidShader);
				devicePasses=1;	//one pass solid, next in wireframe.
				DX8Wrapper::Apply_Render_State_Changes();
				DX8Wrapper::Set_DX8_Texture_Stage_State( 0, D3DTSS_COLORARG2, D3DTA_TFACTOR );
				DX8Wrapper::Set_DX8_Render_State(D3DRS_TEXTUREFACTOR,0xff808080);
				doMultiPassWireFrame=TRUE;
				renderTerrainPass(&rinfo.Camera);
				DX8Wrapper::Set_DX8_Render_State(D3DRS_TEXTUREFACTOR,0xff008000);
				return;
			}
	}
	else
	{
		DX8Wrapper::Set_Material(m_vertexMaterialClass);
		DX8Wrapper::Set_Shader(m_shaderClass);

		if (TheGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT) {
			doCloud = false;
		}

 		st=W3DShaderManager::ST_TERRAIN_BASE; //set default shader
 		
 		//set correct shader based on current settings
 		if (!ShaderClass::Is_Backface_Culling_Inverted())
 		{	//not reflection pass
 			if (TheGlobalData->m_useLightMap && doCloud)
 			{	st=W3DShaderManager::ST_TERRAIN_BASE_NOISE12;
 			}
 			else
 			if (TheGlobalData->m_useLightMap)
 			{	//lightmap only
 				st=W3DShaderManager::ST_TERRAIN_BASE_NOISE2;
 			}
 			else
 			if (doCloud)
 			{	//cloudmap only
 				st=W3DShaderManager::ST_TERRAIN_BASE_NOISE1;
 			}
 		}
 		else
 		{	//reflection pass, just do base texture
 			st=W3DShaderManager::ST_TERRAIN_BASE;
 		}
 
 		//Find number of passes required to render current shader
 		devicePasses=W3DShaderManager::getShaderPasses(st);
 
 		if (m_disableTextures)
 			devicePasses=1;	//force to 1 lighting-only pass
 
 		//Specify all textures that this shader may need.
 		W3DShaderManager::setTexture(0,m_stageZeroTexture);
 		W3DShaderManager::setTexture(1,m_stageZeroTexture);
 		W3DShaderManager::setTexture(2,m_stageTwoTexture);	//cloud
 		W3DShaderManager::setTexture(3,m_stageThreeTexture);//noise
		//Disable writes to destination alpha channel (if there is one)
		if (DX8Wrapper::getBackBufferFormat() == WW3D_FORMAT_A8R8G8B8)
			DX8Wrapper::Set_DX8_Render_State(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
	}

	Int pass;
 	for (pass=0; pass<devicePasses; pass++) {
#ifdef TIMING_TESTS
#endif
		if (!doMultiPassWireFrame)	//multi-pass wireframe doesn't use regular shaders.
		{
 			if (m_disableTextures ) {
 				DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaque2DShader);
 				DX8Wrapper::Set_Texture(0,NULL);
   			} else {
 				W3DShaderManager::setShader(st, pass);
			}
		}

		for (j=0; j<m_numVBTilesY; j++)
			for (i=0; i<m_numVBTilesX; i++)
			{
				static int count = 0;
				count++;
				Int numPolys = VERTEX_BUFFER_TILE_LENGTH*VERTEX_BUFFER_TILE_LENGTH*2;
				Int numVertex = (VERTEX_BUFFER_TILE_LENGTH*2)*(VERTEX_BUFFER_TILE_LENGTH*2);
				if (HALF_RES_MESH) {
					numPolys /= 4;
					numVertex /= 4;
				}
				DX8Wrapper::Set_Vertex_Buffer(m_vertexBufferTiles[j*m_numVBTilesX+i]);
#ifdef PRE_TRANSFORM_VERTEX
				if (m_xformedVertexBuffer && pass==0) {
					// Note - m_xformedVertexBuffer should only be used for non T&L hardware.  jba.
					DX8Wrapper::Apply_Render_State_Changes();
					int code = DX8Wrapper::_Get_D3D_Device8()->ProcessVertices(0, 0, numVertex, m_xformedVertexBuffer[j*m_numVBTilesX+i], 0); 
					::OutputDebugString("did process vertex\n");
				}
				if (m_xformedVertexBuffer) {
					// Note - m_xformedVertexBuffer should only be used for non T&L hardware.  jba.
					DX8Wrapper::Apply_Render_State_Changes();
					DX8Wrapper::_Get_D3D_Device8()->SetStreamSource(
						0,
						m_xformedVertexBuffer[j*m_numVBTilesX+i],
						D3DXGetFVFVertexSize(D3DFVF_XYZRHW |D3DFVF_DIFFUSE|D3DFVF_TEX2));
					DX8Wrapper::_Get_D3D_Device8()->SetVertexShader(D3DFVF_XYZRHW |D3DFVF_DIFFUSE|D3DFVF_TEX2);
				}
#endif				
				if (Is_Hidden() == 0) {
					DX8Wrapper::Draw_Triangles(	0,numPolys, 0,	numVertex);
				}

			}
	}		

	if (!doMultiPassWireFrame)
	{
		if (pass)	//shader was applied at least once?
 			W3DShaderManager::resetShader(st);

		//Draw feathered shorelines
		renderShoreLines(&rinfo.Camera);

		//Do additional pass over any tiles that have 3 textures blended together.
		if (TheGlobalData->m_use3WayTerrainBlends)
			renderExtraBlendTiles();

		Int yCoordMin = m_map->getDrawOrgY();
		Int yCoordMax = m_y+m_map->getDrawOrgY()-1;
		Int xCoordMin = m_map->getDrawOrgX();
		Int xCoordMax = m_x+m_map->getDrawOrgX()-1;	
	#ifdef TEST_CUSTOM_EDGING
		// Draw edging just before last pass.
		DX8Wrapper::Set_Texture(0,NULL);
		DX8Wrapper::Set_Texture(1,NULL);
		m_stageTwoTexture->restore();
		m_customEdging->drawEdging(m_map, xCoordMin, xCoordMax, yCoordMin, yCoordMax, 
			m_stageZeroTexture, doCloud?m_stageTwoTexture:NULL, TheGlobalData->m_useLightMap?m_stageThreeTexture:NULL);
	#endif
	#ifdef DO_ROADS
		DX8Wrapper::Set_Texture(0,NULL);
		DX8Wrapper::Set_Texture(1,NULL);
		m_stageTwoTexture->restore();

		ShaderClass::Invalidate();
		if (!ShaderClass::Is_Backface_Culling_Inverted()) {
			DX8Wrapper::Set_Material(m_vertexMaterialClass);
			if (Scene) {
				RTS3DScene *pMyScene = (RTS3DScene *)Scene;
				RefRenderObjListIterator pDynamicLightsIterator(pMyScene->getDynamicLights());
				m_roadBuffer->drawRoads(&rinfo.Camera, doCloud?m_stageTwoTexture:NULL, TheGlobalData->m_useLightMap?m_stageThreeTexture:NULL,
					m_disableTextures,xCoordMin-m_map->getBorderSizeInline(), xCoordMax-m_map->getBorderSizeInline(), yCoordMin-m_map->getBorderSizeInline(), yCoordMax-m_map->getBorderSizeInline(), &pDynamicLightsIterator);
			}
		}
	#endif
	if (m_propBuffer) {
		m_propBuffer->drawProps(rinfo);
	}
	#ifdef DO_SCORCH
		DX8Wrapper::Set_Texture(0,NULL);
		DX8Wrapper::Set_Texture(1,NULL);
		m_stageTwoTexture->restore();

		ShaderClass::Invalidate();
		if (!ShaderClass::Is_Backface_Culling_Inverted()) {
			drawScorches();
		}
	#endif
		DX8Wrapper::Set_Texture(0,NULL);
		DX8Wrapper::Set_Texture(1,NULL);
		m_stageTwoTexture->restore();
		ShaderClass::Invalidate();
		DX8Wrapper::Apply_Render_State_Changes();

		m_bridgeBuffer->drawBridges(&rinfo.Camera, m_disableTextures, doCloud?m_stageTwoTexture:NULL);

		if (TheTerrainTracksRenderObjClassSystem)
			TheTerrainTracksRenderObjClassSystem->flush();

		if (m_shroud && rinfo.Additional_Pass_Count())
		{
			rinfo.Peek_Additional_Pass(0)->Install_Materials();
			renderTerrainPass(&rinfo.Camera);
			rinfo.Peek_Additional_Pass(0)->UnInstall_Materials();
		}

		ShaderClass::Invalidate();
		DX8Wrapper::Apply_Render_State_Changes();
	}
	else
			m_bridgeBuffer->drawBridges(&rinfo.Camera, m_disableTextures, m_stageTwoTexture);

  if ( m_waypointBuffer ) 
	  m_waypointBuffer->drawWaypoints(rinfo);

	m_bibBuffer->renderBibs();

	// We do some custom blending, so tell the shader class to reset everything.
	DX8Wrapper::Set_Texture(0,NULL);
	DX8Wrapper::Set_Texture(1,NULL);
	m_stageTwoTexture->restore();
	ShaderClass::Invalidate();
	DX8Wrapper::Set_Material(NULL);

}


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
#pragma inline_depth()
#endif
