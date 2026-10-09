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
union PackedColor { unsigned c; unsigned short w[2]; unsigned char b[4]; };
__forceinline void unpack(unsigned short color,unsigned int *dest) {
 PackedColor a,b;
 a.c=color<<3;
 a.b[1]<<=3;
 b.c=(color>>10)<<19;
 b.w[0]=a.w[0];
 b.c+=((b.c>>5)&0x3f3f3f);
 *dest=b.c;
}
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
  unsigned int rgb; unpack(tile->pixel,&rgb);
  unsigned char *data=(unsigned char*)&rgb;
  out->red=data[0]*(1.0/255.0);
  out->green=data[1]*(1.0/255.0);
  out->blue=data[2]*(1.0/255.0);
 }
}
