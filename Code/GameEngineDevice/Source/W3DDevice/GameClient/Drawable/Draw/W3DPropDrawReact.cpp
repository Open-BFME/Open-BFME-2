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

// W3DPropDraw::reactToTransformChange, ported from Zero Hour's
// GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DPropDraw.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference)
// onto the BFME 2 layout: module data +0x04, drawable +0x08, m_propAdded
// +0x0C (constructor 0x000CEEC0). W3DPropDrawModuleData keeps the model name
// at +0x08 and adds a flag at +0x0C, which BFME 2's
// BaseHeightMapRenderObjClass::addProp takes as an extra last argument.
// Coord3D has a user-declared (empty) destructor in BFME 2, which is what
// gives this body its unwind frame around the by-value location argument.

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

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

class Drawable
{
public:
	const Coord3D *getPosition( void ) const;
	Real getOrientation( void ) const { return m_cachedAngle; }
	const Real getScale( void ) const;
	DrawableID getID( void ) const;
private:
	char m_unrecovered00[ 0x44 ];
	Real m_cachedAngle;																												///< 0x44
};

class BaseHeightMapRenderObjClass
{
public:
	void addProp( Int id, Coord3D location, Real angle, Real scale, const AsciiString &modelName, Bool bfmeFlag );
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class W3DPropDrawModuleData
{
public:
	char m_unrecovered00[ 0x08 ];
	AsciiString m_modelName;																									///< 0x08
	Bool m_bfmeFlag;																													///< 0x0C
};

class Matrix3D;

class W3DPropDraw
{
public:
	virtual void reactToTransformChange( const Matrix3D *oldMtx, const Coord3D *oldPos, Real oldAngle );
protected:
	Drawable *getDrawable( void ) const { return m_drawable; }
	const W3DPropDrawModuleData *getW3DPropDrawModuleData( void ) const { return m_moduleData; }
private:
	const W3DPropDrawModuleData *m_moduleData;																///< 0x04
	Drawable *m_drawable;																											///< 0x08
	Bool m_propAdded;																													///< 0x0C
};

void W3DPropDraw::reactToTransformChange( const Matrix3D *oldMtx,
																							 const Coord3D *oldPos,
																							 Real oldAngle )
{
	Drawable *draw = getDrawable();
	if (m_propAdded) {
		return;
	}
	if (draw->getPosition()->x==0.0f && draw->getPosition()->y == 0.0f) {
		return;
	}
	m_propAdded = true;
	const W3DPropDrawModuleData *moduleData = getW3DPropDrawModuleData();
	if (!moduleData) {
		return;
	}
	Real scale = draw->getScale();
	TheTerrainRenderObject->addProp((Int)draw->getID(), *draw->getPosition(),
		draw->getOrientation(), scale, moduleData->m_modelName, moduleData->m_bfmeFlag);

}
