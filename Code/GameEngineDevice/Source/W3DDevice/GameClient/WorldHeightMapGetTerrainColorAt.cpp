// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include
// ?getTerrainColorAt@WorldHeightMap@@QAEXMMPAURGBColor@@@Z retail 0x000AC514
// (299 bytes). Zero Hour WorldHeightMap::getTerrainColorAt over BFME 2's
// layout (width/height/border at +0x08/+0x0C/+0x10, data size +0x20, tile
// indices +0x98). REAL_TO_INT_FLOOR is ZH's fast_float2long_round(floorf(x)).
// BFME 2 reads the source tile's one-pixel colour as a 16-bit RGB555 word at
// +0x2AB0 and expands it to 8:8:8 with an inline asm helper: retail spills the
// word and the destination pointer to frame slots, reloads them inside the
// block and clobbers EDI (the MSVC inline-asm shape), uses partial-register
// shl bh / mov ax,bx no C++ spelling lowers to, and the same unpack sequence
// occurs at five more sites in the TileData code.
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
__forceinline void unpackRGB555(unsigned short color, unsigned int *dest)
{
	__asm {
		movzx eax, color
		mov ebx, eax
		shr eax, 0Ah
		shl ebx, 3
		shl eax, 13h
		shl bh, 3
		mov ax, bx
		mov ebx, eax
		shr ebx, 5
		and ebx, 3F3F3Fh
		add eax, ebx
		mov edi, dest
		mov [edi], eax
	}
}
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(floorf(x)))
#include "Lib/RGBColor.h"
class Rva000ABD00 { public: int rva000ABD00(unsigned int); };
struct Rva000AC514Tile { char pad[0x2ab0]; unsigned short pixel; };
#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"
void WorldHeightMap::getTerrainColorAt(float x, float y, RGBColor *pColor)
{
	int xIndex = REAL_TO_INT_FLOOR(x / 10.0f);
	int yIndex = REAL_TO_INT_FLOOR(y / 10.0f);
	xIndex += m_borderSize;
	yIndex += m_borderSize;
	pColor->red = pColor->green = pColor->blue = 0;
	if (xIndex < 0) xIndex = 0;
	if (yIndex < 0) yIndex = 0;
	if (xIndex >= m_width) xIndex = m_width - 1;
	if (yIndex >= m_height) yIndex = m_height - 1;
	int ndx = (yIndex * m_width) + xIndex;
	if (ndx < 0 || ndx >= m_dataSize) return;
	short tileNdx = m_tileNdxes[ndx];
	tileNdx = tileNdx >> 2;
	Rva000AC514Tile *pTile = (Rva000AC514Tile *)((Rva000ABD00 *)this)->rva000ABD00(tileNdx);
	if (pTile) {
		unsigned int rgb;
		unsigned short color = pTile->pixel;
		unsigned int *dest = &rgb;
		unpackRGB555(color, dest);
		unsigned char *pData = (unsigned char *)&rgb;
		pColor->red = pData[0] * (1.0 / 255.0);
		pColor->green = pData[1] * (1.0 / 255.0);
		pColor->blue = pData[2] * (1.0 / 255.0);
	}
}
