// ?rva00530212@Pathfinder@@QAEXPAVObject@@_N11@Z
// partial score=0.7795442928632816 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /I.
// Native 00530212..00530F47, RET16, 3381B. New reconstruction.
// ZH AIPathfind.cpp classifyObjectFootprint/internal_classifyObjectFootprint
// provide the filtering/rasterization/pinching semantics. BFME-specific wall,
// portal, multi-shape, gate and layer checks are read from target bytes and WB.
#include "Code/Libraries/Include/Lib/Coord3D.h"
struct ICoord2D{int x,y;};
struct Region2D { float lx,ly,hx,hy; };
struct FootprintBounds{int lx,ly,hx,hy;};
class Rva0027C36A {public:Rva0027C36A();char bytes[0xa8];};
class Drawable {public:
 bool rva0027267D(int,int,int,int);bool rva002726C3(int,int,int,int);
 int rva0027257B(int);bool rva00272C1E();void rva0027A018();
};
class Rva00279677{public:void rva00279677();};
struct BfmeVecVNB{float x,y,z;};
class BfmeXformVNB{public:void bfmeApplyVNB(BfmeVecVNB*,float);};
struct BfmeShapeE15 {int type;int field4;float major,minor,offsetX,offsetY,offsetZ;bool flag1C;char pad1D[3];bool enabled;char pad21[3];};
class BfmeObjE15{public:BfmeShapeE15 *bfmeAtE15(int);};
class Rva0087E370{public:void method(const Coord3D&,float,Region2D&)const;};
struct FootprintTemplate {char pad[0x108];union {unsigned kinds[6];struct {unsigned kind0;unsigned pad1:28;unsigned isWall:1;unsigned isDefense:1;unsigned pad2:2;unsigned rest[4];};};unsigned words120;char pad124[0x4a0-0x124];float fenceWidth;__forceinline unsigned kind(int b)const{return kinds[b/32]&(1u<<(b%32));}};
enum ObjectStatusTypes{Status77=77,Status88=88};
class Object {public:
 Drawable *getDrawable()const;void rva0028AD32();void rva0028AD8C();void rva0028AD7C();bool rva002907A1();bool testStatus(ObjectStatusTypes)const;bool rva0006F039(int)const;
 char pad0[4];FootprintTemplate *templ;char pad8[0x38-8];Coord3D position;float orientation;char pad48[0xac-0x48];bool small;char padAD[0xd4-0xad];BfmeShapeE15 *begin,*end;
};
class Thing{public:float getHeightAboveTerrain()const;};
struct Rva0052DEEFArg;struct Rva0052DFB1Arg;struct In002E6BA1{int x,y;};
class PathfindCell {public:
 bool SetType_Dirty(int);bool rva0052DEEF(const Rva0052DEEFArg*,bool,In002E6BA1*);bool rva0052DFB1(const Rva0052DFB1Arg*);
 __forceinline int type()const{return m_type;}__forceinline int layer()const{return m_layer;}__forceinline bool pinched()const{return m_pinched;}__forceinline void pinch(bool b){m_pinched=b;}
 __forceinline bool gate()const{return m_gate;}
 char pad[12];unsigned m_type:4;unsigned m_layer:6;unsigned m_low:6;unsigned m_pinched:1;unsigned m_gate:1;unsigned m_mid:4;unsigned m_22:1;unsigned m_23:1;unsigned m_high:8;
};
class Rva0052E001{public:bool rva0052E001(bool);};
class Rva0052E02F{public:bool rva0052E02F(bool);};
class PathfindZoneManager{public:void MarkDirty(int,int);};
extern "C" __declspec(dllimport)double __cdecl floor(double);
extern "C" __declspec(dllimport)double __cdecl ceil(double);
float Sin(float);float Cos(float);
static __forceinline int float2long(float f){int i;__asm{
 fld f
 fistp i
}return i;}
#define FLOOR(x) float2long((float)floor(x))
#define CEIL(x) float2long((float)ceil(x))
enum PathfindLayerEnum{LayerGround=1};
class Pathfinder{public:
 void rva00530212(Object*,bool,bool,bool);void rva0052F63F(Object*,bool);void rva0052E4C9(Object*,bool);PathfindCell *getCell(PathfindLayerEnum,int,int);
 char pad0[0x10];PathfindCell**map;FootprintBounds extent;char pad24[0x460-0x24];PathfindZoneManager zones;char pad461[0x1beb4-0x461];bool changedWall,changedGate;
};
void Pathfinder::rva00530212(Object*obj,bool insert,bool keepGate,bool goal)
{
 Drawable *drawable=obj->getDrawable();
 if(drawable){if(insert)drawable->rva0027A018();else ((Rva00279677*)drawable)->rva00279677();}
 if(obj->templ->kind(25)||obj->templ->kind(24)||obj->templ->kind(149))return;
 bool wall=obj->templ->isWall;
 if(!wall && obj->templ->fenceWidth>0.0f && !obj->templ->kind(61)){rva0052E4C9(obj,insert);return;}
 if(!insert){obj->rva0028AD32();if(!goal)obj->rva0028AD8C();}else obj->rva0028AD7C();
 if(!obj->templ->kind(7)||obj->rva002907A1()||obj->small||obj->testStatus(Status88))return;
 if(wall){if(obj->templ->kind(150))wall=obj->getDrawable()->rva00272C1E();else if(obj->testStatus(Status77))wall=false;}
 if(((Thing*)obj)->getHeightAboveTerrain()>10.0f&&!wall)return;
 if(wall&&drawable){float z;if(!drawable->rva0027257B((int)&z)){changedWall=true;rva0052F63F(obj,insert);return;}}
 bool gate=obj->templ->kind(137)||wall;
 bool bit22=insert ? ((obj->templ->words120>>9)&1)!=0:false;
 if((gate||bit22)&&!insert)changedGate=true;
 if(insert&&obj->templ->kind(120)&&obj->rva0006F039(94)){
  int x=(int)(obj->position.x*0.1f),y=(int)(obj->position.y*0.1f);
  for(int i=-60;i<=60;++i)for(int j=-60;j<=60;++j){PathfindCell*cell=getCell(LayerGround,x+i,y+j);if(cell&&cell->gate()){((Rva0052E001*)cell)->rva0052E001(false);zones.MarkDirty(x+i,y+j);}}
 }
 Rva0027C36A data;
 if(drawable){void*poly;if(drawable->rva0027267D((int)&data,(int)&poly,0,0)||drawable->rva002726C3((int)&data,(int)&poly,0,0))gate=true;}
 float angle=obj->orientation;
 for(int k=0;k<obj->end-obj->begin;++k){
  BfmeShapeE15 *shape=((BfmeObjE15*)((char*)obj+0xa8))->bfmeAtE15(k);
  if(!shape->enabled||shape->offsetZ>10.0f)continue;
  BfmeVecVNB pos={obj->position.x,obj->position.y,obj->position.z};
  float c=Cos(angle),s=Sin(angle);
  ((BfmeXformVNB*)shape)->bfmeApplyVNB(&pos,angle);
  switch(shape->type){
  case 2:{
   float halfX=shape->major,halfY=shape->minor;
   float ydx=s*5.0f,ydy=-c*5.0f,xdx=c*5.0f,xdy=s*5.0f;
   int nx=CEIL(halfX*0.4f),ny=CEIL(halfY*0.4f);
   float tlx=pos.x-halfX*c-halfY*s,tly=pos.y+halfY*c-halfX*s;
   for(int iy=0;iy<ny;++iy,tlx+=ydx,tly+=ydy){
    float x=tlx,y=tly;
    for(int ix=0;ix<nx;++ix,x+=xdx,y+=xdy){
     int cx=FLOOR((x+0.5f)*0.1f),cy=FLOOR((y+0.5f)*0.1f);
     if(cx<0||cy<0||cx>=extent.hx||cy>=extent.hy)continue;
     bool accept=false;
     if(map[cx][cy].layer()!=1){
      if(!gate)continue;
      int ty=map[cx][cy].type();
      if((ty==0||ty==3)&&insert)accept=true;
      if((ty==4||ty==3)&&!insert)accept=true;
      if(!accept)continue;
     }
     bool dirty;
     if(insert){
      if(gate){int ty=map[cx][cy].type();if(ty==2||ty==3){map[cx][cy].SetType_Dirty(0);zones.MarkDirty(cx,cy);}}
      In002E6BA1 p={cx,cy};dirty=map[cx][cy].rva0052DEEF((const Rva0052DEEFArg*)obj,false,&p);
     }else dirty=map[cx][cy].rva0052DFB1((const Rva0052DFB1Arg*)obj);
     if(dirty)zones.MarkDirty(cx,cy);
     if(gate&&!keepGate&&map[cx][cy].gate()!=insert){((Rva0052E001*)&map[cx][cy])->rva0052E001(insert);zones.MarkDirty(cx,cy);}
     if(((Rva0052E02F*)&map[cx][cy])->rva0052E02F(bit22))zones.MarkDirty(cx,cy);
    }
   }
  }break;
  case 0:case 1:{
   float radius=shape->major;
   int left=FLOOR((pos.x-radius)*0.1f+0.5f)-1,top=FLOOR((pos.y-radius)*0.1f+0.5f)-1;
   float size=radius*0.1f+0.4f,cx=pos.x*0.1f,cy=pos.y*0.1f,r2=size*size;
   int right=(int)(left+2*size+2),bottom=(int)(top+2*size+2);
   for(int j=top;j<bottom;++j)for(int i=left;i<right;++i){
    float dx=i+0.5f-cx,dy=j+0.5f-cy;
    if(dx*dx+dy*dy>r2||i<0||j<0||i>=extent.hx||j>=extent.hy||map[i][j].layer()!=1)continue;
    bool dirty;
    if(insert){In002E6BA1 p={i,j};dirty=map[i][j].rva0052DEEF((const Rva0052DEEFArg*)obj,false,&p);}
    else dirty=map[i][j].rva0052DFB1((const Rva0052DFB1Arg*)obj);
    if(dirty)zones.MarkDirty(i,j);
    if(gate&&map[i][j].gate()!=insert){((Rva0052E001*)&map[i][j])->rva0052E001(insert);zones.MarkDirty(i,j);}
    if(((Rva0052E02F*)&map[i][j])->rva0052E02F(bit22))zones.MarkDirty(i,j);
   }
  }break;
  }
 }
 Region2D world;
 ((Rva0087E370*)((char*)obj+0xa8))->method(obj->position,obj->orientation,world);
 FootprintBounds b={FLOOR(world.lx*0.1f)-1,FLOOR(world.ly*0.1f)-1,CEIL(world.hx*0.1f)+1,CEIL(world.hy*0.1f)+1};
 if(b.lx<extent.lx)b.lx=extent.lx;
 if(b.ly<extent.ly)b.ly=extent.ly;
 if(b.ly<extent.ly)b.ly=extent.ly;
 if(b.hx>extent.hx)b.hx=extent.hx;
 if(b.hy>extent.hy)b.hy=extent.hy;
 if(!insert)for(int j=b.ly;j<=b.hy;++j)for(int i=b.lx;i<=b.hx;++i){
  PathfindCell *cell=&map[i][j];if(cell->layer()==1&&cell->type()==5){cell->SetType_Dirty(0);zones.MarkDirty(i,j);}
 }
 for(int j=b.ly;j<=b.hy;++j)for(int i=b.lx;i<=b.hx;++i){
  if(map[i][j].layer()==1)map[i][j].pinch(false);
  if(map[i][j].layer()==1&&map[i][j].type()==0){
   int total=0,ortho=0;
   for(int k=i-1;k<i+2;++k){if(k<extent.lx||k>extent.hx)continue;
    for(int l=j-1;l<j+2;++l){if(l<extent.ly||l>extent.hy)continue;
     if(k==i&&l==j)continue;
     if(map[k][l].layer()==1&&map[k][l].type()==0){++total;if(k==i||l==j)++ortho;}
    }
   }
   if(ortho<2||total<4)map[i][j].pinch(true);
  }
 }
 for(int j=b.ly;j<=b.hy;++j)for(int i=b.lx;i<=b.hx;++i){
  if(map[i][j].layer()==1&&map[i][j].pinched()&&map[i][j].type()==0){map[i][j].SetType_Dirty(5);map[i][j].pinch(false);zones.MarkDirty(i,j);}
 }
 for(int j=b.ly;j<=b.hy;++j)for(int i=b.lx;i<=b.hx;++i){
  if(map[i][j].layer()==1&&map[i][j].type()==0){
   bool adjacent=false;
   for(int k=i-1;k<i+2;++k){if(k<extent.lx||k>extent.hx)continue;
    for(int l=j-1;l<j+2;++l){if(l<extent.ly||l>extent.hy)continue;
     if(k==i&&l==j)continue;if(k!=i&&l!=j)continue;
     if(map[k][l].type()==4){adjacent=true;break;}
    }
   }
   if(adjacent)map[i][j].pinch(true);
  }
 }
 if(wall&&drawable){float z;if(drawable->rva0027257B((int)&z))rva0052F63F(obj,insert);}
}
