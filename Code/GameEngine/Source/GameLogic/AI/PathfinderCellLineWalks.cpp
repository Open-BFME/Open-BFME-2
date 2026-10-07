// cl: /DNDEBUG /MD
//
// Pathfinder::getCell (retail 0x002E6D62) and fifteen cell-space line walks
// that iterate the cells between two ICoord2D cells with Bresenham and hand
// each (previous, current, x, y) to a per-caller callback object.  The walk
// is Open-BFME-1's PathfinderIterateCellsAlongLineMADStruct.cpp donor
// (reference/open-bfme-1, game/GameEngine/Source/GameLogic/AI), which BFME 1
// emits with getCell inlined; BFME 2 keeps getCell and abs out of line and
// otherwise compiles the donor body unchanged under /O1 /G7.  Like the donor,
// each callback type gets its own private overload; the fifteen retail
// copies differ only in the callback their REL32 names.
//
// getCell follows the Zero Hour inline (extent check, layers 2..15 first,
// then the ground map); BFME 2's PathfindLayer is 0x40 bytes with the layer
// array at +0x60.  PathfindLayer::getCell (0x00366626), abs (0x00629952) and
// every callback are declared and resolve to pins.  Callback owners are
// named after their cellCallback address; their identities are not
// recovered.
//
//   walk        cellCallback
//   0x002E8045  0x002E7261
//   0x002E8348  0x002E6F92
//   0x002E8448  0x002E7B29
//   0x002E8A47  0x002E7ED6
//   0x002EB6B4  0x002E93A7
//   0x002EEF16  0x002ECE6A
//   0x002EF016  0x002ED01E
//   0x002EF116  0x002ED15A
//   0x002F1F3F  0x002F18D4
//   0x002F203F  0x002F1BD5
//   0x002F4391  0x002F3F7D
//   0x002F69E3  0x002F4491
//   0x002F6B22  0x002F5925
//   0x002F6C22  0x002F4D8B
//   0x002F6D22  0x002F600C

#include "../../../../Libraries/Include/Lib/Coord3D.h"

extern "C" int __cdecl abs( int n );

typedef int Int;

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);

class PathfindCell
{
public:
	char m_pad[12];
	unsigned int m_flags;
};

class Pathfinder;

class PathfindLayer
{
public:
	PathfindCell *getCell( Int cellX, Int cellY );

private:
	char m_unreconstructed[0x40];
};

#define PATHFINDER_CELL_LINE_CALLBACK( Info ) \
struct Info \
	{ \
		Pathfinder *m_pathfinder; \
		Int m_arg; \
		Int cellCallback( PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY ); \
	};

PATHFINDER_CELL_LINE_CALLBACK( Rva002E7261Info )
PATHFINDER_CELL_LINE_CALLBACK( Rva002E6F92Info )
PATHFINDER_CELL_LINE_CALLBACK( Rva002E7B29Info )
PATHFINDER_CELL_LINE_CALLBACK( Rva002E7ED6Info )
PATHFINDER_CELL_LINE_CALLBACK( Rva002E93A7Info )
PATHFINDER_CELL_LINE_CALLBACK( Rva002ECE6AInfo )
PATHFINDER_CELL_LINE_CALLBACK( Rva002ED01EInfo )
PATHFINDER_CELL_LINE_CALLBACK( Rva002ED15AInfo )
PATHFINDER_CELL_LINE_CALLBACK( Rva002F18D4Info )
PATHFINDER_CELL_LINE_CALLBACK( Rva002F1BD5Info )
PATHFINDER_CELL_LINE_CALLBACK( Rva002F3F7DInfo )
PATHFINDER_CELL_LINE_CALLBACK( Rva002F4491Info )
PATHFINDER_CELL_LINE_CALLBACK( Rva002F5925Info )
PATHFINDER_CELL_LINE_CALLBACK( Rva002F4D8BInfo )
PATHFINDER_CELL_LINE_CALLBACK( Rva002F600CInfo )

#define PATHFINDER_CELL_LINE_WALK_DECL( Info ) \
	Int iterateCellsAlongLine( const ICoord2D *startCell, const ICoord2D *destinationCell, \
		PathfindLayerEnum layer, Info *callbackInfo );

class Pathfinder
{
public:
	PathfindCell *getCell( PathfindLayerEnum layer, Int cellX, Int cellY );
	Int rva002E7749(void *unused, Int cellX, Int cellY, Int layer, Int arg, bool check);
	Int rva002F9578(const Coord3D *startPos, const Coord3D *destPos, PathfindLayerEnum layer, Rva002F4D8BInfo *info);

private:
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002E7261Info )
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002E6F92Info )
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002E7B29Info )
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002E7ED6Info )
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002E93A7Info )
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002ECE6AInfo )
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002ED01EInfo )
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002ED15AInfo )
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002F18D4Info )
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002F1BD5Info )
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002F3F7DInfo )
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002F4491Info )
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002F5925Info )
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002F4D8BInfo )
	PATHFINDER_CELL_LINE_WALK_DECL( Rva002F600CInfo )
	Int rva002E8251(const ICoord2D *startCell, const ICoord2D *destinationCell,
		PathfindLayerEnum layer, Rva002E7ED6Info *callbackInfo);

	char m_beforeMap[0x10];
	PathfindCell **m_map;
	struct
	{
		ICoord2D lo;
		ICoord2D hi;
	} m_extent;
	char m_beforeLayers[0x60 - 0x24];
	PathfindLayer m_layers[16];
};

