// cl: /O1 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// stlport

// BFME2 WorldHeightMap TGA tile helpers. Retail builds this family with
// /O1 (frame-pointer prologue, idiv division, push/pop materialization);
// the full ZH-port sibling TU builds /G7, which emits shift-based division
// and frameless code, so the /O1 bodies live here. Declarations mirror the
// Zero Hour reference (GameEngineDevice/Include/W3DDevice/GameClient/
// WorldHeightMap.h, GameEngine/Include/Common/InputStream.h).

typedef int Int;
typedef bool Bool;
typedef short Short;
typedef unsigned char UnsignedByte;

#define TILE_PIXEL_EXTENT 64

class InputStream
{
public:
	virtual Int read(void *pData, Int numBytes);
};

class TileData;

class WorldHeightMap
{
public:
	static Int countTiles(InputStream *pStr, Bool *halfTile);
	static Bool readTiles(InputStream *pStr, TileData **tiles, Int numRows);
};

typedef struct {
	UnsignedByte	idLength;
	UnsignedByte	colorMapType; // 0 = rgb, 1 = indexed.
	UnsignedByte	imageType; //0x1 = indexed, 0x2 = rgb, 0x8 = rle.
	UnsignedByte	colorMapInfo[5]; // we ignore, only do rgb.
	Short			xOrigin;
	Short			yOrigin;
	Short			imageWidth;
	Short			imageHeight;
	UnsignedByte	pixelDepth;
	UnsignedByte	flags; //  &0x0F = alpha channel bits, &0x10 is right to left flag,
						   // 0x20 is top to bottom flag.  (0x0? is left to right, bottom to top)
						   // 0x3? is top to bottom, right to left.
} TTargaHeader;

/// Count how many tiles come in from a targa file.
Int WorldHeightMap::countTiles(InputStream *pStr, Bool *halfTile)
{
	TTargaHeader hdr;
	if (halfTile) {
		*halfTile = false;
	}
	Int len = pStr->read(&hdr,sizeof(hdr));
	if (len!=sizeof(hdr)) return(0);
	Int tileWidth = hdr.imageWidth/TILE_PIXEL_EXTENT;
	Int tileHeight = hdr.imageHeight/TILE_PIXEL_EXTENT;

	if (hdr.colorMapType != 0) {
		return(0); // we don't do indexed at this time. jba.
	}
	if (hdr.imageType != 0x2 && hdr.imageType != 0xA) {
		return(0); // we don't do indexed at this time. jba.
	}

	if (hdr.pixelDepth < 24) return(false);
	if (hdr.pixelDepth > 32) return(false);
	// 4x4 gives 16,
	// 3x3 gives 9,
	// 2x2 gives 4,
	// 1x1 gives 1,
	// else 0;
	if (tileWidth>16 || tileHeight>16) return(0);  // don't do huge images, or bad files.
	Int width;
	for (width = 16; width > 0; width--) {
		if (tileWidth >= width && tileHeight >= width) {
			return width*width;
		}
	}
	if (halfTile && hdr.imageHeight==TILE_PIXEL_EXTENT/2 && hdr.imageWidth==TILE_PIXEL_EXTENT/2) {
		return (*halfTile = true);
	}
	return(0);
}
