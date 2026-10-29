// cl: /EHsc /O1 /G7 /arch:SSE /MD /ICode/Libraries/Include/Lib
//
// Five byte-twin grid queries of one owner class (683 bytes each):
//   ?rva0027DCF2@Rva0027DCF2@@QAEXPAUCoord3D@@MPAVRva0027D244@@_NH@Z  0x0027DCF2..0x0027DF9D
//   ?rva0027DF9D@Rva0027DF9D@@QAEXPAUCoord3D@@MPAVRva0027D244@@_NH@Z  0x0027DF9D..0x0027E248
//   ?rva0027E248@Rva0027E248@@QAEXPAUCoord3D@@MPAVRva0027D30D@@_NH@Z  0x0027E248..0x0027E4F3
//   ?rva0027E4F3@Rva0027E4F3@@QAEXPAUCoord3D@@MPAVRva0027D347@@_NH@Z  0x0027E4F3..0x0027E79E
//   ?rva0027E79E@Rva0027E79E@@QAEXPAUCoord3D@@MPAVRva0027D35F@@_NH@Z  0x0027E79E..0x0027EA49
// Each walks the 50x50 cell grid of short chain heads at +0x588 over the
// owner's object array (+0x578/+0x57C): the bounds come from virtual slot 10
// (+0x28) as a Region3D, the query square (radius + 7) is clamped to it and
// turned into cell ranges with floor and ceil of 49.9 cells per extent; every
// live entry (+0x0C) not excluded by the flag (+0x18) or the mode (1: +0x2C,
// 2: +0x2D) and inside the radius goes to the result object: rowed
// Rva0027D244::rva0027D276 (0x0027D276), Rva0027D30D::rva0027D30D
// (0x0027D30D), Rva0027D347::rva0027D347 (0x0027D347),
// Rva0027D244::rva0027D1EF (0x0027D1EF; 0x0027DCF2, called from 0x0027F0FB,
// 0x0027F12F and 0x00283DBC) and Rva0027D35F::rva0027D35F (0x0027D35F;
// 0x0027E79E, called from 0x0027F2CD). Callers:
// Rva0027F13CHost::rva0027F13C (0x0027F13C), BfmeThingCME::rva0027F171
// (0x0027F171) and TerrainLogic::rva0027F28E (0x0027F28E), all on their own
// this (ECX), with (point radius result 0 mode).
// The cell indices round through BaseType's REAL_TO_INT_FLOOR / _CEIL shape
// with math.h's inline floorf and ceilf; one x and one y float carry first
// the low corner and then the high corner, and the ceil results go back into
// them, which is what gives retail's two float slots and x87 store order.
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include "Coord3D.h"
#include <math.h>

#include "Region3D.h"

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
	struct Vec12
	{
		Vec12() {}
		Vec12(const Vec12 &o) : x(o.x), y(o.y), z(o.z) {}
		float x, y, z;
	};
	Rva0027D244 *rva0027D244(int v);
	void rva0027D1EF(Rva0027D244 *a, Rva0027D244 *b);
	void rva0027D276(Rva0027D244 *a, Rva0027D244 *b);
private:
	Vec12 m_pos00;
	int m_0C;
	float m_10;
	int m_14;
	int m_18;
};
void Rva0027D244::rva0027D1EF(Rva0027D244 *a, Rva0027D244 *b)
{
	Vec12 p = b->m_pos00;
	float dx = p.x - a->m_pos00.x;
	float dy = p.y - a->m_pos00.y;
	float d2 = dx * dx + dy * dy;
	if (m_0C != 0 && !(m_10 > d2))
		return;
	m_0C = a->m_0C;
	m_pos00 = a->m_pos00;
	m_10 = d2;
	m_14 = (int)a;
}


class PolygonTrigger;
class Rva0027D30D
{
public:
	void rva0027D30D(Coord3D *pos, int dummy);
private:
	int m_count; // +0x00
	PolygonTrigger *m_trigger; // +0x04
};

struct Rva0027D347Arg;
struct Rva0027D35FArg;

class Rva0027D347
{
public:
	void rva0027D347(Rva0027D347Arg *a, int dummy);
private:
	int m_00; // +0x00
};

