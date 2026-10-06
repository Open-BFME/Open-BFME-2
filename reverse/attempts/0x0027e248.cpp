// ?rva0027E248@Rva0027E248@@QAEXPAUCoord3D@@MPAVRva0027D30D@@_NH@Z
// partial score=0.96 date=2026-10-06
// cl: /O1 /MD /arch:SSE /G7
// ?rva0027E248@Rva0027E248@@QAEXPAUCoord3D@@MPAVRva0027D30D@@_NH@Z, retail 0x0027E248, 683 bytes.
// Grid query over 50-wide short grid at +0x588 with object array +0x578/+0x57c.
// Bounds from slot 0x28 are Region3D loX loY loZ hiX hiY hiZ (Z unused for 2D
// grid) which explains frame 0x34 and gaps at -0x2c/-0x20; floor/ceil to cell
// range, walks cells and short-linked chain at +0x2e, radius check then rowed
// ?rva0027D30D@Rva0027D30D@@QAEXPAUCoord3D@@H@Z. Evidence: caller 0x0027F171,
// TerrainLogic getExtent Region3D precedent, grid width 0x32 stride 0x64.
struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Region3D
{
	float loX;
	float loY;
	float loZ;
	float hiX;
	float hiY;
	float hiZ;
};

struct GridEntry
{
	float x;
	float y;
	float z;
	int unk0c;
	char pad10[8];
	unsigned char flag18;
	char pad19[19];
	unsigned char flag2c;
	unsigned char flag2d;
	short next;
};

class Rva0027D30D
{
public:
	void rva0027D30D(Coord3D *p, int dummy);
};

extern float g_00BCEAFC;
extern float g_00BCEAF8;
extern "C" __declspec(dllimport) double __cdecl floor(double x);
extern "C" __declspec(dllimport) double __cdecl ceil(double x);

// Proven x87 blocker: plain (int) emits __ftol2 under /O1, retail uses
// fld/fistp (see Rva003641AEFinish.cpp precedent). Inline asm helper only.
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

class Rva0027E248
{
public:
	virtual void _s00();
	virtual void _s01();
	virtual void _s02();
	virtual void _s03();
	virtual void _s04();
	virtual void _s05();
	virtual void _s06();
	virtual void _s07();
	virtual void _s08();
	virtual void _s09();
	virtual void getBounds(Region3D *out);
	void rva0027E248(Coord3D *center, float radius, Rva0027D30D *out, bool flag, int mode);
private:
	char _pad04[0x578 - 4];
	GridEntry **m_base;
	GridEntry **m_end;
	char _pad580[8];
	short m_grid[1];
};

void Rva0027E248::rva0027E248(Coord3D *center, float radius, Rva0027D30D *out, bool flag, int mode)
{
	int count = (int)(m_end - m_base);
	if (count == 0)
		return;
	float eps = g_00BCEAFC;
	radius += eps;
	Region3D b;
	getBounds(&b);
	float minX = center->x - radius;
	float minY = center->y - radius;
	if (b.loX > minX)
		minX = b.loX;
	if (b.loY > minY)
		minY = b.loY;
	if (minX > b.hiX)
		minX = b.hiX;
	if (minY > b.hiY)
		minY = b.hiY;
	int xmin;
	int ymin;
	float f_floor;
	float f_ceil;
	f_floor = (float)floor((double)((minX - b.loX) / (b.hiX - b.loX) * g_00BCEAF8));
	xmin = fast_float2long_round(f_floor);
	f_floor = (float)floor((double)((minY - b.loY) / (b.hiY - b.loY) * g_00BCEAF8));
	ymin = fast_float2long_round(f_floor);
	float maxY;
	float maxX;
	maxX = center->x + radius;
	maxY = center->y + radius;
	if (b.loX > maxX)
		maxX = b.loX;
	if (b.loY > maxY)
		maxY = b.loY;
	if (maxX > b.hiX)
		maxX = b.hiX;
	if (maxY > b.hiY)
		maxY = b.hiY;
	int xmax;
	int ymax;
	f_ceil = (float)ceil((double)((maxX - b.loX) / (b.hiX - b.loX) * g_00BCEAF8));
	xmax = fast_float2long_round(f_ceil);
	f_ceil = (float)ceil((double)((maxY - b.loY) / (b.hiY - b.loY) * g_00BCEAF8));
	ymax = fast_float2long_round(f_ceil);
	for (int x = xmin; x < xmax; ++x) {
		if (ymin >= ymax)
			continue;
		short *cell = &m_grid[ymin * 50 + x];
		int remaining = ymax - ymin;
		do {
			int idx = *cell;
			while (idx != -1) {
				if (idx < 0 || idx >= count)
					break;
				GridEntry *obj = m_base[idx];
				if (obj->unk0c == 0) {
					idx = obj->next;
					continue;
				}
				if (flag && obj->flag18) {
					idx = obj->next;
					continue;
				}
				if (mode == 1) {
					if (!obj->flag2c) {
						idx = obj->next;
						continue;
					}
				} else if (mode == 2) {
					if (!obj->flag2d) {
						idx = obj->next;
						continue;
					}
				}
				float dx = obj->x - center->x;
				float dy = obj->y - center->y;
				float dz = obj->z - center->z;
				float dist2 = dx * dx + dy * dy + dz * dz;
				float rad2 = radius * radius;
				if (rad2 > dist2)
					out->rva0027D30D((Coord3D *)obj, (int)center);
				idx = obj->next;
			}
			cell += 50;
		} while (--remaining != 0);
	}
}
