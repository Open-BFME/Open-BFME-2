// ?updateScorches@BaseHeightMapRenderObjClass@@QAEXXZ
// partial score=0.8611885404568331 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /Oy- /MD /EHsc /DNDEBUG
// Bank: native 000678BB..00067E8E, full1491B void/RET0; 1461B trial.
// BF1@575ba2b game/GameEngineDevice/Source/W3DDevice/GameClient/
// BaseHeightMapUpdateScorches.cpp and ZH BaseHeightMap.cpp updateScorches guide
// the purpose, lock lifetimes and mesh loops. All BFME2 offsets, active skip,
// UV normalization, color gain and budgets are established from target bytes;
// sibling BaseHeightMapScorchOverlap.cpp proves the 28B record independently.
// Named canonical GlobalData pointer is viewed through a target prefix. The
// ShaderOverbrightEnabled owner is ShaderClassApply.cpp, not an address pin.
// Both buffer lock lifetimes, height query 6653B and flip query ADF41 are owned.
// Signed color packing preserves the exact native SSE color block. Inline
// FISTP is the reference fast_float2long_round primitive: ordinary casts emit
// __ftol2 and /QIfist is incompatible with the target SSE codegen.
// Residue: active-field cursor anchor, floor cleanup order, bound clamp CSE,
// integer homes and UV register schedule; no new private ABI or provider.
#include <math.h>
extern bool ShaderOverbrightEnabled;
class GlobalData;extern GlobalData *TheGlobalData;
struct ScorchRGB {float r,g,b;};
struct ScorchLightingView {char pad[0x8D8];ScorchRGB ambient;char pad8E4[0x18];ScorchRGB diffuse;char pad908[0x3C];ScorchRGB factor;};
class IndexBufferClass {public:class WriteLockClass {
 IndexBufferClass *buffer;unsigned short *data;char deviceLock;
 public:WriteLockClass(IndexBufferClass*,int=0);~WriteLockClass();__forceinline unsigned short *Get_Index_Array()const{return data;}
};};
class VertexBufferClass {public:class WriteLockClass {
 VertexBufferClass *buffer;void *data;char deviceLock;
 public:WriteLockClass(VertexBufferClass*,int=0);~WriteLockClass();__forceinline void *Get_Vertex_Array()const{return data;}
};};
struct ScorchPosition {float x,y,z;};
struct ScorchEntry {void *unknown;ScorchPosition position;float radius;int type;bool active;char pad[3];};
struct ScorchVertex {float x,y,z;unsigned diffuse;float u,v;};
struct ScorchMap {char pad[8];int width,height,border;};
class Rva0006653B {public:unsigned short rva0006653B(int,int);};
class Gen_0074B410 {public:bool bfmeBitA(int,int)const;};
// VC7.1 cannot select x87 FISTP with /arch:SSE through a C++ cast; the
// native floor/ceil path uses this rounding conversion after an integral result.
static __forceinline int scorchFist(float f) {int i;__asm {
 fld f
 fistp i
 } return i;}
