// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
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
class VertexBufferClass {public:class WriteLockClass {public:WriteLockClass(VertexBufferClass*,int);~WriteLockClass();VertexBufferClass*buffer;ProjectionVertex687EF*vertices;char mutex[4];};};
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
class BaseHeightMapRenderObjClass {public:
 virtual void s000();
 virtual void s001();
 virtual void s002();
 virtual void s003();
 virtual void s004();
 virtual void s005();
 virtual void s006();
 virtual void s007();
 virtual void s008();
 virtual void s009();
 virtual void s010();
 virtual void s011();
 virtual void s012();
 virtual void s013();
 virtual void s014();
 virtual void s015();
 virtual void s016();
 virtual void s017();
 virtual void s018();
 virtual void s019();
 virtual void s020();
 virtual void s021();
 virtual void s022();
 virtual void s023();
 virtual void s024();
 virtual void s025();
 virtual void s026();
 virtual void s027();
 virtual void s028();
 virtual void s029();
 virtual void s030();
 virtual void s031();
 virtual void s032();
 virtual void s033();
 virtual void s034();
 virtual void s035();
 virtual void s036();
 virtual void s037();
 virtual void s038();
 virtual void s039();
 virtual void s040();
 virtual void s041();
 virtual void s042();
 virtual void s043();
 virtual void s044();
 virtual void s045();
 virtual void s046();
 virtual void s047();
 virtual void s048();
 virtual void s049();
 virtual void s050();
 virtual void s051();
 virtual void s052();
 virtual void s053();
 virtual void s054();
 virtual void s055();
 virtual void s056();
 virtual void s057();
 virtual void s058();
 virtual void s059();
 virtual void s060();
 virtual void s061();
 virtual void s062();
 virtual void s063();
 virtual void s064();
 virtual void s065();
 virtual void s066();
 virtual void s067();
 virtual void s068();
 virtual void s069();
 virtual void s070();
 virtual void s071();
 virtual void s072();
 virtual void s073();
 virtual void s074();
 virtual void s075();
 virtual void s076();
 virtual void s077();
 virtual void s078();
 virtual void s079();
 virtual void s080();
 virtual void s081();
 virtual void s082();
 virtual void s083();
 virtual void s084();
 virtual void s085();
 virtual void s086();
 virtual void s087();
 virtual void s088();
 virtual void s089();
 virtual void s090();
 virtual void s091();
 virtual void s092();
 virtual void s093();
 virtual void s094();
 virtual void s095();
 virtual void s096();
 virtual void s097();
 virtual void s098();
 virtual void s099();
 virtual void s100();
 virtual void s101();
 virtual void s102();
 virtual void s103();
 virtual void s104();
 virtual void s105();
 virtual void s106();
 virtual void s107();
 virtual void s108();
 virtual void s109();
 virtual void s110();
 virtual void s111();
 virtual void s112();
 virtual void s113();
 virtual void s114();
 virtual void s115();
 virtual void s116();
 virtual void s117();
 virtual void s118();
 virtual void s119();
 virtual void s120();
 virtual void s121();
 virtual void s122();
 virtual void s123();
 virtual void s124();
 virtual void s125();
 virtual void s126();
 virtual void s127();
 virtual void s128();
 virtual void s129();
 virtual void s130();
 virtual void s131();
 virtual void s132();
 virtual void s133();
 virtual void s134();
 virtual void s135();
 virtual void s136();
 virtual void s137();
 virtual void s138();
 virtual void s139();
 virtual void s140();
 virtual void s141();
 virtual void s142();
 virtual void s143();
 virtual void s144();
 virtual float height244(float,float,void*);
 void rva000687EF();
 char pad04[0x37a4-4];VertexBufferClass*vertices37a4;IndexBufferClass*indices37a8;int count37ac,vertices37b0,indices37b4,maxVertices37b8,maxIndices37bc;ProjectionMap687EF*map37c0;char pad37c4[0x3850-0x37c4];W3DTreeBuffer*tree3850;
};
void BaseHeightMapRenderObjClass::rva000687EF(){
 if(tree3850){
  count37ac=0;vertices37b0=0;indices37b4=0;
  if(((ProjectionGlobal687EF*)TheWritableGlobalData)->enabled61){
   IndexBufferClass::WriteLockClass il(indices37a8,0);unsigned short*curIb=il.indices;
   VertexBufferClass::WriteLockClass vl(vertices37a4,0);ProjectionVertex687EF*curVb=vl.vertices;
   int borderSize=(map37c0?map37c0:map37c0)->border;int count=tree3850->count;
   for(int curTree=0;curTree<count;curTree++){
    Rva000EAFA4Coord3 loc;float radius;Rva000EAFA4Coord2 scale,offset;
    if(tree3850->rva000EAFA4(curTree,&loc,&radius,&scale,&offset)){
     float minXf=floorf((loc.x-radius)*0.1f);
     int minX=fast_float2long_round(minXf);
     float minYf=floorf((loc.y-radius)*0.1f);
     int minY=fast_float2long_round(minYf);
     if(minX<-borderSize)minX=-borderSize;if(minY<-borderSize)minY=-borderSize;
     int maxX=fast_float2long_round(ceilf((loc.x+radius)*0.1f));maxX++;
     int maxY=fast_float2long_round(ceilf((loc.y+radius)*0.1f));maxY++;
     if(maxX>map37c0->width-borderSize){int extent=map37c0->width;maxX=extent-borderSize;}
     if(maxY>map37c0->height-borderSize){int extent=map37c0->height;maxY=extent-borderSize;}
     int startVertex=vertices37b0;int i,j;
     for(j=minY;j<maxY;j++){
      float Y=j*10.0f;
      for(i=minX;i<maxX;i++){
       if(vertices37b0>=maxVertices37b8){vertices37b0=startVertex;return;}
       float X=i*10.0f;float u=(X-loc.x)/(2*radius)+0.5f,v=(Y-loc.y)/(2*radius)+0.5f;
       float x=X,y=Y;
       if(!(u<0.0f||u>1.0f||v<0.0f||v>1.0f)){
        u=u*scale.x+offset.x;v=v*scale.y+offset.y;
        curVb->z=(float)((Rva0006653B*)map37c0)->rva0006653B(i+borderSize,j+borderSize)*0.0390625f+1.0f;
       }else{
        if(u<0.0f){x-=u*radius*2;u=0;}else if(u>1.0f){x-=(u-1)*radius*2;u=1;}
        if(v<0.0f){y-=v*radius*2;v=0;}else if(v>1.0f){y-=(v-1)*radius*2;v=1;}
        u=u*scale.x+offset.x;v=v*scale.y+offset.y;
        curVb->z=height244(x,y,0)+1.0f;
       }
       curVb->diffuse=0xffffffff;curVb->u=u;curVb->v=v;curVb->x=x;curVb->y=y;curVb++;vertices37b0++;
      }
     }
     int yOffset=maxX-minX;
     for(j=0;j<maxY-minY-1;j++){
      int yNdx=j+minY+borderSize;
      for(i=0;i<maxX-minX-1;i++){
       if(indices37b4+6>maxIndices37bc)return;
       bool flip=((Gen_0074B410*)map37c0)->bfmeBitA(i+minX+borderSize,yNdx);
       if(flip){
        *curIb++=startVertex+j*yOffset+i+1;*curIb++=startVertex+(j+1)*yOffset+i;*curIb++=startVertex+j*yOffset+i;
        *curIb++=startVertex+j*yOffset+i+1;*curIb++=startVertex+(j+1)*yOffset+i+1;*curIb++=startVertex+(j+1)*yOffset+i;
       }else{
        *curIb++=startVertex+j*yOffset+i;*curIb++=startVertex+(j+1)*yOffset+i+1;*curIb++=startVertex+(j+1)*yOffset+i;
        *curIb++=startVertex+j*yOffset+i;*curIb++=startVertex+j*yOffset+i+1;*curIb++=startVertex+(j+1)*yOffset+i+1;
       }
       indices37b4+=6;
      }
     }
     count37ac++;
    }
   }
  }
 }
}
