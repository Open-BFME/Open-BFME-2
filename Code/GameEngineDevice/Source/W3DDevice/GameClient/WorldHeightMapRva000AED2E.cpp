// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva000AED2E@Rva000AED2EWorldHeightMapView@@QAEPAEHHHHHH@Z retail
// 0x000AED2E..0x000AEED8 (428 bytes ret 0x18). BFME 2's six-argument
// WorldHeightMap::getPointerToTileData (Zero Hour's three-argument body plus
// a mode and a destination with its pitch; WorldBuilder twin 0x007722C0).
// Rejects out-of-map cells. Without a blend tile (or on a cliff cell per
// 0x000ABD19) and with a destination it copies the source tile's 2-byte
// pixels straight into the destination rows (TileData +0x2AB4 alternate for
// mode 1 via 0x00111784; hasRGBDataForWidth 0x001117B4; getRGBDataForWidth
// 0x000ABC71) and returns NULL. Otherwise it loads the raw tile into
// s_buffer (rawTile 0x000AC88E) blends the blend tile and with
// TheWritableGlobalData +0x44 the extra blend tile (blendTile 0x000ADDCE
// over the 16-byte blended-tile vector at +0x80B0) and returns s_buffer.
// s_buffer is the ledger's _s_buffer (0x009E81C8) owned by WorldHeightMap.cpp.
#include <string.h>
#include <vector>

typedef unsigned char UnsignedByte;
typedef short Short;
typedef int Int;

struct TBlendTileInfo
{
	Int m_data[4];
};

class Rva00111784DwordField
{
public:
	Int get() const;
};

class TileData
{
public:
	bool hasRGBDataForWidth(Int width);
	UnsignedByte *getRGBDataForWidth(Int width);
};

class Rva000ABD19
{
public:
	bool rva000ABD19(Int x, Int y);
};

class Rva000ADDCEWorldHeightMapView
{
public:
	bool rawTile(Short tile, Int width, UnsignedByte *buffer, Int bytes, Int mode);
	void blendTile(TBlendTileInfo *blend, Int width, Int mode);
};

class GlobalData
{
	char m_pad[0x44];

public:
	Int m_44; // +0x44
};
extern GlobalData *TheWritableGlobalData;

extern "C" UnsignedByte s_buffer[];

class Rva000AED2EWorldHeightMapView
{
public:
	UnsignedByte *rva000AED2E(Int xIndex, Int yIndex, Int width, Int mode, Int destArg, Int pitch);

private:
	char m_pad00[8];
	Int m_width; // +0x08
	Int m_height; // +0x0C
	char m_pad10[0x20 - 0x10];
	Int m_dataSize; // +0x20
	char m_pad24[0x98 - 0x24];
	Short *m_tileNdxes; // +0x98
	Int *m_blendTileNdxes; // +0x9C
	char m_padA0[4];
	Int *m_extraBlendTileNdxes; // +0xA4
	char m_padA8[0xB0 - 0xA8];
	TileData *m_sourceTiles[0x1000]; // +0xB0
	TileData *m_edgeTiles[0x1000]; // +0x40B0
	_STL::vector<TBlendTileInfo> m_blendedTiles; // +0x80B0
};

UnsignedByte *Rva000AED2EWorldHeightMapView::rva000AED2E(Int xIndex, Int yIndex, Int width, Int mode, Int destArg, Int pitch)
{
	Int ndx = yIndex * m_width + xIndex;
	if (yIndex < 0 || xIndex < 0 || xIndex >= m_width || yIndex >= m_height)
		return 0;
	if (ndx < 0 || ndx >= m_dataSize)
		return 0;
	Short tileNdx = m_tileNdxes[ndx];
	Int blendNdx = m_blendTileNdxes[ndx];
	Int extraNdx = m_extraBlendTileNdxes[ndx];
	if (reinterpret_cast<Rva000ABD19 *>(this)->rva000ABD19(xIndex, yIndex))
		blendNdx = 0;

	if (blendNdx <= 0 && destArg != 0)
	{
		if (tileNdx / 4 >= 0x1000)
			return 0;
		TileData *pSrc = m_sourceTiles[tileNdx / 4];
		if (mode == 1)
		{
			if (pSrc == 0)
				return 0;
			pSrc = reinterpret_cast<TileData *>(reinterpret_cast<Rva00111784DwordField *>(pSrc)->get());
		}
		if (pSrc == 0)
			return 0;
		if (!pSrc->hasRGBDataForWidth(2 * width))
			return 0;
		UnsignedByte *pSrcData = pSrc->getRGBDataForWidth(2 * width);
		if (tileNdx & 1)
			pSrcData += 2 * width;
		if (tileNdx & 2)
			pSrcData += width * width * 4;
		for (Int j = 0; j < width; j++)
		{
			memcpy(reinterpret_cast<UnsignedByte *>(destArg), pSrcData, width * 2);
			destArg += pitch * 2;
			pSrcData += width * 4;
		}
		return 0;
	}

	Rva000ADDCEWorldHeightMapView *view = reinterpret_cast<Rva000ADDCEWorldHeightMapView *>(this);
	if (!view->rawTile(tileNdx, width, s_buffer, 0x2000, mode))
		return 0;
	if (blendNdx > 0 && (unsigned)blendNdx < m_blendedTiles.size())
		view->blendTile(&m_blendedTiles[blendNdx], width, mode);
	if (TheWritableGlobalData->m_44 && extraNdx > 0 && (unsigned)extraNdx < m_blendedTiles.size())
		view->blendTile(&m_blendedTiles[extraNdx], width, mode);
	return s_buffer;
}
