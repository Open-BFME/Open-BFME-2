// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
#include <string.h>
#include "wwmath.h"

// Reference: Open-BFME-1 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroudInitBfme.cpp.
// Identity: WB 0x7FC650 (W3DShroud.cpp lines 101..102); retail
// 0x00072B72..0x00072D5D. Retail establishes the height-map field offsets,
// 64-byte shroud layout, three buffer allocations and ShroudManager receiver.
// WWMath's established x87 conversion preserves retail's FISTP rounding.
typedef float Real;
typedef bool Bool;

// Retail IAT: MSVCR71.dll!ceil at VA 0x01359394, floor at 0x013593B8.
extern "C" __declspec(dllimport) double __cdecl ceil(double value);
extern "C" __declspec(dllimport) double __cdecl floor(double value);

__forceinline Real ShroudCeil(Real value)
{
	return (Real)ceil((double)value);
}

__forceinline Real ShroudFloor(Real value)
{
	return (Real)floor((double)value);
}

void *__cdecl operator new[](unsigned int size);

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
class ShroudManager;
extern ShroudManager *TheShroudManager;

class W3DShroud
{
public:
	Bool ReAcquireResources();
	void init(WorldHeightMap *map, Real worldCellSizeX,
		Real worldCellSizeY);

private:
	int m_numCellsX;
	int m_numCellsY;
	int m_numMaxVisibleCellsX;
	int m_numMaxVisibleCellsY;
	Real m_cellWidth;
	Real m_cellHeight;
	unsigned short *m_shroudData;
	ShroudTextureHandle m_dstTexture;
	int m_dstTextureWidth;
	int m_dstTextureHeight;
	int m_shroudFilter;
	Real m_drawOriginX;
	Real m_drawOriginY;
	unsigned char m_drawFogOfWar;
	unsigned char m_clearDstTexture;
	unsigned char m_borderShroudLevel;
	unsigned char m_pad37;
	unsigned char *m_finalFogData;
	unsigned char *m_currentFogData;
};

// ?init@W3DShroud@@QAEXPAVWorldHeightMap@@MM@Z
void W3DShroud::init(WorldHeightMap *map,
	Real worldCellSizeX, Real worldCellSizeY)
{
	int dstTextureWidth = 0;
	int dstTextureHeight = 0;
	m_cellWidth = worldCellSizeX;
	m_cellHeight = worldCellSizeY;

	if (map)
	{
		m_numCellsX = WWMath::Float_To_Long(ShroudCeil(
			(Real)(map->getXExtent() - map->getBorderSize() * 2 - 1)
				/ worldCellSizeX * 10.0f));
		m_numCellsY = WWMath::Float_To_Long(ShroudCeil(
			(Real)(map->getYExtent() - map->getBorderSize() * 2 - 1)
				/ m_cellHeight * 10.0f));

		dstTextureWidth = m_numMaxVisibleCellsX =
			WWMath::Float_To_Long(ShroudFloor(
				(Real)(map->getDrawWidth() - 1) / m_cellWidth
					* 10.0f)) + 1;
		dstTextureHeight = m_numMaxVisibleCellsY =
			WWMath::Float_To_Long(ShroudFloor(
				(Real)(map->getDrawHeight() - 1) / m_cellHeight
					* 10.0f)) + 1;

		dstTextureWidth = m_numCellsX + 2;
		dstTextureHeight = m_numCellsY + 2;
		BFMEDX8DeviceLock lock;
		TextureLoader::Validate_Texture_Size(
			(unsigned &)dstTextureWidth, (unsigned &)dstTextureHeight);

	}

	m_finalFogData = new unsigned char[
		m_numCellsX * m_numCellsY];
	m_currentFogData = new unsigned char[
		m_numCellsX * m_numCellsY];
	memset(m_currentFogData, 0,
		m_numCellsX * m_numCellsY);
	memset(m_finalFogData, 0,
		m_numCellsX * m_numCellsY);

	m_shroudData = new unsigned short[
		m_numCellsX * m_numCellsY];
	memset(m_shroudData, 0,
		m_numCellsX * m_numCellsY * 2);

	if (dstTextureWidth != m_dstTextureWidth ||
		dstTextureHeight != m_dstTextureHeight)
	{
		reinterpret_cast<Rva000728E2 *>(this)->rva000728E2();
	}

	if (!m_dstTexture.m_p)
	{
		m_dstTextureWidth = dstTextureWidth;
		m_dstTextureHeight = dstTextureHeight;
		ReAcquireResources();
	}
	if (TheShroudManager)
		reinterpret_cast<Rva007397D0 *>(TheShroudManager)->rva007397D0();
}
