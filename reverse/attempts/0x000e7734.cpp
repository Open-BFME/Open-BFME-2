// ?rva000E7734@W3DShrubBuffer@@QAEXPAVThing@@@Z
// partial score=0.9826478283621141 date=2026-10-10
// ?rva000E7734@W3DShrubBuffer@@QAEXPAVThing@@@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include
// W3DShrubBuffer::unitMoved, retail 0x000E7734 (780 bytes, ret 4): when a mobile unit moves, every shrub of the
// 50 by 50 partition cells under the unit's footprint (radius + 7) that is within that radius is pushed aside.
// Open-BFME-1 twin: W3DShrubBuffer_unitMoved.cpp (0x00721B20). BFME2 layout read from retail: partition table of
// shorts at +0x5C0, world bounds at +0x1948 (lo x, lo y, hi x, hi y), 2000 shrub records of 0xA0 at +0x1958
// (type +0x40, drawable +0x58, next in partition +0x74), count +0x4FB58, types of 0x5C at +0x4FB70 with the type
// data at +0x20 (frames to move outward +0x10); the unit is described by its position at +0x38, kind-of mask byte
// at template+0x108 and major radius at +0xB8; GlobalData flags +0x1C/+0x1D.
#include "Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef short Short;

extern "C" __declspec(dllimport) double floor(double);
extern "C" __declspec(dllimport) double ceil(double);

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))
#define REAL_TO_INT_CEIL(x) (fast_float2long_round((Real)ceil((double)(x))))

class GlobalData;
struct Rva000E7734GlobalData
{
	unsigned char m_pad00[0x1c];
	bool m_flag1c;
	bool m_flag1d;
};
extern GlobalData *TheWritableGlobalData;

struct Rva000E7734Template
{
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf;
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D(void) const;

	unsigned char m_pad00[4];
	Rva000E7734Template *m_template;
	unsigned char m_pad08[0x38 - 0x08];
	Real m_x;
	Real m_y;
	Real m_z;
	unsigned char m_pad44[0x74 - 0x44];
	UnsignedInt m_id;
	unsigned char m_pad78[0xb8 - 0x78];
	Real m_majorRadius;
};

struct Rva000E7734Region
{
	Real lox;
	Real loy;
	Real hix;
	Real hiy;
};

struct Rva000E7734TreeData
{
	char m_pad00[0x10];
	UnsignedInt m_framesToMoveOutward;
};

struct Rva000E7734Type
{
	char m_pad00[0x20];
	Rva000E7734TreeData *m_data;
	char m_pad24[0x5c - 0x24];
};

struct Rva000E7734Tree
{
	Coord3D m_location;
	char m_pad0c[0x34];
	Int m_treeType;
	char m_pad44[0x58 - 0x44];
	UnsignedInt m_drawableID;
	char m_pad5c[0x74 - 0x5c];
	Int m_nextInPartition;
	char m_pad78[0xa0 - 0x78];
};

class W3DShrubBuffer
{
public:
	void rva000E7734(Thing *unit);
	void rva000E72B3(UnsignedInt id, const Coord3D *pusherPos, const Coord3D *pusherDirection, UnsignedInt pusherID);

private:
	char m_pad00[0x5c0];
	Short m_areaPartition[(0x1948 - 0x5c0) / 2];
	Rva000E7734Region m_bounds;
	Rva000E7734Tree m_trees[2000];
	Int m_numTrees;
	char m_pad4fb5c[0x4fb70 - 0x4fb5c];
	Rva000E7734Type m_treeTypes[64];
};

void W3DShrubBuffer::rva000E7734(Thing *unit)
{
	const Rva000E7734GlobalData *global = (const Rva000E7734GlobalData *)TheWritableGlobalData;
	if (!global->m_flag1c || !global->m_flag1d)
		return;

	if (unit->m_template->m_kindOf & 4)
		return;

	Real radius = unit->m_majorRadius + 7.0f;
	Coord3D pos;
	pos.x = unit->m_x;
	pos.y = unit->m_y;
	pos.z = unit->m_z;
	Real x = pos.x - radius;
	Real y = pos.y - radius;
	if (x < m_bounds.lox) x = m_bounds.lox;
	if (y < m_bounds.loy) y = m_bounds.loy;
	if (x > m_bounds.hix) x = m_bounds.hix;
	if (y > m_bounds.hiy) y = m_bounds.hiy;
	Real xRatio = x / (m_bounds.hix - m_bounds.lox);
	Int xIndex = REAL_TO_INT_FLOOR(xRatio * 49.9f);
	Real yRatio = y / (m_bounds.hiy - m_bounds.loy);
	Int yIndex = REAL_TO_INT_FLOOR(yRatio * 49.9f);

	x = pos.x + radius;
	y = pos.y + radius;
	if (x < m_bounds.lox) x = m_bounds.lox;
	if (y < m_bounds.loy) y = m_bounds.loy;
	if (x > m_bounds.hix) x = m_bounds.hix;
	if (y > m_bounds.hiy) y = m_bounds.hiy;
	Real xMaxRatio = x / (m_bounds.hix - m_bounds.lox);
	Int xMax = REAL_TO_INT_CEIL(xMaxRatio * 49.9f);
	Real yMaxRatio = y / (m_bounds.hiy - m_bounds.loy);
	Int yMax = REAL_TO_INT_CEIL(yMaxRatio * 49.9f);

	Int i, j;
	for (i = xIndex; i < xMax; i++) {
		for (j = yIndex; j < yMax; j++) {
			Int treeNdx = m_areaPartition[i + 50 * j];
			while (treeNdx != -1) {
				if (treeNdx < 0 || treeNdx >= m_numTrees)
					break;
				if (m_trees[treeNdx].m_treeType < 0) {
					treeNdx = m_trees[treeNdx].m_nextInPartition;
					continue;
				}
				Coord3D delta;
				delta.x = m_trees[treeNdx].m_location.x;
				delta.y = m_trees[treeNdx].m_location.y;
				delta.z = m_trees[treeNdx].m_location.z;
				delta.x -= pos.x;
				delta.y -= pos.y;
				delta.z -= pos.z;
				if (radius * radius > delta.x * delta.x + delta.y * delta.y + delta.z * delta.z) {
					Rva000E7734TreeData *data = m_treeTypes[m_trees[treeNdx].m_treeType].m_data;
					if (data != 0 && data->m_framesToMoveOutward > 0) {
						rva000E72B3(m_trees[treeNdx].m_drawableID, (const Coord3D *)&pos, unit->getUnitDirectionVector2D(), unit->m_id);
					}
				}
				treeNdx = m_trees[treeNdx].m_nextInPartition;
			}
		}
	}
}
