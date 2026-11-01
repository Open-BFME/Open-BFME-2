// cl: -DNDEBUG -MD -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient
// BFME1 0x00729EA0 / BFME2 0x001130D1: W3DTerrainBackground::castTriangle builds a
// triangle normal and casts the test ray against it. Thiscall: the caller
// getTriangleIntersection (0x0011319A) passes ecx=this; this itself is unused.

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/tri.h
class TriClass
{
public:
	const Vector3 *N;
	const Vector3 *V[3];
	void Compute_Normal(void);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/lineseg.h
class LineSegClass
{
public:
	LineSegClass(const Vector3 &p0, const Vector3 &p1);
private:
	unsigned char m_storage[0x34]; // +0x00
};

struct CastResultStruct;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/coltest.h
// Native primary ctor 6F1A6/55B proves this 44-byte view, Ray at 0C
// and three flags at 40/41/42; both terrain callers use the same prefix.
class RenderObjClass;
class RayCollisionTestClass
{
public:
	RayCollisionTestClass(const LineSegClass & ray,CastResultStruct * res,int collision_type,bool check_translucent, bool check_hidden);

	CastResultStruct *			Result;
	int								CollisionType;
	RenderObjClass *				CollidedRenderObj;
	LineSegClass 		Ray;
	bool CheckTranslucent;
	bool CheckHidden;
	bool _bfme_flag42; // Retail primary constructor initializes this extra flag to false.
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/colmath.h
class CollisionMath
{
	public:
	static bool Collide(const LineSegClass &line, const TriClass &tri, CastResultStruct *result);
};

class W3DTerrainBackground
{
public:
	bool castTriangle(RayCollisionTestClass &raytest,
		const Vector3 &p0, const Vector3 &p1, const Vector3 &p2);
};

// ?castTriangle@W3DTerrainBackground@@QAE_NAAVRayCollisionTestClass@@ABVVector3@@11@Z
bool W3DTerrainBackground::castTriangle(RayCollisionTestClass &raytest,
	const Vector3 &p0, const Vector3 &p1, const Vector3 &p2)
{
	Vector3 normal;
	TriClass tri;
	tri.V[0] = &p0;
	tri.V[1] = &p1;
	tri.V[2] = &p2;
	tri.N = &normal;
	tri.Compute_Normal();
	return CollisionMath::Collide(raytest.Ray, tri, raytest.Result);
}