extern bool __cdecl Rva001E3679(Int layer);

// ?cellCallback@Rva002E93A7Info@@QAEHPAVPathfindCell@@0HH@Z @0x002E93A7 104B.
// The pin and caller establish this callback type; its two stored words and
// field offsets come from the retail loads at [this] and [this+4].
Int Rva002E93A7Info::cellCallback(PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY)
{
	if (previousCell != 0)
	{
		Int layer = (currentCell->m_flags >> 4) & 0x3f;
		if (Rva001E3679(layer))
		{
			Int previousLayer = (previousCell->m_flags >> 4) & 0x3f;
			if (previousLayer == layer)
				return 0;
		}
	}
	Int layer = (currentCell->m_flags >> 4) & 0x3f;
	Int result = m_pathfinder->rva002E7749(0, cellX, cellY, layer, m_arg, true);
	return result != m_arg;
}

class Rva002E6CD8Owner
{
public:
	Rva002E6CD8Owner& rva002E6CD8(int a0, unsigned char a1, int a2, unsigned char a3, unsigned char a4);
private:
	int m_00;
	unsigned char m_04;
	unsigned char m_05;
	char m_pad06[2];
	int m_08;
	unsigned char m_0C;
};

// ?rva002E6CD8@Rva002E6CD8Owner@@QAEAAV1@HEHEE@Z @0x002E6CD8 38B
Rva002E6CD8Owner& Rva002E6CD8Owner::rva002E6CD8(int a0, unsigned char a1, int a2, unsigned char a3, unsigned char a4)
{
	m_00 = a0;
	m_04 = a1;
	m_05 = a3;
	m_08 = a2;
	m_0C = a4;
	return *this;
}

class Rva002E6CFE
{
	int m_00;
	int m_04;
	int m_08;
public:
	void rva002E6CFE(int a, int b, int c);
	bool rva002E6D2F();
};

// ?rva002E6CFE@Rva002E6CFE@@QAEXHHH@Z @0x002E6CFE 49B
void Rva002E6CFE::rva002E6CFE(int a, int b, int c)
{
	m_08 = c;
	if (c > 0) {
		m_04 = ((b - a) << 8) / c;
		m_00 = (m_04 / 2) + (a << 8);
	}
}

// ?rva002E6D2F@Rva002E6CFE@@QAE_NXZ @0x002E6D2F 19B
bool Rva002E6CFE::rva002E6D2F()
{
	m_00 += m_04;
	return --m_08 > 0;
}

// ?rva002E6D42@@YAHHH@Z @0x002E6D42 18B
int __cdecl rva002E6D42(int a, int b)
{
	int next = a + 1;
	return (next == b) ? 0 : next;
}

// ?rva002E6D54@@YAHHH@Z @0x002E6D54 14B
int __cdecl rva002E6D54(int a, int b)
{
	if (a != 0)
		return a - 1;
	return b - 1;
}

PathfindCell *Pathfinder::getCell( PathfindLayerEnum layer, Int cellX, Int cellY )
{
	if (cellX >= m_extent.lo.x && cellX <= m_extent.hi.x &&
		cellY >= m_extent.lo.y && cellY <= m_extent.hi.y)
	{
		if (layer > 1 && layer <= 15)
		{
			PathfindCell *cell = m_layers[layer].getCell( cellX, cellY );
			if (cell)
				return cell;
		}
		return &m_map[cellX][cellY];
	}
	return 0;
}

#define PATHFINDER_CELL_LINE_WALK( Info ) \
Int Pathfinder::iterateCellsAlongLine( const ICoord2D *startCell, \
	const ICoord2D *destinationCell, PathfindLayerEnum layer, \
	Info *callbackInfo ) \
{ \
	Int delta_x = abs( destinationCell->x - startCell->x ); \
	Int delta_y = abs( destinationCell->y - startCell->y ); \
 \
	Int xinc2, yinc1, xinc1, numpixels, numadd, den; \
	Int yinc2, num; \
	if (delta_x >= delta_y) \
	{ \
		numpixels = delta_x + 1; \
		num = 2 * delta_y - delta_x; \
		numadd = delta_y << 1; \
		den = 2 * (delta_y - delta_x); \
		xinc2 = 1; \
		yinc2 = 0; \
		yinc1 = 1; \
		xinc1 = 1; \
	} \
	else \
	{ \
		numpixels = delta_y + 1; \
		num = 2 * delta_x - delta_y; \
		numadd = delta_x << 1; \
		den = 2 * (delta_x - delta_y); \
		yinc2 = 1; \
		xinc2 = 0; \
		yinc1 = 1; \
		xinc1 = 1; \
	} \
 \
	if (startCell->x > destinationCell->x) \
	{ \
		xinc2 = -xinc2; \
		xinc1 = -1; \
	} \
	if (startCell->y > destinationCell->y) \
	{ \
		yinc2 = -yinc2; \
		yinc1 = -1; \
	} \
 \
	Int x = startCell->x; \
	Int y = startCell->y; \
	PathfindCell *previousCell = 0; \
	for (Int curpixel = 0; curpixel < numpixels; curpixel++) \
	{ \
		PathfindCell *currentCell = getCell( layer, x, y ); \
		if (currentCell == 0) \
			return 0; \
 \
		Int ret = callbackInfo->cellCallback( previousCell, currentCell, x, y ); \
		if (ret != 0) \
			return ret; \
		previousCell = currentCell; \
 \
		if (num < 0) \
		{ \
			num += numadd; \
			x += xinc2; \
			y += yinc2; \
		} \
		else \
		{ \
			num += den; \
			x += xinc1; \
			y += yinc1; \
		} \
	} \
	return 0; \
}

