// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /I.
// ?rva00530212@Pathfinder@@QAEXPAVObject@@_N11@Z, native 0x00530212..0x00530F47
// (RET 16, 3381 B): the object-footprint classifier behind the four
// Pathfinder add/remove forwarders (PathfindShimAddObject.cpp) and newMap.
// Identity and boundary are target facts (callers, RET 16, neighbours
// 0x0052F63F and 0x00530F47); the semantic spine is carried from ZH
// AIPathfind.cpp classifyObjectFootprint / internal_classifyObjectFootprint
// (filters, box and sphere rasterizers, pinch and border passes). BFME-specific
// wall, portal, multi-shape, gate and layer checks are read from target bytes
// and WorldBuilder. No original BFME 2 member name is proven: the RVA name stays.
// Codegen notes: the function-scope `int i, j;` used by the gate-clearing and
// sphere loops (ZH style) sets retail's base/index order in the box gate path;
// the post-switch passes declare their own loop counters.
#include "Code/Libraries/Include/Lib/Coord3D.h"
// All floor operations inline here; keep the unused wrapper local.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>
#include "Code/Libraries/Include/Lib/ICoord2D.h"
#include "Code/Libraries/Include/Lib/Region2D.h"
struct FootprintCoord2D{float x,y;};
struct FootprintBounds{int lx,ly,hx,hy;};
class Rva0027C36A {public:Rva0027C36A();unsigned words[0xa8/4];};
class Drawable {public:
 bool rva0027267D(int,int,int,int);bool rva002726C3(int,int,int,int);
 int rva0027257B(int);bool rva00272C1E();void createEmbeddedPortals();
};
class Rva00279677{public:void rva00279677();};
struct BfmeVecVNB{float x,y,z; BfmeVecVNB(const float *v):x(v[0]),y(v[1]),z(v[2]){} };
class BfmeXformVNB{public:void bfmeApplyVNB(BfmeVecVNB*,float);};
struct BfmeShapeE15 {int type;int field4;float major,minor,offsetX,offsetY,offsetZ;bool flag1C;char pad1D[3];bool enabled;char pad21[3];};
class BfmeObjE15{public:BfmeShapeE15 *getGeometryShape(int);};
class Rva0087E370{public:void method(const Coord3D&,float,Region2D&)const;};
struct FootprintTemplate {char pad[0x108];union {unsigned kinds[6];struct {unsigned kind0;unsigned pad1:28;unsigned isWall:1;unsigned isDefense:1;unsigned pad2:2;unsigned rest[4];};};unsigned words120;char pad124[0x4a0-0x124];float fenceWidth;__forceinline unsigned kind(int b)const{return kinds[b/32]&(1u<<(b%32));}};
enum ObjectStatusTypes{Status77=77,Status88=88};
enum KindOfType{KINDOF_5E=0x5E};
class Object {public:
 Drawable *getDrawable()const;void rva0028AD32();void rva0028AD8C();void rva0028AD7C();bool isMobile()const;bool testStatus(ObjectStatusTypes)const;bool isKindOf(KindOfType)const;
 const Coord3D *getPosition()const{return &position;}
 char pad0[4];FootprintTemplate *templ;char pad8[0x38-8];Coord3D position;float orientation;char pad48[0xac-0x48];bool small;char padAD[0xd4-0xad];BfmeShapeE15 *begin,*end;
};
#include "../../Common/Thing/thing.h"
struct Rva0052DEEFArg;struct Rva0052DFB1Arg;struct In002E6BA1{int x,y;};
class PathfindCell {public:
 bool SetType_Dirty(int);bool rva0052DEEF(const Rva0052DEEFArg*,bool,In002E6BA1*);bool rva0052DFB1(const Rva0052DFB1Arg*);
 enum CellType{Clear=0,Water=1,Cliff=2,Reserved=3,Obstacle=4,Impassable=5}; __forceinline int type()const{return m_type;}__forceinline int layer()const{return m_layer;}__forceinline bool pinched()const{return m_pinched;}__forceinline void pinch(bool b){m_pinched=b;}
 __forceinline bool gate()const{return m_gate;}
 char pad[12];unsigned m_type:4;unsigned m_layer:6;unsigned m_low:6;unsigned m_pinched:1;unsigned m_gate:1;unsigned m_mid:4;unsigned m_22:1;unsigned m_23:1;unsigned m_high:8;
};
class Rva0052E001{public:bool rva0052E001(bool);};
class Rva0052E02F{public:bool rva0052E02F(bool);};
class PathfindZoneManager{public:void MarkDirty(int,int);};
float Sin(float);float Cos(float);
static __forceinline long float2long(float f){long i;__asm{
 fld f
 fistp i
}return i;}
#define FLOOR(x) float2long(floorf(x))
#define CEIL(x) float2long(ceilf(x))
enum PathfindLayerEnum{LayerGround=1};
class Pathfinder{public:
 void rva00530212(Object*,bool,bool,bool);void ClassifyWall(Object*,bool);void rva0052E4C9(Object*,bool);PathfindCell *getCell(PathfindLayerEnum,int,int);
 char pad0[0x10];PathfindCell**map;FootprintBounds extent;char pad24[0x460-0x24];PathfindZoneManager zones;char pad461[0x1beb4-0x461];bool changedWall,changedGate;
};
void Pathfinder::rva00530212(Object*obj,bool insert,bool keepGate,bool goal)
{
 int i,j;
 const Coord3D *objPos=obj->getPosition();
 Drawable *drawable=obj->getDrawable();
 if(drawable){if(insert)drawable->createEmbeddedPortals();else ((Rva00279677*)drawable)->rva00279677();}
 if(obj->templ->kind(25)||obj->templ->kind(24)||obj->templ->kind(149))return;
 bool wall=obj->templ->isWall;
 if(!wall && obj->templ->fenceWidth>0.0f && !obj->templ->kind(61)){rva0052E4C9(obj,insert);return;}
 if(!insert){obj->rva0028AD32();if(!goal)obj->rva0028AD8C();}else obj->rva0028AD7C();
 // mobile aren't obstacles.
 /// For now, all small objects will not be obstacles
 if(!obj->templ->kind(7)||obj->isMobile()||obj->small||obj->testStatus(Status88))return;
 if(wall){if(obj->templ->kind(150))wall=obj->getDrawable()->rva00272C1E();else if(obj->testStatus(Status77))wall=false;}
 // Don't add bounds that are up in the air....
 if(((Thing*)obj)->getHeightAboveTerrain()>10.0f&&!wall)return;
 if(wall&&drawable){float z;if(!drawable->rva0027257B((int)&z)){changedWall=true;ClassifyWall(obj,insert);return;}}
 bool gate=obj->templ->kind(137)||wall;
 bool bit22=insert ? ((obj->templ->words120>>9)&1)!=0:false;
 if((gate||bit22)&&!insert)changedGate=true;
 if(insert&&obj->templ->kind(120)&&obj->isKindOf(KINDOF_5E)){
  int x=(int)(objPos->x*0.1f),y=(int)(objPos->y*0.1f);
  for(i=-60;i<=60;++i)for(j=-60;j<=60;++j){PathfindCell*cell=getCell(LayerGround,x+i,y+j);if(cell&&cell->gate()){((Rva0052E001*)cell)->rva0052E001(false);zones.MarkDirty(x+i,y+j);}}
 }
 Rva0027C36A data;
 void*poly;
 if(drawable){if(drawable->rva0027267D((int)&data,(int)&poly,0,0)||drawable->rva002726C3((int)&data,(int)&poly,0,0))gate=true;}
 float angle=obj->orientation;
 for(int k=0;k<obj->end-obj->begin;++k){
  BfmeShapeE15 *shape=((BfmeObjE15*)((char*)obj+0xa8))->getGeometryShape(k);
  if(!shape->enabled||shape->offsetZ>10.0f)continue;
  BfmeVecVNB pos(&objPos->x);
  float cosine=Cos(angle),s=Sin(angle);
  ((BfmeXformVNB*)shape)->bfmeApplyVNB(&pos,angle);
  switch(shape->type){
  case 2:{
   float halfX=shape->major,halfY=shape->minor;
   // in theory, should be PATHFIND_CELL_SIZE_F exactly, but needs to be smaller to avoid aliasing problems
   float ydx=s*5.0f,ydy=-(cosine*5.0f),xdx=cosine*5.0f,xdy=s*5.0f;
   int nx=CEIL(2.0f*halfX/5.0f),ny=CEIL(2.0f*halfY/5.0f);
   float tlx=pos.x-halfX*cosine-halfY*s,tly=pos.y+halfY*cosine-halfX*s;
   for(int iy=0;iy<ny;++iy,tlx+=ydx,tly+=ydy){
    float x=tlx,y=tly;
    for(int ix=0;ix<nx;++ix,x+=xdx,y+=xdy){
     int cx=FLOOR((x+0.5f)*0.1f),cy=FLOOR((y+0.5f)*0.1f);
     if(cx<0||cy<0||cx>=extent.hx||cy>=extent.hy)continue;
     bool accept=false;
     if(map[cx][cy].layer()!=1){
      if(!gate)continue;
      if((map[cx][cy].type()==0||map[cx][cy].type()==3)&&insert)accept=true;
      if((map[cx][cy].type()==4||map[cx][cy].type()==3)&&!insert)accept=true;
      if(!accept)continue;
     }
     bool dirty;
     if(insert){
      if(gate){if(map[cx][cy].type()==2||map[cx][cy].type()==3){map[cx][cy].SetType_Dirty(0);zones.MarkDirty(cx,cy);}}
      In002E6BA1 cellPoint={cx,cy};dirty=map[cx][cy].rva0052DEEF((const Rva0052DEEFArg*)obj,false,&cellPoint);
     }else dirty=map[cx][cy].rva0052DFB1((const Rva0052DFB1Arg*)obj);
     if(dirty)zones.MarkDirty(cx,cy);
     if(gate&&!keepGate&&map[cx][cy].gate()!=insert){((Rva0052E001*)&map[cx][cy])->rva0052E001(insert);zones.MarkDirty(cx,cy);}
     if(((Rva0052E02F*)&map[cx][cy])->rva0052E02F(bit22))zones.MarkDirty(cx,cy);
    }
   }
  }break;
  case 0: // not quite right, but close enough
  case 1:{
   // fill in all cells that overlap as obstacle cells
   /// @todo This is a very inefficient circle-rasterizer
   ICoord2D topLeft,bottomRight;
   FootprintCoord2D center,delta;
   float radius=shape->major;
   float radiusSquared,size;
   topLeft.x=FLOOR((pos.x-radius)*0.1f+0.5f)-1;
   topLeft.y=FLOOR((pos.y-radius)*0.1f+0.5f)-1;
   size=radius*0.1f;center.x=pos.x*0.1f;center.y=pos.y*0.1f;
   size+=0.4f;radiusSquared=size*size;
   bottomRight.x=(int)(topLeft.x+2*size+2);bottomRight.y=(int)(topLeft.y+2*size+2);
   for(j=topLeft.y;j<bottomRight.y;++j)for(i=topLeft.x;i<bottomRight.x;++i){
    delta.x=i+0.5f-center.x;delta.y=j+0.5f-center.y;
    if(!(delta.x*delta.x+delta.y*delta.y<=radiusSquared)||i<0||j<0||i>=extent.hx||j>=extent.hy||map[i][j].layer()!=1)continue;
    if(insert){In002E6BA1 cellPoint={i,j};if(map[i][j].rva0052DEEF((const Rva0052DEEFArg*)obj,false,&cellPoint))zones.MarkDirty(i,j);}
    else if(map[i][j].rva0052DFB1((const Rva0052DFB1Arg*)obj))zones.MarkDirty(i,j);
    if(gate&&map[i][j].gate()!=insert){((Rva0052E001*)&map[i][j])->rva0052E001(insert);zones.MarkDirty(i,j);}
    if(((Rva0052E02F*)&map[i][j])->rva0052E02F(bit22))zones.MarkDirty(i,j);
   }
  }break;
  }
 }
 Region2D world;
 ((Rva0087E370*)((char*)obj+0xa8))->method(obj->position,obj->orientation,world);
 FootprintBounds bounds; bounds.lx=FLOOR(world.lo.x*0.1f)-1; bounds.ly=FLOOR(world.lo.y*0.1f)-1; bounds.hx=CEIL(world.hi.x*0.1f)+1; bounds.hy=CEIL(world.hi.y*0.1f)+1;
 if(bounds.lx<extent.lx)bounds.lx=extent.lx;
 if(bounds.ly<extent.ly)bounds.ly=extent.ly;
 if(bounds.ly<extent.ly)bounds.ly=extent.ly;
 if(bounds.hx>extent.hx)bounds.hx=extent.hx;
 if(bounds.hy>extent.hy)bounds.hy=extent.hy;
 if(!insert)for(int j=bounds.ly;j<=bounds.hy;++j)for(int i=bounds.lx;i<=bounds.hx;++i){
  if(map[i][j].type()==5&&map[i][j].layer()==1){map[i][j].SetType_Dirty(0);zones.MarkDirty(i,j);}
 }
 // Check for pinched cells, and close them off.
 for(int j=bounds.ly;j<=bounds.hy;++j)for(int i=bounds.lx;i<=bounds.hx;++i){
  if(map[i][j].layer()!=1)continue;
  map[i][j].pinch(false);
  if(map[i][j].type()==0){
   int total=0,ortho=0;
   for(int k=i-1;k<i+2;++k){if(k<extent.lx||k>extent.hx)continue;
    for(int neighborY=j-1;neighborY<j+2;++neighborY){if(neighborY<extent.ly||neighborY>extent.hy)continue;
     if(k==i&&j==neighborY)continue;
     if(map[k][neighborY].type()==0){++total;if(k==i||neighborY==j)++ortho;}
    }
   }
   // If the total open cells are < 2 or total cells < 4, we are pinched.
   if(ortho<2||total<4)map[i][j].pinch(true);
  }
 }
 for(int j=bounds.ly;j<=bounds.hy;++j)for(int i=bounds.lx;i<=bounds.hx;++i){
  if(map[i][j].layer()==1&&map[i][j].pinched()&&map[i][j].type()==0){map[i][j].SetType_Dirty(5);map[i][j].pinch(false);zones.MarkDirty(i,j);}
 }
 // Expand building bounds 1 cell.
 for(int j=bounds.ly;j<=bounds.hy;++j)for(int i=bounds.lx;i<=bounds.hx;++i){
  if(map[i][j].layer()==1&&map[i][j].type()==0){
   bool adjacent=false;
   for(int k=i-1;k<i+2;++k){if(k<extent.lx||k>extent.hx)continue;
    for(int neighborY=j-1;neighborY<j+2;++neighborY){if(neighborY<extent.ly||neighborY>extent.hy)continue;
     if(k==i&&neighborY==j)continue;if(k!=i&&neighborY!=j)continue;
     if(map[k][neighborY].type()==4){adjacent=true;break;}
    }
   }
   if(adjacent)map[i][j].pinch(true);
  }
 }
 if(wall&&drawable){float z;if(drawable->rva0027257B((int)&z))ClassifyWall(obj,insert);}
}
