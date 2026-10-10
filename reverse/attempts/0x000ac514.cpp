// ?getTerrainColorAt@WorldHeightMap@@QAEXMMPAURGBColor@@@Z
// partial score=0.97 date=2026-10-10
// ?getTerrainColorAt@WorldHeightMap@@QAEXMMPAURGBColor@@@Z
// partial score=0.97
// 299B exact size; the RGB555 unpack is an inline asm block (matches retail EBX/BH merge, pointer-through-memory store).
// Only difference: retail places the first POP ECX of the floor() call cleanup before the FSTP [ebp+8]; cl puts FSTP first (4 lines).
// Tried: flag sweep (O1/Os/G5/G6/G7/Gy/Zi), x reassign, separate float temps, double math variants, QIfist (incompatible with arch:SSE).
// ?getTerrainColorAt@WorldHeightMap@@QAEXMMPAURGBColor@@@Z
// partial score=0.75 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Oy-
extern "C" __declspec(dllimport) double __cdecl floor(double);
__forceinline long round_float(float f) { long i; __asm { fld [f]
 fistp [i] } return i; }
struct RGBColor { float red,green,blue; };
class Rva000ABD00 { public: int rva000ABD00(unsigned int); };
struct Tile { char pad[0x2ab0]; unsigned short pixel; };
class WorldHeightMap { public: void getTerrainColorAt(float,float,RGBColor*); private: char pad[8]; int width,height,border; char pad14[0x20-0x14]; int dataSize; char pad24[0x98-0x24]; short *tileNdxes; };
void WorldHeightMap::getTerrainColorAt(float x,float y,RGBColor* out) {
 int ix=round_float((float)floor((double)(x*.1f)));
 int iy=round_float((float)floor((double)(y*.1f)));
 ix+=border; iy+=border;
 out->red=out->green=out->blue=0;
 if(ix<0)ix=0;if(iy<0)iy=0;
 if(ix>=width)ix=width-1;
 if(iy>=height)iy=height-1;
 int ndx=iy*width+ix;
 if(ndx<0||ndx>=dataSize)return;
 short tileNdx=tileNdxes[ndx];
 tileNdx=tileNdx>>2;
 Tile* tile=(Tile*)((Rva000ABD00*)this)->rva000ABD00(tileNdx);
 if(tile) {
  unsigned int rgb;
  unsigned short color=tile->pixel;
  unsigned int *dest=&rgb;
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
  unsigned char *data=(unsigned char*)&rgb;
  out->red=data[0]*(1.0/255.0);
  out->green=data[1]*(1.0/255.0);
  out->blue=data[2]*(1.0/255.0);
 }
}
