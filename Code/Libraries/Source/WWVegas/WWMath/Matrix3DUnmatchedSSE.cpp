// cl: /Ireference/shims/bfmerendobj /O2 /G7 /MD /arch:SSE /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Dedicated SSE TU for Matrix3D helpers that matrix3d.cpp compiles without /arch:SSE.

#include "rendobj.h"
#include "matrix3d.h"
#include "vector3.h"

#include <math.h>

Vector3 Matrix3D::Rotate_Vector(const Vector3 &vect) const
{
	return Vector3(
		(Row[0][0]*vect[0] + Row[0][1]*vect[1] + Row[0][2]*vect[2]),
		(Row[1][0]*vect[0] + Row[1][1]*vect[1] + Row[1][2]*vect[2]),
		(Row[2][0]*vect[0] + Row[2][1]*vect[1] + Row[2][2]*vect[2])
	);
}

Vector3 Matrix3D::Inverse_Rotate_Vector(const Vector3 &vect) const
{
	return Vector3(
		(Row[0][0]*vect[0] + Row[1][0]*vect[1] + Row[2][0]*vect[2]),
		(Row[0][1]*vect[0] + Row[1][1]*vect[1] + Row[2][1]*vect[2]),
		(Row[0][2]*vect[0] + Row[1][2]*vect[1] + Row[2][2]*vect[2])
	);
}

void Matrix3D::Look_At(const Vector3 &p,const Vector3 &t,float roll)
{
	float	dx,dy,dz;
	float	len1,len2;
	float	sinp,cosp;
	float	siny,cosy;

	dx = (t[0] - p[0]);
	dy = (t[1] - p[1]);
	dz = (t[2] - p[2]);

	len1 = (float)WWMath::Sqrt(dx*dx + dy*dy + dz*dz);
	len2 = (float)WWMath::Sqrt(dx*dx + dy*dy);

	if (len1 != 0.0f) {
		sinp = dz/len1;
		cosp = len2/len1;
	} else {
		sinp = 0.0f;
		cosp = 1.0f;
	}

	if (len2 != 0.0f) {
		siny = dy/len2;
		cosy = dx/len2;
	} else {
		siny = 0.0f;
		cosy = 1.0f;
	}

	Row[0].X = 0.0f;	Row[0].Y = 0.0f;	Row[0].Z = -1.0f;
	Row[1].X = -1.0f;	Row[1].Y = 0.0f;	Row[1].Z = 0.0f;
	Row[2].X = 0.0f;	Row[2].Y = 1.0f;	Row[2].Z = 0.0f;

	Row[0].W = p.X;
	Row[1].W = p.Y;
	Row[2].W = p.Z;

	Rotate_Y(siny,cosy);
	Rotate_X(sinp,cosp);
	Rotate_Z(-roll);
}

void Matrix3D::buildTransformMatrix( const Vector3 &pos, const Vector3 &dir )
{
	float sinp, cosp;
	float siny, cosy;

	float len2 = (float)sqrt( (dir.X * dir.X) + (dir.Y * dir.Y) );

	sinp = dir.Z;
	cosp = len2;

	if( len2 != 0.0f )
	{
		siny = dir.Y / len2;
		cosy = dir.X / len2;
	}
	else
	{
		siny = 0.0f;
		cosy = 1.0f;
	}

	Make_Identity();
	Translate( pos );
	Rotate_Z( siny, cosy );
	Rotate_Y( -sinp, cosp );
}

