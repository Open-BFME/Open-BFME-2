// ?exitObjectViaDoor@SupplyCenterProductionExitUpdate@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

// SupplyCenterProductionExitUpdate (Zero Hour GameEngine/Source/GameLogic/
// Object/Update/ProductionExitUpdate/SupplyCenterProductionExitUpdate.cpp).
// The module's ctor and pool key live in the SupplyCenterProductionExitUpdate*
// shards under Object/Update/.
//
// Target evidence. Primary vtable 0x00852D30 (installed by the rowed ctor
// 0x004A65AE) holds getExitPosition 0x004A6642 at slot 13; it is the same
// body as DefaultProductionExitUpdate's (vtable 0x0084B2AC, same slot) and
// BFME 1's SupplyCenterProductionExitUpdate::getExitPosition takes the same
// primary slot. The ExitInterface table 0x00852D00 at module +0x20 holds
// exitObjectViaDoor 0x004A6702 at slot 2 and the DefaultProductionExitUpdate
// rally point accessors at slots 7 and 8, which use +0x24 (Coord3D) and
// +0x30 (exists flag) -- the fields the ctor zeroes. The body sets the
// position through Thing::setPosition 0x0030AA80, takes the ground height
// from TerrainLogic slot 6 and the AI's supply truck interface from AI slot
// 95 (+0x17C), whose slot 11 (+0x2C) is setForceWantingState.
//
// Donor-carried: the names and the ZH bodies. BFME 2 drops the temporary
// stealth grant after the supply truck kick; the exit path goes through the
// rowed AICommandInterface wrapper 0x0047971C as in QueueProductionExitUpdate.

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include <vector>

class Object;
class ThingTemplate;

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

class SupplyTruckAIInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10();
	virtual void setForceWantingState(Bool v);																// slot 11 -> offset 0x2C
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
	virtual void v9_0(); virtual void v9_1(); virtual void v9_2(); virtual void v9_3(); virtual void v9_4();
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface();												// slot 95 -> offset 0x17C
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

class AIUpdateInterface : public AIUpdateInterfaceBase, public AICommandInterface
{
};

class Object : public Thing
{
public:
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }

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
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *obj);
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

class SupplyCenterProductionExitUpdateModuleData : public ModuleData
{
public:
	Coord3D m_unitCreatePoint;																								///< 0x08
	Coord3D m_naturalRallyPoint;																							///< 0x14
};

class UpdateModule
{
public:
	virtual void v00();
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
};

class SupplyCenterProductionExitUpdate : public UpdateModule, public ExitInterface
{
public:
	virtual void exitObjectViaDoor( Object *newObj, ExitDoorType exitDoor );
	virtual Bool getExitPosition( Coord3D& exitPosition ) const;
protected:
	const SupplyCenterProductionExitUpdateModuleData *getSupplyCenterProductionExitUpdateModuleData() const
	{
		return (const SupplyCenterProductionExitUpdateModuleData *)getModuleData();
	}
private:
	Coord3D m_rallyPoint;																											///< 0x24
	Bool m_rallyPointExists;																									///< 0x30
};

//-------------------------------------------------------------------------------------------------
void SupplyCenterProductionExitUpdate::exitObjectViaDoor( Object *newObj, ExitDoorType exitDoor )
{
	Object *creationObject = getObject();
	if (creationObject)
	{
		const SupplyCenterProductionExitUpdateModuleData* md = getSupplyCenterProductionExitUpdateModuleData();

		Real exitAngle = creationObject->getOrientation();
		const Matrix3D *transform = creationObject->getTransformMatrix();
		Vector3 loc;
		Coord3D createPoint;

		//
		// calculate the position to create the object at, we take the coord specified
		// in INI which is in model space, rotate it to match the building angle
		// and translate for building location via a transform call
		//
		loc.Set( md->m_unitCreatePoint.x, md->m_unitCreatePoint.y, md->m_unitCreatePoint.z );
		transform->Transform_Vector( *transform, loc, &loc );

		// make sure the point is on the terrain
		loc.Z = TheTerrainLogic ? TheTerrainLogic->getGroundHeight( loc.X, loc.Y ) : 0.0f;

		// we need it in Coord3D form
		createPoint = *(const Coord3D *)&loc;

		newObj->setPosition( &createPoint );
		newObj->setOrientation( exitAngle );

		// tell the AI about it
		TheAI->pathfinder()->AddObjectToPathfindMap( newObj );

		Vector3 p;

		//
		// get the natural rally point from the INI definition, this coord is in model space relative
		// to the model (0,0,0)
		//
		p.X = md->m_naturalRallyPoint.x;
		p.Y = md->m_naturalRallyPoint.y;
		p.Z = md->m_naturalRallyPoint.z;

		// transform the point into world space
		transform->Transform_Vector( *transform, p, &p );

		Rva0035149F exitPath;

		Coord3D tmp; tmp.x = p.X; tmp.y = p.Y; tmp.z = p.Z;
		exitPath.push_back(tmp);

		if (m_rallyPointExists)
		{
			exitPath.push_back(m_rallyPoint);
		}

		AIUpdateInterface  *ai = newObj->getAIUpdateInterface();
		if( ai )
		{
			ai->rva0047971C( exitPath, creationObject, CMD_FROM_AI );

			// Here is the special bit for this exit style, force wanting on SupplyTruck types
			SupplyTruckAIInterface* supplyTruckAI = ai->getSupplyTruckAIInterface();

			if( supplyTruckAI )
				supplyTruckAI->setForceWantingState(true);
		}
	}
}

//-------------------------------------------------------------------------------------------------
Bool SupplyCenterProductionExitUpdate::getExitPosition( Coord3D& exitPosition ) const
{
	const Object *obj = getObject();
	if (!obj)
		return false;

	const Matrix3D *transform = obj->getTransformMatrix();

	const SupplyCenterProductionExitUpdateModuleData *md = getSupplyCenterProductionExitUpdateModuleData();

	Vector3 loc;
	loc.Set( md->m_unitCreatePoint.x, md->m_unitCreatePoint.y, md->m_unitCreatePoint.z );
	transform->Transform_Vector( *transform, loc, &loc );

	exitPosition = *(const Coord3D *)&loc;

	return true;
}
