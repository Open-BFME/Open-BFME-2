// cl: /D_OPERATOR_NEW_DEFINED_ /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// Native687EF..68D431364. ZH updateScorches supplies terrain-grid mesh semantics;
// BFME2 uses tree queryEAFA4 for radius and atlas transforms, clips outside UVs
// to the projection edge and samples the terrain virtual height there.
// Keep the CRT's inlined floorf local; its public body is owned by the
// terrain-lightmap unit at 0x0004D649.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>
#include "Lib/BaseType.h"
struct Rva000EAFA4Coord3 {float x,y,z;};struct Rva000EAFA4Coord2 {float x,y;};
class W3DTreeBuffer {public:bool rva000EAFA4(int,Rva000EAFA4Coord3*,float*,Rva000EAFA4Coord2*,Rva000EAFA4Coord2*);char pad00[0x44540];int count;};
struct ProjectionVertex687EF {float x,y,z;unsigned diffuse;float u,v;};
#include "../../../../Libraries/Source/WWVegas/WW3D2/VertexBufferClass.h"
#include "../../../../Libraries/Source/WWVegas/WW3D2/IndexBufferClass.h"
class Rva0006653B {public:
 unsigned short rva0006653B(int x,int y) {
  if(x<0)x=0;else if(x>=width)x=width-1;
  if(y<0)y=0;else if(y>=height)y=height-1;
  int extent=width;unsigned short*data=heights;return data[y*extent+x];
 }
 char pad00[8];int width,height,border;char pad14[0x24-0x14];unsigned short*heights;
};
class Gen_0074B410
{
public:
	bool bfmeBitA(int x, int y) const;
};
struct ProjectionMap687EF {char pad00[8];int width,height,border;};
class GlobalData;extern GlobalData*TheWritableGlobalData;
struct ProjectionGlobal687EF {char pad00[0x61];bool enabled61;};
#define REFCOUNT_H
#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"
void BaseHeightMapRenderObjClass::rva000687EF(){
 if(m_treeBuffer){
  field37AC=0;field37B0=0;field37B4=0;
  if(((ProjectionGlobal687EF*)TheWritableGlobalData)->enabled61){
   IndexBufferClass::WriteLockClass il(((IndexBufferClass *)field37A8),0);unsigned short*curIb=il.indices;
   VertexBufferClass::WriteLockClass vl(((VertexBufferClass *)field37A4),0);ProjectionVertex687EF*curVb=(ProjectionVertex687EF*)vl.Get_Vertex_Array();
   int borderSize=((ProjectionMap687EF *)(m_map?m_map:m_map))->border;int count=m_treeBuffer->count;
   for(int curTree=0;curTree<count;curTree++){
    Rva000EAFA4Coord3 loc;float radius;Rva000EAFA4Coord2 scale,offset;
    if(m_treeBuffer->rva000EAFA4(curTree,&loc,&radius,&scale,&offset)){
     float minXf=floorf((loc.x-radius)*0.1f);
     int minX=fast_float2long_round(minXf);
     float minYf=floorf((loc.y-radius)*0.1f);
     int minY=fast_float2long_round(minYf);
     if(minX<-borderSize)minX=-borderSize;if(minY<-borderSize)minY=-borderSize;
     int maxX=fast_float2long_round(ceilf((loc.x+radius)*0.1f));maxX++;
     int maxY=fast_float2long_round(ceilf((loc.y+radius)*0.1f));maxY++;
     if(maxX>((ProjectionMap687EF *)m_map)->width-borderSize){int extent=((ProjectionMap687EF *)m_map)->width;maxX=extent-borderSize;}
     if(maxY>((ProjectionMap687EF *)m_map)->height-borderSize){int extent=((ProjectionMap687EF *)m_map)->height;maxY=extent-borderSize;}
     int startVertex=field37B0;int i,j;
     for(j=minY;j<maxY;j++){
      float Y=j*10.0f;
      for(i=minX;i<maxX;i++){
       if(field37B0>=field37B8){field37B0=startVertex;return;}
       float X=i*10.0f;float u=(X-loc.x)/(2*radius)+0.5f,v=(Y-loc.y)/(2*radius)+0.5f;
       float x=X,y=Y;
       if(!(u<0.0f||u>1.0f||v<0.0f||v>1.0f)){
        u=u*scale.x+offset.x;v=v*scale.y+offset.y;
        curVb->z=(float)((Rva0006653B*)m_map)->rva0006653B(i+borderSize,j+borderSize)*0.0390625f+1.0f;
       }else{
        if(u<0.0f){x-=u*radius*2;u=0;}else if(u>1.0f){x-=(u-1)*radius*2;u=1;}
        if(v<0.0f){y-=v*radius*2;v=0;}else if(v>1.0f){y-=(v-1)*radius*2;v=1;}
        u=u*scale.x+offset.x;v=v*scale.y+offset.y;
        curVb->z=getHeightMapHeight(x,y,0)+1.0f;
       }
       curVb->diffuse=0xffffffff;curVb->u=u;curVb->v=v;curVb->x=x;curVb->y=y;curVb++;field37B0++;
      }
     }
     int yOffset=maxX-minX;
     for(j=0;j<maxY-minY-1;j++){
      int yNdx=j+minY+borderSize;
      for(i=0;i<maxX-minX-1;i++){
       if(field37B4+6>field37BC)return;
       bool flip=((Gen_0074B410*)m_map)->bfmeBitA(i+minX+borderSize,yNdx);
       if(flip){
        *curIb++=startVertex+j*yOffset+i+1;*curIb++=startVertex+(j+1)*yOffset+i;*curIb++=startVertex+j*yOffset+i;
        *curIb++=startVertex+j*yOffset+i+1;*curIb++=startVertex+(j+1)*yOffset+i+1;*curIb++=startVertex+(j+1)*yOffset+i;
       }else{
        *curIb++=startVertex+j*yOffset+i;*curIb++=startVertex+(j+1)*yOffset+i+1;*curIb++=startVertex+(j+1)*yOffset+i;
        *curIb++=startVertex+j*yOffset+i;*curIb++=startVertex+j*yOffset+i+1;*curIb++=startVertex+(j+1)*yOffset+i+1;
       }
       field37B4+=6;
      }
     }
     field37AC++;
    }
   }
  }
 }
}
