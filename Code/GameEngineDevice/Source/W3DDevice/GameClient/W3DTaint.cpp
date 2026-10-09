// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// W3DTaint::setTaintLevel: WB 0x0082D3C0 names the function and W3DTaint.cpp
// assertion 330; game.dat 0x00073CC0..0x000740C2 supplies its full boundary.
// Semantic donor: Open-BFME-1 9cbfb551fe20dae985f91f2319d8997287b6a705
// game/GameEngineDevice/Source/W3DDevice/GameClient/TaintBuffer_setShroudLevel.cpp.
// BFME2 target evidence adds the mode query / FireManager colour sampling and
// changes GlobalData colours to +0xBEC..+0xC00 and enable byte to +0xC6A.
// The existing Rva000729CC four-word consuming signature is retained: its
// other method's owner remains unproven. Low bytes establish level/textureOnly.
// Virtual-view names describe observed consumption rather than original APIs.
// g_bfmeTaintModeView denotes the pointer read at VA 0x00DEBC5C; its original
// name and owner are unknown. FireManager binding comes from existing GameClient
// rows at VA 0x00DFF4B4; slot +0x3C returns three floats by hidden result pointer.
// WWMath::Float_To_Long supplies the witnessed x87 rounded conversion after
// floor; the local floor adapter retains retail's double CRT import instead of
// the donor header's newer floorf. Scale getters retain its evaluation order.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