class Rva0027D35F
{
public:
	void rva0027D35F(Rva0027D35FArg *a, int dummy);
private:
	unsigned char m_00; // +0x00
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

class Rva0027DCF2 : public Rva0027GridOwner
{
public:
	void rva0027DCF2(Coord3D *center, float radius, Rva0027D244 *out, bool flag, int mode);
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

class Rva0027E79E : public Rva0027GridOwner
{
public:
	void rva0027E79E(Coord3D *center, float radius, Rva0027D35F *out, bool flag, int mode);
};

void Rva0027DCF2::rva0027DCF2(Coord3D *center, float radius, Rva0027D244 *out, bool flag, int mode)
{
	int count = (int)(m_end - m_base);
	if (count == 0)
		return;
	radius = 7.0f + radius;
	Region3D b;
	getBounds(&b);
	float px = center->x - radius;
	float py = center->y - radius;
	if (b.lo.x > px)
		px = b.lo.x;
	if (b.lo.y > py)
		py = b.lo.y;
	if (px > b.hi.x)
		px = b.hi.x;
	if (py > b.hi.y)
		py = b.hi.y;
	int xmin = fast_float2long_round(floorf((px - b.lo.x) / (b.hi.x - b.lo.x) * 49.9f));
	int ymin = fast_float2long_round(floorf((py - b.lo.y) / (b.hi.y - b.lo.y) * 49.9f));
	px = center->x + radius;
	py = center->y + radius;
	if (b.lo.x > px)
		px = b.lo.x;
	if (b.lo.y > py)
		py = b.lo.y;
	if (px > b.hi.x)
		px = b.hi.x;
	if (py > b.hi.y)
		py = b.hi.y;
	px = ceilf((px - b.lo.x) / (b.hi.x - b.lo.x) * 49.9f);
	int xmax = fast_float2long_round(px);
	py = ceilf((py - b.lo.y) / (b.hi.y - b.lo.y) * 49.9f);
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
					out->rva0027D1EF((Rva0027D244 *)obj, (Rva0027D244 *)center);
				idx = obj->next;
			}
			cell += 50;
		} while (--remaining != 0);
	}
}

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
	if (b.lo.x > px)
		px = b.lo.x;
	if (b.lo.y > py)
		py = b.lo.y;
	if (px > b.hi.x)
		px = b.hi.x;
	if (py > b.hi.y)
		py = b.hi.y;
	int xmin = fast_float2long_round(floorf((px - b.lo.x) / (b.hi.x - b.lo.x) * 49.9f));
	int ymin = fast_float2long_round(floorf((py - b.lo.y) / (b.hi.y - b.lo.y) * 49.9f));
	px = center->x + radius;
	py = center->y + radius;
	if (b.lo.x > px)
		px = b.lo.x;
	if (b.lo.y > py)
		py = b.lo.y;
	if (px > b.hi.x)
		px = b.hi.x;
	if (py > b.hi.y)
		py = b.hi.y;
	px = ceilf((px - b.lo.x) / (b.hi.x - b.lo.x) * 49.9f);
	int xmax = fast_float2long_round(px);
	py = ceilf((py - b.lo.y) / (b.hi.y - b.lo.y) * 49.9f);
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
	if (b.lo.x > px)
		px = b.lo.x;
	if (b.lo.y > py)
		py = b.lo.y;
	if (px > b.hi.x)
		px = b.hi.x;
	if (py > b.hi.y)
		py = b.hi.y;
	int xmin = fast_float2long_round(floorf((px - b.lo.x) / (b.hi.x - b.lo.x) * 49.9f));
	int ymin = fast_float2long_round(floorf((py - b.lo.y) / (b.hi.y - b.lo.y) * 49.9f));
	px = center->x + radius;
	py = center->y + radius;
	if (b.lo.x > px)
		px = b.lo.x;
	if (b.lo.y > py)
		py = b.lo.y;
	if (px > b.hi.x)
		px = b.hi.x;
	if (py > b.hi.y)
		py = b.hi.y;
	px = ceilf((px - b.lo.x) / (b.hi.x - b.lo.x) * 49.9f);
	int xmax = fast_float2long_round(px);
	py = ceilf((py - b.lo.y) / (b.hi.y - b.lo.y) * 49.9f);
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
	if (b.lo.x > px)
		px = b.lo.x;
	if (b.lo.y > py)
		py = b.lo.y;
	if (px > b.hi.x)
		px = b.hi.x;
	if (py > b.hi.y)
		py = b.hi.y;
	int xmin = fast_float2long_round(floorf((px - b.lo.x) / (b.hi.x - b.lo.x) * 49.9f));
	int ymin = fast_float2long_round(floorf((py - b.lo.y) / (b.hi.y - b.lo.y) * 49.9f));
	px = center->x + radius;
	py = center->y + radius;
	if (b.lo.x > px)
		px = b.lo.x;
	if (b.lo.y > py)
		py = b.lo.y;
	if (px > b.hi.x)
		px = b.hi.x;
	if (py > b.hi.y)
		py = b.hi.y;
	px = ceilf((px - b.lo.x) / (b.hi.x - b.lo.x) * 49.9f);
	int xmax = fast_float2long_round(px);
	py = ceilf((py - b.lo.y) / (b.hi.y - b.lo.y) * 49.9f);
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

