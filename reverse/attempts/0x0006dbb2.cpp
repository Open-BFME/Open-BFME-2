// ?rva0006DBB2@Rva000677CAHost@@QAEX_NHHHH@Z
// partial score=0.9875166297117517 date=2026-10-09
// cl: /O1 /Oy- /DNDEBUG /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
//
// ?updateView@Rva000677CAHost@@QAEX_NHHHH@Z, retail 0x0006dc8e, 195 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
#include <vector>
extern "C" double sqrt(double) throw();
extern "C" double fabs(double) throw();
extern "C" double tan(double) throw();
class BoundedShortGrid {public:short rva00062A58(int,int);};
struct Rva0006DC8EDimensions {char opaque00[8]; int width; int height;};
class Rva000677CAHost
{
public:
    void updateView(bool partial, int minX, int maxX, int minY, int maxY);
 void rva0006DBB2(bool partial,int minX,int maxX,int minY,int maxY);
 bool rva0006737E(int x,int y,float limit);
	bool rva000677CA(int a, int b, float f);
	void rva00067494(int a1, int a2, int a3, int a4, int a5, int a6, unsigned char *p, bool *out);
private:
    char opaque00[0x379C];
 float cliffSlope;
    float slope;
    char opaque37A4[0x37C0-0x37A4];
    Rva0006DC8EDimensions *map;
    char opaque37C4[0x37EC-0x37C4];
 _STL::vector<bool> cliffBits;

    _STL::vector<bool> bits;
};

bool Rva000677CAHost::rva000677CA(int a, int b, float f)
{
	bool out = false;
	unsigned char *p = &((unsigned char *)&f)[3];
	int fi = (int)f;
	rva00067494(a, b, 0x100, 0, fi, 0, p, &out);
	return out == false;
}

void Rva000677CAHost::updateView(bool partial, int minX, int maxX, int minY, int maxY)
{
    int xSize=map->width;
    int ySize=map->height;
    if (bits.size()!=xSize*ySize)
        bits.resize(xSize*ySize);
    if (!partial) {
        minX=0; minY=0; maxX=xSize; maxY=ySize;
    }
    for (int j=minY; j<maxY; ++j)
        for (int i=minX; i<maxX; ++i)
            bits[i+j*xSize]=rva000677CA(i,j,slope);
}

// ZH BaseHeightMap.cpp evaluateAsVisibleCliff and BF1 f98983a7d clean
// BaseHeightMapEvaluateVisibleCliff.cpp establish the slope-test purpose.
// Native6737E..67494 proves unsigned16 samples through owned grid62A58,
// height scale10/256 and 10/sqrt(2)*10/10 edge distances. Class original name
// is donor-supported but this existing target storage view retains its owner.
// Codegen blocker: 30+ complete C++ variants retained one independent
// MOVSS10 / x87 FMUL10 swap. The isolated initialization block preserves
// exact native x87 evaluation and guard timing; the grid and loop are C++.
// Local constants are independently verified: PE BC34F8 double2 and BC2428
// float10. Native DB4144 distance extent16 starts0/10, then stores its diagonal
// and final10; native DE1EB4 bit0 is the one-time initialization guard.
bool Rva000677CAHost::rva0006737E(int x,int y,float limit){
 static const double two=2.0;
 static const float ten=10.0f;
 static float distance[4]={0.0f,10.0f,0.0f,0.0f};
 static unsigned initialized=0;
 if(!(initialized&1)) {
  __asm { fld qword ptr two }
  initialized|=1;
  __asm {
   push ecx
   push ecx
   fstp qword ptr [esp]
   call sqrt
   movss xmm0, dword ptr ten
   fmul dword ptr ten
   pop ecx
   pop ecx
   fstp dword ptr distance[8]
   movss dword ptr distance[12], xmm0
  }
 }
 BoundedShortGrid *grid=reinterpret_cast<BoundedShortGrid *>(map);
 unsigned short samples[4]={grid->rva00062A58(x,y),grid->rva00062A58(x+1,y),grid->rva00062A58(x+1,y+1),grid->rva00062A58(x,y+1)};
 float heights[4]={samples[0]*0.0390625f,samples[1]*0.0390625f,samples[2]*0.0390625f,samples[3]*0.0390625f};
 bool any=false;
 for(int i=1;i<4&&!any;++i) {double a=fabs((heights[i]-heights[0])/distance[i]);if(a>limit)any=true;}
 return any;
}

void Rva000677CAHost::rva0006DBB2(bool partial,int minX,int maxX,int minY,int maxY){
 int xSize=map->width,ySize=map->height;
 if(cliffBits.size()!=xSize*ySize)cliffBits.resize(xSize*ySize);
 if(!partial){minX=0;minY=0;maxX=xSize;maxY=ySize;}
 float threshold=(float)tan(cliffSlope*0.01745329238474369f);
 for(int j=minY;j<maxY;++j)for(int i=minX;i<maxX;++i)cliffBits[i+j*xSize]=rva0006737E(i,j,threshold);
}
