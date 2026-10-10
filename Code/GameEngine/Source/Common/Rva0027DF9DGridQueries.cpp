// cl: /O1 /G7 /arch:SSE /MD /ICode/Libraries/Include/Lib
//
// Three byte-twin grid queries of one owner class (683 bytes each):
//   ?rva0027DF9D@Rva0027DF9D@@QAEXPAUCoord3D@@MPAVRva0027D244@@_NH@Z  0x0027DF9D..0x0027E248
//   ?rva0027E248@Rva0027E248@@QAEXPAUCoord3D@@MPAVRva0027D30D@@_NH@Z  0x0027E248..0x0027E4F3
//   ?rva0027E4F3@Rva0027E4F3@@QAEXPAUCoord3D@@MPAVRva0027D347@@_NH@Z  0x0027E4F3..0x0027E79E
// Each walks the 50x50 cell grid of short chain heads at +0x588 over the
// owner's object array (+0x578/+0x57C): the bounds come from virtual slot 10
// (+0x28) as a Region3D, the query square (radius + 7) is clamped to it and
// turned into cell ranges with floor and ceil of 49.9 cells per extent; every
// live entry (+0x0C) not excluded by the flag (+0x18) or the mode (1: +0x2C,
// 2: +0x2D) and inside the radius goes to the result object: rowed
// Rva0027D244::rva0027D276 (0x0027D276), Rva0027D30D::rva0027D30D
// (0x0027D30D) and Rva0027D347::rva0027D347 (0x0027D347). Callers:
// Rva0027F13CHost::rva0027F13C (0x0027F13C), BfmeThingCME::rva0027F171
// (0x0027F171) and TerrainLogic::rva0027F28E (0x0027F28E), all on their own
// this (ECX), with (point radius result 0 mode). The twin 0x0027E79E feeds
// Rva0027D35F the same way.
// The cell indices round through BaseType's REAL_TO_INT_FLOOR / _CEIL shape
// with math.h's inline floorf and ceilf; one x and one y float carry first
// the low corner and then the high corner, and the ceil results go back into
// them, which is what gives retail's two float slots and x87 store order.
#include "Coord3D.h"
#include <math.h>

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
	int live;			// +0x0C
	char pad10[8];
	unsigned char excluded;		// +0x18
	char pad19[19];
	unsigned char mode1;		// +0x2C
	unsigned char mode2;		// +0x2D
	short next;			// +0x2E
};

class Rva0027D244
{
public:
	void rva0027D276(Rva0027D244 *a, Rva0027D244 *b);
};

class Rva0027D30D
{
public:
	void rva0027D30D(Coord3D *p, int dummy);
};

struct Rva0027D347Arg;

class Rva0027D347
{
public:
	void rva0027D347(Rva0027D347Arg *a, int dummy);
};

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

// The grid owner's layout as the three queries read it.
class Rva0027GridOwner
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
	virtual void getBounds(Region3D *out);	// +0x28
protected:
	char _pad04[0x578 - 4];
	GridEntry **m_base;			// +0x578
	GridEntry **m_end;			// +0x57C
	char _pad580[8];
	short m_grid[1];			// +0x588, 50 x 50
};

class Rva0027DF9D : public Rva0027GridOwner
{
public:
	void rva0027DF9D(Coord3D *center, float radius, Rva0027D244 *out, bool flag, int mode);
};

class Rva0027E248 : public Rva0027GridOwner
{
public:
	void rva0027E248(Coord3D *center, float radius, Rva0027D30D *out, bool flag, int mode);
};

class Rva0027E4F3 : public Rva0027GridOwner
{
public:
	void rva0027E4F3(Coord3D *center, float radius, Rva0027D347 *out, bool flag, int mode);
};

