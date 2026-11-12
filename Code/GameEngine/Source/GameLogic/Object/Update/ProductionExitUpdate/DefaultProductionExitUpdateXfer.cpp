// cl: /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

// DefaultProductionExitUpdate::xfer, ported from Zero Hour's GameEngine/Source/
// GameLogic/Object/Update/ProductionExitUpdate/DefaultProductionExitUpdate.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference):
// slot 3 of the vftable whose slot-2 name getter returns
// DefaultProductionExitUpdate. The identical body serves
// SupplyCenterProductionExitUpdate. BFME 2 runs UpdateModule's xfer and the
// light-CRC early-out before the version, then ZH's rally point (+0x24) and
// rally-point flag (+0x30).
//
// exitObjectViaDoor (retail 0x00488099, 463 B) is ZH's body under BFME 2
// layouts: interface vftable 0x0084B1B0 slot 2 (this = ExitInterface at +0x20,
// module data at this-0x1C, object at this-0x18); Object's AI at +0x258 and
// out-of-line layer getter/setter 0x0028B511/0x0028B4CE; TerrainLogic
// getLayerHeight in slot 7; pathfinder at TheAI+0x10; isDoingGroundMovement in
// AI slot 137 and the locomotor set at +0x1CC. Retail block-copies the
// transformed point into createPoint and reuses its frame slot for the exit
// path, which the two inner scopes reproduce.

#include "../../../../../../Libraries/Include/Lib/Coord3DBase.h"
#include "../../../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
#include "../../../../Common/Thing/thing.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../../../Include/Common/BfmeXfer.h"

#include "../../../../../Include/Common/XferVersion.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

// Call the canonical 12-byte allocator and keep only the inline proxy forwarding.
namespace _STL {
template <> Coord3D * allocator<Coord3D>::allocate(size_t, const void *) const;
template <> __declspec(dllimport) __forceinline
Coord3D * _STLP_alloc_proxy<Coord3D*,Coord3D,allocator<Coord3D> >::allocate(size_t count) {
 return __stl_alloc_rebind(static_cast<allocator<Coord3D>&>(*this),(Coord3D*)0).allocate(count,0);
}
}


// Declaration-only _Construct: retail's push_back calls the pinned out-of-line
// helper (0x002CA82C) instead of inlining the element copy (row 35 family-LK3).
namespace _STL {
template <> void _Construct<Coord3D, Coord3D>(Coord3D *, const Coord3D &);
}

class Object;
class ThingTemplate;
class LocomotorSet;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

enum ExitDoorType
{
	DOOR_1 = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};

#include "../../../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

// Preserve this unit's alias-safe transform using canonical Matrix3D storage.
struct DefaultExitTransform
{
	static __forceinline void Transform_Vector(const Matrix3D &matrix3D, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		const Vector3 *v;
		if (out == &in) {
			tmp = in;
			v = &tmp;
		} else {
			v = &in;
		}
		out->X = (matrix3D.Row[0].X * v->X + matrix3D.Row[0].Y * v->Y + matrix3D.Row[0].Z * v->Z + matrix3D.Row[0].W);
		out->Y = (matrix3D.Row[1].X * v->X + matrix3D.Row[1].Y * v->Y + matrix3D.Row[1].Z * v->Z + matrix3D.Row[1].W);
		out->Z = (matrix3D.Row[2].X * v->X + matrix3D.Row[2].Y * v->Y + matrix3D.Row[2].Z * v->Z + matrix3D.Row[2].W);
	}
};

// The rowed wrapper at 0x0047971C takes the exit path by reference; its
// placeholder class is this vector of points.
class Rva0035149F : public _STL::vector<Coord3D>
{
};

#include "../../../../../Include/GameLogic/Module/AIUpdate.h"

class Object : public Thing
{
public:
	__declspec(dllimport) __forceinline PathfindLayerEnum getLayer() const { return (PathfindLayerEnum)rva0028B511(); }
	__declspec(dllimport) AIUpdateInterface *getAIUpdateInterface() { return m_ai; }

