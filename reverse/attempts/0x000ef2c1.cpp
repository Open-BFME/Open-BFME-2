// ?updateFlat@TerrainTextureClass@@QAEHPAVWorldHeightMap@@HHHHH@Z
// partial score=0.65 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


// BFME1 clean donor: 34f59164f6d1efd413c5fd37f4894ec834c3c0fe
// game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006D5750Update.cpp.
// BFME2 native EF4A3..EF63F and WB8C5080 prove the extra tile-kind argument,
// six-word tile lookup, out-of-line memcpy and Log_DX8_ErrorCode calls.
// Original setLOD body retained and reverified with the same TextureClass base.
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "WW3D2/Texture.h"
#include "WWMATH/Matrix3d.h"
#include "common/AsciiString.h"
#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "W3DDevice/GameClient/TileData.h"
#include "WW3D2/dx8wrapper.h"
#include "d3dx8tex.h"

struct Rva006D53A0SurfaceDesc
{
	D3DFORMAT Format;
	D3DRESOURCETYPE Type;
	DWORD Usage;
	D3DPOOL Pool;
	UINT Size;
	UINT reserved;
	UINT Width;
	UINT Height;
};

class SurfaceResource
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void __stdcall Release(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual int __stdcall GetDesc(Rva006D53A0SurfaceDesc *desc);
	virtual int __stdcall LockRect(D3DLOCKED_RECT *locked, const RECT *rect, unsigned flags);
	virtual int __stdcall UnlockRect(void);
};

class BfmeD3DTexture
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual int __stdcall GetSurfaceLevel(unsigned level, SurfaceResource **surface);
};

extern void Log_DX8_ErrorCode(unsigned int);
static __forceinline void BFME_DX8_ErrorCode(int result) { if(result) Log_DX8_ErrorCode(result); }
class Rva000AED2EWorldHeightMapView { public: unsigned char *rva000AED2E(int,int,int,int,int,int); };

#include <string.h>

// Retail calls memcpy out of line.

// TU-scoped: inputs/reference/shims/sweep/d3dx8tex.h routes to the validated DX8 shim,
// which declares D3DXFilterTexture but not the memory loader this body needs.
extern "C" HRESULT __stdcall D3DXLoadSurfaceFromMemory(void *pDestSurface,
	const void *pDestPalette, const void *pDestRect, const void *pSrcMemory,
	D3DFORMAT SrcFormat, unsigned SrcPitch, const void *pSrcPalette,
	const void *pSrcRect, unsigned long Filter, unsigned long ColorKey);

// The shim's D3DX_FILTER_BOX is 3; the SDK the retail build used numbers BOX 5,
// which is the value in the image.
#define RVA006D5750_FILTER_BOX 5

// Zero Hour's TerrainTex.h has no updateFlatDXT1, so this TU declares
// TerrainTextureClass itself instead of including that header.
class TerrainTextureClass : public TextureClass
{
public:
	void setLOD(Int LOD);
 int updateFlat(WorldHeightMap*,int,int,int,int,int);
	Int updateFlatDXT1(WorldHeightMap *htMap, Int xCell, Int yCell,
		Int cellWidth, Int pixelsPerCell, Int tileKind);
};

struct Rva006D5750SurfaceStorage
{
	Rva006D53A0SurfaceDesc desc;
};

Int TerrainTextureClass::updateFlatDXT1(WorldHeightMap *htMap, Int xCell,
	Int yCell, Int cellWidth, Int pixelsPerCell, Int tileKind)
{
	SurfaceResource *surface_level;
	Rva006D5750SurfaceStorage surface_storage;
	Rva006D53A0SurfaceDesc &surface_desc = surface_storage.desc;
	TerrainTextureClass *self = this;
	Int width = cellWidth * pixelsPerCell;
	UnsignedByte *buffer = (UnsignedByte *)(new UnsignedInt[width * width]);
	Int cellStride = pixelsPerCell * 4;

	Int cellX, cellY;
	for (cellX = 0; cellX < cellWidth; cellX++) {
		for (cellY = 0; cellY < cellWidth; cellY++) {
			UnsignedByte *pBGR = reinterpret_cast<Rva000AED2EWorldHeightMapView*>(htMap)->rva000AED2E(xCell + cellX, yCell + cellY, pixelsPerCell, tileKind, 0, 0);
			if (pBGR == NULL) continue;
			Int k;
			for (k = pixelsPerCell - 1; k >= 0; k--) {
				UnsignedByte *pBGRX = buffer + (cellWidth - cellY - 1) * cellStride * width +
					k * width * 4 + cellX * cellStride;
				memcpy(pBGRX, pBGR, pixelsPerCell * 4);
				pBGR += pixelsPerCell * TILE_BYTES_PER_PIXEL;
			}
		}
	}

	BFME_DX8_ErrorCode(reinterpret_cast<BfmeD3DTexture *>(self->Peek_D3D_Base_Texture())->GetSurfaceLevel(0, &surface_level));
	BFME_DX8_ErrorCode(surface_level->GetDesc(&surface_desc));
	if (surface_desc.Width != width) {
		delete [] buffer;
		return 0;
	}

	RECT source_rect;
	source_rect.top = 0;
	source_rect.left = 0;
	source_rect.bottom = width;
	source_rect.right = width;
	BFME_DX8_ErrorCode(D3DXLoadSurfaceFromMemory(surface_level, NULL, NULL,
		buffer, D3DFMT_X8R8G8B8, width * 4, NULL, &source_rect, D3DX_FILTER_NONE, 0));
	surface_level->Release();
	BFME_DX8_ErrorCode(D3DXFilterTexture(reinterpret_cast<IDirect3DTexture8 *>(self->Peek_D3D_Base_Texture()), NULL, 0, RVA006D5750_FILTER_BOX));
	delete [] buffer;
	return width;
}

