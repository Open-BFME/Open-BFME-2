// ?init@W3DShroud@@QAEXPAVWorldHeightMap@@MM@Z
// partial score=0.94 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME W3DShroud::init.  The BFME WorldHeightMap moves the width, height,
// border, and draw extents relative to the Zero Hour header; keep both views
// local to this TU until the class identity is recovered from the image.

#include <string.h>

typedef float Real;
typedef unsigned char Bool;

// Retail IAT: MSVCR71.dll!ceil at VA 0x01359394, floor at 0x013593B8.
extern "C" __declspec(dllimport) double __cdecl ceil(double value);
extern "C" __declspec(dllimport) double __cdecl floor(double value);

__forceinline long Rva0071A150FloatToLong(Real value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

__forceinline Real Rva0071A150Ceil(Real value)
{
	return (Real)ceil((double)value);
}

__forceinline Real Rva0071A150Floor(Real value)
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
};

class TextureClass
{
public:
	void Release_Ref();
};

class Rva0071A150TexHandle
{
public:
	TextureClass *m_p;
};

__forceinline void Rva0071A150ReleaseTexture(TextureClass *&texture)
{
	if (texture)
	{
		texture->Release_Ref();
		texture = 0;
	}
}

// Retail call target 0x009056F0 is the real ?Validate_Texture_Size@TextureLoader@@SAXAAI0@Z
// body (two reference arguments), defined by
// game/Libraries/Source/WWVegas/WW3D2/TextureLoaderValidateTextureSize.cpp.
// Declared here rather than included: textureloader.h carries the upstream
// three-argument overload, which mangles differently.
class TextureLoader
{
public:
	static void Validate_Texture_Size(unsigned &width, unsigned &height);
};

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
struct ShroudInitDeviceLock { ShroudInitDeviceLock(){BFME_DX8_Thread_Lock();} ~ShroudInitDeviceLock(){BFME_DX8_Thread_Assert();} };
class Rva000728E2 { public: void rva000728E2(); };



// Retail call target 0x008F7420 is ?m@Gen_008f7420@@QAEXXZ (defined by
// game/gen_small/fun_005.cpp), so the call is respelled onto that class and
// member directly instead of a stand-in PartitionManager::notify.
class Rva007397D0
{
public:
	void rva007397D0();
};

class ShroudManager;
extern ShroudManager *TheShroudManager;

#define ThePartitionManager (*reinterpret_cast<Rva007397D0 **>(&TheShroudManager))

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
	Rva0071A150TexHandle m_dstTexture;
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
		m_numCellsX = Rva0071A150FloatToLong(Rva0071A150Ceil(
			(Real)(map->m_xExtent - map->m_borderSize * 2 - 1)
				/ worldCellSizeX * 10.0f));
		m_numCellsY = Rva0071A150FloatToLong(Rva0071A150Ceil(
			(Real)(map->m_yExtent - map->m_borderSize * 2 - 1)
				/ m_cellHeight * 10.0f));

		dstTextureWidth = m_numMaxVisibleCellsX =
			Rva0071A150FloatToLong(Rva0071A150Floor(
				(Real)(map->m_drawWidth - 1) / m_cellWidth
					* 10.0f)) + 1;
		dstTextureHeight = m_numMaxVisibleCellsY =
			Rva0071A150FloatToLong(Rva0071A150Floor(
				(Real)(map->m_drawHeight - 1) / m_cellHeight
					* 10.0f)) + 1;

		dstTextureWidth = m_numCellsX + 2;
		dstTextureHeight = m_numCellsY + 2;
		{ ShroudInitDeviceLock lock;
// Two-argument retail overload, matched at 0x009056F0 (no linker alias needed).
		TextureLoader::Validate_Texture_Size(
			(unsigned &)dstTextureWidth, (unsigned &)dstTextureHeight);
		}
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
		((Rva000728E2 *)this)->rva000728E2();
	}

	if (!m_dstTexture.m_p)
	{
		m_dstTextureWidth = dstTextureWidth;
		m_dstTextureHeight = dstTextureHeight;
		reinterpret_cast<W3DShroud *>(this)->ReAcquireResources();
	}
	if (ThePartitionManager)
		ThePartitionManager->rva007397D0();
}
