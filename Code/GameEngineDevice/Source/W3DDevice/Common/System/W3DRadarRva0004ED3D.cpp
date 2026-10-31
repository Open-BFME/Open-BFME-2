// cl: /D__PLACEMENT_VEC_NEW_INLINE /FIzh_ascii.h /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/sweep_bfme1_outofline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Include/Lib /ICode/Libraries/Include /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2
// stlport
//
// ?rva0004ED3D@W3DRadar@@QAEXHHE@Z @0x0004ED3D 544B, thiscall ret 0xC.
// W3DRadar taint counterpart of setShroudLevel (0x0004EB00): gate on the
// GlobalData taint-enable byte (+0xC6A), take the terrain's second grid
// (TheTerrainRenderObject +0x387C, cell size +0x10/+0x14), map the cell to a
// radar rectangle through Radar::worldToRadar and fill it on the radar's taint
// texture (+0x1498) with the TaintColor-style tint below level 128 (colour
// GlobalData +0xBEC scaled by (127-level)*2), the second colour (+0xBF8) above
// it (level*2-256) and opaque white tint at exactly 128.
// Evidence (target): the +0xBEC/+0xBF8 colour pair and +0xC6A enable byte are
// the ones W3DTaint.cpp names; retail loads the grid, the shared DX8 thread
// lock (0x0011F520 / 0x00120F50) and Get_Surface_Level (0x00132D70) exactly as
// the rowed setShroudLevel does. Donor (structure only): BFME 1
// W3DRadar_taintCell_rva006C2710.cpp (same function in the earlier title).
// The method name is not known; it keeps the address.
// Shape note: the body after the missing-grid return sits in its else block
// (as in setShroudLevel); that is what puts cellX in eax before the first
// cell-width load.
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
#include "Common/GlobalData.h"
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

// BFME's offsets of the taint colours and enable byte, reached through the real TheWritableGlobalData.
class W3DRadarGlobalDataView
{
	unsigned char m_pad00[0xBEC];

public:
	Real m_lowRed;
	Real m_lowGreen;
	Real m_lowBlue;
	Real m_highRed;
	Real m_highGreen;
	Real m_highBlue;

private:
	unsigned char m_padC04[0xC6A - 0xC04];

public:
	UnsignedByte m_taintOn;
};

Bool legalRadarPoint(Int px, Int py);

void W3DRadar::rva0004ED3D(Int cellX, Int cellY, UnsignedByte level)
{
	if (!((W3DRadarGlobalDataView *)TheWritableGlobalData)->m_taintOn)
		return;

	TaintGrid *grid = TheTerrainRenderObject ? ((W3DRadarTerrainView *)TheTerrainRenderObject)->getTaintGrid() : 0;
	if (!grid)
		return;
	else {
		BFMEDX8DeviceLock lock;
		W3DRadarResetSurface surface = m_fogTexture.Get_Surface_Level();

		Int mapMinX = cellX * grid->getCellWidth();
		Int mapMinY = cellY * grid->getCellHeight();
		Int mapMaxX = (cellX + 1) * grid->getCellWidth();
		Int mapMaxY = (cellY + 1) * grid->getCellHeight();

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

		Int alpha;
		Int red;
		Int green;
		Int blue;
		if (level < 128) {
			alpha = (127 - level) * 2;
			red = alpha * ((W3DRadarGlobalDataView *)TheWritableGlobalData)->m_lowRed;
			green = alpha * ((W3DRadarGlobalDataView *)TheWritableGlobalData)->m_lowGreen;
			blue = alpha * ((W3DRadarGlobalDataView *)TheWritableGlobalData)->m_lowBlue;
		} else if (level > 128) {
			alpha = level * 2 - 256;
			red = alpha * ((W3DRadarGlobalDataView *)TheWritableGlobalData)->m_highRed;
			green = alpha * ((W3DRadarGlobalDataView *)TheWritableGlobalData)->m_highGreen;
			blue = alpha * ((W3DRadarGlobalDataView *)TheWritableGlobalData)->m_highBlue;
		} else {
			alpha = 0;
			red = 255;
			green = 255;
			blue = 255;
		}

		for (Int y = radarMinY; y <= radarMaxY; y++) {
			for (Int x = radarMinX; x <= radarMaxX; x++) {
				if (legalRadarPoint(x, y))
					surface->DrawPixel(x, y, GameMakeColor(red, green, blue, alpha));
			}
		}

	}
}
