// cl: /D__PLACEMENT_VEC_NEW_INLINE /FIzh_ascii.h /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/sweep_bfme1_outofline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Include/Lib /ICode/Libraries/Include /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2
// stlport
// Native [0004EB00,0004ED3D),573B, RET12. BFME 2 W3DRadar::setShroudLevel;
// the ZH setShroudLevel (W3DRadar.cpp) is the semantic guide: shroud cell to
// world rectangle (W3DShroud cell size +0x10/+0x14 on TheTerrainRenderObject
// +0x3878), worldToRadar both corners, then write the alpha of every legal
// radar pixel of the shroud texture (+0x148C) surface. BFME 2 holds the DX8
// thread lock around the surface, squeezes the rectangle by the radar aspect
// scale from 0x002D790A (centered with the texture height 0x00132784 or width
// 0x0013275A) and writes only the alpha byte (0x00116D10). The body after
// the missing-shroud return is its else block (retail's block layout).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
#include "W3DDevice/Common/W3DRadar.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "WW3D2/Texture.h"

extern void BFME_DX8_Thread_Lock(void);
extern bool BFME_DX8_Thread_Assert(void);

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class TaintGrid
{
public:
	Real getCellWidth() const { return m_cellWidth; }
	Real getCellHeight() const { return m_cellHeight; }

private:
	unsigned char m_pad00[0x10];
	Real m_cellWidth;
	Real m_cellHeight;
};

// BFME's offsets of the terrain's two grids, reached through the real TheTerrainRenderObject.
class W3DRadarTerrainView
{
public:
	__declspec(dllimport) __forceinline W3DShroud *getShroud() { return m_shroud; }
	TaintGrid *getTaintGrid() { return m_taintGrid; }
	char m_pad00[0x3878];
private:
	W3DShroud *m_shroud; // +0x3878
	TaintGrid *m_taintGrid; // +0x387C
};

Bool legalRadarPoint(Int px, Int py);

void W3DRadar::setShroudLevel(Int shroudX, Int shroudY, CellShroudStatus setting)
{
	W3DShroud *shroud = TheTerrainRenderObject ? ((W3DRadarTerrainView *)TheTerrainRenderObject)->getShroud() : 0;
	if (!shroud)
		return;
	else
	{
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
			Real offset = (UnsignedInt)((TextureBaseClass *)&m_shroudTexture)->rva00132784() * ((1.0f - scaleY) * 0.5f);
			radarMinY = radarMinY + offset;
			radarMaxY = radarMaxY + offset;
		} else {
			radarMinX = radarMinX * scaleX;
			radarMaxX = radarMaxX * scaleX;
			Real offset = (UnsignedInt)((TextureBaseClass *)&m_shroudTexture)->rva0013275A() * ((1.0f - scaleX) * 0.5f);
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
}
