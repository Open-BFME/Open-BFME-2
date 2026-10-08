// cl: /O1 /DNDEBUG /MD /arch:SSE
// Radar.cpp: Radar bodies retail links from this TU (tu_map approved), folded
// from six split units that shared these exact flags. One non-virtual Radar
// view carries every offset the folded bodies were byte-verified against:
//   +0x24/+0x28 x/y sample, +0x1430 radar window, +0x1434 draw extent,
//   +0x144C draw rect, +0x145C dirty byte, +0x1460 cleared dword.
// Bodies that reach Radar through its second base (the frame tick at
// 0x002D7DD5) keep their own unit, since their `this` is that subobject.

typedef bool Bool;
typedef int Int;
typedef float Real;

#define NULL 0

struct ICoord2D
{
	Int x;
	Int y;
};

#include "../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class GameWindow
{
public:
	Int winGetSize(Int *width, Int *height);
};

struct RadarExtent
{
	Real minX;
	Real minY;
	Int reserved;
	Real maxX;
	Real maxY;

	Real width() const { return maxX - minX; }
	Real height() const { return maxY - minY; }
};

struct RadarRect16
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

class Object
{
public:
	char m_pad[0x38];
	Coord3D m_pos; // +0x38
};

class RadarObject
{
public:
	virtual void *deleteInstance(int pool);
	Object *m_object; // +0x04
	RadarObject *m_next; // +0x08
};

class Radar
{
public:
	bool worldToRadar(const Coord3D *world, ICoord2D *radar);
	bool rva002D782C(const Coord3D *world, Coord2D *radar);
	Object *searchListForRadarLocationMatch(RadarObject *list, ICoord2D *target);
	void findDrawPositions(Int startX, Int startY, Int width, Int height,
		ICoord2D *ul, ICoord2D *lr);
	void rva002D7AA6(int dummy);
	void rva002D7BB7(void const *src);
	Bool localPixelToRadar(const ICoord2D *pixel, ICoord2D *radar);

private:
	unsigned char m_pad[0x24];
	float m_xSample; // +0x24
	float m_ySample; // +0x28
	char m_pad2C[0x1430 - 0x2C];
	GameWindow *m_radarWindow; // +0x1430
	RadarExtent m_extent; // +0x1434..+0x1447
	char m_pad1448[0x144C - 0x1448];
	RadarRect16 m_rect; // +0x144C 16B copied from arg
	unsigned char m_dirty; // +0x145C
	char m_pad145D[0x1460 - 0x145D];
	int m_1460;
};

enum
{
	RADAR_CELL_WIDTH = 128,
	RADAR_CELL_HEIGHT = 128
};

// ?rva002D782C@Radar@@QAE_NPBUCoord3D@@PAVCoord2D@@@Z @0x002D782C 120B Radar float
// radar from world via samples plus float clamp.
// Evidence: same this as rowed worldToRadar with m_xSample at +0x24 and
// m_ySample at +0x28; caller 0x0004F53B in FUN_0044f515; prev worldToRadar
// and next searchListForRadarLocationMatch share flags and Radar class; float
// limits live in .rdata at 0x007C4E90 and 0x007C4DBC.
bool Radar::rva002D782C(const Coord3D *world, Coord2D *radar)
{
	if (world == 0 || radar == 0)
		return false;
	radar->x = world->x / m_xSample;
	radar->y = world->y / m_ySample;
	if (radar->x < 0.0f)
		radar->x = 0.0f;
	if (radar->x >= 128.0f)
		radar->x = 127.0f;
	if (radar->y < 0.0f)
		radar->y = 0.0f;
	if (radar->y >= 128.0f)
		radar->y = 127.0f;
	return true;
}

// ?searchListForRadarLocationMatch@Radar@@QAEPAVObject@@PAVRadarObject@@PAUICoord2D@@@Z
// @0x002D78A4 102B Radar list search: walks a RadarObject list (m_object at +4,
// m_next at +8), runs rowed worldToRadar on each Object pos at +0x38 into a stack
// ICoord2D, and returns the first Object whose radar cell is within +-1 of the
// target ICoord2D. Evidence: same this as rowed worldToRadar; caller 0x002D834E
// passes m_localObjectList +0x18 then m_objectList +0x14 with a localPixelToRadar
// ICoord2D; prev/next are Radar_radarToWorld / findDrawPositions with same flags.
Object *Radar::searchListForRadarLocationMatch(RadarObject *list, ICoord2D *target)
{
	if (list == 0 || target == 0)
		return 0;
	for (RadarObject *node = list; node != 0; node = node->m_next)
	{
		Object *obj = node->m_object;
		if (obj == 0)
			continue;
		ICoord2D tmp;
		worldToRadar(&obj->m_pos, &tmp);
		if (tmp.x >= target->x - 1 && tmp.x <= target->x + 1
			&& tmp.y >= target->y - 1 && tmp.y <= target->y + 1)
			return obj;
	}
	return 0;
}

