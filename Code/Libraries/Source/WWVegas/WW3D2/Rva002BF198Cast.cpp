// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2renderobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?Rva002BF198Cast@@YG_NPAVRenderObjClass@@ABVVector3@@1PAV2@H_N@Z @0x002BF198 287B.
// Free stdcall raycast helper: builds a 100000.0f LineSeg from start along dir,
// tests it against the given RenderObj via Cast_Ray slot 0xF0, and writes the
// ContactPoint into out via Set or zeroes it. ComputeContactPoint is true.
// Evidence: callees rowed LineSeg 0x000927F9 and RayCollision 0x0006F1A6;
// callers at 0x0020E354 0x002BF2B7 0x002BF4F3 0x002BF841 pass COLL_TYPE_ALL 1.
// LINK-COMDAT: hide the header-inline LineSeg bodies so calls reach the kept
// copies (scene.cpp/matrix3.cpp/vp.cpp). Same 52B layout (4xVector3+float),
// ctor declaration-only.
#define LINESEG_H
class Vector3;
class Matrix3D;
class LineSegClass
{
public:
	LineSegClass(const Vector3 &p0, const Vector3 &p1);
	LineSegClass(const LineSegClass &that, const Matrix3D &tm);
	const Vector3 &Get_P0() const;
	const Vector3 &Get_P1() const;
private:
	float m_pad[13];
};
#include "rendobj.h"
#include "coltest.h"
#include "lineseg.h"
#include "vector3.h"
#include "castres.h"

bool __stdcall Rva002BF198Cast(RenderObjClass *obj, const Vector3 &start, const Vector3 &dir, Vector3 *out, int collisionType, bool checkHidden)
{
	CastResultStruct res;
	res.ComputeContactPoint = true;
	Vector3 p0 = start;
	Vector3 p1;
	p1.X = start.X + dir.X * 100000.0f;
	p1.Y = start.Y + dir.Y * 100000.0f;
	p1.Z = start.Z + dir.Z * 100000.0f;
	LineSegClass ray(p0, p1);
	RayCollisionTestClass raytest(ray, &res, collisionType, false, false);
	raytest.CheckHidden = checkHidden;
	bool hit = obj->Cast_Ray(raytest);
	if (out) {
		if (hit) {
			out->Set(raytest.Result->ContactPoint.X, raytest.Result->ContactPoint.Y, raytest.Result->ContactPoint.Z);
		} else {
			out->Set(0.0f, 0.0f, 0.0f);
		}
	}
	return hit;
}
