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

class PathfindCell
{
public:
	char m_unreconstructed[0x10];
};

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
