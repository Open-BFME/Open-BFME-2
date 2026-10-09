// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
//
// ?rva00072109@RTS3DScene@@QAEXAAVRayCollisionTestClass@@HAAV?$multimap@MUTreeOpaqueMapped00372FF4@@U?$less@M@_STL@@V?$allocator@U?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@@3@@_STL@@@Z
// retail 0x00072109..0x00072381 (632 bytes) thiscall RET 0xC.
//
// An all-hits variant of Zero Hour's RTS3DScene::castRay (GeneralsMD
// W3DScene.cpp): clear the caller's float-keyed multimap (placeholder clear
// 0x0006FA70); walk the render list (multi-list head +0xF0; objects reached
// through the MultiListObjectClass base at +8); skip objects failing the
// +0x180 visibility virtual or the +0x1E0 collision-type mask; run Zero
// Hour's quick ray-sphere test against Get_Bounding_Sphere (+0x104) and, when
// it misses, retry with the sphere re-centred (rowed SphereClass::Re_Center
// 0x0006F400) on the user-data drawable's position (+0x15C user data, its +4
// drawable, pinned Drawable::getPosition 0x002763E6) keeping the original
// radius; then cast a temporary RayCollisionTestClass (rowed ctor 0x0006F1A6
// with COLL_TYPE_0 then COLL_TYPE_ALL plus CheckTranslucent and the BFME +0x42
// flag) through Cast_Ray (+0xF0) and insert (fraction, object) through rowed
// insert_equal 0x004EA301. Retail caller 0x0008B305 passes W3DDisplay's
// m_3DScene (0x009E1B34) as this. WB twin 0x0072BFB0 (named only by its
// vector3.h asserts) shows the same sequence. The method name is
// address-derived; virtual slot names are carried from Zero Hour.
#include <map>
#include "Coord3D.h"

class Vector3
{
public:
	Vector3() {}
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	void Set(float x, float y, float z) { X = x; Y = y; Z = z; }
	float Length2() const { return X * X + Y * Y + Z * Z; }
	static float Dot_Product(const Vector3 &a, const Vector3 &b) { return a.X * b.X + a.Y * b.Y + a.Z * b.Z; }
	friend Vector3 operator-(const Vector3 &a, const Vector3 &b) { return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z); }
	float X;
	float Y;
	float Z;
};

class SphereClass
{
public:
	void Re_Center(const Vector3 &center);
	Vector3 Center;
	float Radius;
};

class LineSegClass
{
public:
	const Vector3 &Get_P0() const { return P0; }
	const Vector3 &Get_Dir() const { return Dir; }
	Vector3 P0;
	Vector3 P1;
	Vector3 DP;
	Vector3 Dir;
	float Length;
};

struct CastResultStruct
{
	CastResultStruct() { Reset(); }
	void Reset()
	{
		StartBad = false;
		Fraction = 1.0f;
		Normal.Set(0, 0, 0);
		SurfaceType = 0;
		ComputeContactPoint = false;
		ContactPoint.Set(0, 0, 0);
	}
	bool StartBad;
	float Fraction;
	Vector3 Normal;
	unsigned int SurfaceType;
	bool ComputeContactPoint;
	Vector3 ContactPoint;
};

class RenderObjClass;

enum
{
	COLL_TYPE_ALL = 0x01,
	COLL_TYPE_0 = 0x02
};

class CollisionTestClass
{
public:
	CastResultStruct *Result;
	int CollisionType;
	RenderObjClass *CollidedRenderObj;
};

class RayCollisionTestClass : public CollisionTestClass
{
public:
	RayCollisionTestClass(const LineSegClass &ray, CastResultStruct *res, int collision_type = COLL_TYPE_0, bool check_translucent = false, bool check_hidden = false);
	LineSegClass Ray;
	bool CheckTranslucent;
	bool CheckHidden;
	bool _bfme_flag42;
};

class Drawable
{
public:
	const Coord3D *getPosition() const;
};

struct DrawableInfo
{
	int m_shroudStatusObjectID;
	Drawable *m_drawable;
};

class RefCountClass
{
public:
	virtual ~RefCountClass();
	int NumRefs;
};

struct MultiListNodeClass;

class MultiListObjectClass
{
public:
	MultiListNodeClass *ListNode;
};

