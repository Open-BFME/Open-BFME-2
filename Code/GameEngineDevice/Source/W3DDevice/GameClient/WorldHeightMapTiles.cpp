// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// stlport

// BFME2 WorldHeightMap TGA tile helpers. Retail builds this family with
// /O1 (frame-pointer prologue, idiv division, push/pop materialization);
// the full ZH-port sibling TU builds /G7, which emits shift-based division
// and frameless code, so the /O1 bodies live here. Declarations mirror the
// Zero Hour reference (GameEngineDevice/Include/W3DDevice/GameClient/
// WorldHeightMap.h, GameEngine/Include/Common/InputStream.h).

#include <string.h>

// Array new and delete bind to the game's array operators, not the scalar ones.
#include <new>

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

// ABI view: refcounted 0x2AC0-byte tile whose vtable slot 0 deletes it; the
// rowed members keep their address-derived names.
#include "../../../Include/W3DDevice/GameClient/TileDataClass.h"

// Rowed getter of the companion normal-map tile at TileData+0x2AB4.
#include "../../../Include/W3DDevice/GameClient/Rva00111784DwordField.h"

class GlobalData;
extern GlobalData *TheWritableGlobalData;
// Retail tests the normal-map switch at TheWritableGlobalData+0x49.
struct GlobalDataNormalMapView
{
	char m_pad[0x49];
	Bool m_useNormalMaps;
};

#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"

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

// Flat normal (0x7F,0x7F) row for tiles whose normal map has no source stream.
static UnsignedByte s_defaultNormalRow[TILE_PIXEL_EXTENT*4];

/*Break down a .tga file into a collection of tiles.  numRows * numRows total tiles.*/
Bool WorldHeightMap::readTiles(InputStream *pStr, InputStream *pNormalStr, TileData **tiles, Int numRows)
{
	TTargaHeader hdr;
	pStr->read(&hdr, sizeof(hdr));
	Int tileWidth = hdr.imageWidth/TILE_PIXEL_EXTENT;
	Int tileHeight = hdr.imageHeight/TILE_PIXEL_EXTENT;

	if (hdr.imageHeight==TILE_PIXEL_EXTENT/2) {
		tileHeight = 1;
	}
	if (hdr.imageWidth==TILE_PIXEL_EXTENT/2) {
		tileWidth = 1;
	}

	if (tileWidth<numRows && tileHeight<numRows) {
		return(false);
	}
	if (hdr.imageType & 0x08) {
		return(false);
	}
	if (hdr.imageWidth > 1024) {
		return(false);
	}
	Int bytesPerPixel = (hdr.pixelDepth+7)/8;
	if (bytesPerPixel < 3 || bytesPerPixel > 4) {
		return(false);
	}
	Int normalBytesPerPixel = 0;
	if (pNormalStr) {
		TTargaHeader normalHdr;
		pNormalStr->read(&normalHdr, sizeof(normalHdr));
		if (normalHdr.imageHeight != hdr.imageHeight || normalHdr.imageWidth != hdr.imageWidth) {
			return(false);
		}
		if (normalHdr.imageType & 0x08) {
			return(false);
		}
		normalBytesPerPixel = (normalHdr.pixelDepth+7)/8;
		if (normalBytesPerPixel < 3 || normalBytesPerPixel > 4) {
			return(false);
		}
	}
	for (Int i=0; i<numRows*numRows; i++) {
		if (tiles[i] == NULL) {
			tiles[i] = new TileData;
		}
		if (((GlobalDataNormalMapView *)TheWritableGlobalData)->m_useNormalMaps && ((Rva00111784DwordField *)tiles[i])->get() == 0) {
			TileData *normalTile = new TileData;
			tiles[i]->rva0011178B(normalTile);
			if (normalTile) {
				if (--normalTile->NumRefs == 0) {
					normalTile->Delete_This();
				}
			}
		}
	}
	UnsignedByte *buf = new UnsignedByte[hdr.imageWidth*4*TILE_PIXEL_EXTENT];
	UnsignedByte *normalBuf = NULL;
	if (pNormalStr) {
		normalBuf = new UnsignedByte[hdr.imageWidth*4*TILE_PIXEL_EXTENT];
	}
	for (Int tileRow=0; tileRow<numRows; tileRow++) {
		for (Int row=0; row<TILE_PIXEL_EXTENT; row++) {
			if (tileRow*TILE_PIXEL_EXTENT+row < hdr.imageHeight) {
				pStr->read(buf+hdr.imageWidth*4*row, hdr.imageWidth*bytesPerPixel);
				if (bytesPerPixel == 3) {
					// Widen BGR to BGRA in place, last pixel first.
					UnsignedByte *src = buf+hdr.imageWidth*4*row;
					UnsignedByte *dst = src;
					src += hdr.imageWidth*3;
					dst += hdr.imageWidth*4;
					for (Int col=hdr.imageWidth; col>0; col--) {
						src -= 3;
						dst -= 4;
						dst[3] = 0;
						dst[2] = src[2];
						dst[1] = src[1];
						dst[0] = src[0];
					}
				}
				if (pNormalStr) {
					pNormalStr->read(normalBuf+hdr.imageWidth*4*row, hdr.imageWidth*normalBytesPerPixel);
					if (normalBytesPerPixel == 3) {
						UnsignedByte *src = normalBuf+hdr.imageWidth*4*row;
						UnsignedByte *dst = src;
						src += hdr.imageWidth*3;
						dst += hdr.imageWidth*4;
						for (Int col=hdr.imageWidth; col>0; col--) {
							src -= 3;
							dst -= 4;
							dst[2] = src[2];
							dst[1] = src[1];
							dst[0] = src[0];
						}
					}
					// The normal map carries the color map's alpha.
					UnsignedByte *srcAlpha = buf+hdr.imageWidth*4*row;
					UnsignedByte *dstAlpha = normalBuf+hdr.imageWidth*4*row;
					for (Int col=hdr.imageWidth; col>0; col--, srcAlpha+=4, dstAlpha+=4) {
						*dstAlpha = srcAlpha[3];
					}
				}
			} else {
				memset(buf+hdr.imageWidth*4*row, 0, hdr.imageWidth*4);
				if (pNormalStr) {
					UnsignedByte *dst = normalBuf+hdr.imageWidth*4*row;
					for (Int col=0; col<hdr.imageWidth; col++, dst+=4) {
						dst[3] = 0;
						dst[0] = 0;
						dst[2] = 0x7F;
						dst[1] = 0x7F;
					}
				}
			}
		}
		for (Int i=0; i<numRows; i++) {
			if ((i+1)*TILE_PIXEL_EXTENT > hdr.imageWidth) {
				break;
			}
			tiles[i]->rva00111A05(buf+i*TILE_PIXEL_EXTENT*4, hdr.imageWidth*4);
			if (((Rva00111784DwordField *)tiles[i])->get()) {
				if (normalBuf) {
					((TileData *)((Rva00111784DwordField *)tiles[i])->get())->rva00111A05(normalBuf+i*TILE_PIXEL_EXTENT*4, hdr.imageWidth*4);
				} else {
					if (s_defaultNormalRow[1] == 0) {
						for (Int j=0; j<TILE_PIXEL_EXTENT; j++) {
							s_defaultNormalRow[j*4+2] = 0x7F;
							s_defaultNormalRow[j*4+1] = 0x7F;
						}
					}
					((TileData *)((Rva00111784DwordField *)tiles[i])->get())->rva00111A05(s_defaultNormalRow, 0);
				}
			}
		}
		tiles += numRows;
	}
	delete [] normalBuf;
	delete [] buf;
	return(true);
}