void Rva0027DF9D::rva0027DF9D(Coord3D *center, float radius, Rva0027D244 *out, bool flag, int mode)
{
	int count = (int)(m_end - m_base);
	if (count == 0)
		return;
	radius = 7.0f + radius;
	Region3D b;
	getBounds(&b);
	float px = center->x - radius;
	float py = center->y - radius;
	if (b.loX > px)
		px = b.loX;
	if (b.loY > py)
		py = b.loY;
	if (px > b.hiX)
		px = b.hiX;
	if (py > b.hiY)
		py = b.hiY;
	int xmin = fast_float2long_round(floorf((px - b.loX) / (b.hiX - b.loX) * 49.9f));
	int ymin = fast_float2long_round(floorf((py - b.loY) / (b.hiY - b.loY) * 49.9f));
	px = center->x + radius;
	py = center->y + radius;
	if (b.loX > px)
		px = b.loX;
	if (b.loY > py)
		py = b.loY;
	if (px > b.hiX)
		px = b.hiX;
	if (py > b.hiY)
		py = b.hiY;
	px = ceilf((px - b.loX) / (b.hiX - b.loX) * 49.9f);
	int xmax = fast_float2long_round(px);
	py = ceilf((py - b.loY) / (b.hiY - b.loY) * 49.9f);
	int ymax = fast_float2long_round(py);
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
				if (obj->live == 0) {
					idx = obj->next;
					continue;
				}
				if (flag && obj->excluded) {
					idx = obj->next;
					continue;
				}
				if (mode == 1) {
					if (!obj->mode1) {
						idx = obj->next;
						continue;
					}
				} else if (mode == 2) {
					if (!obj->mode2) {
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

void Rva0027E248::rva0027E248(Coord3D *center, float radius, Rva0027D30D *out, bool flag, int mode)
{
	int count = (int)(m_end - m_base);
	if (count == 0)
		return;
	radius = 7.0f + radius;
	Region3D b;
	getBounds(&b);
	float px = center->x - radius;
	float py = center->y - radius;
	if (b.loX > px)
		px = b.loX;
	if (b.loY > py)
		py = b.loY;
	if (px > b.hiX)
		px = b.hiX;
	if (py > b.hiY)
		py = b.hiY;
	int xmin = fast_float2long_round(floorf((px - b.loX) / (b.hiX - b.loX) * 49.9f));
	int ymin = fast_float2long_round(floorf((py - b.loY) / (b.hiY - b.loY) * 49.9f));
	px = center->x + radius;
	py = center->y + radius;
	if (b.loX > px)
		px = b.loX;
	if (b.loY > py)
		py = b.loY;
	if (px > b.hiX)
		px = b.hiX;
	if (py > b.hiY)
		py = b.hiY;
	px = ceilf((px - b.loX) / (b.hiX - b.loX) * 49.9f);
	int xmax = fast_float2long_round(px);
	py = ceilf((py - b.loY) / (b.hiY - b.loY) * 49.9f);
	int ymax = fast_float2long_round(py);
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
				if (obj->live == 0) {
					idx = obj->next;
					continue;
				}
				if (flag && obj->excluded) {
					idx = obj->next;
					continue;
				}
				if (mode == 1) {
					if (!obj->mode1) {
						idx = obj->next;
						continue;
					}
				} else if (mode == 2) {
					if (!obj->mode2) {
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

void Rva0027E4F3::rva0027E4F3(Coord3D *center, float radius, Rva0027D347 *out, bool flag, int mode)
{
	int count = (int)(m_end - m_base);
	if (count == 0)
		return;
	radius = 7.0f + radius;
	Region3D b;
	getBounds(&b);
	float px = center->x - radius;
	float py = center->y - radius;
	if (b.loX > px)
		px = b.loX;
	if (b.loY > py)
		py = b.loY;
	if (px > b.hiX)
		px = b.hiX;
	if (py > b.hiY)
		py = b.hiY;
	int xmin = fast_float2long_round(floorf((px - b.loX) / (b.hiX - b.loX) * 49.9f));
	int ymin = fast_float2long_round(floorf((py - b.loY) / (b.hiY - b.loY) * 49.9f));
	px = center->x + radius;
	py = center->y + radius;
	if (b.loX > px)
		px = b.loX;
	if (b.loY > py)
		py = b.loY;
	if (px > b.hiX)
		px = b.hiX;
	if (py > b.hiY)
		py = b.hiY;
	px = ceilf((px - b.loX) / (b.hiX - b.loX) * 49.9f);
	int xmax = fast_float2long_round(px);
	py = ceilf((py - b.loY) / (b.hiY - b.loY) * 49.9f);
	int ymax = fast_float2long_round(py);
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
				if (obj->live == 0) {
					idx = obj->next;
					continue;
				}
				if (flag && obj->excluded) {
					idx = obj->next;
					continue;
				}
				if (mode == 1) {
					if (!obj->mode1) {
						idx = obj->next;
						continue;
					}
				} else if (mode == 2) {
					if (!obj->mode2) {
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
					out->rva0027D347((Rva0027D347Arg *)obj, (int)center);
				idx = obj->next;
			}
			cell += 50;
		} while (--remaining != 0);
	}
}
