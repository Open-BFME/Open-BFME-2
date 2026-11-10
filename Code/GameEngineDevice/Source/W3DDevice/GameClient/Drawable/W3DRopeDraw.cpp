// cl: /DBFME_SNAPSHOT_NAME_SLOT /Ireference/shims/update_modules_bfme2 /Ireference/shims/moduledata /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /arch:SSE /DNDEBUG /MD /EHsc /DBFME_MODULE_NO_MPO /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
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

// FILE: W3DRopeDraw.cpp ////////////////////////////////////////////////////////////////////////
// Author: Steven Johnson, Aug 2002
// Desc:   Rope drawing
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <windows.h>
#include "Common/Thing.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameClient/ClientRandomValue.h"
#include "GameClient/Color.h"
// Retail doDrawModule calls the out-of-line Drawable::getPosition 0x002763E6
// (BFMERopeDrawableGetPosition.cpp), not ZH's inline Thing accessor.
#define _DRAWABLE_H_
class Drawable
{
public:
	const Coord3D *getPosition() const;
};
// GameClient.h needs ZH's full Drawable; nothing here uses it.
#include "GameLogic/GameLogic.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/Module/W3DRopeDraw.h"
#include "WW3D2/Line3D.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "Common/GameState.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// The exact retail constructor is emitted by W3DRopeDrawCtor.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Retail buildSegments is defined in Draw/W3DRopeDraw.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/W3DRopeDrawDestructorThunk.cpp
// W3DRopeDraw::tossSegments: defined in W3DRopeDrawTossSegments.cpp (its row's unit).


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// W3DRopeDraw::initRopeParms: defined in W3DRopeDrawInitRopeParms.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void W3DRopeDraw::setRopeCurLen(Real length)
{ 
	m_curLen = length; 
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void W3DRopeDraw::setRopeSpeed(Real curSpeed, Real maxSpeed, Real accel)
{ 
	m_curSpeed = curSpeed; 
	m_maxSpeed = maxSpeed; 
	m_accel = accel;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// W3DRopeDraw's destructor: retail's public virtual body is defined in
// W3DRopeDrawDtor.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#pragma optimize("s", on)
void W3DRopeDraw::doDrawModule(const Matrix3D* transformMtx)
{
	// Retain the rowed SegInfo copy worker without the obsolete donor body.
	// Member scope permits the private nested type; automatic storage emits no guard.
	typedef void (__cdecl *ConstructSeg)(SegInfo *, const SegInfo &);
	ConstructSeg const emitSegCopy = &_STL::_Construct<SegInfo, SegInfo>;
	(void)emitSegCopy;

	if (m_segments.empty())
	{
		buildSegments();
	}

	if (!m_segments.empty())
	{
		Real deflection = Sin(m_curWobblePhase) * m_wobbleAmp;
		const Coord3D* pos = getDrawable()->getPosition();
		Vector3 start(pos->x, pos->y, pos->z + m_curZOffset);
		Real eachLen = m_curLen / m_segments.size();
		for (std::vector<SegInfo>::iterator it = m_segments.begin(); it != m_segments.end(); ++it)
		{
			Vector3 end(pos->x + deflection*it->wobbleAxisX, pos->y + deflection*it->wobbleAxisY, start.Z - eachLen);
			if (it->line)
				(it->line)->Reset(start, end);
			if (it->softLine)
				(it->softLine)->Reset(start, end);
			start = end;
		}
	}

	m_curWobblePhase += m_wobbleRate;
	if (m_curWobblePhase > 2*PI)
		m_curWobblePhase -= 2*PI;

	m_curZOffset += m_curSpeed;
	m_curSpeed += m_accel;
	if (m_curSpeed > m_maxSpeed)
		m_curSpeed = m_maxSpeed;
	else if (m_curSpeed < -m_maxSpeed)
		m_curSpeed = -m_maxSpeed;
}
#pragma optimize("", on)

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// The Snapshot name slot follows the BFME 2 module contract.

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/W3DRopeDrawDestructorThunk.cpp
// W3DRopeDraw::xfer: defined in W3DRopeDrawXfer.cpp (its row's unit).
  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@W3DRopeDraw@@MAEXXZ present-unmatched
void W3DRopeDraw::loadPostProcess( void )
{

	// extend base class
	DrawModule::loadPostProcess();

}  // end loadPostProcess
