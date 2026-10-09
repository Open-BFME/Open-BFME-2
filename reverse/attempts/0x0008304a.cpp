// ?rva0008304A@Rva0008304A@@QAEXXZ
// partial score=0.226 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>
#include <string.h>
#include "../../Code/Libraries/Include/Lib/Coord2D.h"
namespace _STL {
 template<> class vector<char,allocator<char> > {
  public: char *start,*finish,*end;
  void resize(unsigned int,char);
 };
}
struct BfmeE12 { float x,y,z; };
struct BfmeE16 { float x,y,z,w; };
struct BfmePod44 {int a[11];};
void Rva00030830FreeAllocation(void *);
namespace _STL {
 template<> inline void allocator<BfmeE12>::deallocate(BfmeE12 *p,size_type) const {if(p) Rva00030830FreeAllocation(p);}
 template<> inline void allocator<BfmeE16>::deallocate(BfmeE16 *p,size_type) const {if(p) Rva00030830FreeAllocation(p);}
}
class Rva00082A53 {
 int self;
 _STL::vector<BfmeE12> cells;
 int dimX,dimY;
 public:
 _STL::vector<BfmeE16> records;
 int origin[3]; float spacing;
 Rva00082A53(int,int,int,float,int*,int);
 ~Rva00082A53();
 unsigned short rva00082E33(int,int);
};
class ModuleData;
class Rva00081F03 {public:void rva00081F03();};
class Rva0030D111Shape {public:virtual int count();};
bool Rva0030D111Contains(Rva0030D111Shape*,const Coord2D*);
struct Region2D {Region2D(){} Region2D(const Region2D&r){x0=r.x0;y0=r.y0;x1=r.x1;y1=r.y1;} ~Region2D(){} float x0,y0,x1,y1;};
class PolygonTrigger { public:Region2D rva0007E03A();};
class GameLODManager;
extern GameLODManager *TheGameLODManager;
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock {public: BFMEDX8DeviceLock(){BFME_DX8_Thread_Lock();} ~BFMEDX8DeviceLock(){BFME_DX8_Thread_Assert();}};
class IndexBufferClass {public:
 class WriteLockClass {
  IndexBufferClass *buffer; public: unsigned short *indices; private: BFMEDX8DeviceLock lock;
  public:WriteLockClass(IndexBufferClass*,int);~WriteLockClass();
 };
};
class DX8IndexBufferClass {
 public:enum UsageType{USAGE_DEFAULT=0};
 char record[24];
 DX8IndexBufferClass(unsigned,UsageType);
};
class VertexBufferClass {public:
 class WriteLockClass {
  VertexBufferClass *buffer;public: void *vertices;private:BFMEDX8DeviceLock lock;
  public:WriteLockClass(VertexBufferClass*,int);~WriteLockClass();
 };
};
class BfmeDynamicNativeVB {
 public:char record[32];
 BfmeDynamicNativeVB(unsigned,unsigned short,unsigned,unsigned);
};
void Rva0007DEC8Add(float*,float,float,const float*);
struct Rva0007DEC8Pair:Coord2D {
 Rva0007DEC8Pair(float a,float b){x=a;y=b;}
 Rva0007DEC8Pair(const Rva0007DEC8Pair &p){x=p.x;y=p.y;}
 ~Rva0007DEC8Pair(){}
};
typedef void (__cdecl *Rva0007DEC8Aggregate)(float*,Rva0007DEC8Pair,const float*);
class Rva0008304A {
 char pad00[0x14];float *boundary;
 char pad18[0x28];PolygonTrigger *area;
 char pad44[0x2c];
 _STL::vector<const ModuleData*> vertexBuffers,vertexCounts,indexBuffers,indexCounts;
 public:void rva0008304A();
};
void Rva0008304A::rva0008304A() {
 reinterpret_cast<Rva00081F03*>(this)->rva00081F03();
 BFMEDX8DeviceLock guard;
 Region2D bounds=reinterpret_cast<PolygonTrigger*>(reinterpret_cast<char*>(area)+0x30)->rva0007E03A();
 int limit=60000;register float spacing=20.0f;
 if(TheGameLODManager && *reinterpret_cast<int*>(reinterpret_cast<char*>(TheGameLODManager)+0x1784)<=2){limit=30000;spacing=40.0f;}
 int nx,ny,total;
 do {
  nx=int(bounds.x1/spacing)-int(bounds.x0/spacing)+1;
  ny=int(bounds.y1/spacing)-int(bounds.y0/spacing)+1;
  total=nx*ny;
  if(total>limit)spacing*=2.0f;
 }while(total>limit);
 bounds.x0=(float)int(bounds.x0/spacing)*spacing;
 bounds.y0=(float)int(bounds.y0/spacing)*spacing;
 bounds.x1=(int(bounds.x1/spacing)+1.0f)*spacing;
 bounds.y1=(int(bounds.y1/spacing)+1.0f)*spacing;
 _STL::_Vector_base<BfmeE12,_STL::allocator<BfmeE12> > flags((_STL::allocator<BfmeE12>()));
 reinterpret_cast<_STL::vector<char>*>(&flags)->resize(total,0);
 float half[2]={spacing*.5f,spacing*.5f};
 Coord2D center;
 reinterpret_cast<Rva0007DEC8Aggregate>(&Rva0007DEC8Add)(&center.x,*reinterpret_cast<Rva0007DEC8Pair*>(&bounds),half);
 int count=0;
 char *row=*reinterpret_cast<char**>(&flags);
 for(int y=0;y<ny;++y) {
  char *slot=row;
  Coord2D pos;pos.y=y*spacing+center.y;
  for(int x=0;x<nx;++x){
   pos.x=x*spacing+center.x;
   
   Rva0030D111Shape *shape=area ? reinterpret_cast<Rva0030D111Shape*>(reinterpret_cast<char*>(area)+0x18+(*reinterpret_cast<int**>(reinterpret_cast<char*>(area)+0x18))[1]) : 0;
   bool in=Rva0030D111Contains(shape,&pos);
   *slot++=in;
   count+=in;
  }
  row+=nx;
 }
 if(count){
  int origin[3];origin[0]=*reinterpret_cast<int*>(&bounds.x0);origin[1]=*reinterpret_cast<int*>(&bounds.y0);origin[2]=*reinterpret_cast<int*>(boundary+2);
  int indexCount=count*6;
  Rva00082A53 cache(reinterpret_cast<int>(this),nx,ny,spacing,origin,2*count+nx+1);
  const ModuleData *ib=reinterpret_cast<const ModuleData*>(new DX8IndexBufferClass(indexCount,DX8IndexBufferClass::USAGE_DEFAULT));
  indexBuffers.push_back(ib);
  {
   IndexBufferClass::WriteLockClass lock(reinterpret_cast<IndexBufferClass*>(const_cast<ModuleData*>(indexBuffers.back())),0);
   unsigned short *out=lock.indices;
   for(int y=0;y<ny;++y){
    char *slot=*reinterpret_cast<char**>(&flags)+y*nx;
    for(int x=0;x<nx;++x){
     if(*slot){
      out[0]=cache.rva00082E33(x,y);
      out[1]=cache.rva00082E33(x+1,y+1);
      out[2]=cache.rva00082E33(x,y+1);
      out[3]=cache.rva00082E33(x,y);
      out[4]=cache.rva00082E33(x+1,y);
      out[5]=cache.rva00082E33(x+1,y+1);
      out+=6;
     }
     ++slot;
    }
   }
  }
  _STL::vector<BfmePod44> *records=reinterpret_cast<_STL::vector<BfmePod44>*>(&cache.records);
  const ModuleData *vb=reinterpret_cast<const ModuleData*>(new BfmeDynamicNativeVB(0x252,records->size(),0,0));
  vertexBuffers.push_back(vb);
  {
   VertexBufferClass::WriteLockClass lock(reinterpret_cast<VertexBufferClass*>(const_cast<ModuleData*>(vertexBuffers.back())),0);
   memcpy(lock.vertices,records->begin(),records->size()*44);
  }
  int vc=records->size();vertexCounts.push_back(*reinterpret_cast<const ModuleData**>(&vc));
  indexCounts.push_back(*reinterpret_cast<const ModuleData**>(&indexCount));
 }
}
