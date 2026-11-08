// cl: /D_OPERATOR_NEW_DEFINED_ /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
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

// BaseHeightMapRenderObjClass::addProp, ported from Zero Hour's
// GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference). BFME 2 keeps
// the prop buffer at +0x3858 and passes one more flag through to
// W3DPropBuffer::addProp (the caller W3DPropDraw::reactToTransformChange
// reads it from its module data). Coord3D has a user-declared copy
// constructor and destructor in BFME 2.

typedef int Int;
typedef bool Bool;
typedef float Real;

// The canonical header first: its WWMath sphere.h and vector3.h serve the
// prop buffer header (Code's SphereClass.h shares the SPHERE_H guard).
#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"
#define REFCOUNT_H
#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_DTOR
#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"

#include "ascii_string.h"

class GeometryInfo;
#include "../../../Include/W3DDevice/GameClient/W3DPropBufferClass.h"

#include "../../../../GameEngine/Include/Common/DataChunkOutput.h"


//-----------------------------------------------------------------------------
// BaseHeightMapRenderObjClass::addProp
//-----------------------------------------------------------------------------
/** Adds a prop to the prop buffer.  jba */
void BaseHeightMapRenderObjClass::addProp(Int id, Coord3D location, Real angle, Real scale, 
																					const AsciiString &modelName, Bool distanceFog)
{
	if (m_propBuffer) {
		m_propBuffer->addProp(id, location, angle, scale, modelName, distanceFog);
	}
}

// 0x000683AC (48B), unreferenced in retail: the same null-checked forward
// for the rowed W3DPropBuffer::updatePropPosition (0x000EE203), with the
// location taken by value like addProp's and false without a buffer. The
// member name is address-derived (no caller names it).
Bool BaseHeightMapRenderObjClass::rva000683AC(Int id, Coord3D location, Real angle, Real scale)
{
	if (m_propBuffer) {
		return m_propBuffer->updatePropPosition(id, location, angle, scale);
	}
	return false;
}

// 0x00068494 (114B), unreferenced in retail: writes an "EnvironmentData"
// chunk (version 3) through the rowed DataChunkOutput writers: the two reals
// at +0x37E4 and +0x37E8, the flag at +0x3834, then the strings at +0x382C
// and +0x3820. Field meanings and the member name are not recovered.
void BaseHeightMapRenderObjClass::writeEnvironmentData(DataChunkOutput *chunk)
{
	chunk->openDataChunk("EnvironmentData", 3);
	chunk->writeReal(field37E4);
	chunk->writeReal(field37E8);
	chunk->writeByte(field3834 != 0);
	chunk->writeAsciiString(field382C);
	chunk->writeAsciiString(field3820);
	chunk->closeDataChunk();
}
