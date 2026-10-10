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

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3D &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include <vector>

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

struct Vector3
{
	Real X;
	Real Y;
	Real Z;

	Vector3() {}
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	void Set(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
};

class Matrix3D
{
public:
	static __forceinline void Transform_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp;
		const Vector3 *v;
		if (out == &in) {
			tmp = in;
			v = &tmp;
		} else {
			v = &in;
		}
		out->X = (A.Row[0][0] * v->X + A.Row[0][1] * v->Y + A.Row[0][2] * v->Z + A.Row[0][3]);
		out->Y = (A.Row[1][0] * v->X + A.Row[1][1] * v->Y + A.Row[1][2] * v->Z + A.Row[1][3]);
		out->Z = (A.Row[2][0] * v->X + A.Row[2][1] * v->Y + A.Row[2][2] * v->Z + A.Row[2][3]);
	}

	Real Row[3][4];
};

class Thing
{
public:
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	Real getOrientation() const { return m_cachedAngle; }
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);

private:
	char m_unrecovered00[0x08];
	Matrix3D m_transform;																											///< 0x08
	Coord3D m_cachedPos;																											///< 0x38
	Real m_cachedAngle;																												///< 0x44
};

#define VM10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class AIUpdateInterfaceBase
{
public:
	VM10(v0_)
	VM10(v1_)
	VM10(v2_)
	VM10(v3_)
	VM10(v4_)
	VM10(v5_)
	VM10(v6_)
	VM10(v7_)
	VM10(v8_)
	VM10(v9_)
	VM10(v10_)
	VM10(v11_)
	VM10(v12_)
	virtual void v130();
	virtual void v131();
	virtual void v132();
	virtual void v133();
	virtual void v134();
	virtual void v135();
	virtual void v136();
	virtual Bool isDoingGroundMovement() const;			// slot 137 -> offset 0x224
private:
	char m_unrecovered04[0x20 - 0x04];
};

// The rowed wrapper at 0x0047971C takes the exit path by reference; its
// placeholder class is this vector of points.
class Rva0035149F : public _STL::vector<Coord3D>
{
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const void *parms) = 0;
	void rva0047971C(const Rva0035149F &path, Object *ignoreObject, CommandSourceType cmdSource);
};

class LocomotorSet
{
private:
	char m_unrecovered00[0x04];
};

class AIUpdateInterface : public AIUpdateInterfaceBase, public AICommandInterface
{
public:
	const LocomotorSet &getLocomotorSet() const { return m_locomotorSet; }
private:
	char m_unrecovered24[0x1CC - 0x24];
	LocomotorSet m_locomotorSet;																							///< 0x1CC
};

class Object : public Thing
{
public:
	PathfindLayerEnum getLayer() const { return (PathfindLayerEnum)rva0028B511(); }
	void setLayer(PathfindLayerEnum layer) { rva0028B4CE(layer); }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }

	Int rva0028B511() const;
	void rva0028B4CE(PathfindLayerEnum layer);

private:
	char m_unrecovered48[0x258 - 0x48];
	AIUpdateInterface *m_ai;																									///< 0x258
};

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal = 0, Bool clip = true);
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *obj);
	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest = 0);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	char m_unrecovered00[0x10];
	Pathfinder *m_pathfinder;																									///< 0x10
};

extern AI *TheAI;

class ModuleData
{
private:
	char m_unrecovered00[0x08];
};

class DefaultProductionExitUpdateModuleData : public ModuleData
{
public:
	Coord3D m_unitCreatePoint;																								///< 0x08
	Coord3D m_naturalRallyPoint;																							///< 0x14
};

class UpdateModule
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
protected:
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
private:
	const ModuleData *m_moduleData;																						///< 0x04
	Object *m_object;																													///< 0x08
	char m_unrecovered0C[ 0x20 - 0x0C ];
};

class ExitInterface
{
public:
	virtual Bool isExitBusy() const = 0;
	virtual ExitDoorType reserveDoorForExit( const ThingTemplate *objType, Object *specificObject ) = 0;
	virtual void exitObjectViaDoor( Object *newObj, ExitDoorType exitDoor ) = 0;
	virtual void exitObjectInAHurry( Object *newObj );
	virtual void unreserveDoorForExit( ExitDoorType exitDoor ) = 0;
	virtual void exitObjectByBudding( Object *newObj, Object *budHost ) = 0;
	virtual Bool vslot06() const;
	virtual void setRallyPoint( const Coord3D *pos ) = 0;
	virtual const Coord3D *getRallyPoint( void ) const = 0;
	virtual Bool getNaturalRallyPoint( Coord3D& rallyPoint, Bool offset = true ) const;
};

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
			transform->Transform_Vector( *transform, loc, &loc );

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
					if (TheAI->pathfinder()->adjustDestination(newObj, ai->getLocomotorSet(), &tmp))
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
	*xfer == m_rallyPoint;

	// rally point exists
	*xfer == m_rallyPointExists;

}  // end xfer