struct MultiListNodeClass
{
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	MultiListObjectClass *Object;
	void *List;
};

#define RENDEROBJ_SLOT(n) virtual void slot##n();

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
public:
	RENDEROBJ_SLOT(01) RENDEROBJ_SLOT(02) RENDEROBJ_SLOT(03) RENDEROBJ_SLOT(04)
	RENDEROBJ_SLOT(05) RENDEROBJ_SLOT(06) RENDEROBJ_SLOT(07) RENDEROBJ_SLOT(08)
	RENDEROBJ_SLOT(09) RENDEROBJ_SLOT(10) RENDEROBJ_SLOT(11) RENDEROBJ_SLOT(12)
	RENDEROBJ_SLOT(13) RENDEROBJ_SLOT(14) RENDEROBJ_SLOT(15) RENDEROBJ_SLOT(16)
	RENDEROBJ_SLOT(17) RENDEROBJ_SLOT(18) RENDEROBJ_SLOT(19) RENDEROBJ_SLOT(20)
	RENDEROBJ_SLOT(21) RENDEROBJ_SLOT(22) RENDEROBJ_SLOT(23) RENDEROBJ_SLOT(24)
	RENDEROBJ_SLOT(25) RENDEROBJ_SLOT(26) RENDEROBJ_SLOT(27) RENDEROBJ_SLOT(28)
	RENDEROBJ_SLOT(29) RENDEROBJ_SLOT(30) RENDEROBJ_SLOT(31) RENDEROBJ_SLOT(32)
	RENDEROBJ_SLOT(33) RENDEROBJ_SLOT(34) RENDEROBJ_SLOT(35) RENDEROBJ_SLOT(36)
	RENDEROBJ_SLOT(37) RENDEROBJ_SLOT(38) RENDEROBJ_SLOT(39) RENDEROBJ_SLOT(40)
	RENDEROBJ_SLOT(41) RENDEROBJ_SLOT(42) RENDEROBJ_SLOT(43) RENDEROBJ_SLOT(44)
	RENDEROBJ_SLOT(45) RENDEROBJ_SLOT(46) RENDEROBJ_SLOT(47) RENDEROBJ_SLOT(48)
	RENDEROBJ_SLOT(49) RENDEROBJ_SLOT(50) RENDEROBJ_SLOT(51) RENDEROBJ_SLOT(52)
	RENDEROBJ_SLOT(53) RENDEROBJ_SLOT(54) RENDEROBJ_SLOT(55) RENDEROBJ_SLOT(56)
	RENDEROBJ_SLOT(57) RENDEROBJ_SLOT(58) RENDEROBJ_SLOT(59)
	virtual bool Cast_Ray(RayCollisionTestClass &raytest);				// +0xF0
	RENDEROBJ_SLOT(61) RENDEROBJ_SLOT(62) RENDEROBJ_SLOT(63) RENDEROBJ_SLOT(64)
	virtual const SphereClass &Get_Bounding_Sphere() const;				// +0x104
	RENDEROBJ_SLOT(66) RENDEROBJ_SLOT(67) RENDEROBJ_SLOT(68)
	RENDEROBJ_SLOT(69) RENDEROBJ_SLOT(70) RENDEROBJ_SLOT(71) RENDEROBJ_SLOT(72)
	RENDEROBJ_SLOT(73) RENDEROBJ_SLOT(74) RENDEROBJ_SLOT(75) RENDEROBJ_SLOT(76)
	RENDEROBJ_SLOT(77) RENDEROBJ_SLOT(78) RENDEROBJ_SLOT(79) RENDEROBJ_SLOT(80)
	RENDEROBJ_SLOT(81) RENDEROBJ_SLOT(82) RENDEROBJ_SLOT(83) RENDEROBJ_SLOT(84)
	RENDEROBJ_SLOT(85) RENDEROBJ_SLOT(86)
	virtual void *Get_User_Data();										// +0x15C
	RENDEROBJ_SLOT(88)
	RENDEROBJ_SLOT(89) RENDEROBJ_SLOT(90) RENDEROBJ_SLOT(91) RENDEROBJ_SLOT(92)
	RENDEROBJ_SLOT(93) RENDEROBJ_SLOT(94) RENDEROBJ_SLOT(95)
	virtual int Is_Really_Visible();									// +0x180
	RENDEROBJ_SLOT(97) RENDEROBJ_SLOT(98) RENDEROBJ_SLOT(99) RENDEROBJ_SLOT(100)
	RENDEROBJ_SLOT(101) RENDEROBJ_SLOT(102) RENDEROBJ_SLOT(103) RENDEROBJ_SLOT(104)
	RENDEROBJ_SLOT(105) RENDEROBJ_SLOT(106) RENDEROBJ_SLOT(107) RENDEROBJ_SLOT(108)
	RENDEROBJ_SLOT(109) RENDEROBJ_SLOT(110) RENDEROBJ_SLOT(111) RENDEROBJ_SLOT(112)
	RENDEROBJ_SLOT(113) RENDEROBJ_SLOT(114) RENDEROBJ_SLOT(115) RENDEROBJ_SLOT(116)
	RENDEROBJ_SLOT(117) RENDEROBJ_SLOT(118) RENDEROBJ_SLOT(119)
	virtual int Get_Collision_Type() const;								// +0x1E0
};

