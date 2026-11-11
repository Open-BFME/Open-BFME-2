// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include
// Native [0004DBD5,0004DDBF),490B, RET20. BFME 2 W3DRadar::drawViewBox: the
// ZH drawViewBox (W3DRadar.cpp) is the semantic guide - project the
// tactical view origin to the terrain average Z (+0x1C), convert it to radar
// cells over the map extent (+0x1434, 128 cells per side) and walk the stored
// view box offsets (+0x14E0) through the float radarToPixel 0x0004DB76.
// BFME 2 no longer draws the four lines itself: it hands the four pixel
// corners to theRadarWindowOverrideSource (0x002D55D2). Coord2D has inline
// empty ctor/dtor, so only the corner array runs the out-of-line folded
// copies through the eh vector iterators. The fifth argument is unused here.

#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
#include "Lib/ICoord2D.h"

// Out-of-line empty ctor/dtor (rowed 0x0047A6A9 / 0x000B3FD0, defined in
// W3DRadarCornerLifetimes.cpp): only the corner array runs them, through the
// eh vector iterators; the scalar Coord2D temporaries stay plain.
struct BfmeRadarMapPoint : Coord2D {
	BfmeRadarMapPoint();
	~BfmeRadarMapPoint();
};

#include "../../../../../Libraries/Include/Lib/Region3D.h"

#define BFME_PAD_VIRTUAL(n) virtual void pad##n();
#define BFME_PAD_VIRTUAL8(n) BFME_PAD_VIRTUAL(n##0) BFME_PAD_VIRTUAL(n##1) \
	BFME_PAD_VIRTUAL(n##2) BFME_PAD_VIRTUAL(n##3) BFME_PAD_VIRTUAL(n##4) \
	BFME_PAD_VIRTUAL(n##5) BFME_PAD_VIRTUAL(n##6) BFME_PAD_VIRTUAL(n##7)

#include "../../../../../GameEngine/Include/GameClient/View.h"

extern View *TheTacticalView;

struct BfmePod8 { int fields[2]; };
#include "../../../../../GameEngine/Include/Common/RadarWindowOverrideSource.h"

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
	ICoord2D ulScreen;
	Coord2D ulRadar;
	Coord3D ulWorld;
	Coord2D ulStart;
	Coord2D start, end;
	ulStart.x = 0.0f;
	ulStart.y = 0.0f;

	TheTacticalView->getOrigin(&ulScreen.x, &ulScreen.y);
	TheTacticalView->screenToWorldAtZ(&ulScreen, &ulWorld, m_terrainAverageZ);
	ulRadar.x = ulWorld.x / (m_mapExtent.width() / RADAR_CELL_WIDTH);
	ulRadar.y = ulWorld.y / (m_mapExtent.height() / RADAR_CELL_HEIGHT);
	rva0004DB76(&ulRadar, &ulStart, pixelX, pixelY, width, height);

	BfmeRadarMapPoint box[4];
	Coord2D radar;

	start = ulStart;
	radar.x = ulRadar.x + m_viewBox[1].x;
	radar.y = ulRadar.y + m_viewBox[1].y;
	rva0004DB76(&radar, &end, pixelX, pixelY, width, height);
	(Coord2D &)box[0] = start;

	start = end;
	radar.x += m_viewBox[2].x;
	radar.y += m_viewBox[2].y;
	rva0004DB76(&radar, &end, pixelX, pixelY, width, height);
	(Coord2D &)box[1] = start;

	start = end;
	radar.x += m_viewBox[3].x;
	radar.y += m_viewBox[3].y;
	rva0004DB76(&radar, &end, pixelX, pixelY, width, height);
	(Coord2D &)box[2] = start;
	(Coord2D &)box[3] = end;

	if (theRadarWindowOverrideSource)
		theRadarWindowOverrideSource->rva002D55D2(reinterpret_cast<const BfmePod8*>(box));
}
