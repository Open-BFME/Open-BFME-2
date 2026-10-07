// cl: /Ireference/shims/zh_ascii_outofline /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBuffer.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
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

// FILE: W3DPropBuffer.cpp ////////////////////////////////////////////////
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
// File name: W3DPropBuffer.cpp
//
// Created:   John Ahlquist, May 2001
//
// Desc:      Draw buffer to handle all the props in a scene.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//         Includes                                                      
//-----------------------------------------------------------------------------
#include "W3DDevice/GameClient/W3DPropBuffer.h"

#include <stdio.h>
#include <string.h>
#include <assetmgr.h>
#include "Common/Geometry.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "WW3D2/Camera.h"
#include "WW3D2/RInfo.h"
#include "WW3D2/Light.h"
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/dx8renderer.h"
#include "W3DDevice/GameClient/Module/W3DPropDraw.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "W3DDevice/GameClient/BaseHeightMap.h"
#include "GameLogic/PartitionManager.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif




//-----------------------------------------------------------------------------
//         Private Functions                                               
//-----------------------------------------------------------------------------

//=============================================================================
// W3DPropBuffer::cull
//=============================================================================
/** Culls the props, marking the visible flag.  If a prop becomes visible, it sets
it's sortKey */
//=============================================================================
// ?cull@W3DPropBuffer@@ present-unmatched
void W3DPropBuffer::cull(CameraClass * camera)
{
	Int curProp;

	for (curProp=0; curProp<m_numProps; curProp++) {
		Bool visible = !camera->Cull_Sphere(m_props[curProp].bounds);
		m_props[curProp].visible=visible;
	}
}



//-----------------------------------------------------------------------------
//         Public Functions                                                
//-----------------------------------------------------------------------------

//=============================================================================
// W3DPropBuffer::~W3DPropBuffer
//=============================================================================
/** Destructor. Releases w3d assets. */
//=============================================================================
// ??1W3DPropBuffer@@ present-unmatched
W3DPropBuffer::~W3DPropBuffer(void)
{
	Int i;
	for (i=0; i<MAX_TYPES; i++) {
		REF_PTR_RELEASE(m_propTypes[i].m_robj);
	}
	REF_PTR_RELEASE(m_light);
	REF_PTR_RELEASE(m_propShroudMaterialPass);
}

//=============================================================================
// W3DPropBuffer::W3DPropBuffer
//=============================================================================
/** Constructor. Sets m_initialized to true if it finds the w3d models it needs
for the props. */
//=============================================================================
// ??0W3DPropBuffer@@ present-unmatched
W3DPropBuffer::W3DPropBuffer(void)
{
	memset(this, sizeof(W3DPropBuffer), 0);
	m_initialized = false;
	clearAllProps();
	m_light = NEW_REF( LightClass, (LightClass::DIRECTIONAL) );
	m_propShroudMaterialPass = NEW_REF(W3DShroudMaterialPassClass,());
	m_initialized = true;
}





//=============================================================================
// W3DPropBuffer::clearAllProps
//=============================================================================
/** Removes all props. */
//=============================================================================
// ?clearAllProps@W3DPropBuffer@@ present-unmatched
void W3DPropBuffer::clearAllProps(void)
{
	m_numProps=0;
	Int i;
	for (i=0; i<MAX_TYPES; i++) {
		REF_PTR_RELEASE(m_propTypes[i].m_robj);
		m_propTypes[i].m_robjName.clear();
	}
	m_numPropTypes = 0;
}

//=============================================================================
// W3DPropBuffer::addPropTypes
//=============================================================================
/** Adds a type of prop (model & texture). */
//=============================================================================
// ?addPropType@W3DPropBuffer@@ present-unmatched
Int W3DPropBuffer::addPropType(const AsciiString &modelName)
{
	if (m_numPropTypes>=MAX_TYPES) {
		DEBUG_CRASH(("Too many kinds of props in map.  Reduce kinds of props, or raise prop limit. jba.")); 
		return 0;
	}

	m_propTypes[m_numPropTypes].m_robj = WW3DAssetManager::Get_Instance()->Create_Render_Obj(modelName.str());
	if (m_propTypes[m_numPropTypes].m_robj==NULL) {
		DEBUG_CRASH(("Unable to find model for prop %s\n", modelName.str()));
		return -1;
	}
	m_propTypes[m_numPropTypes].m_robjName = modelName;
	
	SphereClass bounds = m_propTypes[m_numPropTypes].m_robj->Get_Bounding_Sphere();
	m_propTypes[m_numPropTypes].m_bounds = bounds;
	m_numPropTypes++;
	return m_numPropTypes-1;
}