class GenericMultiListClass
{
public:
	virtual ~GenericMultiListClass();
	MultiListNodeClass Head;
};

class RefRenderObjListIterator
{
public:
	RefRenderObjListIterator(GenericMultiListClass *list) : List(list), CurNode(list->Head.Next) {}
	bool Is_Done() const { return CurNode == &List->Head; }
	void Next() { CurNode = CurNode->Next; }
	RenderObjClass *Peek_Obj() const { return (RenderObjClass *)Current_Object(); }
	MultiListObjectClass *Current_Object() const { return CurNode->Object; }

private:
	GenericMultiListClass *List;
	MultiListNodeClass *CurNode;
};

struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::multimap<float, TreeOpaqueMapped00372FF4> RenderObjHitMap;

class Rva0006F318
{
public:
	void rva0006FA70();
};

class RTS3DScene
{
public:
	void rva00072109(RayCollisionTestClass &raytest, int collisionType, RenderObjHitMap &hits);

private:
	char m_pad000[0xEC];
	GenericMultiListClass RenderList;	// +0xEC
};

void RTS3DScene::rva00072109(RayCollisionTestClass &raytest, int collisionType, RenderObjHitMap &hits)
{
	((Rva0006F318 *)&hits)->rva0006FA70();

	RefRenderObjListIterator it(&RenderList);
	while (!it.Is_Done())
	{
		RenderObjClass *robj = it.Peek_Obj();
		it.Next();

		if (!robj->Is_Really_Visible())
			continue;
		if (!(robj->Get_Collision_Type() & collisionType))
			continue;

		const SphereClass *sphere = &robj->Get_Bounding_Sphere();
		Vector3 sphere_vector(sphere->Center - raytest.Ray.Get_P0());
		float Alpha = Vector3::Dot_Product(sphere_vector, raytest.Ray.Get_Dir());
		float Beta = sphere->Radius * sphere->Radius - (sphere_vector.Length2() - Alpha * Alpha);
		if (Beta < 0.0f)
		{
			DrawableInfo *drawInfo = (DrawableInfo *)robj->Get_User_Data();
			Drawable *draw = drawInfo ? drawInfo->m_drawable : 0;
			if (!draw)
				continue;
			SphereClass moved(*sphere);
			moved.Re_Center(*(const Vector3 *)draw->getPosition());
			Vector3 moved_vector(moved.Center - raytest.Ray.Get_P0());
			Alpha = Vector3::Dot_Product(moved_vector, raytest.Ray.Get_Dir());
			Beta = sphere->Radius * sphere->Radius - (moved_vector.Length2() - Alpha * Alpha);
			if (Beta < 0.0f)
				continue;
		}

		CastResultStruct result;
		RayCollisionTestClass tempRayTest(raytest.Ray, &result);
		tempRayTest._bfme_flag42 = true;
		tempRayTest.CollisionType = COLL_TYPE_ALL;
		tempRayTest.CheckTranslucent = true;
		if (robj->Cast_Ray(tempRayTest))
		{
			TreeOpaqueMapped00372FF4 hit;
			hit.m_bits = (unsigned int)robj;
			hits.insert(RenderObjHitMap::value_type(tempRayTest.Result->Fraction, hit));
		}
	}
}
