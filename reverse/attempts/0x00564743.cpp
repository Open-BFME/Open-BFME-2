// ?rva00564743@Rva005646BC@@UAEXXZ
// partial score=0.7868 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /arch:SSE
// ?rva00564743@Rva005646BC@@UAEXXZ, retail 0x00564743, 443 bytes.
// Leaf: vtable slot 1 of Rva005646BC class; terrain-collision FX check via
// TheTerrainLogic ground height, identity Matrix3D, atan2f/cos/sin orient,
// FXList::doFXPos, flags at +0x20/+0x1c/+0xC. Evidence: calls atan2f 0x422CD,
// ji thunks 0x62920A/0x629216, doFXPos 0x94C29; data TheTerrainLogic, g_Va00BBB8D8.
#include <math.h>

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D
{
public:
	float m[12];
};

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx, float speed, const Coord3D *secondary);
};

class TerrainLogic
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual float getGroundHeight(float x, float y, void *n) const;
};

extern TerrainLogic *TheTerrainLogic;
extern float g_Va00BBB8D8;
extern "C" float __cdecl atan2f(float y, float x);

struct Particle
{
	char m_pad0[0x10];
	float m_10;
	float m_14;
	char m_pad18[4];
	float m_1c;
	float m_20;
	float m_24;
	char m_pad28[0x54 - 0x28];
	int m_54;
};

class Rva005646BC
{
public:
	virtual ~Rva005646BC();
	virtual void rva00564743();
public:
	Particle *m_04;
	int m_08;
	bool m_0c;
	char m_pad0d[3];
	int m_10pad;
	float m_14;
	const FXList *m_18;
	bool m_1c;
	char m_pad1d[3];
	bool m_20;
};

// ?rva00564743@Rva005646BC@@UAEXXZ present-unmatched
void Rva005646BC::rva00564743()
{
	if (!m_20)
		return;
	if (!m_18)
		return;
	TerrainLogic *tl = TheTerrainLogic;
	Particle *p = m_04;
	if (tl->getGroundHeight(p->m_1c, p->m_20, 0) < p->m_24)
		return;
	Matrix3D mtx;
	mtx.m[0] = g_Va00BBB8D8;
	mtx.m[1] = 0.0f;
	mtx.m[2] = 0.0f;
	mtx.m[3] = 0.0f;
	mtx.m[4] = 0.0f;
	mtx.m[5] = g_Va00BBB8D8;
	mtx.m[6] = 0.0f;
	mtx.m[7] = 0.0f;
	mtx.m[8] = 0.0f;
	mtx.m[9] = 0.0f;
	mtx.m[10] = g_Va00BBB8D8;
	mtx.m[11] = 0.0f;
	if (m_1c)
	{
		float angle = atan2f(m_04->m_14, m_04->m_10);
		float c = (float)cos((double)angle);
		float s = (float)sin((double)angle);
		float m0 = mtx.m[0];
		float m1 = mtx.m[1];
		float m4 = mtx.m[4];
		float m5 = mtx.m[5];
		float m8 = mtx.m[8];
		float m9 = mtx.m[9];
		mtx.m[0] = c * m0 + s * m1;
		mtx.m[1] = c * m1 - s * m0;
		mtx.m[4] = c * m4 + s * m5;
		mtx.m[5] = c * m5 - s * m4;
		mtx.m[8] = c * m8 + s * m9;
		mtx.m[9] = c * m9 - s * m8;
	}
	Coord3D pos;
	Coord3D *src = (Coord3D *)((char *)m_04 + 0x1c);
	pos.x = src->x;
	pos.y = src->y;
	pos.z = src->z + m_14;
	FXList::doFXPos(m_18, &pos, &mtx, 0.0f, 0);
	m_20 = false;
	if (m_0c)
		m_04->m_54 = 1;
}
