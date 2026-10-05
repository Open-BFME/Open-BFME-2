// cl: /O2 /MD
// Lane A callback table and matched BfmeInstallSpreadTable's tier-A slot
// identify the same function at1D7200. The installer only takes the pointer;
// its void() placeholder declaration does not establish the callable ABI.
// Native204B body independently reads six stack arguments and calls the
// three already-rowed typed MMX filters. Source addresses are byte pointers,
// destination is writable, stride is signed, and coefficient indices scale32.
// No original codec function name is claimed: retain the installer's inherited
// address-qualified spelling and supply its typed callable definition.

extern const unsigned short g_rva00DB81B0Weights[9][16];
void __cdecl rva009C66F0BinkMmx(const void *,void *,int,int,int,int,const void *);
void __cdecl rva009C6780BinkMmx(const void *,void *,int,int,int,int,const void *);
void __cdecl Rva009C6800(const unsigned char *,unsigned char *,int,const void *,const void *);
void Rva009C6900(const unsigned char *a,const unsigned char *b,unsigned char *destination,int stride,int x,int y)
{
 int distance=b-a;
 if(distance<0) {const unsigned char *old=a;a=b;distance=old-a;}
 if(distance==1)rva009C66F0BinkMmx(a,destination,stride,1,8,8,g_rva00DB81B0Weights[x]);
 else if(distance==stride)rva009C6780BinkMmx(a,destination,stride,stride,8,8,g_rva00DB81B0Weights[y]);
 else if(distance==stride-1)Rva009C6800(a-1,destination,stride,g_rva00DB81B0Weights[x],g_rva00DB81B0Weights[y]);
 else if(distance==stride+1)Rva009C6800(a,destination,stride,g_rva00DB81B0Weights[x],g_rva00DB81B0Weights[y]);
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
#pragma comment(linker, "/alternatename:?Rva009C6900@@YAXXZ=?Rva009C6900@@YAXPBE0PAEHHH@Z")
