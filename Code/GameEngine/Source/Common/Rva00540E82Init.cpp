// cl: /Ob0
//
// ??0Rva00540E82@@QAE@XZ, retail 0x00540E82 27B.
// Constructor: int at +0 = 2, floats at +4 +8 +0xC = 0.0 via xorps/movss.
// Evidence: no calls; callers at 0x00540FFE (outer init constructs +4
// subobject after zeroing +0) and 0x00542351 (stack temp in waypoint
// array loop); unblocks 0x00540FF6 and 0x00542314.
// ??0Rva00540FF6@@QAE@XZ, retail 0x00540FF6 16B: outer ctor with int at +0
// = 0 and inner Rva00540E82 at +4 via rowed ctor. /Ob0 keeps the inner
// call from inlining so retail keeps lea ecx,[edx+4] call.
// ??0Rva00540FDB@@QAE@HABURegion3D@@@Z, retail 0x00540FDB 27B: ctor with
// int at +0 and Region3D at +4 via rowed copy ctor 0x0009AC04.
// ??0Rva00540E9D@@QAE@ABURva00540E9DSrc@@H@Z, retail 0x00540E9D 32B:
// ctor with 12B src at +4..+0xC and int at +0.
// ??0Rva00540D67@@QAE@XZ, retail 0x00540D67 45B: sibling of 0x00540E82
// with int 2 at +0, zeros at +4 +8 +0xC +0x10, global float 0x00BC74F0
// at +0x14.
// ??0Rva00540FCB@@QAE@XZ, retail 0x00540FCB 16B: outer ctor with int at +0
// = 0 and inner Rva00540D67 at +4 via rowed ctor. /Ob0 keeps the inner
// call from inlining so retail keeps lea ecx,[edx+4] call.

class Rva00540E82
{
public:
	Rva00540E82();
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
};

Rva00540E82::Rva00540E82() : m_00(2), m_04(0.0f), m_08(0.0f), m_0c(0.0f)
{
}

class Rva00540FF6
{
public:
	Rva00540FF6();
	int m_00;
	Rva00540E82 m_04;
};

Rva00540FF6::Rva00540FF6() : m_00(0)
{
}

struct Region3D
{
	Region3D(const Region3D &that);
};

class Rva00540FDB
{
public:
	Rva00540FDB(int v, const Region3D &r);
	int m_00;
	Region3D m_04;
};

Rva00540FDB::Rva00540FDB(int v, const Region3D &r) : m_00(v), m_04(r)
{
}

struct Rva00540E9DSrc
{
	int a;
	int b;
	int c;
};

class Rva00540E9D
{
public:
	Rva00540E9D(const Rva00540E9DSrc &src, int v);
	int m_00;
	Rva00540E9DSrc m_04;
};

Rva00540E9D::Rva00540E9D(const Rva00540E9DSrc &src, int v) : m_00(v)
{
	m_04.a = src.a;
	m_04.b = src.b;
	m_04.c = src.c;
}

extern float g_Va00BC74F0;
// g_Va00BC74F0: matched references place it at VA 0xbc74f0 (retail .rdata value 0.87266463f).
float g_Va00BC74F0 = 0.87266463f;

class Rva00540D67
{
public:
	Rva00540D67();
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
};

Rva00540D67::Rva00540D67() : m_00(2), m_04(0.0f), m_08(0.0f), m_0c(0.0f), m_10(0.0f), m_14(g_Va00BC74F0)
{
}

class Rva00540FCB
{
public:
	Rva00540FCB();
	int m_00;
	Rva00540D67 m_04;
};

Rva00540FCB::Rva00540FCB() : m_00(0)
{
}

// ??0Rva00541006@@QAE@HABURegion2D@@@Z @0x00541006 27B: ctor with int at +0
// and Region2D at +4 via rowed copy ctor 0x0004254E. Evidence: same shape
// as sibling ??0Rva00540FDB@@QAE@HABURegion3D@@@Z 27B in this TU; caller at
// 0x0054211B passes (int, Region2D) and stores result stride 0x14.
struct Region2D
{
	Region2D(const Region2D &that);
};

class Rva00541006
{
public:
	Rva00541006(int v, const Region2D &r);
	int m_00;
	Region2D m_04;
};

Rva00541006::Rva00541006(int v, const Region2D &r) : m_00(v), m_04(r)
{
}

// ?rva00540EBD@@YA?AVRva00540E9D@@MPAXPAXPAVRva005C71ADView@@PAXPAXPAXPAXPAX@Z,
// retail 0x00540EBD. Target evidence: its only caller at 0x00541BB7 passes a
// float, eight pointers and a context; the body transforms a 12-byte record
// through 0x005C71AD and constructs the rowed Rva00540E9D from that result
// and the context's first dword. Original function name remains unresolved.
class Rva005C71ADView
{
public:
	void *rva005C71AD(void *out, float value, void *a, void *b, void *c,
		void *d, void *e, void *f, void *g, void *h);
};

Rva00540E9D rva00540EBD(float value, void *arg10, void *arg14,
	Rva005C71ADView *context, void *arg1c, void *arg20, void *arg24,
	void *arg28, void *arg2c)
{
	Rva00540E9DSrc transformed;
	return Rva00540E9D(
		*(Rva00540E9DSrc *)context->rva005C71AD(
			&transformed, value, (char *)arg10 + 4, arg14,
			(char *)context + 4, arg1c, (char *)arg20 + 4, arg24,
			(char *)arg28 + 4, arg2c),
		*(int *)context);
}
