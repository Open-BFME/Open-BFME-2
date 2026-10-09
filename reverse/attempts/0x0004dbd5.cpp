// ?drawViewBox@W3DRadar@@QAEXHHHHH@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [0004DBD5,0004DDBF),490B, RET20. BFME 2 W3DRadar::drawViewBox: the
// ZH drawViewBox (W3DRadar.cpp) is the semantic guide - project the
// tactical view origin to the terrain average Z (+0x1C), convert it to radar
// cells over the map extent (+0x1434, 128 cells per side) and walk the stored
// view box offsets (+0x14E0) through the float radarToPixel 0x0004DB76.
// BFME 2 no longer draws the four lines itself: it hands the four pixel
// corners to theRadarWindowOverrideSource (0x002D55D2). Coord2D has inline
// empty ctor/dtor, so only the corner array runs the out-of-line folded
// copies through the eh vector iterators. The fifth argument is unused here.

struct ICoord2D
{
	int x;
	int y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Coord2D
{
public:
	Coord2D() {}
	~Coord2D() {}
	float x;
	float y;
};

struct Region3D
{
	Coord3D lo;
	Coord3D hi;
	float width() const { return hi.x - lo.x; }
	float height() const { return hi.y - lo.y; }
};

#define BFME_PAD_VIRTUAL(n) virtual void pad##n();
#define BFME_PAD_VIRTUAL8(n) BFME_PAD_VIRTUAL(n##0) BFME_PAD_VIRTUAL(n##1) \
	BFME_PAD_VIRTUAL(n##2) BFME_PAD_VIRTUAL(n##3) BFME_PAD_VIRTUAL(n##4) \
	BFME_PAD_VIRTUAL(n##5) BFME_PAD_VIRTUAL(n##6) BFME_PAD_VIRTUAL(n##7)

class View
{
public:
	BFME_PAD_VIRTUAL8(0) BFME_PAD_VIRTUAL8(1)
	BFME_PAD_VIRTUAL(20) BFME_PAD_VIRTUAL(21) BFME_PAD_VIRTUAL(22)
	virtual void getOrigin(int *x, int *y);	// slot 19
	BFME_PAD_VIRTUAL8(3) BFME_PAD_VIRTUAL8(4) BFME_PAD_VIRTUAL8(5)
	BFME_PAD_VIRTUAL8(6) BFME_PAD_VIRTUAL8(7) BFME_PAD_VIRTUAL8(8)
	BFME_PAD_VIRTUAL8(9) BFME_PAD_VIRTUAL8(a) BFME_PAD_VIRTUAL(b0) BFME_PAD_VIRTUAL(b1)
	BFME_PAD_VIRTUAL(b2) BFME_PAD_VIRTUAL(b3) BFME_PAD_VIRTUAL(b4) BFME_PAD_VIRTUAL(b5)
	BFME_PAD_VIRTUAL(b6)
	virtual void screenToWorldAtZ(const ICoord2D *s, Coord3D *w, float z);	// slot 91
};

extern View *TheTacticalView;

struct BfmePod8 { int fields[2]; };
class RadarWindowOverrideSource
{
public:
	void rva002D55D2(const BfmePod8 *corners);
};

extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

class Radar
{
public:
	void rva0004DB76(const Coord2D *radar, Coord2D *pixel,
		int radarUpperLeftX, int radarUpperLeftY, int radarWidth, int radarHeight);
};

class W3DRadar : public Radar
{
public:
	void drawViewBox(int pixelX, int pixelY, int width, int height, int unused);

private:
	unsigned char m_pad00[0x1C];
	float m_terrainAverageZ;
	unsigned char m_pad20[0x1434 - 0x20];
	Region3D m_mapExtent;
	unsigned char m_pad144c[0x14E0 - 0x144C];
	Coord2D m_viewBox[4];
};

enum { RADAR_CELL_WIDTH = 128, RADAR_CELL_HEIGHT = 128 };

// Native [0004DB76,0004DBD5),95B, RET24: float-coordinate counterpart of
// radarToPixel (moved from W3DRadar.cpp). Callers load ECX with the radar
// (0x0004F557, and drawViewBox below, which keeps XMM values live across the
// call: the helper must be compiled ahead of it in this unit). Retail
// constants are 1/128 at VA BC4DB8 and 127 at BC4DBC.
void Radar::rva0004DB76(const Coord2D *radar, Coord2D *pixel,
	int upperLeftX, int upperLeftY, int width, int height)
{
	if (radar == 0 || pixel == 0)
		return;
	pixel->x = (radar->x * width / 128.0f) + upperLeftX;
	pixel->y = ((127.0f - radar->y) * height / 128.0f) + upperLeftY;
}

void W3DRadar::drawViewBox(int pixelX, int pixelY, int width, int height, int unused)
{
	Coord2D radar;
	ICoord2D ulScreen;
	Coord2D ulRadar;
	Coord3D ulWorld;
	Coord2D ulStart;
	ulStart.x = 0.0f;
	ulStart.y = 0.0f;

	TheTacticalView->getOrigin(&ulScreen.x, &ulScreen.y);
	TheTacticalView->screenToWorldAtZ(&ulScreen, &ulWorld, m_terrainAverageZ);
	ulRadar.x = ulWorld.x / (m_mapExtent.width() / RADAR_CELL_WIDTH);
	ulRadar.y = ulWorld.y / (m_mapExtent.height() / RADAR_CELL_HEIGHT);
	rva0004DB76(&ulRadar, &ulStart, pixelX, pixelY, width, height);

	Coord2D corners[4];
	radar.x = ulRadar.x + m_viewBox[1].x;
	radar.y = ulRadar.y + m_viewBox[1].y;
	rva0004DB76(&radar, &ulRadar, pixelX, pixelY, width, height);
	corners[0] = ulStart;
	corners[1] = ulRadar;

	radar.x += m_viewBox[2].x;
	radar.y += m_viewBox[2].y;
	rva0004DB76(&radar, &ulRadar, pixelX, pixelY, width, height);
	corners[2] = ulRadar;

	radar.x += m_viewBox[3].x;
	radar.y += m_viewBox[3].y;
	rva0004DB76(&radar, &ulRadar, pixelX, pixelY, width, height);
	corners[3] = ulRadar;

	if (theRadarWindowOverrideSource)
		theRadarWindowOverrideSource->rva002D55D2(reinterpret_cast<const BfmePod8*>(corners));
}
