// cl: /O2 /G7 /MD /arch:SSE
//
// Matrix3D::Transform_Min_Max_AABox, retail 0x00712B60, 319 bytes.
// Dedicated TU so matrix3d.cpp keeps its matched bodies.

#include "Vector3Data.h"

// Const-reference component read; the header's value-returning const subscript changes this code.
static inline const float &constComponent(const Vector3 &v, int i) { return (&v.X)[i]; }

class Matrix3D
{
public:
	void Transform_Min_Max_AABox(const Vector3 &min, const Vector3 &max,
		Vector3 *set_min, Vector3 *set_max) const;
	void Transform_Center_Extent_AABox(const Vector3 &center, const Vector3 &extent,
		Vector3 *set_center, Vector3 *set_extent) const;

	float Row[3][4];
};

void Matrix3D::Transform_Min_Max_AABox(
	const Vector3 &min,
	const Vector3 &max,
	Vector3 *set_min,
	Vector3 *set_max
) const
{
	float tmp0, tmp1;

	set_min->X = set_max->X = Row[0][3];
	set_min->Y = set_max->Y = Row[1][3];
	set_min->Z = set_max->Z = Row[2][3];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tmp0 = Row[i][j] * constComponent(min, j);
			tmp1 = Row[i][j] * constComponent(max, j);
			if (tmp0 < tmp1) {
				(*set_min)[i] += tmp0;
				(*set_max)[i] += tmp1;
			} else {
				(*set_min)[i] += tmp1;
				(*set_max)[i] += tmp0;
			}
		}
	}
}

inline float WWMath_Fabs(float val)
{
	int value = *(int *)&val;
	value &= 0x7fffffff;
	return *(float *)&value;
}

void Matrix3D::Transform_Center_Extent_AABox(
	const Vector3 &center,
	const Vector3 &extent,
	Vector3 *set_center,
	Vector3 *set_extent
) const
{
	for (int i = 0; i < 3; i++) {
		(*set_center)[i] = Row[i][3];
		(*set_extent)[i] = 0.0f;
		for (int j = 0; j < 3; j++) {
			(*set_center)[i] += Row[i][j] * constComponent(center, j);
			(*set_extent)[i] += WWMath_Fabs(Row[i][j] * constComponent(extent, j));
		}
	}
}
