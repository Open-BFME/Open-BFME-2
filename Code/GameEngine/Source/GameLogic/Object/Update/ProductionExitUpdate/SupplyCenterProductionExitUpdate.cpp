// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX
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
// primary slot. The body reads the module data's create point (+0x08) and
// the object's transform (+0x08).
//
// Donor-carried: the name and the ZH body. exitObjectViaDoor 0x004A6702
// (ExitInterface table 0x00852D00, slot 2) is banked in reverse/attempts:
// it is exact apart from the operand order of the rally-point transform.

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;

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

private:
	char m_unrecovered00[0x08];
	Matrix3D m_transform;																											///< 0x08
};

class Object : public Thing
{
};

class ModuleData
{
private:
	char m_unrecovered00[0x08];
};

class SupplyCenterProductionExitUpdateModuleData : public ModuleData
{
public:
	Coord3D m_unitCreatePoint;																								///< 0x08
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
};

class SupplyCenterProductionExitUpdate : public UpdateModule
{
public:
	virtual Bool getExitPosition( Coord3D& exitPosition ) const;
protected:
	const SupplyCenterProductionExitUpdateModuleData *getSupplyCenterProductionExitUpdateModuleData() const
	{
		return (const SupplyCenterProductionExitUpdateModuleData *)getModuleData();
	}
};

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
