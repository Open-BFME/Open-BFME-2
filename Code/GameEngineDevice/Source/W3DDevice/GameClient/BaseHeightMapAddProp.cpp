// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
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

// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_DTOR
#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"

#include "ascii_string.h"

class GeometryInfo;
#include "../../../Include/W3DDevice/GameClient/W3DPropBufferClass.h"

#include "../../../../GameEngine/Include/Common/DataChunkOutput.h"

class BaseHeightMapRenderObjClass
{
public:
	void addProp( Int id, Coord3D location, Real angle, Real scale, const AsciiString &modelName, Bool distanceFog );
	Bool rva000683AC( Int id, Coord3D location, Real angle, Real scale );
	void writeEnvironmentData( DataChunkOutput *chunk );
private:
	char m_unrecovered0000[ 0x37e4 ];
	Real m_37e4;																							///< 0x37e4
	Real m_37e8;																							///< 0x37e8
	char m_unrecovered37ec[ 0x3820 - 0x37ec ];
	AsciiString m_3820;																						///< 0x3820
	char m_unrecovered3824[ 0x382c - 0x3824 ];
	AsciiString m_382c;																						///< 0x382c
	char m_unrecovered3830[ 0x3834 - 0x3830 ];
	Bool m_3834;																							///< 0x3834
	char m_unrecovered3835[ 0x3858 - 0x3835 ];
	W3DPropBuffer *m_propBuffer;																							///< 0x3858
};

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
	chunk->writeReal(m_37e4);
	chunk->writeReal(m_37e8);
	chunk->writeByte(m_3834 != 0);
	chunk->writeAsciiString(m_382c);
	chunk->writeAsciiString(m_3820);
	chunk->closeDataChunk();
}
