// ?Rva0036CBF9Rotate@@YAXPBUCoord3D@@0PAUCoord2D@@@Z
// partial score=0.75 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Op /DNDEBUG /MD
// Retail 0x0036CBF9, 129 bytes: cdecl group-offset rotation called from
// computeGoal (0x345E53) and the AIGroup formation code (0x36D744,
// 0x3716C6, 0x3717B0, 0x3718AD). The first half (dir = to - from, z = 0,
// Coord3D::normalize at 0x35B6) matches exactly. Under /Op the second half
// differs only in register allocation: retail loads dir.x once into xmm1
// and reuses it for x*dir.x and dir.x*y (6 xmm regs); every source shape
// tried (scalar/Coord2D perp, product temporaries in all orders, inline
// helpers) reads dir.x from memory twice. Without /Op, two movaps go too.
typedef float Real;
struct Coord2D { Real x, y; };
struct Coord3D { Real x, y, z; void normalize(); };

void Rva0036CBF9Rotate(const Coord3D *from, const Coord3D *to, Coord2D *offset)
{
	Coord3D dir;
	dir.x = to->x;
	dir.y = to->y;
	dir.x -= from->x;
	dir.y -= from->y;
	dir.z = 0.0f;
	dir.normalize();

	Coord2D perp;
	perp.x = -dir.y;
	perp.y = dir.x;

	Real y = offset->y;
	Real x = offset->x;
	Real a = x * dir.x;
	Real b = x * dir.y;
	Real c = y * perp.x;
	Real d = y * perp.y;
	offset->x = a + c;
	offset->y = d + b;
}
