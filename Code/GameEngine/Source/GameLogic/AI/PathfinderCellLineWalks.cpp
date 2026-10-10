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

class Object;

class Rva002E7E26
{
public:
	Int rva002E7E26( Object *cell, Int cellX, Int cellY );
};

class Rva002E9D09 {public:Int rva002E9D09(Object*,Int,Int);};
class Rva004DD9E3 {public:Int rva004DD9E3(Int,Int,Int);};

class Pathfinder
{
public:
	PathfindCell *getCell( PathfindLayerEnum layer, Int cellX, Int cellY );
	Int rva002EB7B4(Int*,Int*,Int,Int,Rva002E9D09*);
	Int rva004DDA9A(Int*,Int*,Int,Int,Rva004DD9E3*);
	Int rva002E8773( Int *xPts, Int *yPts, Int numEdges, Int layer, Rva002E7E26 *visitor );
	Int rva002E7749(void *unused, Int cellX, Int cellY, Int layer, Int arg, bool check);

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
public:
	int m_00;	// x in 24.8 fixed point
	int m_04;	// x step per row
	int m_08;	// rows left on this edge
	int m_0C;	// vertex index (used by the convex polygon walk)
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

// ?rva002E8773@Pathfinder@@QAEHPAH0HHPAVRva002E7E26@@@Z @0x002E8773 724B.
// Pathfinder::ProcessConvexPoly for the 0x002E7E26 visitor: WorldBuilder twin
// 0xD71F60 (pathfinder.inl, assert "!(numEdges<3)" at line 479) gives the
// statement order.  Repeated and closing duplicate vertices are dropped and
// fewer than three edges return -1; the polygon is then scan-converted from
// its top vertex with a left and a right 24.8 edge walker (Rva002E6CFE, whose
// fourth word holds the walker's vertex index) and each cell getCell returns
// goes to the visitor, whose nonzero result ends the walk.  Retail reuses
// yPts[topIdx] across the edge-setup call, so that call's body (0x002E6CFE)
// must be visible in this unit.  The edge step (0x002E6D2F) is auto-inlined;
// the cyclic next/previous vertex indices are macros (the WB twin keeps bare
// ternary temporaries with no parameter copies) and reproduce the inlined
// 0x002E6D42 and 0x002E6D54 shapes where calling those functions does not.
#define nextIndex(i, n) ((i) + 1 == (n) ? 0 : (i) + 1)
#define prevIndex(i, n) ((i) != 0 ? (i) - 1 : (n) - 1)

Int Pathfinder::rva002E8773( Int *xPts, Int *yPts, Int numEdges, Int layer, Rva002E7E26 *visitor )
{
	Int i;
	Int j = 1;
	for (i = 1; i < numEdges; i++) {
		if (xPts[i] != xPts[j - 1] || yPts[i] != yPts[j - 1]) {
			xPts[j] = xPts[i];
			yPts[j] = yPts[i];
			j++;
		}
	}
	numEdges = j;
	while (numEdges > 2 && xPts[0] == xPts[numEdges - 1] && yPts[0] == yPts[numEdges - 1]) {
		numEdges--;
	}
	if (numEdges < 3) {
		return -1;
	}

	Int topIdx = 0;
	Int maxY = 0;
	for (i = 1; i < numEdges; i++) {
		if (yPts[i] < yPts[topIdx] || (yPts[i] == yPts[topIdx] && xPts[i] < xPts[topIdx]))
			topIdx = i;
		if (yPts[i] > maxY)
			maxY = yPts[i];
	}

	Int y = yPts[topIdx];
	Rva002E6CFE left;
	left.m_0C = topIdx;
	left.rva002E6CFE( xPts[left.m_0C], xPts[prevIndex(left.m_0C, numEdges)],
		yPts[prevIndex(left.m_0C, numEdges)] - yPts[left.m_0C] );
	left.m_0C = prevIndex(left.m_0C, numEdges);

	while (yPts[topIdx] == yPts[nextIndex(topIdx, numEdges)])
		topIdx = nextIndex(topIdx, numEdges);
	Rva002E6CFE right;
	right.m_0C = topIdx;
	right.rva002E6CFE( xPts[right.m_0C], xPts[nextIndex(right.m_0C, numEdges)],
		yPts[nextIndex(right.m_0C, numEdges)] - yPts[right.m_0C] );
	right.m_0C = nextIndex(right.m_0C, numEdges);

	while (y <= maxY) {
		Int x = (left.m_00 + 0x80) / 256;
		Int xEnd = (right.m_00 + 0x80) / 256;
		while (x <= xEnd) {
			PathfindCell *cell = getCell( (PathfindLayerEnum)layer, x, y );
			x++;
			if (!cell)
				continue;
			Int ret = visitor->rva002E7E26( (Object *)cell, x - 1, y );
			if (ret)
				return ret;
		}
		y++;
		if (!left.rva002E6D2F()) {
			while (left.m_08 == 0) {
				Int dy = yPts[prevIndex(left.m_0C, numEdges)] - yPts[left.m_0C];
				if (dy < 0)
					break;
				left.rva002E6CFE( xPts[left.m_0C], xPts[prevIndex(left.m_0C, numEdges)], dy );
				left.m_0C = prevIndex(left.m_0C, numEdges);
			}
		}
		if (!right.rva002E6D2F()) {
			while (right.m_08 == 0) {
				Int dy = yPts[nextIndex(right.m_0C, numEdges)] - yPts[right.m_0C];
				if (dy < 0)
					break;
				right.rva002E6CFE( xPts[right.m_0C], xPts[nextIndex(right.m_0C, numEdges)], dy );
				right.m_0C = nextIndex(right.m_0C, numEdges);
				if (right.m_08 < 0)
					return 0;
			}
		}
	}
	return 0;
}


// Native 002EB7B4..002EBA88 and 004DDA9A..004DDD6E: 724B RET20.
// WB D70A30/1287DE0 and rowed rectangle callers 002EED80/004DDDA4
// establish the same ProcessConvexPoly family; visitor identities remain opaque.
// The second visitor retains its existing integer cell-pointer ABI. Visible
// edge setup and four-word walker recover both twins of landed 002E8773.
Int Pathfinder::rva002EB7B4( Int *xPts, Int *yPts, Int numEdges, Int layer, Rva002E9D09 *visitor )
{
	Int i;
	Int j = 1;
	for (i = 1; i < numEdges; i++) {
		if (xPts[i] != xPts[j - 1] || yPts[i] != yPts[j - 1]) {
			xPts[j] = xPts[i];
			yPts[j] = yPts[i];
			j++;
		}
	}
	numEdges = j;
	while (numEdges > 2 && xPts[0] == xPts[numEdges - 1] && yPts[0] == yPts[numEdges - 1]) {
		numEdges--;
	}
	if (numEdges < 3) {
		return -1;
	}

	Int topIdx = 0;
	Int maxY = 0;
	for (i = 1; i < numEdges; i++) {
		if (yPts[i] < yPts[topIdx] || (yPts[i] == yPts[topIdx] && xPts[i] < xPts[topIdx]))
			topIdx = i;
		if (yPts[i] > maxY)
			maxY = yPts[i];
	}

	Int y = yPts[topIdx];
	Rva002E6CFE left;
	left.m_0C = topIdx;
	left.rva002E6CFE( xPts[left.m_0C], xPts[prevIndex(left.m_0C, numEdges)],
		yPts[prevIndex(left.m_0C, numEdges)] - yPts[left.m_0C] );
	left.m_0C = prevIndex(left.m_0C, numEdges);

	while (yPts[topIdx] == yPts[nextIndex(topIdx, numEdges)])
		topIdx = nextIndex(topIdx, numEdges);
	Rva002E6CFE right;
	right.m_0C = topIdx;
	right.rva002E6CFE( xPts[right.m_0C], xPts[nextIndex(right.m_0C, numEdges)],
		yPts[nextIndex(right.m_0C, numEdges)] - yPts[right.m_0C] );
	right.m_0C = nextIndex(right.m_0C, numEdges);

	while (y <= maxY) {
		Int x = (left.m_00 + 0x80) / 256;
		Int xEnd = (right.m_00 + 0x80) / 256;
		while (x <= xEnd) {
			PathfindCell *cell = getCell( (PathfindLayerEnum)layer, x, y );
			x++;
			if (!cell)
				continue;
			Int ret = visitor->rva002E9D09( (Object *)cell, x - 1, y );
			if (ret)
				return ret;
		}
		y++;
		if (!left.rva002E6D2F()) {
			while (left.m_08 == 0) {
				Int dy = yPts[prevIndex(left.m_0C, numEdges)] - yPts[left.m_0C];
				if (dy < 0)
					break;
				left.rva002E6CFE( xPts[left.m_0C], xPts[prevIndex(left.m_0C, numEdges)], dy );
				left.m_0C = prevIndex(left.m_0C, numEdges);
			}
		}
		if (!right.rva002E6D2F()) {
			while (right.m_08 == 0) {
				Int dy = yPts[nextIndex(right.m_0C, numEdges)] - yPts[right.m_0C];
				if (dy < 0)
					break;
				right.rva002E6CFE( xPts[right.m_0C], xPts[nextIndex(right.m_0C, numEdges)], dy );
				right.m_0C = nextIndex(right.m_0C, numEdges);
				if (right.m_08 < 0)
					return 0;
			}
		}
	}
	return 0;
}


Int Pathfinder::rva004DDA9A( Int *xPts, Int *yPts, Int numEdges, Int layer, Rva004DD9E3 *visitor )
{
	Int i;
	Int j = 1;
	for (i = 1; i < numEdges; i++) {
		if (xPts[i] != xPts[j - 1] || yPts[i] != yPts[j - 1]) {
			xPts[j] = xPts[i];
			yPts[j] = yPts[i];
			j++;
		}
	}
	numEdges = j;
	while (numEdges > 2 && xPts[0] == xPts[numEdges - 1] && yPts[0] == yPts[numEdges - 1]) {
		numEdges--;
	}
	if (numEdges < 3) {
		return -1;
	}

	Int topIdx = 0;
	Int maxY = 0;
	for (i = 1; i < numEdges; i++) {
		if (yPts[i] < yPts[topIdx] || (yPts[i] == yPts[topIdx] && xPts[i] < xPts[topIdx]))
			topIdx = i;
		if (yPts[i] > maxY)
			maxY = yPts[i];
	}

	Int y = yPts[topIdx];
	Rva002E6CFE left;
	left.m_0C = topIdx;
	left.rva002E6CFE( xPts[left.m_0C], xPts[prevIndex(left.m_0C, numEdges)],
		yPts[prevIndex(left.m_0C, numEdges)] - yPts[left.m_0C] );
	left.m_0C = prevIndex(left.m_0C, numEdges);

	while (yPts[topIdx] == yPts[nextIndex(topIdx, numEdges)])
		topIdx = nextIndex(topIdx, numEdges);
	Rva002E6CFE right;
	right.m_0C = topIdx;
	right.rva002E6CFE( xPts[right.m_0C], xPts[nextIndex(right.m_0C, numEdges)],
		yPts[nextIndex(right.m_0C, numEdges)] - yPts[right.m_0C] );
	right.m_0C = nextIndex(right.m_0C, numEdges);

	while (y <= maxY) {
		Int x = (left.m_00 + 0x80) / 256;
		Int xEnd = (right.m_00 + 0x80) / 256;
		while (x <= xEnd) {
			PathfindCell *cell = getCell( (PathfindLayerEnum)layer, x, y );
			x++;
			if (!cell)
				continue;
			Int ret = visitor->rva004DD9E3( (Int)cell, x - 1, y );
			if (ret)
				return ret;
		}
		y++;
		if (!left.rva002E6D2F()) {
			while (left.m_08 == 0) {
				Int dy = yPts[prevIndex(left.m_0C, numEdges)] - yPts[left.m_0C];
				if (dy < 0)
					break;
				left.rva002E6CFE( xPts[left.m_0C], xPts[prevIndex(left.m_0C, numEdges)], dy );
				left.m_0C = prevIndex(left.m_0C, numEdges);
			}
		}
		if (!right.rva002E6D2F()) {
			while (right.m_08 == 0) {
				Int dy = yPts[nextIndex(right.m_0C, numEdges)] - yPts[right.m_0C];
				if (dy < 0)
					break;
				right.rva002E6CFE( xPts[right.m_0C], xPts[nextIndex(right.m_0C, numEdges)], dy );
				right.m_0C = nextIndex(right.m_0C, numEdges);
				if (right.m_08 < 0)
					return 0;
			}
		}
	}
	return 0;
}

