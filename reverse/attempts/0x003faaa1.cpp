// ?rva003FAAA1@Rva003FAAA1@@QAE_NPAX@Z
// partial score=0.99 date=2026-10-05
// cl: /O1 /arch:SSE /MD
// ?rva003FAAA1@Rva003FAAA1@@QAE_NPAX@Z @0x003FAAA1, 236B.
// Overlap test via rowed Region3D copy 0x0009AC04 LineSeg ctor 0x000927F9 and Overlap_Test 0x00723870.
// Evidence: retail calls 0x0009AC04 0x000927F9 0x00723870 plus virtuals at +0x108 and +0x34, data g_00DFEF18 g_00BC7000, caller 0x002BFE80.
//
// The field write ORDER is load-bearing and is not the natural spelling. Writing
// p0 as Y,Z,X (not X,Y,Z) is what fixes the register assignment: it makes
// xmm4=[ebp-0x14] and xmm5=[ebp-0x10] load in retail's order rather than
// swapped, which in turn fixes the addss operands. Restoring p0.X from the
// captured sink BEFORE the p1 field writes (rather than after) is what moves the
// final nine-store block to its retail order. Both are codegen devices.
class Vector3
{
public:
	float X;
	float Y;
	float Z;
};
class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;
};
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
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;
extern float g_00BC7000;
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
	virtual void GetVectors(void *arg, Vector3 *a, Vector3 *b);
};
#define TheGlobal003FAAA1 (*(Global **)&g_00DFEF18)
class Rva003FAAA1
{
public:
	bool rva003FAAA1(void *arg);

private:
	char m_00[0x10];
	Inner1 *m_10;
};

// ?rva003FAAA1@Rva003FAAA1@@QAE_NPAX@Z present-unmatched
bool Rva003FAAA1::rva003FAAA1(void *arg)
{
	Inner1 *a = m_10;
	if (a == 0)
		return false;
	Inner2 *b = a->m_14;
	if (!b)
	{
		b = a->m_08;
		if (b == 0)
			return false;
	}
	Region3D box(*b->GetRegion());
	Vector3 b2;
	Vector3 b1;
	TheGlobal003FAAA1->GetVectors(arg, &b1, &b2);
	float scale = g_00BC7000;
	Vector3 p0;
	p0.Y = b1.Y;
	p0.Z = b1.Z;
	p0.X = b1.X;
	b2.X *= scale;
	b2.Y *= scale;
	b2.Z *= scale;
	float sink = p0.X;
	b1.X += b2.X;
	b1.Y += b2.Y;
	b1.Z += b2.Z;
	p0.X = sink;
	Vector3 p1;
	p1.X = b1.X;
	p1.Y = b1.Y;
	p1.Z = b1.Z;
	LineSegClass seg(p0, p1);
	if (CollisionMath::Overlap_Test(box, seg) == 1)
		return false;
	return true;
}