//=============================================================================
// W3DPropBuffer::addProp
//=============================================================================
/** Adds a prop.  Name is the W3D model name, supported models are
ALPINE, DECIDUOUS and SHRUB. */
//=============================================================================
// ?addProp@W3DPropBuffer@@ present-unmatched
void W3DPropBuffer::addProp(Int id, Coord3D location, Real angle,Real scale, const AsciiString &modelName)
{
	if (m_numProps >= MAX_PROPS) {
		return;  
	}
	if (!m_initialized) {
		return;  
	}
	Int propType = -1;
	Int i;
	for (i=0; i<m_numPropTypes; i++) {
		if (m_propTypes[i].m_robjName.compareNoCase(modelName)==0) {
			propType = i;
			break;
		}
	}
	if (propType<0) {
		propType = addPropType(modelName);
		if (propType<0) {
			return;
		}
	}

	Matrix3D mtx(true);
	mtx.Rotate_Z(angle);
	mtx.Scale(scale);
	mtx.Set_Translation(Vector3(location.x, location.y, location.z));

	m_props[m_numProps].location = location;
	m_props[m_numProps].id = id;
	m_props[m_numProps].ss = OBJECTSHROUD_INVALID;
	m_props[m_numProps].m_robj = m_propTypes[propType].m_robj->Clone();
	m_props[m_numProps].m_robj->Set_Transform(mtx);
	m_props[m_numProps].m_robj->Set_ObjectScale(scale);
	m_props[m_numProps].propType = propType;
	// Translate the bounding sphere of the model.
	m_props[m_numProps].bounds = m_propTypes[propType].m_bounds;
	m_props[m_numProps].bounds.Center += Vector3(location.x, location.y, location.z);
	// Initially set it invisible.  cull will update it's visiblity flag.
	m_props[m_numProps].visible = false;

	m_numProps++;
}

//=============================================================================
// W3DPropBuffer::updatePropPosition
//=============================================================================
/** Updates a prop's position */
//=============================================================================
// ?updatePropPosition@W3DPropBuffer@@ present-unmatched
Bool W3DPropBuffer::updatePropPosition(Int id, const Coord3D &location, Real angle, Real scale)
{
	Int i;
	for (i=0; i<m_numProps; i++) {
		if (m_props[i].id == id) {
			Matrix3D mtx(true);
			mtx.Rotate_Z(angle);
			mtx.Scale(scale);
			mtx.Set_Translation(Vector3(location.x, location.y, location.z));
			m_props[i].location = location;
			m_props[i].m_robj->Set_Transform(mtx);
			m_props[i].m_robj->Set_ObjectScale(scale);
			// Translate the bounding sphere of the model.
			m_props[i].bounds = m_propTypes[m_props[i].propType].m_bounds;
			m_props[i].bounds.Center += Vector3(location.x, location.y, location.z);
			m_anythingChanged = true;
			return true;
		}
	}
	return false;
}

//=============================================================================
// W3DPropBuffer::removeProp
//=============================================================================
/** Removes a prop.  */
//=============================================================================
// W3DPropBuffer::removeProp is defined with its retail-matched body in Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferRemoveProp.cpp (0x000EDFCE).

//=============================================================================
// W3DPropBuffer::removePropsForConstruction
//=============================================================================
/** Removes any props that would be under a building.  */
//=============================================================================
// W3DPropBuffer::removePropsForConstruction is defined with its retail-matched body in Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferRemovePropsForConstruction.cpp (0x000EF154).



//=============================================================================
// W3DPropBuffer::notifyShroudChanged
//=============================================================================
/** Sets the shroud to status, so it is recomputed.  */
//=============================================================================
// Retail reads the manager slot at 0xDFE74C here. TerrainLogic's target body
// calls TheShroudManager through that same slot; ThePartitionManager is at
// 0xDFE748.
extern PartitionManager *TheShroudManager;

