// ?rva0027DF9D@Rva0027DF9D@@QAEXPAUCoord3D@@MPAVRva0027D244@@_NH@Z
// partial score=0.93 date=2026-10-06
// cl: /O1 /MD /arch:SSE /G7
// ?rva0027DF9D@Rva0027DF9D@@QAEXPAUCoord3D@@MPAVRva0027D244@@_NH@Z, retail 0x0027DF9D, 683 bytes.
// Grid query over 50-wide short grid at +0x588 with object array +0x578/+0x57C.
// Bounds from slot 0x28 are Region3D loX loY loZ hiX hiY hiZ (Z unused for 2D
// grid); floor/ceil to cell range, walks cells and short-linked chain at +0x2e,
// radius check then rowed ?rva0027D276@Rva0027D244@@QAEXPAV1@0@Z.
// Evidence: caller 0x0027F13C builds Rva0027D244 struct then calls with (point float radius out 0 2),
// slot 0x28 like Rva0027D0D6 fetchBounds, grid width 0x32 stride 0x64, entry layout like Rva0027C230.
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

class Rva0027D244
{
public:
	void rva0027D276(Rva0027D244 *a, Rva0027D244 *b);
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

class Rva0027DF9D
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
	void rva0027DF9D(Coord3D *center, float radius, Rva0027D244 *out, bool flag, int mode);
private:
	char _pad04[0x578 - 4];
	GridEntry **m_base;
	GridEntry **m_end;
	char _pad580[8];
	short m_grid[1];
};

void Rva0027DF9D::rva0027DF9D(Coord3D *center, float radius, Rva0027D244 *out, bool flag, int mode)
{
	int count = (int)(m_end - m_base);
	if (count == 0)
		return;
	radius = radius + g_00BCEAFC;
	Region3D b;
	getBounds(&b);
	float minY = center->y - radius;
	float minX = center->x - radius;
	if (b.loX > minX)
		minX = b.loX;
	if (b.loY > minY)
		minY = b.loY;
	if (minX > b.hiX)
		minX = b.hiX;
	if (minY > b.hiY)
		minY = b.hiY;
	int xmin = fast_float2long_round((float)floor((double)((minX - b.loX) / (b.hiX - b.loX) * g_00BCEAF8)));
	int ymin = fast_float2long_round((float)floor((double)((minY - b.loY) / (b.hiY - b.loY) * g_00BCEAF8)));
	float maxX = center->x + radius;
	float maxY = center->y + radius;
	if (b.loX > maxX)
		maxX = b.loX;
	if (b.loY > maxY)
		maxY = b.loY;
	if (maxX > b.hiX)
		maxX = b.hiX;
	if (maxY > b.hiY)
		maxY = b.hiY;
	maxX = (float)ceil((double)((maxX - b.loX) / (b.hiX - b.loX) * g_00BCEAF8));
	int xmax = fast_float2long_round(maxX);
	maxY = (float)ceil((double)((maxY - b.loY) / (b.hiY - b.loY) * g_00BCEAF8));
	int ymax = fast_float2long_round(maxY);
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
					out->rva0027D276((Rva0027D244 *)obj, (Rva0027D244 *)center);
				idx = obj->next;
			}
			cell += 50;
		} while (--remaining != 0);
	}
}
