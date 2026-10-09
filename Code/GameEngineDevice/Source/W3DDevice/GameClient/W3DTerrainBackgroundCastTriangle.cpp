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
	unsigned char m_pad[0x34];
};

struct CastResultStruct;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/coltest.h
class RayCollisionTestClass
{
public:
	CastResultStruct *Result;
	unsigned char m_pad04[0x08];
	LineSegClass Ray;
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
