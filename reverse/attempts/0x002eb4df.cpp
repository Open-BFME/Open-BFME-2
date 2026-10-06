// ?rva002EB4DF@Pathfinder@@QAEHPBUICoord2D@@0MHPAX@Z
// partial score=0.8 date=2026-10-06
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Dump lane range 13: ?rva002EB4DF @0x002EB4DF 406B. Rotated-rectangle cell
// collector: when the (w,h) extent at a2 is exactly (1,1), resolve one cell
// through Pathfinder::getCell and filter it through the 0x002E7E26 worker;
// otherwise build the four rotated corners (fsincos of angle, half extents
// scaled by the pooled 0.5 at 0x00BC26F0; exact-0.0f takes the axis-aligned
// integer path) and hand the corner arrays to the 0x002E8773 worker.
// Identities of the two workers unproven; classes address-derived.
struct ICoord2D
{
	int x;
	int y;
};
enum PathfindLayerEnum
{
	PF_LAYER_0 = 0
};
class PathfindCell
{
public:
	char m_pad[0x10];
};
struct Rva002E7E26
{
	int rva002E7E26(void *cell, int x, int y);
};
struct Rva002E8773
{
	int rva002E8773(int *xs, int *ys, int n, int d, void *e);
};
class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, int x, int y);
	int rva002EB4DF(const ICoord2D *a1, const ICoord2D *a2, float angle, int a4, void *a5);
};
// ?rva002EB4DF@Pathfinder@@QAEHPBUICoord2D@@0MHPAX@Z @0x002EB4DF 406B.
int Pathfinder::rva002EB4DF(const ICoord2D *a1, const ICoord2D *a2, float angle, int a4, void *a5)
{
	int v = a2->x;
	if (v == 1 && a2->y == v) {
		PathfindCell *cell = getCell((PathfindLayerEnum)a4, a1->x, a1->y);
		if (cell != 0)
			return ((Rva002E7E26 *)a5)->rva002E7E26(cell, a1->x, a1->y);
		return 0;
	}
	int xs[4];
	int ys[4];
	if (angle != 0.0f) {
		float c;
		float s;
		__asm {
			fld angle
			fsincos
			fstp s
			fstp c
		}
		float x = (float)a1->x;
		float y = (float)a1->y;
		float half = 0.5f;
		float w = (float)a2->x;
		float h = (float)a2->y;
		float hh = h * half;
		float hw = w * half;
		float hhc = hh * c;
		float hhs = hh * s;
		float hws = hw * s;
		float hwc = hw * c;
		float tx = x - hws;
		float ty = y - hhs;
		xs[0] = (int)(hhc + tx);
		ys[0] = (int)(ty - hwc);
		xs[1] = (int)(hhc + hws + x);
		ys[1] = (int)(hwc + ty);
		xs[2] = (int)(hws + x - hhc);
		ys[2] = (int)(hwc + hhs + y);
		xs[3] = (int)(tx - hhc);
		ys[3] = (int)(hhs + y - hwc);
	} else {
		int tw = v / 2;
		int h = a2->y;
		int th = h / 2;
		int x0 = a1->x - tw;
		int y0 = a1->y - th;
		int x1 = x0 + v - 1;
		int y1 = y0 + h - 1;
		xs[0] = x0;
		xs[1] = x1;
		xs[2] = x1;
		xs[3] = x0;
		ys[0] = y0;
		ys[1] = y0;
		ys[2] = y1;
		ys[3] = y1;
	}
	return ((Rva002E8773 *)this)->rva002E8773(xs, ys, 4, a4, a5);
}
