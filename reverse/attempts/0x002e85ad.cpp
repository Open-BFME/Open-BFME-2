// ?iterateCellsAlongLine@Pathfinder@@AAEHPBUICoord2D@@0W4PathfindLayerEnum@@PAURva002E85ADInfo@@@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE
//
// ?rva002E85AD@Pathfinder@@QAEHPBUICoord2D@@0W4PathfindLayerEnum@@PAURva002E85ADInfo@@@Z 0x002E85AD 454B
// Cell-space Bresenham walk between two ICoord2D cells, 16th copy beside the
// fifteen in PathfinderCellLineWalks.cpp (prev 0x002E8448, next 0x002E8A47).
// Evidence: same 4-arg (start, dest, layer, info) shape with ret 0x10, same
// /O1 /G7 Bresenham prologue (abs out of line at 0x00629952, numpixels/num/
// numadd/den and xinc/yinc negation), same rowed getCell 0x002E6D62 call,
// world wrapper caller 0x002EB4A0 converting two Coord3D via WorldToCell
// 0x002E7875. Body differs by inlined per-cell work: packed&0xF reject
// 5/2/4, Rva002E6DC4 predicate via info+0xC when info+0x1C set, first-cell
// layer range check via Rva002E6E8AGet when info+8==1, then info+8=layer and
// world (cell*10) float record at info+4. Offsets and callees from retail.

extern "C" int __cdecl abs( int n );

typedef int Int;
typedef float Real;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord2D
{
	Real x;
	Real y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class PathfindCell
{
public:
	char m_pad0[0x0C];
	unsigned int m_packed;
};

class PathfindLayer
{
public:
	PathfindCell *getCell( Int cellX, Int cellY );

private:
	char m_unreconstructed[0x40];
};

class Rva002E6DC4
{
public:
	bool rva002E6DC4( void *a, void *b );
};

int __cdecl Rva002E6E8AGet( int v );

struct Rva002E85ADInfo
{
	Rva002E6DC4 *m_owner;
	Coord2D *m_out;
	Int m_layer;
	char m_check[0x10];
	unsigned char m_flag;
};

class Pathfinder
{
public:
	PathfindCell *getCell( PathfindLayerEnum layer, Int cellX, Int cellY );

private:
	Int iterateCellsAlongLine( const ICoord2D *startCell, const ICoord2D *destinationCell,
		PathfindLayerEnum layer, Rva002E85ADInfo *callbackInfo );

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

// ?iterateCellsAlongLine@Pathfinder@@AAEHPBUICoord2D@@0W4PathfindLayerEnum@@PAURva002E85ADInfo@@@Z present-unmatched
Int Pathfinder::iterateCellsAlongLine( const ICoord2D *startCell,
	const ICoord2D *destinationCell, PathfindLayerEnum layer,
	Rva002E85ADInfo *callbackInfo )
{
	Int delta_x = abs( destinationCell->x - startCell->x );
	Int delta_y = abs( destinationCell->y - startCell->y );

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

	Int curpixel = 0;
	Int x = startCell->x;
	Int y = startCell->y;
	Int wy = y * 10;
	Int wx = x * 10;
	Int yinc1w = yinc1 * 10;
	Int yinc2w = yinc2 * 10;
	Int xinc1w = xinc1 * 10;
	Int xinc2w = xinc2 * 10;
	for (; curpixel < numpixels; curpixel++)
	{
		PathfindCell *currentCell = getCell( layer, x, y );
		if (currentCell == 0)
			return 0;

		unsigned int flags = currentCell->m_packed;
		if ((flags & 0xF) == 5 || (flags & 0xF) == 2 || (flags & 0xF) == 4)
			return 1;

		if (callbackInfo->m_flag != 0)
		{
			if (!callbackInfo->m_owner->rva002E6DC4( &callbackInfo->m_check, currentCell ))
				return 1;
		}

		if (callbackInfo->m_layer == 1)
		{
			if ((unsigned char)Rva002E6E8AGet( (flags >> 4) & 0x3F ))
				return 1;
		}
		callbackInfo->m_layer = (flags >> 4) & 0x3F;
		callbackInfo->m_out->x = (Real)wx;
		callbackInfo->m_out->y = (Real)wy;

		if (num < 0)
		{
			x += xinc2;
			num += numadd;
			wx += xinc2w;
			y += yinc2;
			wy += yinc2w;
		}
		else
		{
			x += xinc1;
			num += den;
			wx += xinc1w;
			y += yinc1;
			wy += yinc1w;
		}
	}
	return 0;
}
