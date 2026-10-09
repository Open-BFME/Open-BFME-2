// cl: /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// Ported from Open-BFME-1's game/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBuffer.cpp
// (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db) with /O1 /arch:SSE
// added to its flags, the settings W3DView.cpp's donor bodies match under.
// Searched by masked whole-.text search, the body places once on unclaimed
// game.dat .text at 0x000EDFCE (124B). Only W3DPropBuffer::removeProp is carried:
// W3DPropBuffer.cpp keeps the unit's other bodies at its own settings, where
// this one compiles 9 bytes longer (133B).
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
#include "../../../../../reference/shims/bfme_vector3_ctor_link/vector3.h"
#include "W3DDevice/GameClient/W3DPropBuffer.h"
#include "string_base.h"

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

RenderObjClass *Create_Render_Obj(const char *name);

class PropNameString
{
public:
	const char *str( void ) const
	{
		return m_data ? (const char *)m_data + 8 : "";
	}

	void *m_data;
};

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




//-----------------------------------------------------------------------------
//         Public Functions                                                
//-----------------------------------------------------------------------------

//=============================================================================
// W3DPropBuffer::~W3DPropBuffer
//=============================================================================
/** Destructor. Releases w3d assets. */
//=============================================================================
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferDestructor.cpp
// ??1W3DPropBuffer@@QAE@XZ present-unmatched


//=============================================================================
// W3DPropBuffer::W3DPropBuffer
//=============================================================================
/** Constructor. Sets m_initialized to true if it finds the w3d models it needs
for the props. */
//=============================================================================
// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferDestructor.cpp






//=============================================================================
// W3DPropBuffer::clearAllProps
//=============================================================================
/** Removes all props. */
//=============================================================================


//=============================================================================
// W3DPropBuffer::addPropTypes
//=============================================================================
/** Adds a type of prop (model & texture). */
//=============================================================================


//=============================================================================
// W3DPropBuffer::addProp
//=============================================================================
/** Adds a prop.  Name is the W3D model name, supported models are
ALPINE, DECIDUOUS and SHRUB. */
//=============================================================================


//=============================================================================
// W3DPropBuffer::updatePropPosition
//=============================================================================
/** Updates a prop's position */
//=============================================================================


//=============================================================================
// W3DPropBuffer::removeProp
//=============================================================================
/** Removes a prop.  */
//=============================================================================
void W3DPropBuffer::removeProp(Int id)
{
	Int i;
	for (i=0; i<m_numProps; i++) {
		if (m_props[i].id == id) {
			m_props[i].location.set(0,0,0);
			m_props[i].propType = -1;
			if (m_props[i].m_robj) {
				m_props[i].m_robj->Release_Ref();
				m_props[i].m_robj = NULL;
			}
			// Translate the bounding sphere of the model.
			m_props[i].bounds.Center = Vector3(0,0,0);
			m_props[i].bounds.Radius = 1;
			m_anythingChanged = true;
		}
	}
}

//=============================================================================
// W3DPropBuffer::removePropsForConstruction
//=============================================================================
/** Removes any props that would be under a building.  */
//=============================================================================
// ?removePropsForConstruction@W3DPropBuffer@@QAEXPBUCoord3D@@ABVGeometryInfo@@M@Z present-unmatched




//=============================================================================
// W3DPropBuffer::notifyShroudChanged
//=============================================================================
/** Sets the shroud to status, so it is recomputed.  */
//=============================================================================
// The shroud subsystem is a SEPARATE global from the partition manager in BFME:
// the engine-init tag block at 0x0038A1F0 stores 0x012ED5BC and then pushes the
// tag "TheShroudManager", while ThePartitionManager is constructed just before it
// at 0x012ED5B8.  Every shroud entry point in this tree reaches the former.
extern PartitionManager *TheShroudManager;				///< retail 0x012ED5BC





//=============================================================================
// W3DPropBuffer::drawProps
//=============================================================================
/** Draws the props.  Uses camera to cull. */
//=============================================================================
// ?drawProps@W3DPropBuffer@@QAEXAAVRenderInfoClass@@@Z present-unmatched



// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@W3DPropBuffer@@MAEXPAVXfer@@@Z present-unmatched
  // end CRC

// ------------------------------------------------------------------------------------------------
/** Xfer
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@W3DPropBuffer@@MAEXPAVXfer@@@Z present-unmatched
  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
  // end loadPostProcess
