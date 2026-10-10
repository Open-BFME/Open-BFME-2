// ?rva0028EFB8@Object@@QBEMPBUCoord3D@@PBV1@0@Z
// partial score=0.992107 date=2026-10-10
// ?rva0028EFB8@Object@@QBEMPBUCoord3D@@PBV1@0@Z
// BF1 pinned575 single-box distance C++ supplies semantic/structural guide;
// native BF2 adds active-shape loop and nearest signed gap before squaring.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Include/Lib /I.

#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "matrix3d.h"

typedef int Int;
typedef float Real;

extern "C" double __cdecl fabs(double value);
extern "C" double __cdecl sqrt(double value);



// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct BfmeShapeE15;
struct BfmeVecVNB;

class BfmeObjE15
{
public:
    BfmeShapeE15 *bfmeAtE15(int index);
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
	unsigned char m_pad014[0x2c - 0x14];
	BfmeGeometryPiece *m_begin;
	BfmeGeometryPiece *m_end;

	friend class Object;
};

#define BfmeGeometryPieceAt(geometry, index) ((const BfmeGeometryPiece *)((BfmeObjE15 *)&(geometry))->bfmeAtE15(index))
#define BfmeTransformCenter(piece, position, angle) (((BfmeXformVNB *)(piece))->bfmeApplyVNB((BfmeVecVNB *)(position), angle))

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Real rva0028EFB8(
		const Coord3D *position,
		const Object *other,
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
 Real best=3.402823466e+38F;
 bool found=false;
 for(Int i=0;i<geometry->m_end-geometry->m_begin;++i){
 const BfmeGeometryPiece *piece = BfmeGeometryPieceAt(*geometry,i);
 if(!piece->m_active)continue;
	Coord3D center;
	center.x=position->x;center.y=position->y;center.z=position->z;
	BfmeTransformCenter(piece, &center, m_orientation);

	Vector3 delta(
		otherPosition->x - center.x,
		otherPosition->y - center.y,
		0.0f);
	Vector3 direction(delta);
	Real projectedX = (Real)fabs(Vector3::Dot_Product(
		m_transform.Get_X_Vector(), delta));
	Real projectedY = (Real)fabs(Vector3::Dot_Product(
		m_transform.Get_Y_Vector(), delta));

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
		Real directionLengthSquared = delta.Length2();
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
		distanceSquared = delta.X * delta.X + delta.Y * delta.Y;
	}

	Real combinedRadius=radius+other->m_geometry.m_boundingCircleRadius;
 Real distance=(Real)sqrt(distanceSquared)-combinedRadius;
 if(found){if(distance<best)best=distance;}else{found=true;best=distance;}
 }
 return best<=0.0f?0.0f:best*best;
}
