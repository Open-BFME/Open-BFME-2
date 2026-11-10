// cl: /Ob2 /DNDEBUG /MD /EHsc
// ?getMaximumVisibleBox@BaseHeightMapRenderObjClass@@QAE_NABVFrustumClass@@PAVAABoxClass@@_N@Z @0x0006B1FA 505B
// Ground-plane clip of frustum corners then AABox init. Donor is BFME1
// game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap_getMaximumVisibleBox.cpp
// (same shape: Plane(0,0,1) with m_minHeight, 4-iteration clip, 8-point Init,
// unused bool third param). BFME2 deltas: m_minHeight at this+0x37D8,
// Compute_Intersection rowed at 0x00069168. Callers at 0x00107FB5 0x0004D4B3
// pass TheTerrainRenderObject as this with (frustum+0x100, local box, 1).
#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"
static __forceinline Vector3 &copyStorageVector3(Vector3 &out,const Vector3 &in) {out.X=in.X;out.Y=in.Y;out.Z=in.Z;return out;}



inline Vector3 operator+(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

inline Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

__declspec(dllimport) __forceinline Vector3 operator*(const Vector3 &a, float k)
{
	return Vector3((a.X * k), (a.Y * k), (a.Z * k));
}

class PlaneClass
{
public:
	Vector3 N;
	float D;

	__declspec(dllimport) __forceinline PlaneClass(const Vector3 &normal, float dist)
	{
		copyStorageVector3(N, normal);
		D = dist;
	}

	bool Compute_Intersection(const Vector3 &p0, const Vector3 &p1, float *set_t) const;
};

class FrustumClass
{
public:
	char CameraTransformAndPlanes[0x90];
	Vector3 Corners[8];
};

class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;

	__forceinline void Init(Vector3 *points, int num)
	{
		Vector3 Min = points[0];
		Vector3 Max = points[0];

		for (int i = 1; i < num; i++)
		{
			if (Min.X > points[i].X)
				Min.X = points[i].X;
			if (Min.Y > points[i].Y)
				Min.Y = points[i].Y;
			if (Min.Z > points[i].Z)
				Min.Z = points[i].Z;

			if (Max.X < points[i].X)
				Max.X = points[i].X;
			if (Max.Y < points[i].Y)
				Max.Y = points[i].Y;
			if (Max.Z < points[i].Z)
				Max.Z = points[i].Z;
		}

		copyStorageVector3(Center,(Max + Min) * 0.5f);
		copyStorageVector3(Extent,(Max - Min) * 0.5f);
	}
};

class BaseHeightMapRenderObjClass
{
public:
	bool getMaximumVisibleBox(const FrustumClass &frustum, AABoxClass *box, bool ignoreMaxHeight);

private:
	char _pad[0x37D8];
	float m_minHeight;
};

bool BaseHeightMapRenderObjClass::getMaximumVisibleBox(const FrustumClass &frustum, AABoxClass *box, bool ignoreMaxHeight)
{
	PlaneClass groundPlane(Vector3(0, 0, 1), m_minHeight);

	float clipFraction;
	Vector3 ClippedCorners[8];
	copyStorageVector3(ClippedCorners[0],frustum.Corners[0]);
	for (int i = 0; i < 4; i++)
	{
		copyStorageVector3(ClippedCorners[i],frustum.Corners[i]);
		if (groundPlane.Compute_Intersection(frustum.Corners[i], frustum.Corners[i + 4], &clipFraction))
		{
			copyStorageVector3(ClippedCorners[i + 4],frustum.Corners[i] + (frustum.Corners[i + 4] - frustum.Corners[i]) * clipFraction);
		}
		else
			copyStorageVector3(ClippedCorners[i + 4],frustum.Corners[i + 4]);
	}

	if (box)
		box->Init(ClippedCorners, 8);

	return true;
}