PATHFINDER_CELL_LINE_WALK( Rva002E7261Info )
PATHFINDER_CELL_LINE_WALK( Rva002E6F92Info )
PATHFINDER_CELL_LINE_WALK( Rva002E7B29Info )
PATHFINDER_CELL_LINE_WALK( Rva002E7ED6Info )
PATHFINDER_CELL_LINE_WALK( Rva002E93A7Info )
PATHFINDER_CELL_LINE_WALK( Rva002ECE6AInfo )
PATHFINDER_CELL_LINE_WALK( Rva002ED01EInfo )
PATHFINDER_CELL_LINE_WALK( Rva002ED15AInfo )
PATHFINDER_CELL_LINE_WALK( Rva002F18D4Info )
PATHFINDER_CELL_LINE_WALK( Rva002F1BD5Info )
PATHFINDER_CELL_LINE_WALK( Rva002F3F7DInfo )
PATHFINDER_CELL_LINE_WALK( Rva002F4491Info )
PATHFINDER_CELL_LINE_WALK( Rva002F5925Info )
PATHFINDER_CELL_LINE_WALK( Rva002F4D8BInfo )
PATHFINDER_CELL_LINE_WALK( Rva002F600CInfo )

// ?rva002E8251@Pathfinder@@AAEHPBUICoord2D@@0W4PathfindLayerEnum@@PAURva002E7ED6Info@@@Z @0x002E8251 247B.
// Private line walk checking flags &0x3f0 vs 0x10 via rowed getCell 0x002E6D62
// and abs 0x00629952. Same Bresenham as iterateCellsAlongLine above with the
// callback replaced by the flag test. Evidence is pin plus caller 0x002EAE16
// plus abut to 0x002E8348.
Int Pathfinder::rva002E8251(const ICoord2D *startCell, const ICoord2D *destinationCell, PathfindLayerEnum layer, Rva002E7ED6Info *callbackInfo)
{
	(void)callbackInfo;
	Int delta_x = abs(destinationCell->x - startCell->x);
	Int delta_y = abs(destinationCell->y - startCell->y);

	Int xinc2, yinc1, xinc1, numpixels, numadd, den;
	Int yinc2, num;
	if (delta_x >= delta_y)
	{
		numpixels = delta_x + 1;
		num = 2 * delta_y - delta_x;
		numadd = delta_y << 1;
		den = 2 * (delta_y - delta_x);
		xinc2 = 1;
		yinc2 = 0;
		yinc1 = 1;
		xinc1 = 1;
	}
	else
	{
		numpixels = delta_y + 1;
		num = 2 * delta_x - delta_y;
		numadd = delta_x << 1;
		den = 2 * (delta_x - delta_y);
		yinc2 = 1;
		xinc2 = 0;
		yinc1 = 1;
		xinc1 = 1;
	}

	if (startCell->x > destinationCell->x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (startCell->y > destinationCell->y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	Int x = startCell->x;
	Int y = startCell->y;
	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		PathfindCell *currentCell = getCell(layer, x, y);
		if (currentCell == 0)
			return 0;
		Int blocked = ((currentCell->m_flags & 0x3f0) != 0x10);
		if (blocked)
			return blocked;
		if (num < 0)
		{
			num += numadd;
			x += xinc2;
			y += yinc2;
		}
		else
		{
			num += den;
			x += xinc1;
			y += yinc1;
		}
	}
	return 0;
}

// ?rva002F9578@Pathfinder@@QAEHPBUCoord3D@@0W4PathfindLayerEnum@@PAURva002F4D8BInfo@@@Z @0x002F9578 63B.
// The caller and adjacent Pathfinder helpers establish the class; both world-to-cell
// conversions and the Rva002F4D8BInfo line-walk overload are rowed.
Int Pathfinder::rva002F9578(const Coord3D *startPos, const Coord3D *destPos, PathfindLayerEnum layer, Rva002F4D8BInfo *info)
{
	ICoord2D tmpDest;
	ICoord2D tmpStart;
	return iterateCellsAlongLine(Rva002E7875WorldToCell(&tmpStart, true, startPos), Rva002E7875WorldToCell(&tmpDest, true, destPos), layer, info);
}
