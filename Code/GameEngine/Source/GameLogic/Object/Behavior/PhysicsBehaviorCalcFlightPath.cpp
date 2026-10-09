// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// Reference guide: BF1f989 Bezier flight construction and verified BF2 45B5F4.
// WB F8FC90/native3901DA..39051E establish PhysicsBehavior flight path semantics.
// Target facts: primary receiver, data4, vector20, start2C/end38, speed44,
// curve-height48, segments4C and alternate54; MD42 selects simple-Z.
// The address-derived 12B point inherits canonical Coord3D; its separate
// empty callbacks are proven byte-and-relocation twins, not unique recovery.
// Rva0055A246 is the existing address-owned 48B curve view. Reading the
// contiguous four-point source as that view preserves its established copy ABI.
#include <math.h>
#include "vector3.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
struct Rva003901DAPoint : Coord3D { Rva003901DAPoint(); ~Rva003901DAPoint(); };
class Rva0055A246 {
public:Rva0055A246(const Rva0055A246&);float rva0055A627(float)const;void rva0055A7DB(int,void*);
 Rva003901DAPoint points[4];
};
template<int N> class PhysicsFlightSlots: public PhysicsFlightSlots<N-1>{public:virtual void slot(char(*)[N])=0;};
template<> class PhysicsFlightSlots<0>{};
class PhysicsFlightTerrain : public PhysicsFlightSlots<16>{public:virtual float highest(const Coord3D*,const Coord3D*)=0;};
extern PhysicsFlightTerrain *TheTerrainLogic;
struct PhysicsFlightData {
 unsigned char pad[8];float height1,height2,percent1,percent2;unsigned char pad18[0x2c-0x18];float heightB1,heightB2,percentB1,percentB2,heightRange;unsigned char pad40[2];bool simpleZ;unsigned char pad43;float zPercent1,zPercent2;
};
class PhysicsBehavior {
public:bool calcFlightPath(bool,float);
 unsigned vptr;const PhysicsFlightData *data;unsigned char pad8[0x20-8];unsigned start,finish,end;Coord3D source,target;float speed,curveHeight;int segments;unsigned char pad50[4];int alternate;
};
template<class T> inline const T &physicsRefMax(const T&a,const T&b){return a>b?a:b;}
bool PhysicsBehavior::calcFlightPath(bool recalc,float maxHeight)
{
 const PhysicsFlightData *d=data;
 if(maxHeight<0.5f)maxHeight=0.5f;
 float firstPct,secondPct;
 if(!alternate)firstPct=d->percent1;else firstPct=d->percentB1;
 if(!alternate)secondPct=d->percent2;else secondPct=d->percentB2;
 Rva003901DAPoint cp[4];
 static_cast<Coord3D&>(cp[0])=source;static_cast<Coord3D&>(cp[3])=target;
 float z=source.z-target.z;if(z<0.0f)z=0.0f;
 float scale=(maxHeight-z)/maxHeight;if(scale<0.0f)scale=0.0f;
 curveHeight=maxHeight+z;
 cp[1].x=firstPct*(cp[3].x-cp[0].x)+cp[0].x;
 cp[1].y=firstPct*(cp[3].y-cp[0].y)+cp[0].y;
 cp[2].x=(cp[3].x-cp[0].x)*secondPct+cp[0].x;
 cp[2].y=(cp[3].y-cp[0].y)*secondPct+cp[0].y;
 if(d->simpleZ){
  cp[1].z=(cp[3].z-cp[0].z)*d->zPercent1+cp[0].z;
  cp[2].z=(cp[3].z-cp[0].z)*d->zPercent2+cp[0].z;
 }else{
  float highest=TheTerrainLogic->highest(&cp[0],&cp[3]);
  float firstHeight,secondHeight;
  if(!alternate)firstHeight=d->height1;else firstHeight=d->heightB1;
  if(!alternate)secondHeight=d->height2;else secondHeight=d->heightB2;
  firstHeight*=maxHeight;secondHeight*=scale*maxHeight;
  if(d->heightRange>0.0f){
   Vector3 delta;delta.X=cp[3].x-cp[0].x;delta.Y=cp[3].y-cp[0].y;delta.Z=cp[3].z-cp[0].z;
   float factor=delta.Length()/d->heightRange;if(factor>1.0f)factor=1.0f;
   cp[1].z=firstPct*(cp[3].z-cp[0].z)+cp[0].z;
   float z2=(cp[3].z-cp[0].z)*secondPct+cp[0].z;
   if(cp[1].z<highest)cp[1].z=highest;
   cp[1].z=factor*firstHeight+cp[1].z;
   if(z2<highest)z2=highest;
   cp[2].z=factor*secondHeight+z2;
  }else{
   highest=physicsRefMax(highest,cp[0].z);highest=physicsRefMax(highest,cp[3].z);
   cp[1].z=highest+firstHeight;cp[2].z=highest+secondHeight;
  }
 }
 Rva0055A246 segment(*reinterpret_cast<const Rva0055A246*>(cp));
 if(recalc){float step=speed;segments=(int)(ceil(segment.rva0055A627(1.0f)/step)+1.0f);}
 if(segments<3)segments=3;
 segment.rva0055A7DB(segments,&start);
 return true;
}