#pragma optimize("s", on)
void W3DPropBuffer::notifyShroudChanged()
{
	Int i;
	for (i=0; i<m_numProps; i++) {
		m_props[i].ss = TheShroudManager?OBJECTSHROUD_INVALID:OBJECTSHROUD_CLEAR;
	}
}
#pragma optimize("", on)


DECLARE_PERF_TIMER(Prop_Render)

//=============================================================================
// W3DPropBuffer::drawProps
//=============================================================================
/** Draws the props.  Uses camera to cull. */
//=============================================================================
// ?drawProps@W3DPropBuffer@@ present-unmatched
void W3DPropBuffer::drawProps(RenderInfoClass &rinfo)
{
	USE_PERF_TIMER(Prop_Render)

	Int i;
	if (m_doCull) {
		cull(&rinfo.Camera);
	}
	const GlobalData::TerrainLighting *objectLighting = TheGlobalData->m_terrainObjectsLighting[TheGlobalData->m_timeOfDay];

	LightEnvironmentClass lightEnv;
	Vector3 center(0,0,0); // arbitrary center point. [6/6/2003]
	Vector3 ambient(objectLighting[0].ambient.red, objectLighting[0].ambient.green, objectLighting[0].ambient.blue);
	lightEnv.Reset(center, ambient);

	Matrix3D mtx;
	const Vector3 zeroVector(0.0f, 0.0f, 0.0f);
	const Vector3 xVector(1.0f, 0.0f, 0.0f);
	const Vector3 yVector(0.0f, 1.0f, 0.0f);

	for (i = 0; i < MAX_GLOBAL_LIGHTS; ++i)
	{
			m_light->Set_Ambient(zeroVector);
			m_light->Set_Diffuse(Vector3(objectLighting[i].diffuse.red,
																		 objectLighting[i].diffuse.green,
																		 objectLighting[i].diffuse.blue));
			m_light->Set_Specular(zeroVector);
			mtx.Set(xVector, yVector, Vector3(objectLighting[i].lightPos.x, objectLighting[i].lightPos.y, objectLighting[i].lightPos.z), zeroVector);
			m_light->Set_Transform(mtx);
			lightEnv.Add_Light(*m_light);
	}
	
	rinfo.light_environment = &lightEnv;
	for	(i=0; i<m_numProps; i++) {
		if (!m_props[i].visible) {
			continue;
		}
		if (m_props[i].m_robj==NULL) {
			continue;
		}
		if (!ThePlayerList || !ThePartitionManager) {
			//  in Worldbuilder. No shroud either. jba. [6/9/2003]
			m_props[i].ss = OBJECTSHROUD_CLEAR;
		}
		if (m_props[i].ss == OBJECTSHROUD_INVALID) {
			Int localPlayerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;
			m_props[i].ss = ThePartitionManager->getPropShroudStatusForPlayer(localPlayerIndex, &m_props[i].location);
		}
		if (m_props[i].ss >= OBJECTSHROUD_SHROUDED) {
			continue;
		}
		if (m_props[i].ss <= OBJECTSHROUD_INVALID) {
			continue;
		}
		if (TheTerrainRenderObject->getShroud() && m_props[i].ss != CELLSHROUD_CLEAR) {
			rinfo.Push_Material_Pass(m_propShroudMaterialPass);
			m_props[i].m_robj->Render(rinfo);
			rinfo.Pop_Material_Pass();
		} else {
			m_props[i].m_robj->Render(rinfo);
		}
	}
	rinfo.light_environment = NULL;

}


// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@W3DPropBuffer@@ present-unmatched
void W3DPropBuffer::crc( Xfer *xfer )
{
	// empty. jba [8/11/2003]	
}  // end CRC

// ------------------------------------------------------------------------------------------------
/** Xfer
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@W3DPropBuffer@@ present-unmatched
void W3DPropBuffer::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );


}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@W3DPropBuffer@@ present-unmatched
void W3DPropBuffer::loadPostProcess( void )
{
	// empty. jba [8/11/2003]	
}  // end loadPostProcess


// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?crc@GeometryInfo@@MAEXPAVXfer@@@Z=??_GRva0050B2A@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?xfer@GeometryInfo@@MAEXPAVXfer@@@Z=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?loadPostProcess@GeometryInfo@@MAEXXZ=?name@Rva00050C2BNamed@@QBEPBDXZ")
