// ?setShroudLevel@W3DRadar@@UAEXHHW4CellShroudStatus@@@Z
// partial score=0.97 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include
// Native [0004EB00,0004ED3D),573B, RET12. BFME 2 W3DRadar::setShroudLevel;
// the ZH setShroudLevel (W3DRadar.cpp) is the semantic guide: shroud cell to
// world rectangle (W3DShroud cell size +0x10/+0x14 on TheTerrainRenderObject
// +0x3878), worldToRadar both corners, then write the alpha of every legal
// radar pixel of the shroud texture (+0x148C) surface. BFME 2 holds the DX8
// thread lock around the surface, squeezes the rectangle by the radar aspect
// scale from 0x002D790A (centered with the texture height 0x00132784 or width
// 0x0013275A) and writes only the alpha byte (0x00116D10).

#include "Lib/Coord3D.h"

typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

struct ICoord2D
{
	Int x;
	Int y;
};

extern void BFME_DX8_Thread_Lock(void);
extern void BFME_DX8_Thread_Assert(void);

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class SurfaceClass
{
public:
	void rva00116D10(UnsignedInt x, UnsignedInt y, UnsignedByte alpha);
};

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();
	SurfaceClass *operator->() { return (SurfaceClass *)this; }

private:
	void *m_surface;
};

class CursorTextureSlot
{
public:
	W3DRadarResetSurface Get_Surface_Level();
};

class Rva00132D0FHolder
{
public:
	Int rva0013275A();
	Int rva00132784();
};

class W3DShroud
{
public:
	Real getCellWidth() const { return m_cellWidth; }
	Real getCellHeight() const { return m_cellHeight; }

private:
	unsigned char m_pad00[0x10];
	Real m_cellWidth;
	Real m_cellHeight;
};

class BaseHeightMapRenderObjClass
{
public:
	W3DShroud *getShroud() { return m_shroud; }

private:
	unsigned char m_pad00[0x3878];
	W3DShroud *m_shroud;
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

bool legalRadarPoint(Int px, Int py);

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED
};

class Radar
{
public:
	virtual void setShroudLevel(Int shroudX, Int shroudY, CellShroudStatus setting);
	bool worldToRadar(const Coord3D *world, ICoord2D *radar);
	void rva002D790A(Real *scaleX, Real *scaleY);
};

class W3DRadar : public Radar
{
public:
	virtual void setShroudLevel(Int shroudX, Int shroudY, CellShroudStatus setting);

private:
	unsigned char m_pad04[0x148C - 0x04];
	CursorTextureSlot m_shroudTexture;
};

void W3DRadar::setShroudLevel(Int shroudX, Int shroudY, CellShroudStatus setting)
{
	W3DShroud *shroud = TheTerrainRenderObject ? TheTerrainRenderObject->getShroud() : 0;
	if (!shroud)
		return;

	BFMEDX8DeviceLock lock;
	W3DRadarResetSurface surface = m_shroudTexture.Get_Surface_Level();

	Int mapMinX = shroudX * shroud->getCellWidth();
	Int mapMinY = shroudY * shroud->getCellHeight();
	Int mapMaxX = (shroudX + 1) * shroud->getCellWidth();
	Int mapMaxY = (shroudY + 1) * shroud->getCellHeight();

	ICoord2D radarPoint;
	Coord3D worldPoint;
	worldPoint.x = mapMinX;
	worldPoint.y = mapMinY;
	worldToRadar(&worldPoint, &radarPoint);
	Int radarMinX = radarPoint.x;
	Int radarMinY = radarPoint.y;

	worldPoint.x = mapMaxX;
	worldPoint.y = mapMaxY;
	worldToRadar(&worldPoint, &radarPoint);
	Int radarMaxX = radarPoint.x;
	Int radarMaxY = radarPoint.y;

	Real scaleX, scaleY;
	rva002D790A(&scaleX, &scaleY);
	if (scaleX > scaleY) {
		radarMinY = radarMinY * scaleY;
		radarMaxY = radarMaxY * scaleY;
		Real offset = (UnsignedInt)((Rva00132D0FHolder *)&m_shroudTexture)->rva00132784() * ((1.0f - scaleY) * 0.5f);
		radarMinY = radarMinY + offset;
		radarMaxY = radarMaxY + offset;
	} else {
		radarMinX = radarMinX * scaleX;
		radarMaxX = radarMaxX * scaleX;
		Real offset = (UnsignedInt)((Rva00132D0FHolder *)&m_shroudTexture)->rva0013275A() * ((1.0f - scaleX) * 0.5f);
		radarMinX = radarMinX + offset;
		radarMaxX = radarMaxX + offset;
	}

	UnsignedByte alpha;
	if (setting == CELLSHROUD_SHROUDED)
		alpha = 255;
	else if (setting == CELLSHROUD_FOGGED)
		alpha = 127;
	else
		alpha = 0;

	for (Int y = radarMinY; y <= radarMaxY; y++) {
		for (Int x = radarMinX; x <= radarMaxX; x++) {
			if (legalRadarPoint(x, y))
				surface->rva00116D10(x, y, alpha);
		}
	}
}