void Matrix3D::Obj_Look_At(const Vector3 &p,const Vector3 &t,float roll)
{
	float	dx,dy,dz;
	float	len1,len2;
	float	sinp,cosp;
	float	siny,cosy;

	dx = (t[0] - p[0]);
	dy = (t[1] - p[1]);
	dz = (t[2] - p[2]);

	len1 = (float)sqrt(dx*dx + dy*dy + dz*dz);
	len2 = (float)sqrt(dx*dx + dy*dy);

	if (len1 != 0.0f) {
		sinp = dz/len1;
		cosp = len2/len1;
	} else {
		sinp = 0.0f;
		cosp = 1.0f;
	}

	if (len2 != 0.0f) {
		siny = dy/len2;
		cosy = dx/len2;
	} else {
		siny = 0.0f;
		cosy = 1.0f;
	}

	Make_Identity();
	Translate(p);
	Rotate_Z(siny,cosy);
	Rotate_Y(-sinp,cosp);
	Rotate_X(roll);
}

void Matrix3D::Copy_3x3_Matrix(float matrix[3][3])
{
	Row[0][0] = matrix[0][0];
	Row[0][1] = matrix[0][1];
	Row[0][2] = matrix[0][2];
	Row[0][3] = 0;
	Row[1][0] = matrix[1][0];
	Row[1][1] = matrix[1][1];
	Row[1][2] = matrix[1][2];
	Row[1][3] = 0;
	Row[2][0] = matrix[2][0];
	Row[2][1] = matrix[2][1];
	Row[2][2] = matrix[2][2];
	Row[2][3] = 0;
}

int Matrix3D::Is_Orthogonal(void) const
{
	Vector3 x(Row[0].X,Row[0].Y,Row[0].Z);
	Vector3 y(Row[1].X,Row[1].Y,Row[1].Z);
	Vector3 z(Row[2].X,Row[2].Y,Row[2].Z);

	if (Vector3::Dot_Product(x,y) > WWMATH_EPSILON) return 0;
	if (Vector3::Dot_Product(y,z) > WWMATH_EPSILON) return 0;
	if (Vector3::Dot_Product(z,x) > WWMATH_EPSILON) return 0;

	if (WWMath::Fabs(x.Length2() - 1.0f) > WWMATH_EPSILON) return 0;
	if (WWMath::Fabs(y.Length2() - 1.0f) > WWMATH_EPSILON) return 0;
	if (WWMath::Fabs(z.Length2() - 1.0f) > WWMATH_EPSILON) return 0;

	return 1;
}

void Matrix3D::Re_Orthogonalize(void)
{
	Vector3 x(Row[0][0],Row[0][1],Row[0][2]);
	Vector3 y(Row[1][0],Row[1][1],Row[1][2]);
	Vector3 z;

	(Vector3::Cross_Product(x,y,&z));
	(Vector3::Cross_Product(z,x,&y));

	float len = x.Length();
	if (len < WWMATH_EPSILON) {
		Make_Identity();
		return;
	} else {
		x *= 1.0f/len;
	}

	len = y.Length();
	if (len < WWMATH_EPSILON) {
		Make_Identity();
		return;
	} else {
		y *= 1.0f/len;
	}

	len = z.Length();
	if (len < WWMATH_EPSILON) {
		Make_Identity();
		return;
	} else {
		z *= 1.0f/len;
	}

	Row[0][0] = x.X;
	Row[0][1] = x.Y;
	Row[0][2] = x.Z;

	Row[1][0] = y.X;
	Row[1][1] = y.Y;
	Row[1][2] = y.Z;

	Row[2][0] = z.X;
	Row[2][1] = z.Y;
	Row[2][2] = z.Z;
}

bool Matrix3D::Solve_Linear_System(Matrix3D & system)
{
	if (system[0][0] == 0.0f) return false;
	system[0] *= 1.0f / system[0][0];
	system[1] -= system[1][0] * system[0];
	system[2] -= system[2][0] * system[0];

	if (system[1][1] == 0.0f) return false;
	system[1] *= 1.0f / system[1][1];
	system[2] -= system[2][1] * system[1];

	if (system[2][2] == 0.0f) return false;
	system[2] *= 1.0f / system[2][2];

	system[1] -= system[1][2] * system[2];
	system[0] -= system[0][2] * system[2];

	system[0] -= system[0][1] * system[1];

	return true;
}
