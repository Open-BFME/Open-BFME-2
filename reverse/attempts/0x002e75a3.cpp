// ?rva002E75A3@Pathfinder@@QAEXPAUCoord3D@@0@Z
// partial score=0.8917 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
// ?rva002E75A3@Pathfinder@@QAEXPAUCoord3D@@0@Z @0x002E75A3 304B
// Evidence: Pathfinder m_extent at this+0x14 (same as Rva002E7917 clamp TU); ClipLine2D row 0x0025F406; callers 0x002F722B 0x002F73FC 0x002F96CB; INV scale 0x7C2424 and cell->world *10+offset.
// ?rva002E75A3@Pathfinder@@QAEXPAUCoord3D@@0@Z present-unmatched

typedef int Int;
typedef float Real;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

extern "C" float INV;
extern float g_00BC7838;

extern "C" __declspec(dllimport) double __cdecl floor(double);

static __forceinline Real fast_floor(Real f)
{
	return (Real)floor((double)f);
}

static __forceinline long fast_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define R2I(x) (fast_round(fast_floor(x)))

bool __cdecl ClipLine2D(ICoord2D *p1, ICoord2D *p2, ICoord2D *c1, ICoord2D *c2, IRegion2D *clipRegion);

class Pathfinder
{
public:
	void rva002E75A3(Coord3D *a, Coord3D *b);
private:
	unsigned char m_pad[0x14];
	IRegion2D m_extent;
};

// ?rva002E75A3@Pathfinder@@QAEXPAUCoord3D@@0@Z present-unmatched
void Pathfinder::rva002E75A3(Coord3D *a, Coord3D *b)
{
	ICoord2D p2;
	ICoord2D p1;
	IRegion2D *clip = &m_extent;
	ICoord2D c2;
	ICoord2D c1;
	p1.x = R2I(a->x * INV);
	p1.y = R2I(INV * a->y);
	p2.x = R2I(INV * b->x);
	p2.y = R2I(INV * b->y);
	if (!ClipLine2D(&p1, &p2, &c1, &c2, clip))
		return;
	float base = g_00BC7838;
	if (p1.x != c1.x || c1.y != p1.y) {
		a->x = (Real)(c1.x * 10) + base;
		a->y = (Real)(c1.y * 10) + base;
	}
	if (p2.x != c2.x || c2.y != p2.y) {
		b->x = (Real)(c2.x * 10) + base;
		b->y = (Real)(c2.y * 10) + base;
	}
}
