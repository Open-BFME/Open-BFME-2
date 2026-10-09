// ?castRay@Rva0016825DLineView@@QAE_NAAVRayCollisionTestClass@@@Z
// partial score=0.926 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// NEAR (474 of 474 bytes / 17 differing instructions, all in the inlined
// point transform) ?castRay@Rva0016825DLineView@@QAE_NAAVRayCollisionTestClass@@@Z
// retail 0x00168725..0x001688FF (474 bytes RET 4). It is vtable word
// 0x007D42B8 of the line render object whose bounds/sphere slots are
// the rowed Rva0016825DLineView methods (0x0016825D / 0x001681ED). The body
// is the W3D SegmentedLineClass::Cast_Ray source (BFME 2 WW3D2 segline.cpp
// / rowed /O2 copy 0x0015F2C0) compiled /O1 for a class with points at
// +0xC8 / count +0xD0 / width +0xEC: collision-type test (vslot 120) /
// Transform.mulVector3Array of two points / LineSegClass ctor (rowed
// 0x000927F9; BFME 2 LineSegClass is 52 bytes with Dir) /
// Find_Intersection (rowed 0x007192A0) / WWMath::Sqrt length / fill the
// result (SurfaceType 13) on the first hit.
// Everything else is exact: frame / registers / pointer induction / tail.
// Remaining wall: the per-row term order MSVC picks for the three
// row dot products. Retail row 0 is (inX*R00 + R02*inZ) + R01*inY + R03 with
// row 1's X product scheduled before the row 0 store. cl emits (R02*inZ +
// R00*inX) + ... for every source spelling tried. Tried: all six term
// permutations with W first or last / Row[r][c] / (*in) / in[0] / reference
// and copy of *in / ++in ++out order / for-loop indexing / Transform_Vector
// per point / ALLOW_TEMPORARIES operator* / /G5 /G6 /arch:SSE2 /Op /Os /Og
// /Oy- variants.
typedef unsigned int uint32;

class Vector3
{
public:
	float X;
	float Y;
	float Z;
	Vector3() {}
	__forceinline Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	__forceinline float Length2() const { return X * X + Y * Y + Z * Z; }
	__forceinline float Length() const;
	friend __forceinline Vector3 operator-(const Vector3 &a, const Vector3 &b)
	{
		return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
	}
};

static __forceinline float Rva00168725Sqrt(float val)
{
	float retval;
	__asm {
		fld [val]
		fsqrt
		fstp [retval]
	}
	return retval;
}

__forceinline float Vector3::Length() const { return Rva00168725Sqrt(Length2()); }

class Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	__forceinline void mulVector3Array(const Vector3 *in, Vector3 *out, int count) const
	{
		while (count--)
		{
			out->X = (Row[0].X * in->X + Row[0].Y * in->Y + Row[0].Z * in->Z + Row[0].W);
			out->Y = (Row[1].X * in->X + Row[1].Y * in->Y + Row[1].Z * in->Z + Row[1].W);
			out->Z = (Row[2].X * in->X + Row[2].Y * in->Y + Row[2].Z * in->Z + Row[2].W);
			++out;
			++in;
		}
	}
	Vector4 Row[3];
};

class LineSegClass
{
public:
	LineSegClass(const Vector3 &p0, const Vector3 &p1);
	bool Find_Intersection(const LineSegClass &other_line, Vector3 *p1, float *fraction1,
		Vector3 *p2, float *fraction2) const;
private:
	Vector3 P0;
	Vector3 P1;
	Vector3 DP;
	Vector3 Dir;
	float Length;
};

struct CastResultStruct
{
	bool StartBad;
	float Fraction;
	Vector3 Normal;
	uint32 SurfaceType;
};

class RenderObjClass;

class RayCollisionTestClass
{
public:
	CastResultStruct *Result;
	int CollisionType;
	RenderObjClass *CollidedRenderObj;
	LineSegClass Ray;
};

class Rva00168725CollisionView
{
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V10(0) V10(1) V10(2) V10(3) V10(4) V10(5) V10(6) V10(7) V10(8) V10(9) V10(10) V10(11)
#undef V10
#undef V
	virtual int Get_Collision_Type() const;		// slot 120
};

struct Rva0016825DLineView
{
	unsigned char m_pad00[0x18];
	Matrix3D Transform;							// +0x18
	unsigned char m_pad48[0xC8 - 0x48];
	Vector3 *points;							// +0xC8
	unsigned int unknownCC;
	unsigned int count;							// +0xD0
	unsigned char m_padD4[0xEC - 0xD4];
	float width;								// +0xEC
	bool castRay(RayCollisionTestClass &raytest);
};

bool Rva0016825DLineView::castRay(RayCollisionTestClass &raytest)
{
	if ((reinterpret_cast<const Rva00168725CollisionView *>(this)->Get_Collision_Type() & raytest.CollisionType) == 0)
		return false;

	bool retval = false;
	float fraction = 1.0F;
	for (uint32 index = 1; index < count; index++)
	{
		Vector3 curr[2];
		Transform.mulVector3Array(&points[index - 1], curr, 2);
		LineSegClass line_seg(curr[0], curr[1]);

		Vector3 p0;
		Vector3 p1;
		if (raytest.Ray.Find_Intersection(line_seg, &p0, &fraction, &p1, 0))
		{
			float dist = (p0 - p1).Length();
			if (dist <= width && fraction >= 0 && fraction < raytest.Result->Fraction)
			{
				retval = true;
				break;
			}
		}
	}

	if (retval)
	{
		raytest.Result->Fraction = fraction;
		raytest.Result->SurfaceType = 13;
		raytest.CollidedRenderObj = reinterpret_cast<RenderObjClass *>(this);
	}
	return retval;
}
