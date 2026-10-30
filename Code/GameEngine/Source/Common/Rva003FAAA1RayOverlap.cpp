// cl: /I. /O1 /arch:SSE /MD
// ?rva003FAAA1@Rva003FAAA1@@QAE_NPAX@Z @0x003FAAA1, 236B.
// Overlap test via rowed Region3D copy 0x0009AC04 LineSeg ctor 0x000927F9 and Overlap_Test 0x00723870.
// Evidence: retail calls 0x0009AC04 0x000927F9 0x00723870 plus virtuals at +0x108 and +0x34, data TheLivingWorld (0x00DFEF18) and the 100000.0f literal, caller 0x002BFE80.
//
// WB 1063140 twin: copy the object's bounding box, ask the global for a ray
// (start, direction) through virtual +0x34, scale the direction by
// 100000, and test the box against the segment start..start+dir.
// Retail inlines Zero Hour's Coord3D scale/add (Coord3DCtorView with
// COORD3D_VIEW_INLINE): the scale read into a named float first, then the two
// segment points built with Vector3's three-float constructor.
class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	float X;
	float Y;
	float Z;
};
#define COORD3D_VIEW_INLINE
// Retain native inline scale while binding out-of-line uses to the retail copy.
#define scale(args) __declspec(dllimport) __forceinline scale(args)
#include "Code/Libraries/Include/Lib/Coord3DCtorView.h"
#undef scale

class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;
};
// class-gate: allow Region3D codegen view declaring the rowed out-of-line copy constructor 0x0009AC04 (the canonical header has only the inline copy); retail copies the 24-byte box through that call and passes it to Overlap_Test as the AABox
struct Region3D : public AABoxClass
{
	Region3D(Region3D const &);
};
class LineSegClass
{
public:
	Vector3 P0;
	Vector3 P1;
	Vector3 DP;
	Vector3 Dir;
	float Length;
	LineSegClass(Vector3 const &, Vector3 const &);
};
class CollisionMath
{
public:
	enum OverlapType
	{
		OUTSIDE = 0,
		INSIDE = 1,
		OVERLAPPED = 2
	};
	static OverlapType Overlap_Test(AABoxClass const &, LineSegClass const &);
};
class LivingWorld;
extern LivingWorld *TheLivingWorld;
class Inner2
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
	virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
	virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
	virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
	virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
	virtual void s65();
	virtual struct Region3D *GetRegion();
};
class Inner1
{
public:
	char m_00[8];
	Inner2 *m_08;
	char m_0C[8];
	Inner2 *m_14;
};
class Global
{
public:
	virtual void g00(); virtual void g01(); virtual void g02(); virtual void g03(); virtual void g04();
	virtual void g05(); virtual void g06(); virtual void g07(); virtual void g08(); virtual void g09();
	virtual void g10(); virtual void g11(); virtual void g12();
	virtual void GetVectors(void *arg, Coord3D *a, Coord3D *b);
};
class Rva003FAAA1
{
public:
	bool rva003FAAA1(void *query);

private:
	char m_00[0x10];
	Inner1 *m_10;
};

bool Rva003FAAA1::rva003FAAA1(void *query)
{
	Inner1 *inner1 = m_10;
	if (inner1 == 0)
		return false;
	Inner2 *inner2 = inner1->m_14;
	if (!inner2)
	{
		inner2 = inner1->m_08;
		if (inner2 == 0)
			return false;
	}
	Region3D box(*inner2->GetRegion());
	Coord3D start;
	Coord3D dir;
	((Global *)TheLivingWorld)->GetVectors(query, &start, &dir);
	float scale = 100000.0f;
	dir.scale(scale);
	Vector3 p0(start.x, start.y, start.z);
	start.add(&dir);
	Vector3 p1(start.x, start.y, start.z);
	LineSegClass seg(p0, p1);
	if (CollisionMath::Overlap_Test(box, seg) == 1)
		return false;
	return true;
}

