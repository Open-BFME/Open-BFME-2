// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Include/Lib /I.

#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "matrix3d.h"
#include <math.h>

// Native 0x0028EFB8..0x0028F2C4: thiscall float result, RET 12.
// WorldBuilder CE52E0 proves active-shape enumeration, Coord3D delta followed
// by a Vector3 direction constructed from XY, and direction.Length2().
// The BFME1 575ba2b04 single-box distance donor supplies the semantic guide;
// BFME2 bytes establish the active shape loop, geometry offsets and minimum
// signed gap. Matrix3D/Vector3 headers: verified BFME1 cee35b7d8ca0.
// Keep the distinct coordinate and direction locals: using a Vector3 copy
// for delta or taking delta.Length2() changes two x87/SSE scheduling ties.
// The address-derived method name and const qualification are ABI views;
// WorldBuilder alone does not establish the original public method name.

#include "../../../Include/Common/ScalarTypes.h"


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct BfmeShapeE15;
struct BfmeVecVNB;

class BfmeObjE15
{
public:
    BfmeShapeE15 *getGeometryShape(int index);
};

class BfmeXformVNB
{
public:
    void bfmeApplyVNB(BfmeVecVNB *position, float angle);
};

struct BfmeGeometryPiece
{
	Int m_type;
	Real m_height;
	Real m_majorRadius;
	Real m_minorRadius;
	Coord3D m_localCenter;
	unsigned char m_pad01c[4];
	bool m_active;
	unsigned char m_pad021[3];


};

class BfmeGeometryInfo
{
public:

	Real boxMajorRadius() const;
	Real boxMinorRadius() const;

private:
	unsigned char m_pad000[0x10];
	Real m_boundingCircleRadius;
	unsigned char m_pad014[0x24 - 0x14];
	Real m_majorRadius;	// +0x24
	Real m_minorRadius;	// +0x28
	BfmeGeometryPiece *m_begin;
	BfmeGeometryPiece *m_end;

	friend class Object;
};

#define BfmeGeometryPieceAt(geometry, index) ((const BfmeGeometryPiece *)((BfmeObjE15 *)&(geometry))->getGeometryShape(index))
#define BfmeTransformCenter(piece, position, angle) (((BfmeXformVNB *)(piece))->bfmeApplyVNB((BfmeVecVNB *)(position), angle))

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Real rva0028EFB8(
		const Coord3D *position,
		const Object *other,
		const Coord3D *otherPosition) const;
	Real rva0028ED19(
		const Coord3D *position,
		const void *other,
		const Coord3D *otherPosition) const;

private:
	unsigned char m_pad000[0x08];
	Matrix3D m_transform;
	Coord3D m_position;
	Real m_orientation;
	unsigned char m_pad048[0xa8 - 0x48];
	BfmeGeometryInfo m_geometry;
};

Real Object::rva0028EFB8(
	const Coord3D *position,
	const Object *other,
	const Coord3D *otherPosition) const
{
	const BfmeGeometryInfo *geometry=&m_geometry;
 Real best=9999999.0f;
 bool found=false;
 for(Int i=0;i<geometry->m_end-geometry->m_begin;++i){
 const BfmeGeometryPiece *piece = BfmeGeometryPieceAt(*geometry,i);
 if(!piece->m_active)continue;
	Coord3D center;
	center.x=position->x;center.y=position->y;center.z=position->z;
	BfmeTransformCenter(piece, &center, m_orientation);

	Coord3D delta;
	delta.x = otherPosition->x - center.x;
	delta.y = otherPosition->y - center.y;
	delta.z = 0.0f;
	Vector3 direction(delta.x, delta.y, 0.0f);
	Real projectedX = (Real)fabs(Vector3::Dot_Product(
		m_transform.Get_X_Vector(), direction));
	Real projectedY = (Real)fabs(Vector3::Dot_Product(
		m_transform.Get_Y_Vector(), direction));

	if (projectedX < piece->m_majorRadius &&
		projectedY < piece->m_minorRadius)
	{
		return 0.0f;
	}

	Real distanceSquared;
	Real radius;
	if (projectedX < piece->m_majorRadius)
	{
		radius = piece->m_minorRadius;
		distanceSquared = projectedY * projectedY;
	}
	else if (projectedY < piece->m_minorRadius)
	{
		radius = piece->m_majorRadius;
		distanceSquared = projectedX * projectedX;
	}
	else
	{
		Real directionLengthSquared = direction.Length2();
		if (directionLengthSquared != 0.0f)
		{
			Real inverseDistance = WWMath::Inv_Sqrt(directionLengthSquared);
			direction *= inverseDistance;
		}

		Vector3 majorAxis = m_transform.Get_X_Vector();
		Real majorRadius = piece->m_majorRadius;
		majorAxis = majorAxis * majorRadius;
		Real majorProjection =
			(Real)fabs(Vector3::Dot_Product(majorAxis, direction));
		Vector3 minorAxis = m_transform.Get_Y_Vector();
		Real minorRadius = piece->m_minorRadius;
		minorAxis = minorAxis * minorRadius;
		Real minorProjection =
			(Real)fabs(Vector3::Dot_Product(minorAxis, direction));
		radius = majorProjection + minorProjection;
		distanceSquared = delta.x * delta.x + delta.y * delta.y;
	}

	Real combinedRadius=radius+other->m_geometry.m_boundingCircleRadius;
 Real distance=(Real)sqrt(distanceSquared)-combinedRadius;
 if(found){if(distance<best)best=distance;}else{found=true;best=distance;}
 }
 return best<=0.0f?0.0f:best*best;
}