static __forceinline int scorchFloor(float f) {return scorchFist((float)floor((double)f));}
static __forceinline int scorchCeil(float f) {return scorchFist((float)ceil((double)f));}
class BaseHeightMapRenderObjClass {public:void updateScorches();private:
 char pad[0xCC];VertexBufferClass *vertexScorch;IndexBufferClass *indexScorch;void *texture;
 int vertexCount,indexCount;ScorchEntry scorches[500];int count,cached;char pad3798[0x28];ScorchMap *map;
};
void BaseHeightMapRenderObjClass::updateScorches() {
 if(cached>1)return;
 if(count==0)return;
 if(!indexScorch||!vertexScorch)return;
 cached=0;vertexCount=0;indexCount=0;
 const ScorchLightingView *global=(const ScorchLightingView*)TheGlobalData;
 float r=global->factor.r*global->diffuse.r*0.5f+global->ambient.r;
 float g=global->factor.g*global->diffuse.g*0.5f+global->ambient.g;
 float b=global->factor.b*global->diffuse.b*0.5f+global->ambient.b;
 float overbright=1.0f;if(ShaderOverbrightEnabled)overbright=2.0f;
 float red=r*overbright;if(red>1.0f)red=1.0f;
 float green=g*overbright;if(green>1.0f)green=1.0f;
 float blue=b*overbright;if(blue>1.0f)blue=1.0f;
 int diffuse=(int)(red*255.0f)|(int)0xFFFFFF00;
 diffuse=(diffuse<<8)|(int)(green*255.0f);
 diffuse=(diffuse<<8)|(int)(blue*255.0f);
 int border=map->border;
 IndexBufferClass::WriteLockClass ilock(indexScorch);
 unsigned short *curIb=ilock.Get_Index_Array();
 VertexBufferClass::WriteLockClass vlock(vertexScorch);
 ScorchVertex *curVb=(ScorchVertex*)vlock.Get_Vertex_Array();
 for(int s=count-1;s>=0;--s) {
  ScorchEntry &entry=scorches[s];
  if(entry.active)continue;
  ++cached;
  int type=entry.type;
  if(type<0||type>=9)type=0;
  float uOffset=(type%3)*(1.0f/3.0f),vOffset=(type/3)*(1.0f/3.0f);
  float radius=entry.radius;ScorchPosition loc;loc.x=entry.position.x;loc.y=entry.position.y;
  int minX=scorchFloor((loc.x-radius)*0.1f)-1;
  int minY=scorchFloor((loc.y-radius)*0.1f)-1;
  if(minX<-border)minX=-border;if(minY<-border)minY=-border;
  int maxX=scorchCeil((loc.x+radius)*0.1f)+1;
  int maxY=scorchCeil((loc.y+radius)*0.1f)+1;
  if(maxX>map->width-border)maxX=map->width-border;
  if(maxY>map->height-border)maxY=map->height-border;
  int startVertex=vertexCount;
  int yOffset=maxX-minX;
  float spanX=(yOffset-1)*10.0f;
  float spanY=(maxY-minY-1)*10.0f;
  float originX=minX*10.0f,originY=minY*10.0f;
  int i,j;
  for(j=minY;j<maxY;++j) {
   float Y=j*10.0f;
   for(i=minX;i<maxX;++i) {
    if(vertexCount>=0x2002){vertexCount=startVertex;return;}
    curVb->diffuse=diffuse;
    float X=i*10.0f;
    curVb->u=(X-originX)/spanX*(1.0f/3.0f)+uOffset;
    curVb->v=(Y-originY)/spanY*(1.0f/3.0f)+vOffset;
    curVb->x=X;curVb->y=Y;
    curVb->z=(float)((Rva0006653B*)map)->rva0006653B(i+border,j+border)*0.0390625f+1.0f;
    ++curVb;++vertexCount;
   }
  }
  for(j=0;j<maxY-minY-1;++j) {
   for(i=0;i<maxX-minX-1;++i) {
    if(indexCount+6>0xC00C)return;
    bool flip=((Gen_0074B410*)map)->bfmeBitA(i+minX+border,j+minY+border);
    if(flip) {
     *curIb++=(unsigned short)(startVertex+j*yOffset+i+1);
     *curIb++=(unsigned short)(startVertex+(j+1)*yOffset+i);
     *curIb++=(unsigned short)(startVertex+j*yOffset+i);
     *curIb++=(unsigned short)(startVertex+j*yOffset+i+1);
     *curIb++=(unsigned short)(startVertex+(j+1)*yOffset+i+1);
     *curIb++=(unsigned short)(startVertex+(j+1)*yOffset+i);
    } else {
     *curIb++=(unsigned short)(startVertex+j*yOffset+i);
     *curIb++=(unsigned short)(startVertex+(j+1)*yOffset+i+1);
     *curIb++=(unsigned short)(startVertex+(j+1)*yOffset+i);
     *curIb++=(unsigned short)(startVertex+j*yOffset+i);
     *curIb++=(unsigned short)(startVertex+j*yOffset+i+1);
     *curIb++=(unsigned short)(startVertex+(j+1)*yOffset+i+1);
    }
    indexCount+=6;
   }
  }
 }
}