void TerrainTextureClass::setLOD(Int LOD)
{
	if (Peek_D3D_Texture()) Peek_D3D_Texture()->SetLOD(LOD);
}

// C++ expression of the retail partial-register pixel transform. The native
// and unoptimized WB loops share the same hand-written register sequence.
static __forceinline unsigned terrainPixel1555(const unsigned char *source)
{
    unsigned pixel=*reinterpret_cast<const unsigned*>(source);
    unsigned high=(pixel>>19)<<10;
    unsigned short low=static_cast<unsigned short>(pixel);
    low=static_cast<unsigned short>((low&0xff)|((low&0xf800)>>3));
    low=static_cast<unsigned short>(low>>3);
    return static_cast<unsigned short>(low | high | 0x8000);
}

int TerrainTextureClass::updateFlat(WorldHeightMap *htMap, Int xCell, Int yCell, Int cellWidth, Int pixelsPerCell, Int tileKind)
{
	SurfaceResource *surface_level;
	Rva006D5750SurfaceStorage surface_storage;
	Rva006D53A0SurfaceDesc &surface_desc = surface_storage.desc;
	D3DLOCKED_RECT locked_rect;
	TerrainTextureClass *self = this;
	BFME_DX8_ErrorCode(reinterpret_cast<BfmeD3DTexture *>(self->Peek_D3D_Base_Texture())->GetSurfaceLevel(0, &surface_level));
	BFME_DX8_ErrorCode(surface_level->GetDesc(&surface_desc));
	if (surface_desc.Width != cellWidth * pixelsPerCell) {
		return false;
	}

	BFME_DX8_ErrorCode(surface_level->LockRect(&locked_rect, NULL, 0));
    if (surface_desc.Format == D3DFMT_A1R5G5B5) {
        for (int cellY=0; cellY<cellWidth; ++cellY) {
            for (int cellX=0; cellX<cellWidth; ++cellX) {
                unsigned short *destination = reinterpret_cast<unsigned short*>(locked_rect.pBits)
                    + ((cellWidth-cellY-1)*pixelsPerCell+pixelsPerCell-1)*surface_desc.Width
                    + cellX*pixelsPerCell;
                unsigned char *source = reinterpret_cast<Rva000AED2EWorldHeightMapView*>(htMap)->rva000AED2E(
                    xCell+cellX,yCell+cellY,pixelsPerCell,tileKind,reinterpret_cast<int>(destination),-static_cast<int>(surface_desc.Width));
                if (!source) continue;
                unsigned rows=pixelsPerCell;
                do {
                    unsigned *out=reinterpret_cast<unsigned*>(destination);
                    unsigned groups=static_cast<unsigned>(pixelsPerCell)>>2;
                    do {
                        out[0]=terrainPixel1555(source) | (terrainPixel1555(source+4)<<16);
                        out[1]=terrainPixel1555(source+8) | (terrainPixel1555(source+12)<<16);
                        source+=16; out+=2;
                    } while (--groups);
                    destination-=surface_desc.Width;
                } while (--rows);
            }
        }
    }

	surface_level->UnlockRect();
	surface_level->Release();
	BFME_DX8_ErrorCode(D3DXFilterTexture(reinterpret_cast<IDirect3DTexture8 *>(self->Peek_D3D_Base_Texture()), NULL, 0, 5));
	return surface_desc.Height;
}
