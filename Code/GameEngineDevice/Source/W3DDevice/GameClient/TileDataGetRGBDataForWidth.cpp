// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// ?getRGBDataForWidth@TileData@@QAEPAEH@Z @0x000ABC71 86B
// BFME2 TileData::getRGBDataForWidth. Donor: open-bfme-1
// Code/GameEngineDevice/Source/W3DDevice/GameClient/TileData.cpp:68 and
// GeneralsMD Code/GameEngineDevice/Source/W3DDevice/GameClient/TileData.cpp:65
// (same if-chain). Retail keeps the order but halves every level: word
// writes in setupAlphaTiles @0x000AC6F9 (lea [ebx+8], mov word [ecx]) plus
// push 0x2AC0 new size, doMip @0x001117E3 word averaging, updateMips
// @0x00111883 offsets 0x2008/0x2808/0x2A08/0x2A88/0x2AA8/0x2AB0 and ctor
// @0x00111850 vtable 0x007CFAC0 prove 16-bit 2BPP layout. Caller pin read
// from WorldHeightMap::getRGBAlphaDataForWidth @0x000AC6F1 (row 0x000AC6A6).

typedef int Int;
typedef unsigned char UnsignedByte;

extern "C" void __cdecl Rva001117E3Downsample(
	unsigned short *source, Int width, unsigned short *destination);

#include "../../../Include/W3DDevice/GameClient/TileDataClass.h"
// RefCountClass's base teardown is inline here, as in TileData.cpp.
inline RefCountClass::~RefCountClass() {}

#define TILE_PIXEL_EXTENT_MIP1 32
#define TILE_PIXEL_EXTENT_MIP2 16
#define TILE_PIXEL_EXTENT_MIP3 8
#define TILE_PIXEL_EXTENT_MIP4 4
#define TILE_PIXEL_EXTENT_MIP5 2
#define TILE_PIXEL_EXTENT_MIP6 1

UnsignedByte *TileData::getRGBDataForWidth(Int width)
{
	if (width == TILE_PIXEL_EXTENT_MIP1) return m_tileDataMip32;
	if (width == TILE_PIXEL_EXTENT_MIP2) return m_tileDataMip16;
	if (width == TILE_PIXEL_EXTENT_MIP3) return m_tileDataMip8;
	if (width == TILE_PIXEL_EXTENT_MIP4) return m_tileDataMip4;
	if (width == TILE_PIXEL_EXTENT_MIP5) return m_tileDataMip2;
	if (width == TILE_PIXEL_EXTENT_MIP6) return m_tileDataMip1;
	return m_tileData;
}

TileData::TileData()
{
	m_2AB4 = 0;
}

void TileData::updateMips()
{
	Rva001117E3Downsample(reinterpret_cast<unsigned short *>(m_tileData), 0x40,
		reinterpret_cast<unsigned short *>(m_tileDataMip32));
	Rva001117E3Downsample(reinterpret_cast<unsigned short *>(m_tileDataMip32), 0x20,
		reinterpret_cast<unsigned short *>(m_tileDataMip16));
	Rva001117E3Downsample(reinterpret_cast<unsigned short *>(m_tileDataMip16), 0x10,
		reinterpret_cast<unsigned short *>(m_tileDataMip8));
	Rva001117E3Downsample(reinterpret_cast<unsigned short *>(m_tileDataMip8), 0x08,
		reinterpret_cast<unsigned short *>(m_tileDataMip4));
	Rva001117E3Downsample(reinterpret_cast<unsigned short *>(m_tileDataMip4), 0x04,
		reinterpret_cast<unsigned short *>(m_tileDataMip2));
	Rva001117E3Downsample(reinterpret_cast<unsigned short *>(m_tileDataMip2), 0x02,
		reinterpret_cast<unsigned short *>(m_tileDataMip1));
}
