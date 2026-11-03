// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva001E41FA@Locomotor@@QAEXM@Z, retail 0x001E41FA..0x001E42EB (241 bytes).
// Rebuilds the rotation part of the 3x4 transform at +0x68 from a yaw angle,
// keeping its translation column: the Zero Hour Thing::setOrientation
// non-terrain branch (up z, facing u = (Cos, Sin, 0), y = z x u, x = y x z,
// Matrix3D::Set) with Coord3D::crossProduct inlined.
// Evidence: WorldBuilder twin 0xAF0E60 (unnamed, 656 bytes) declares the same
// five Coord3Ds and calls Cos, Sin and Coord3D::crossProduct twice; the only
// caller 0x001E9A00 passes its own this, which it also hands to the rowed
// Locomotor::getMaxTurnRate, so the receiver is the Locomotor. The class name
// is that inference; the method name is a placeholder.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

float Sin(float x);
float Cos(float x);

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
static __forceinline float matrixXTranslation(const Matrix3D &matrix) { return matrix.Row[0][3]; }
static __forceinline float matrixYTranslation(const Matrix3D &matrix) { return matrix.Row[1][3]; }
static __forceinline float matrixZTranslation(const Matrix3D &matrix) { return matrix.Row[2][3]; }
static __forceinline void setMatrixValues(Matrix3D &matrix,float m11,float m12,float m13,float m14,float m21,float m22,float m23,float m24,float m31,float m32,float m33,float m34) { matrix.Row[0].Set(m11,m12,m13,m14);matrix.Row[1].Set(m21,m22,m23,m24);matrix.Row[2].Set(m31,m32,m33,m34); }


static __forceinline void crossProduct(const Coord3D *left, const Coord3D *right, Coord3D *result)
{
	result->x = left->y * right->z - left->z * right->y;
	result->y = left->z * right->x - left->x * right->z;
	result->z = left->x * right->y - left->y * right->x;
}

#include "../../../Include/GameLogic/LocomotorClass.h"

void Locomotor::rva001E41FA(float angle)
{
	Coord3D translation, x, y, z, u;
	translation.x = matrixXTranslation(m_68);
	translation.y = matrixYTranslation(m_68);
	translation.z = matrixZTranslation(m_68);
	z.x = 0.0f;
	z.y = 0.0f;
	z.z = 1.0f;
	u.x = Cos(angle);
	u.y = Sin(angle);
	u.z = 0.0f;
	crossProduct(&z, &u, &y);
	crossProduct(&y, &z, &x);
	setMatrixValues(m_68,x.x, y.x, z.x, translation.x,
		x.y, y.y, z.y, translation.y,
		x.z, y.z, z.z, translation.z);
}