	Int rva0028B511() const;
	void setLayer(PathfindLayerEnum layer);

private:
	char m_unrecovered60[0x258 - 0x60];
	AIUpdateInterface *m_ai;																									///< 0x258
};

#include "../../../../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;

#include "../../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../../Include/GameLogic/AI.h"

#include "../../../../../Include/Common/ModuleData.h"

class DefaultProductionExitUpdateModuleData : public ModuleData
{
public:
	Coord3D m_unitCreatePoint;																								///< 0x08
	Coord3D m_naturalRallyPoint;																							///< 0x14
};

#include "../../../../../Include/GameLogic/Module/UpdateModule.h"

#include "../../../../../Include/GameLogic/Module/ExitInterface.h"

class DefaultProductionExitUpdate : public UpdateModule, public ExitInterface
{
public:
	virtual void exitObjectViaDoor( Object *newObj, ExitDoorType exitDoor );
protected:
	virtual void xfer( Xfer *xfer );
	const DefaultProductionExitUpdateModuleData *getDefaultProductionExitUpdateModuleData() const
	{
		return (const DefaultProductionExitUpdateModuleData *)getModuleData();
	}
private:
	Coord3D m_rallyPoint;																											///< 0x24
	Bool m_rallyPointExists;																									///< 0x30
};

//-------------------------------------------------------------------------------------------------
void DefaultProductionExitUpdate::exitObjectViaDoor( Object *newObj, ExitDoorType exitDoor )
{
	Object *creationObject = getObject();
	if (creationObject)
	{
		const DefaultProductionExitUpdateModuleData* md = getDefaultProductionExitUpdateModuleData();

		Real exitAngle = creationObject->getOrientation();
		Coord3D createPoint;
		{
			const Matrix3D *transform = creationObject->getTransformMatrix();
			Vector3 loc;

			//
			// calculate the position to create the object at, we take the coord specified
			// in INI which is in model space, rotate it to match the building angle
			// and translate for building location via a transform call
			//
			loc.Set( md->m_unitCreatePoint.x, md->m_unitCreatePoint.y, md->m_unitCreatePoint.z );
			DefaultExitTransform::Transform_Vector( *transform, loc, &loc );

			// make sure the point is on the terrain
			loc.Z = TheTerrainLogic ? TheTerrainLogic->getLayerHeight( loc.X, loc.Y, creationObject->getLayer() ) : 0.0f;

			// we need it in Coord3D form
			createPoint = *(const Coord3D *)&loc;
		}

		newObj->setPosition( &createPoint );
		newObj->setOrientation( exitAngle );
		newObj->setLayer( creationObject->getLayer() );

		// tell the AI about it
		TheAI->pathfinder()->AddObjectToPathfindMap( newObj );
		{
			Coord3D tmp;
			getNaturalRallyPoint(tmp);
			Rva0035149F exitPath;
			exitPath.push_back(tmp);

			AIUpdateInterface *ai = newObj->getAIUpdateInterface();
			if (m_rallyPointExists)
			{
				tmp = m_rallyPoint;
				if (ai && ai->isDoingGroundMovement())
				{
					if (TheAI->pathfinder()->AdjustDestination(newObj, ai->getLocomotorSet(), &tmp))
						exitPath.push_back(tmp);
				}
			}
			if (ai) {
				ai->rva0047971C( exitPath, creationObject, CMD_FROM_AI );
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void DefaultProductionExitUpdate::xfer( Xfer *xfer )
{

	// extend base class
	UpdateModule::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// rally point
	// Coord3DBase is the canonical Xfer operand for this same 12-byte triple.
	*xfer == *reinterpret_cast<Coord3DBase *>(&m_rallyPoint);

	// rally point exists
	*xfer == m_rallyPointExists;

}  // end xfer
