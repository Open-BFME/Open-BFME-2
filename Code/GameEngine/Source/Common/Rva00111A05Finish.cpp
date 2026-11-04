// ?rva00111A05@TileData@@QAEXPBEH@Z
// cl: /O1 /MD
// Native111A05-111A8B, caller ABEA0 supplies64-row RGBA blocks plus stride.
// All seven target offsets agree with rowedTileData getRGBDataForWidthABC71.
// Semantic guide: ZH TileData::updateMips; native directly resamples original
// RGBA through1118EC at factors1,2,4,8,16,32,64 into packed16-bit buffers.
extern "C" void __cdecl Rva001118ECResampleRgb555(
    const unsigned char *,int,int,unsigned short *);
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/TileDataClass.h"
void TileData::rva00111A05(const unsigned char *source,int stride)
{
    Rva001118ECResampleRgb555(source,stride,1,reinterpret_cast<unsigned short *>(m_tileData));
    Rva001118ECResampleRgb555(source,stride,2,reinterpret_cast<unsigned short *>(m_tileDataMip32));
    Rva001118ECResampleRgb555(source,stride,4,reinterpret_cast<unsigned short *>(m_tileDataMip16));
    Rva001118ECResampleRgb555(source,stride,8,reinterpret_cast<unsigned short *>(m_tileDataMip8));
    Rva001118ECResampleRgb555(source,stride,16,reinterpret_cast<unsigned short *>(m_tileDataMip4));
    Rva001118ECResampleRgb555(source,stride,32,reinterpret_cast<unsigned short *>(m_tileDataMip2));
    Rva001118ECResampleRgb555(source,stride,64,reinterpret_cast<unsigned short *>(m_tileDataMip1));
}

// Pending pin: _Rva001118ECResampleRgb555 ->0x001118EC; full281B helper independently decoded.
