// ?rva00111A05@TileData@@QAEXPBEH@Z
// partial score=1.0 date=2026-10-04
// cl: /O1 /MD
// Native111A05-111A8B, caller ABEA0 supplies64-row RGBA blocks plus stride.
// All seven target offsets agree with rowedTileData getRGBDataForWidthABC71.
// Semantic guide: ZH TileData::updateMips; native directly resamples original
// RGBA through1118EC at factors1,2,4,8,16,32,64 into packed16-bit buffers.
extern "C" void __cdecl Rva001118ECResampleRgb555(
    const unsigned char *,int,int,unsigned short *);
class TileData {
    unsigned char prefix[8];
    unsigned short mip64[64*64],mip32[32*32],mip16[16*16],mip8[8*8];
    unsigned short mip4[4*4],mip2[2*2],mip1[1];
public:
    void rva00111A05(const unsigned char *source,int stride);
};
// ?TileData::rva00111A05 present-unmatched
void TileData::rva00111A05(const unsigned char *source,int stride)
{
    Rva001118ECResampleRgb555(source,stride,1,mip64);
    Rva001118ECResampleRgb555(source,stride,2,mip32);
    Rva001118ECResampleRgb555(source,stride,4,mip16);
    Rva001118ECResampleRgb555(source,stride,8,mip8);
    Rva001118ECResampleRgb555(source,stride,16,mip4);
    Rva001118ECResampleRgb555(source,stride,32,mip2);
    Rva001118ECResampleRgb555(source,stride,64,mip1);
}

// Pending pin: _Rva001118ECResampleRgb555 ->0x001118EC; full281B helper independently decoded.
