// cl: /O1 /Oy- /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// Retail 0x000AC6F9..0x000AC88E, 405 bytes: initialize twelve alpha tiles.
// Preserve the existing call-site name Rva000AC6F9SetupAlphaTiles; the target
// ignores ECX and returns with no stack arguments. ZH WorldHeightMap::
// setupAlphaTiles supplies the six directions plus inverted partners and the
// 64x64 alpha formula (BFME1 checkout dae380faa5f6fa536eec8d6ebbe877321d4cb51d).
// Target changes: 0x2AC0 TileData allocation and sequential WORD stores at +8.
// Its rowed ctor 0x00111850 and six-mip update 0x00111883 establish the
// RefCountClass base, 2BPP arrays and +0x2AB4 initialization; the final eight
// bytes are allocation-size padding with no invented field role.
// Existing WorldHeightMap::m_alphaTiles owns VA 0x00DEA1C8. Declare it, do not
// create a second array or pin. The native ctor is out of line: keeping only
// its declaration preserves construction cleanup and exact compiler EH data.
// This unit isolates the target /O1 settings from the /O2 donor home unit;
// existing matched home functions and the owned global remain unchanged.
typedef int Int;
typedef unsigned char UnsignedByte;

class RefCountClass
{
public:
	RefCountClass();
	virtual void Delete_This();
protected:
	virtual ~RefCountClass();
private:
	int m_refs;
};

class TileData : public RefCountClass
{
public:
	TileData();
	virtual ~TileData();
	UnsignedByte m_tileData[0x2000];
	UnsignedByte m_tileDataMip32[0x800];
	UnsignedByte m_tileDataMip16[0x200];
	UnsignedByte m_tileDataMip8[0x80];
	UnsignedByte m_tileDataMip4[0x20];
	UnsignedByte m_tileDataMip2[0x8];
	UnsignedByte m_tileDataMip1[0x4];
	int m_2AB4;
 unsigned char tail[8];
	UnsignedByte *getRGBDataForWidth(Int width);
	void updateMips();
};

extern "C" void *__cdecl memset(void *,int,unsigned int);
struct TBlendTileInfo { int blendNdx; unsigned char horiz,vert,rightDiagonal,leftDiagonal,inverted,longDiagonal; int customBlendEdgeClass; };
class WorldHeightMap {
 friend void Rva000AC6F9SetupAlphaTiles();
protected: static TileData *m_alphaTiles[12];
};
#define NUM_ALPHA_TILES 12
#define TILE_PIXEL_EXTENT 64
#define K_HORIZ 0
#define K_VERT 1
#define K_RDIAG 3
#define K_LDIAG 2
#define K_LRDIAG 5
#define K_LLDIAG 4
#define K_INV 6
void Rva000AC6F9SetupAlphaTiles(void)
{
	TBlendTileInfo blendInfo;
	if (WorldHeightMap::m_alphaTiles[0] != 0) return;
	Int k;
	for (k=0; k<NUM_ALPHA_TILES; k++) {
		memset(&blendInfo, 0, sizeof(blendInfo));
		Int baseK = k;
		if (k>=K_INV) {
			blendInfo.inverted = true;
			baseK -= K_INV;
		}
		switch(baseK) {
			case K_HORIZ : blendInfo.horiz = true; break;
			case K_VERT : blendInfo.vert = true; break;
			case K_LDIAG : blendInfo.leftDiagonal = true; break;
			case K_RDIAG : blendInfo.rightDiagonal = true; break;
			case K_LLDIAG : blendInfo.leftDiagonal = true; blendInfo.longDiagonal = true; break;
			case K_LRDIAG : blendInfo.rightDiagonal = true; blendInfo.longDiagonal = true; break;
		} // end of case.
		WorldHeightMap::m_alphaTiles[k] = new TileData;
		TileData *pTile = WorldHeightMap::m_alphaTiles[k];

		Int i, j;
		unsigned short *pDest = reinterpret_cast<unsigned short *>(pTile->m_tileData);
		for (j=0; j<TILE_PIXEL_EXTENT; j++) {
			for (i=0; i<TILE_PIXEL_EXTENT; i++) {
				Int h = i;
				Int v = j;
				Int alpha = 255;  // 0 - 255.
				if (blendInfo.horiz) {
					if (!blendInfo.inverted) h = TILE_PIXEL_EXTENT-h-1;
					alpha = (alpha*h)/(TILE_PIXEL_EXTENT-1);
				} else if (blendInfo.vert) {
					if (!blendInfo.inverted) v = TILE_PIXEL_EXTENT-v-1;
					alpha = (alpha*v)/(TILE_PIXEL_EXTENT-1);
				} else if (blendInfo.rightDiagonal) {
					h = TILE_PIXEL_EXTENT-h-1;
					if (!blendInfo.inverted) v = TILE_PIXEL_EXTENT-v-1;
					v += h;				// angled
					if (blendInfo.longDiagonal) {
						v -= TILE_PIXEL_EXTENT;
					}
					alpha = (alpha*v)/(TILE_PIXEL_EXTENT-1);
				} else if (blendInfo.leftDiagonal) {
					if (!blendInfo.inverted) v = TILE_PIXEL_EXTENT-v-1;
					v += h;				// angled
					if (blendInfo.longDiagonal) {
						v -= TILE_PIXEL_EXTENT;
					}
					alpha = (alpha*v)/(TILE_PIXEL_EXTENT-1);
				}
				
				if (alpha > 255) alpha = 255;
				if (alpha<0) alpha = 0;
				alpha = 255-alpha;
				
				
				*pDest = alpha;		// alpha.
				//*pDest = 255;
				pDest++;
			}
		}
		pTile->updateMips();
	}
}