#define _OPERATOR_NEW_DEFINED_ // <set> already declares placement new/delete
#include "wwmath.h"
__forceinline float taintFloor(float v) { return float(floor(double(v))); }
struct BfmeTaintColor { float red,green,blue; };
class FireManager { public:
 virtual void slot0()=0;
 virtual void slot1()=0;
 virtual void slot2()=0;
 virtual void slot3()=0;
 virtual void slot4()=0;
 virtual void slot5()=0;
 virtual void slot6()=0;
 virtual void slot7()=0;
 virtual void slot8()=0;
 virtual void slot9()=0;
 virtual void slot10()=0;
 virtual void slot11()=0;
 virtual void slot12()=0;
 virtual void slot13()=0;
 virtual void slot14()=0;
 virtual BfmeTaintColor sample(int,int)=0;
};
FireManager *TheFireManager; // existing global binding; zero-initialized retail cell
class BfmeTaintModeView { public:
 virtual void slot0()=0;
 virtual void slot1()=0;
 virtual void slot2()=0;
 virtual void slot3()=0;
 virtual void slot4()=0;
 virtual void slot5()=0;
 virtual void slot6()=0;
 virtual void slot7()=0;
 virtual void slot8()=0;
 virtual void slot9()=0;
 virtual void slot10()=0;
 virtual void slot11()=0;
 virtual void slot12()=0;
 virtual void slot13()=0;
 virtual void slot14()=0;
 virtual void slot15()=0;
 virtual void slot16()=0;
 virtual void slot17()=0;
 virtual void slot18()=0;
 virtual void slot19()=0;
 virtual void slot20()=0;
 virtual void slot21()=0;
 virtual void slot22()=0;
 virtual void slot23()=0;
 virtual void slot24()=0;
 virtual void slot25()=0;
 virtual void slot26()=0;
 virtual void slot27()=0;
 virtual void slot28()=0;
 virtual void slot29()=0;
 virtual void slot30()=0;
 virtual void slot31()=0;
 virtual void slot32()=0;
 virtual void slot33()=0;
 virtual void slot34()=0;
 virtual void slot35()=0;
 virtual void slot36()=0;
 virtual void slot37()=0;
 virtual void slot38()=0;
 virtual void slot39()=0;
 virtual void slot40()=0;
 virtual void slot41()=0;
 virtual void slot42()=0;
 virtual void slot43()=0;
 virtual void slot44()=0;
 virtual void slot45()=0;
 virtual void slot46()=0;
 virtual void slot47()=0;
 virtual void slot48()=0;
 virtual void slot49()=0;
 virtual void slot50()=0;
 virtual void slot51()=0;
 virtual void slot52()=0;
 virtual void slot53()=0;
 virtual void slot54()=0;
 virtual void slot55()=0;
 virtual void slot56()=0;
 virtual void slot57()=0;
 virtual void slot58()=0;
 virtual void slot59()=0;
 virtual void slot60()=0;
 virtual void slot61()=0;
 virtual void slot62()=0;
 virtual void slot63()=0;
 virtual void slot64()=0;
 virtual void slot65()=0;
 virtual void slot66()=0;
 virtual void slot67()=0;
 virtual void slot68()=0;
 virtual void slot69()=0;
 virtual void slot70()=0;
 virtual void slot71()=0;
 virtual void slot72()=0;
 virtual void slot73()=0;
 virtual void slot74()=0;
 virtual void slot75()=0;
 virtual void slot76()=0;
 virtual void slot77()=0;
 virtual void slot78()=0;
 virtual void slot79()=0;
 virtual void slot80()=0;
 virtual void slot81()=0;
 virtual void slot82()=0;
 virtual void slot83()=0;
 virtual void slot84()=0;
 virtual void slot85()=0;
 virtual void slot86()=0;
 virtual void slot87()=0;
 virtual void slot88()=0;
 virtual void slot89()=0;
 virtual void slot90()=0;
 virtual void slot91()=0;
 virtual void slot92()=0;
 virtual void slot93()=0;
 virtual void slot94()=0;
 virtual void slot95()=0;
 virtual void slot96()=0;
 virtual void slot97()=0;
 virtual void slot98()=0;
 virtual void slot99()=0;
 virtual void slot100()=0;
 virtual void slot101()=0;
 virtual void slot102()=0;
 virtual void slot103()=0;
 virtual void slot104()=0;
 virtual void slot105()=0;
 virtual void slot106()=0;
 virtual void slot107()=0;
 virtual void slot108()=0;
 virtual void slot109()=0;
 virtual void slot110()=0;
 virtual void slot111()=0;
 virtual void slot112()=0;
 virtual void slot113()=0;
 virtual void slot114()=0;
 virtual void slot115()=0;
 virtual void slot116()=0;
 virtual void slot117()=0;
 virtual void slot118()=0;
 virtual void slot119()=0;
 virtual void slot120()=0;
 virtual void slot121()=0;
 virtual void slot122()=0;
 virtual void slot123()=0;
 virtual void slot124()=0;
 virtual void slot125()=0;
 virtual void slot126()=0;
 virtual void slot127()=0;
 virtual void slot128()=0;
 virtual void slot129()=0;
 virtual void slot130()=0;
 virtual void slot131()=0;
 virtual void slot132()=0;
 virtual void slot133()=0;
 virtual void slot134()=0;
 virtual void slot135()=0;
 virtual void slot136()=0;
 virtual void slot137()=0;
 virtual void slot138()=0;
 virtual void slot139()=0;
 virtual void slot140()=0;
 virtual void slot141()=0;
 virtual void slot142()=0;
 virtual void slot143()=0;
 virtual void slot144()=0;
 virtual void slot145()=0;
 virtual void slot146()=0;
 virtual int mode()=0;
};
BfmeTaintModeView *g_bfmeTaintModeView; // consuming name for the retail BSS cell


typedef unsigned char UnsignedByte;

class GlobalData
{
	unsigned char m_pad00[0xbec];

public:
	float m_lowRed;
	float m_lowGreen;
	float m_lowBlue;
	float m_highRed;
	float m_highGreen;
	float m_highBlue;
	UnsignedByte m_taintAlpha;
	unsigned char m_padca0[0xc6a - 0xc05];
	UnsignedByte m_taintOn;
};

extern GlobalData *TheWritableGlobalData;

class W3DShroud
{
public:
	UnsignedByte getShroudLevel(int x, int y);
};