// Native 0x0028ED19..0x0028EFB8: thiscall float result, RET 12; called by
// Weapon::isWithinAttackRange 0x002CB35C (its pinned const void * spelling).
// The single-box sibling of 0x0028EFB8 (WB CE4050 inlines Vector3
// Dot_Product/Length2): geometry piece 0 places the centre, and the box
// radii are the geometry's own +0x24/+0x28 rather than the piece's.
Real Object::rva0028ED19(
	const Coord3D *position,
	const void *other,
	const Coord3D *otherPosition) const
{
	const BfmeGeometryInfo *geometry = &m_geometry;
	const BfmeGeometryPiece *piece = BfmeGeometryPieceAt(*geometry, 0);
	Coord3D center;
	center.x = position->x;
	center.y = position->y;
	center.z = position->z;
	BfmeTransformCenter(piece, &center, m_orientation);

	Coord3D delta;
	delta.x = otherPosition->x - center.x;
	delta.y = otherPosition->y - center.y;
	delta.z = 0.0f;
	Vector3 direction(delta.x, delta.y, 0.0f);
	Real projectedX = (Real)fabs(Vector3::Dot_Product(
		m_transform.Get_X_Vector(), direction));
	Real projectedY = (Real)fabs(Vector3::Dot_Product(
		m_transform.Get_Y_Vector(), direction));

	if (projectedX < geometry->m_majorRadius &&
		projectedY < geometry->m_minorRadius)
	{
		return 0.0f;
	}

	Real distanceSquared;
	Real radius;
	if (projectedX < geometry->m_majorRadius)
	{
		radius = geometry->m_minorRadius;
		distanceSquared = projectedY * projectedY;
	}
	else if (projectedY < geometry->m_minorRadius)
	{
		radius = geometry->m_majorRadius;
		distanceSquared = projectedX * projectedX;
	}
	else
	{
		Real directionLengthSquared = direction.Length2();
		if (directionLengthSquared != 0.0f)
		{
			Real inverseDistance = WWMath::Inv_Sqrt(directionLengthSquared);
			direction *= inverseDistance;
		}

		Vector3 majorAxis = m_transform.Get_X_Vector();
		Real majorRadius = geometry->m_majorRadius;
		majorAxis = majorAxis * majorRadius;
		Real majorProjection =
			(Real)fabs(Vector3::Dot_Product(majorAxis, direction));
		Vector3 minorAxis = m_transform.Get_Y_Vector();
		Real minorRadius = geometry->m_minorRadius;
		minorAxis = minorAxis * minorRadius;
		Real minorProjection =
			(Real)fabs(Vector3::Dot_Product(minorAxis, direction));
		radius = majorProjection + minorProjection;
		distanceSquared = delta.x * delta.x + delta.y * delta.y;
	}

	Real combinedRadius = radius + ((const Object *)other)->m_geometry.m_boundingCircleRadius;
	Real distance = (Real)sqrt(distanceSquared) - combinedRadius;
	return distance <= 0.0f ? 0.0f : distance * distance;
}
