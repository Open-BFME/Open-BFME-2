// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
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

struct Coord3D
{
	Real x;
	Real y;
	Real z;
	Coord3D( const Coord3D &c ) { x = c.x; y = c.y; z = c.z; }
	~Coord3D() {}
};

#include "ascii_string.h"

class W3DPropBuffer
{
public:
	void addProp( Int id, Coord3D location, Real angle, Real scale, const AsciiString &modelName, Bool bfmeFlag );
};

class BaseHeightMapRenderObjClass
{
public:
	void addProp( Int id, Coord3D location, Real angle, Real scale, const AsciiString &modelName, Bool bfmeFlag );
private:
	char m_unrecovered0000[ 0x3858 ];
	W3DPropBuffer *m_propBuffer;																							///< 0x3858
};

//-----------------------------------------------------------------------------
// BaseHeightMapRenderObjClass::addProp
//-----------------------------------------------------------------------------
/** Adds a prop to the prop buffer.  jba */
void BaseHeightMapRenderObjClass::addProp(Int id, Coord3D location, Real angle, Real scale, 
																					const AsciiString &modelName, Bool bfmeFlag)
{
	if (m_propBuffer) {
		m_propBuffer->addProp(id, location, angle, scale, modelName, bfmeFlag);
	}
}