class BaseHeightMapRenderObjClass
{
	unsigned char m_pad00[0x3878];

public:
	W3DShroud *m_shroud;
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;



class Rva000729CC
{
public:
	void rva00073CC0(int x, int y, int inputLevel, int inputTextureOnly);
 float getXScale() {return scaleX;} float getYScale() {return scaleY;}

private:
	int m_numCellsX;
	int m_numCellsY;
	unsigned char m_padding08[8]; float scaleX, scaleY;
	unsigned int *m_taintData;
	unsigned char m_padding1c[0x1c];
	UnsignedByte *m_cellLevels;
	UnsignedByte *m_referenceCellLevels;
	UnsignedByte m_trackDirtyCells;
	unsigned char m_padding41[3];
	_STL::set<int> m_dirty;
};

// ?rva00073CC0@Rva000729CC@@QAEXHHHH@Z @0x00073CC0
void Rva000729CC::rva00073CC0(int x, int y,
	int inputLevel, int inputTextureOnly)
{
 UnsignedByte level=(UnsignedByte)inputLevel; bool textureOnly=(bool)(UnsignedByte)inputTextureOnly;
	if (m_taintData == 0)
		return;
	if (x >= m_numCellsX)
		return;
	int maxY = m_numCellsY;
	if (y >= maxY)
		return;

	if (TheWritableGlobalData == 0)
		return;
	if (!TheWritableGlobalData->m_taintOn)
		return;

	if (!textureOnly)
	{
		int cell = x + y * m_numCellsX;
		m_cellLevels[cell] = level;
		if (m_trackDirtyCells)
			m_dirty.insert(cell);
	}

	int yForColor = y;
	
	float red=1,green=1,blue=1; int currentShroudLevel=255; int levelValue=level;
 if(g_bfmeTaintModeView && g_bfmeTaintModeView->mode()<=0) {
	if (level < 0x80)
	{
		int delta = 0x80 - levelValue;
		float fraction = (float)delta;
		int xMod5 = x % 5;
		fraction *= 0.0078125f;
		float base = 1.0f - fraction;
		float redAdjustment;
		float greenAdjustment;
		float blueAdjustment;

		if (xMod5 == 0 && yForColor % 2 == 0)
			redAdjustment = 0.03f;
		else
			redAdjustment = -0.02f;

		if (x % 3 == 0 && yForColor % 5 == 0)
			greenAdjustment = -0.02f;
		else
			greenAdjustment = 0.03f;

		if (x % 2 == 0 && yForColor % 3 == 0)
			blueAdjustment = -0.03f;
		else
			blueAdjustment = 0.02f;

		red = base + fraction * (TheWritableGlobalData->m_lowRed + redAdjustment);
		green = base + fraction * (TheWritableGlobalData->m_lowGreen + greenAdjustment);
		blue = base + fraction * (TheWritableGlobalData->m_lowBlue + blueAdjustment);
	}
	else if (level > 0x80)
	{
		int delta = levelValue - 0x80;
		float fraction = (float)delta;
		int xMod5 = x % 5;
		fraction *= 0.007874016f;
		float base = 1.0f - fraction;
		float redAdjustment;
		float greenAdjustment;
		float blueAdjustment;

		if (xMod5 == 0 && yForColor % 2 == 0)
			redAdjustment = 0.03f;
		else
			redAdjustment = -0.02f;

		if (x % 3 == 0 && yForColor % 5 == 0)
			greenAdjustment = -0.02f;
		else
			greenAdjustment = 0.03f;

		if (x % 2 == 0 && yForColor % 3 == 0)
			blueAdjustment = -0.03f;
		else
			blueAdjustment = 0.02f;

		red = base + fraction * (TheWritableGlobalData->m_highRed + redAdjustment);
		green = base + fraction * (TheWritableGlobalData->m_highGreen + greenAdjustment);
		blue = base + fraction * (TheWritableGlobalData->m_highBlue + blueAdjustment);
	}

 if(TheFireManager) {
 int colorX=WWMath::Float_To_Long(taintFloor((x+.5f)*getXScale()));
 int colorY=WWMath::Float_To_Long(taintFloor((y+.5f)*getYScale()));
 BfmeTaintColor rgb=TheFireManager->sample(colorX,colorY);
 red*=rgb.red;green*=rgb.green;blue*=rgb.blue;
 }

	W3DShroud *shroud = TheTerrainRenderObject->m_shroud;
	if (shroud)
		currentShroudLevel = shroud->getShroudLevel(x, yForColor);

 } else if(TheFireManager) {
 BfmeTaintColor rgb=TheFireManager->sample(int((x+.5f)*getXScale()),int((y+.5f)*getYScale()));
 red=rgb.red;green=rgb.green;blue=rgb.blue;
 }
	unsigned int redPixel =
		(unsigned int)(red * (float)currentShroudLevel);
	unsigned int greenPixel =
		(unsigned int)(green * (float)currentShroudLevel);
	unsigned int bluePixel =
		(unsigned int)(blue * (float)currentShroudLevel);
	unsigned int pixel = redPixel & 0xff;
	pixel |= (unsigned int)levelValue << 8;
	pixel <<= 8;
	pixel |= greenPixel & 0xff;
	pixel <<= 8;
	pixel |= bluePixel & 0xff;
	m_taintData[x + m_numCellsX * yForColor] = pixel;
}

class WorldHeightMap
{
public:
	unsigned char m_pad00[8];
	int m_xExtent;
	int m_yExtent;
	int m_borderSize;
	unsigned char m_pad14[0x120E8 - 0x14];
	int m_drawWidth;
	int m_drawHeight;
	int getXExtent() const { return m_xExtent; }
	int getYExtent() const { return m_yExtent; }
	int getBorderSize() const { return m_borderSize; }
	int getDrawWidth() const { return m_drawWidth; }
	int getDrawHeight() const { return m_drawHeight; }

};

class TextureClass
{
public:
	void Release_Ref();
};

class ShroudTextureHandle
{
public:
	TextureClass *m_p;
};

// Two-reference overload at retail 0x0011E670; the upstream shared
// textureloader.h declares a different three-argument overload.
class TextureLoader
{
public:
	static void Validate_Texture_Size(unsigned &width, unsigned &height);
};

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock {
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};
class Rva000728E2 { public: void rva000728E2(); };
class Rva007397D0 { public: void rva007397D0(); };
class TaintManager;
extern TaintManager *TheTaintManager;
class Rva006C0820 { public: void rva006C0820(); };
extern "C" __declspec(dllimport) double __cdecl ceil(double value);
__forceinline float taintCeil(float value) { return float(ceil(double(value))); }
#include <string.h>
// BFME 1 donor 9cbfb551fe20dae985f91f2319d8997287b6a705:
// game/GameEngineDevice/Source/W3DDevice/GameClient/TaintBufferFill.cpp.
// BFME 2 init (WB W3DTaint::init 0x82C800) calls this at 0x738C4.
// Native 0x738C4..0x73950 is the full 140-byte RET4 body. WB 0x82DA60
// independently confirms both loops and alpha clamp. The original method name
// is unknown; rva000738C4 describes the address. Preserve the legacy view used
// by setTaintLevel above while giving this separately proven entry its WB class.
class W3DTaint
{
public:
 void rva000738C4(unsigned char alpha);
 bool ReAcquireResources();
 void init(WorldHeightMap *map, float worldCellSizeX, float worldCellSizeY);
private:
 unsigned int m_numCellsX, m_numCellsY;
 int m_numMaxVisibleCellsX, m_numMaxVisibleCellsY;
 float m_cellWidth, m_cellHeight;
 unsigned int *m_taintData;
 void *m_dstTexture;
 int m_dstTextureWidth, m_dstTextureHeight;
 unsigned char m_pad28[0x38 - 0x28];
 unsigned char *m_cellLevels, *m_referenceCellLevels;
};

// ?rva000738C4@W3DTaint@@QAEXE@Z
void W3DTaint::rva000738C4(unsigned char alpha)
{
	GlobalData *g = TheWritableGlobalData;
	if (!g)
		return;
	if (!g->m_taintOn)
		return;
	unsigned char floor = g->m_taintAlpha;
	if (alpha < floor)
		alpha = floor;
	unsigned int color = alpha;
	color = (color << 8) | alpha;
	color = (color << 8) | alpha;
	color = (color << 8) | alpha;
	unsigned int *dst = m_taintData;
	unsigned int y;
	for (y = 0; y < m_numCellsY; y++)
	{
		unsigned int x;
		for (x = 0; x < m_numCellsX; )
		{
			*dst = color;
			x++;
			dst++;
		}
	}
	unsigned int i = 0;
	unsigned int row = (unsigned int)m_cellLevels;
	for (y = 0; y < m_numCellsY; y++)
	{
		i = 0;
		for (; i < m_numCellsX; )
		{
			*(char *)(i + row) = alpha;
			i++;
		}
		row += m_numCellsX;
	}
}

// Semantic donor: BFME1 9cbfb551 TaintBufferInit.cpp; WB 0x82C800
// establishes W3DTaint::init. Retail 0x739BE..0x73BFE establishes offsets.
// ?init@W3DTaint@@QAEXPAVWorldHeightMap@@MM@Z
void W3DTaint::init(WorldHeightMap *map,
	float worldCellSizeX, float worldCellSizeY)
{
	int dstTextureWidth = 0;
	int dstTextureHeight = 0;
	m_cellWidth = worldCellSizeX;
	m_cellHeight = worldCellSizeY;

	if (map)
	{
		m_numCellsX = WWMath::Float_To_Long(taintCeil(
			(float)(map->getXExtent() - map->getBorderSize() * 2 - 1)
				/ worldCellSizeX * 10.0f));
		m_numCellsY = WWMath::Float_To_Long(taintCeil(
			(float)(map->getYExtent() - map->getBorderSize() * 2 - 1)
				/ m_cellHeight * 10.0f));

		dstTextureWidth = m_numMaxVisibleCellsX =
			WWMath::Float_To_Long(taintFloor(
				(float)(map->getDrawWidth() - 1) / m_cellWidth
					* 10.0f)) + 1;
		dstTextureHeight = m_numMaxVisibleCellsY =
			WWMath::Float_To_Long(taintFloor(
				(float)(map->getDrawHeight() - 1) / m_cellHeight
					* 10.0f)) + 1;

		dstTextureWidth = m_numCellsX + 2;
		dstTextureHeight = m_numCellsY + 2;
		BFMEDX8DeviceLock lock;
		TextureLoader::Validate_Texture_Size(
			(unsigned &)dstTextureWidth, (unsigned &)dstTextureHeight);

	}

	m_cellLevels = new unsigned char[
		m_numCellsX * m_numCellsY];
	m_referenceCellLevels = new unsigned char[
		m_numCellsX * m_numCellsY];
	memset(m_referenceCellLevels, 0x80,
		m_numCellsX * m_numCellsY);
	memset(m_cellLevels, 0x80,
		m_numCellsX * m_numCellsY);

	if (TheWritableGlobalData && TheWritableGlobalData->m_taintOn)
	{
		m_taintData = new unsigned int[m_numCellsX * m_numCellsY];
		memset(m_taintData, 0, m_numCellsX * m_numCellsY * 4);
	}
	if (TheWritableGlobalData && TheWritableGlobalData->m_taintOn)
		rva000738C4(TheWritableGlobalData->m_taintAlpha);

	if (dstTextureWidth != m_dstTextureWidth ||
		dstTextureHeight != m_dstTextureHeight)
	{
		reinterpret_cast<Rva000728E2 *>(this)->rva000728E2();
	}

	if (!m_dstTexture)
	{
		m_dstTextureWidth = dstTextureWidth;
		m_dstTextureHeight = dstTextureHeight;
		ReAcquireResources();
	}
	if (TheWritableGlobalData && TheWritableGlobalData->m_taintOn && TheTaintManager)
		reinterpret_cast<Rva006C0820 *>(TheTaintManager)->rva006C0820();
}
