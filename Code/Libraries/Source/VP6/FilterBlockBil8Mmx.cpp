// cl: /MD
// Clean room: reverse/vp6_cleanroom/specs/001d7200.md plus retail only. No
// decoder source was consulted.
//
// FilterBlockBil_8_mmx retail 0x001D7200 (204 bytes): picks the horizontal,
// vertical or two-dimensional bilinear MMX filter from the distance between
// the two reference pointers (1, one line, one line minus 1 or plus 1). The
// weight table (retail VA 0x00DB81B0) is nine 32-byte rows, the last being
// zero padding after phase 8; its 16-byte alignment is witnessed.

extern const unsigned short g_rva00DB81B0Weights[9][16];
extern "C" void __cdecl FilterBlock1d_hb8_mmx(const void *,void *,int,int,int,int,const void *);
extern "C" void __cdecl FilterBlock1d_vb8_mmx(const void *,void *,int,int,int,int,const void *);
extern "C" void __cdecl FilterBlock2dBil_mmx(const unsigned char *,unsigned char *,int,const void *,const void *);
extern "C" void __cdecl FilterBlockBil_8_mmx(const unsigned char *a,const unsigned char *b,unsigned char *destination,int stride,int xPhase,int yPhase)
{
 int distance=b-a;
 if(distance<0) {const unsigned char *old=a;a=b;distance=old-a;}
 if(distance==1)FilterBlock1d_hb8_mmx(a,destination,stride,1,8,8,g_rva00DB81B0Weights[xPhase]);
 else if(distance==stride)FilterBlock1d_vb8_mmx(a,destination,stride,stride,8,8,g_rva00DB81B0Weights[yPhase]);
 else if(distance==stride-1)FilterBlock2dBil_mmx(a-1,destination,stride,g_rva00DB81B0Weights[xPhase],g_rva00DB81B0Weights[yPhase]);
 else if(distance==stride+1)FilterBlock2dBil_mmx(a,destination,stride,g_rva00DB81B0Weights[xPhase],g_rva00DB81B0Weights[yPhase]);
}

// Native VA DB81B0 contains exactly these nine32B interpolation rows; the
// final row is followed by zero padding. Preserve its witnessed16B alignment.
__declspec(align(16)) extern const unsigned short g_rva00DB81B0Weights[9][16] = {
    {128,128,128,128,128,128,128,128,0,0,0,0,0,0,0,0},
    {112,112,112,112,112,112,112,112,16,16,16,16,16,16,16,16},
    {96,96,96,96,96,96,96,96,32,32,32,32,32,32,32,32},
    {80,80,80,80,80,80,80,80,48,48,48,48,48,48,48,48},
    {64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64},
    {48,48,48,48,48,48,48,48,80,80,80,80,80,80,80,80},
    {32,32,32,32,32,32,32,32,96,96,96,96,96,96,96,96},
    {16,16,16,16,16,16,16,16,112,112,112,112,112,112,112,112},
    {0,0,0,0,0,0,0,0,128,128,128,128,128,128,128,128},
};