// ?rva002D7AA6@Radar@@QAEXH@Z @0x002D7AA6 10B clearer.
// Retail and [ecx+0x1460],0 then ret 4. Evidence: leaf lane; neighbours
// findDrawPositions and RadarNewMap; and-mem-zero needs /O1;
// ret 4 via single dummy int param.
void Radar::rva002D7AA6(int dummy)
{
	(void)dummy;
	m_1460 = 0;
}

// ?rva002D7BB7@Radar@@QAEXPBX@Z @0x002D7BB7 28B Radar copy draw rect and set dirty.
// Evidence: copies 16B from arg to +0x144C via 4x movsd then byte 1 at +0x145C;
// same offsets as sibling rva002D7BD3 invalidate; caller 0x002D3275 passes
// this+0x68 rect with global Radar this; prev newMap and next rva002D7BD3 share class.
void Radar::rva002D7BB7(void const *src)
{
	m_rect = *(RadarRect16 const *)src;
	m_dirty = 1;
}

// ?localPixelToRadar@Radar@@QAE_NPBUICoord2D@@PAU2@@Z retail 0x002D81EC, 248 bytes.
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/System/RadarLocalPixelToRadar.cpp):
// null-guard the arguments, fetch the window size, fold the full-window
// draw extents through findDrawPositions, reject degenerate or
// out-of-range pixels, then scale into the 128-cell radar space (integer
// path along the long axis, float path along the short one).
// Defined before findDrawPositions so the call stays a call.
Bool Radar::localPixelToRadar(const ICoord2D *pixel, ICoord2D *radar)
{
	if (pixel == NULL || radar == NULL)
		return false;

	Int sizeX;
	Int sizeY;
	{
		ICoord2D size;
		m_radarWindow->winGetSize(&size.x, &size.y);
		sizeX = size.x;
		sizeY = size.y;
	}

	ICoord2D ul;
	ICoord2D lr;
	findDrawPositions(0, 0, sizeX, sizeY, &ul, &lr);

	Int scaledWidth = lr.x - ul.x;
	Int scaledHeight = lr.y - ul.y;

	if (scaledWidth < 1)
		return false;
	if (scaledHeight < 1)
		return false;

	if (pixel->x < ul.x || pixel->x > lr.x ||
		pixel->y < ul.y || pixel->y > lr.y)
		return false;

	if (scaledWidth >= scaledHeight)
	{
		radar->x = (pixel->x - ul.x) * RADAR_CELL_WIDTH / scaledWidth;
		Real yNumerator = (Real)(pixel->y - ul.y);
		Real yDenominator = (Real)scaledHeight;
		radar->y = (Int)((yNumerator / yDenominator) * sizeY);
		radar->y = (sizeY - radar->y) * RADAR_CELL_HEIGHT / sizeY;
	}
	else
	{
		Real xNumerator = (Real)(pixel->x - ul.x);
		Real xDenominator = (Real)scaledWidth;
		radar->x = (Int)((xNumerator / xDenominator) * sizeX);
		radar->x = radar->x * RADAR_CELL_WIDTH / sizeX;
		radar->y = (sizeY - pixel->y) * RADAR_CELL_HEIGHT / sizeY;
	}

	return true;
}

// ?findDrawPositions@Radar@@QAEXHHHHPAUICoord2D@@0@Z, retail 0x002D799C, 266 bytes.
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/System/Radar.cpp,
// Radar::findDrawPositions): preserve the map aspect ratio into the draw
// window, centering along the short axis. BFME2 deltas (all retail-measured):
// - the extent is four plain floats (no Region2D calls; the width/height
//   differences are inline here),
// - the int dimensions divide directly (no width * 1.0f),
// - the axis fit multiplies by the precomputed reciprocal (1.0f / ratio),
//   reusing it for both axes.
void Radar::findDrawPositions(Int startX, Int startY, Int width, Int height,
	ICoord2D *ul, ICoord2D *lr)
{
	Real fWidth = (Real)width;
	Real fHeight = (Real)height;
	Real ratioWidth = m_extent.width() / fWidth;
	Real ratioHeight = m_extent.height() / fHeight;
	Coord2D radar;

	if (ratioWidth >= ratioHeight) {
		Real invRatio = 1.0f / ratioWidth;
		radar.x = m_extent.width() * invRatio;
		radar.y = m_extent.height() * invRatio;
		ul->x = 0;
		ul->y = (Int)(((Real)height - radar.y) / 2.0f);
		lr->x = (Int)radar.x;
		lr->y = height - ul->y;
	} else {
		Real invRatio = 1.0f / ratioHeight;
		radar.x = m_extent.width() * invRatio;
		radar.y = m_extent.height() * invRatio;
		ul->x = (Int)(((Real)width - radar.x) / 2.0f);
		ul->y = 0;
		lr->x = width - ul->x;
		lr->y = (Int)radar.y;
	}

	// make them pixel positions
	ul->x += startX;
	ul->y += startY;
	lr->x += startX;
	lr->y += startY;
}
