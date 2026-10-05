// ?rva00462B93@SlaughterHordeContain@@UAE_NPBVRva00462B93Arg@@@Z
// partial score=0.88 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?rva00462B93@SlaughterHordeContain@@UAE_NPBVRva00462B93Arg@@@Z, retail 0x00462B93, 108 bytes.
// Virtual slot 85 (offset 0x154) of vtable 0x00848AA0 (class of
// ??0SlaughterHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z in
// SlaughterHordeContainCtor.cpp). Forward-half-plane predicate ported from
// BFME1 Rva002218A0ForwardHalfPlane.cpp at 6583b3c1 with single localized
// repair info +0x138 -> +0x68 (BFME2 SlaughterHordeContainModuleData layout).
// Threshold/deltaZ/dot-direction semantics, offsets 68/40/8/18/28, 17 table
// anchors. Leaf SSE, ret 4, no callees. Honest address name: method identity
// unproven, slot+shape+donor pair are the evidence.

struct Rva00462B93Coord
{
	float x, y, z;

	void set(const Rva00462B93Coord *a)
	{
		x = a->x;
		y = a->y;
		z = a->z;
	}

	void sub(const Rva00462B93Coord *a)
	{
		x -= a->x;
		y -= a->y;
		z -= a->z;
	}
};

struct Vector300462B93
{
	float X, Y, Z;

	Vector300462B93(float x, float y, float z)
		: X(x), Y(y), Z(z)
	{
	}

	static float Dot_Product(const Vector300462B93 &a, const Vector300462B93 &b)
	{
		return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
	}
};

struct Matrix3D00462B93
{
	float Row[3][4];

	Vector300462B93 Get_X_Vector() const
	{
		return Vector300462B93(Row[0][0], Row[1][0], Row[2][0]);
	}
};

class Rva00462B93Arg
{
public:
	unsigned char m_head[8];
	Matrix3D00462B93 m_matrix08;
	Rva00462B93Coord m_coord38;
};

class Rva00462B93Info
{
public:
	unsigned char m_head[0x68];
	float m_threshold68;
};

class Rva00462B93Owner
{
public:
	unsigned char m_head[0x38];
	Rva00462B93Coord m_coord38;
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();
#define SLOT16(a) SLOT08(a##0,a##1,a##2,a##3,a##4,a##5,a##6,a##7) SLOT08(a##8,a##9,a##A,a##B,a##C,a##D,a##E,a##F)

class SlaughterHordeContain
{
public:
	SLOT16(s0) SLOT16(s1)
	virtual void s20(int); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	SLOT08(s28,s29,s2A,s2B,s2C,s2D,s2E,s2F)
	SLOT08(s30,s31,s32,s33,s34,s35,s36,s37) SLOT08(s38,s39,s3A,s3B,s3C,s3D,s3E,s3F)
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void iterateContained(void *func, void *userData, bool reverse);
	SLOT16(s69)
	virtual bool rva00462B93(const Rva00462B93Arg *arg);
};

bool SlaughterHordeContain::rva00462B93(const Rva00462B93Arg *arg)
{
	if (arg == 0)
		return false;

	const Rva00462B93Info *info = *(Rva00462B93Info *const *)((const char *)this - 0x1c);
	if (info->m_threshold68 < 0.0f)
		return false;

	const Rva00462B93Owner *owner = *(Rva00462B93Owner *const *)((const char *)this - 0x18);
	if (arg->m_coord38.z - owner->m_coord38.z > info->m_threshold68)
		return false;

	Vector300462B93 dir = arg->m_matrix08.Get_X_Vector();
	Rva00462B93Coord delta;
	delta.set(&owner->m_coord38);
	delta.sub(&arg->m_coord38);
	delta.z = 0.0f;

	if (Vector300462B93::Dot_Product(dir, Vector300462B93(delta.x, delta.y, delta.z)) < 0.0f)
		return false;

	return true;
}