void Rva0027E79E::rva0027E79E(Coord3D *center, float radius, Rva0027D35F *out, bool flag, int mode)
{
	int count = (int)(m_end - m_base);
	if (count == 0)
		return;
	radius = 7.0f + radius;
	Region3D b;
	getBounds(&b);
	float px = center->x - radius;
	float py = center->y - radius;
	if (b.lo.x > px)
		px = b.lo.x;
	if (b.lo.y > py)
		py = b.lo.y;
	if (px > b.hi.x)
		px = b.hi.x;
	if (py > b.hi.y)
		py = b.hi.y;
	int xmin = fast_float2long_round(floorf((px - b.lo.x) / (b.hi.x - b.lo.x) * 49.9f));
	int ymin = fast_float2long_round(floorf((py - b.lo.y) / (b.hi.y - b.lo.y) * 49.9f));
	px = center->x + radius;
	py = center->y + radius;
	if (b.lo.x > px)
		px = b.lo.x;
	if (b.lo.y > py)
		py = b.lo.y;
	if (px > b.hi.x)
		px = b.hi.x;
	if (py > b.hi.y)
		py = b.hi.y;
	px = ceilf((px - b.lo.x) / (b.hi.x - b.lo.x) * 49.9f);
	int xmax = fast_float2long_round(px);
	py = ceilf((py - b.lo.y) / (b.hi.y - b.lo.y) * 49.9f);
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
					out->rva0027D35F((Rva0027D35FArg *)obj, (int)center);
				idx = obj->next;
			}
			cell += 50;
		} while (--remaining != 0);
	}
}

// Native283D70..283E97 / WB C478B0: materialize the nearest tree record
// as a neutral-player object, consume its record, or find an alive kind86
// object within10. The original method name is not established.
// The real query and85-byte callback must both be visible: their nonescaping
// result lets MSVC reuse its24-byte stack slot for the16-byte CreateMask.
// Reset27D098 stays visible to preserve the record ID in EDX across its call.
// The mask is initialized before reading the player chain, as WB shows.
#include <string.h>

class Object;
class Player;
class Team;
class ThingTemplate;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	Rva000421C8 *link(Rva000421C8 *next); // 0x00625790
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next; // +0x04
};

class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

struct Rva00045411BitSet
{
public:
	Rva00045411BitSet(int unused, int bit) throw(); // 0x00045411
	unsigned int m_bits[7]; // +0x00
};
template<int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;




#include "PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

class Rva0027D098
{
public:
	void rva0027D098();
	float m_00; // +0x00
	float m_04; // +0x04
	float m_08; // +0x08
	int m_0C; // +0x0C
	int m_10; // +0x10
	const ThingTemplate *m_14; // +0x14
	unsigned char m_18; // +0x18
	char m_pad19[0x3];
	float m_1C; // +0x1C
	float m_20; // +0x20
	float m_24; // +0x24
	int m_28; // +0x28
	unsigned char m_2C; // +0x2C
	unsigned char m_2D; // +0x2D
	char m_pad2E[0x2];
};

void Rva0027D098::rva0027D098()
{
	m_00 = 0.0f;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0.0f;
	m_20 = 0.0f;
	m_24 = 0.0f;
	m_28 = 1;
	m_2C = 1;
	m_2D = 1;
}

struct Rva001A62D0TerrainQueryResult
{
	Rva001A62D0TerrainQueryResult() : m_0C(0), m_10(10000000.0f), m_14(0)
	{
		m_pos.x = 0.0f;
		m_pos.y = 0.0f;
		m_pos.z = 0.0f;
	}
	Coord3D m_pos;
	int m_0C;
	float m_10;
	Rva0027D098 *m_14;
};

struct CreateMask
{
public:
	unsigned int words[4]; // +0x00
};

class Object
{
public:
	void teleportTo(const Coord3D *, bool);	// 0x0029660C
};

class Player
{
public:
	bool rva002AA245() const; // 0x002AA245
	char m_pad00[0x2EC];
	Team *m_2EC; // +0x2EC +0x2EC
};

class PlayerList
{
public:
	char m_pad00[0x18];
	Player *m_18;		// +0x18
};
extern PlayerList *ThePlayerList;

enum ObjectID; class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *, ObjectID);	// 0x002D0A23

};
extern ThingFactory *TheThingFactory;

class TerrainLogic
{
public:

	void rva00283CE7(unsigned int id);	// 0x00283CE7
	Object *rva00283D70(const Coord3D *pos);


};
extern TerrainLogic *TheTerrainLogic;

Object *TerrainLogic::rva00283D70(const Coord3D *pos)
{
	Rva0027D098 *rec;
	{
		Rva001A62D0TerrainQueryResult res;
		((Rva0027DCF2 *)this)->rva0027DCF2(const_cast<Coord3D *>(pos), 10.0f, (Rva0027D244 *)&res, false, 0);
		rec = res.m_14;
	}
	Object *obj = 0;
	if (rec) {
		const ThingTemplate *thingTemplate = rec->m_14;
		if (thingTemplate) {
			CreateMask mask;
			memset(&mask, 0, sizeof(mask));
			Team *team = ThePlayerList->m_18->m_2EC;
			obj = TheThingFactory->newObject(thingTemplate, team, &mask, (ObjectID)0);
			obj->teleportTo(reinterpret_cast<const Coord3D *>(rec), false);
		}
		unsigned int id = rec->m_0C;
		rec->rva0027D098();
		TheTerrainLogic->rva00283CE7(id);
		return obj;
	} else {
		Rva0004584D kindFilter(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 86),
			*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE);
		Rva0026119DFilter aliveFilter;
		kindFilter.link(&aliveFilter);
		return ThePartitionManager->getClosestObject(pos, 10.0f, 1, &kindFilter);
	}
}
