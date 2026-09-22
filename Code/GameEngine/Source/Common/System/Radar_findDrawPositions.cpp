// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?findDrawPositions@Radar@@QAEXHHHHPAUICoord2D@@0@Z,
// retail 0x002D799C, 266 bytes. Shard TU: the caller (localPixelToRadar)
// lives in Radar_localPixelToRadar.cpp, so the body lives here (a TU holding
// a row must not define that row's callees).
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/System/Radar.cpp,
// Radar::findDrawPositions): preserve the map aspect ratio into the draw
// window, centering along the short axis. BFME2 deltas (all retail-measured):
// - the extent is four plain floats (no Region2D calls; the width/height
//   differences are inline here),
// - the int dimensions divide directly (no width * 1.0f),
// - the axis fit multiplies by the precomputed reciprocal (1.0f / ratio),
//   reusing it for both axes.

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

class Radar
{
public:
	void findDrawPositions(Int startX, Int startY, Int width, Int height,
		ICoord2D *ul, ICoord2D *lr);

private:
	char m_pad[0x1430];
	void *m_radarWindow; // +0x1430
	RadarExtent m_extent; // +0x1434..+0x1447
};

// ?findDrawPositions@Radar@@QAEXHHHHPAUICoord2D@@0@Z
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
