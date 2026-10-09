// ?update@BezierProjectileBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.85 date=2026-10-09
// cl: /O1 /Ob2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// WorldBuilder 1181E80 names BezierProjectileBehavior::update; native
// 45C226..45C812. ZH DumbProjectileBehavior::update supplies path retargeting,
// orientation and bridge transitions. BFME1 BezierProjectileBehavior path
// helpers supply the related subsystem semantics; offsets below are BFME2
// ctor/xfer and native access facts, not carried BFME1 layout.
#define _STLP_NO_EXCEPTIONS 1
#include <math.h>
#include <vector>
#include <bitset>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/PartitionRangeQueryCallView.h"
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;
class Vector3;
class Matrix3D { public: void buildTransformMatrix(const Vector3&,const Vector3&); float m[3][4]; };
class GeometryInfo { public: float getMaxHeightAbovePosition() const; char pad[0x10]; float radius; };
class Thing { public: void setPosition(const Coord3D*); void setTransformMatrix(const Matrix3D*); };
struct BezierModelFlags { unsigned words[19];
 __forceinline unsigned test(int i)const{return words[i>>5]&(1u<<(i&31));}
 __forceinline void set(int i){words[i>>5]|=1u<<(i&31);}
};
enum PathfindLayerEnum { LAYER_GROUND=1 };
class Object : public Thing {
public:
 void rva0028AE6D(); void rva0028EC68(int,void*,int);
 int rva0028B511() const; void rva0028B4CE(PathfindLayerEnum);
 char p00[0x38]; Coord3D pos; char p44[0xA8-0x44]; GeometryInfo geometry;
 char pBC[0x10C-0xBC]; BezierModelFlags flags;
 char p158[0x198-0x158]; Coord3D nextPos; char p1A4[2]; bool nextValid;
 __forceinline void setCondition(int bit) { if (!flags.test(bit)) { flags.set(bit); rva0028AE6D(); } }
};
class WeaponTemplate { public: Coord3D *getAimPosition(Coord3D*,const Object*,const Object*,int); };
static __forceinline Coord3D getAimPositionValue(WeaponTemplate *w,Object *o,Object *t) { Coord3D p;return *w->getAimPosition(&p,o,t,1); }
class TerrainLogic {
public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();
 virtual float getGroundHeight(float,float,Coord3D*);
 virtual float getLayerHeight(float,float,int,Coord3D*,bool);
 PathfindLayerEnum getHighestLayerForDestination(const Coord3D*,bool);
};
extern TerrainLogic *TheTerrainLogic;
class BezierDebugDisplay { public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();
 virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();
 virtual void drawCircle(const Coord3D*,float,unsigned);
};
extern BezierDebugDisplay *TheDisplay;
struct BezierGlobalData { char pad[0xE9C]; bool debug; };
extern BezierGlobalData *TheGlobalData;
class Rva000421C8 { public:
 Rva000421C8():m_next(0){} virtual ~Rva000421C8(){} virtual bool allow(Object*)=0;
 virtual int getPlayerMask(); Rva000421C8 *link(Rva000421C8*); Rva000421C8 *m_next;
};
class Rva0026119DFilter:public Rva000421C8 { public: virtual bool allow(Object*); };
class Rva002611BFFilter:public Rva000421C8 { public:
 Rva002611BFFilter(const Object*p):m_obj(p){} virtual bool allow(Object*);const Object *m_obj;
};
class Rva00260EB1Filter:public Rva000421C8 { public:
 Rva00260EB1Filter(const Object*p,int f,bool b):m_obj(p),m_flags(f),m_match(b){}
 virtual bool allow(Object*);virtual int getPlayerMask();const Object *m_obj;int m_flags;bool m_match;
};
class WWMath { public: static float __fastcall Inv_Sqrt(float); };
class Gen_001EFCE0 { public: int bfmeCost() const; };
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff };
struct BezierProjectileBehaviorModuleData {
 char p00[0x3C]; int nearEndFrames; char p40[8];bool tumble;bool orient;
 char p4A[0x8C-0x4A];float adjustDistance;char p90[0xAC-0x90];int effect;
 float effectRadius;bool includeAllies;
};
class BehaviorBase { public:virtual ~BehaviorBase(); const BezierProjectileBehaviorModuleData *data;Object*object; };
struct BehaviorInterface { virtual void s0(); };
struct UpdateModuleInterface { virtual UpdateSleepTime update()=0; };
struct BezierProjectileInterface { virtual void s0();virtual void s1();virtual void s2();virtual void hit(Object*)=0; };
struct BezierSecondInterface { virtual void s0(); };
class BezierUpdateBase:public BehaviorBase,public BehaviorInterface,public UpdateModuleInterface { char storage[12]; };
class BezierProjectileBehavior:public BezierUpdateBase,public BezierProjectileInterface,public BezierSecondInterface {
public:
 virtual UpdateSleepTime update();
private: bool calcFlightPath(bool);
public: void rva0045C026();
 ObjectID launcher;Coord3D launchPos;ObjectID victim;int v3c;WeaponTemplate*weapon;
 _STL::vector<Coord3D> path;char p50[12];Coord3D end;float collisionRadius;int p6c;int step;
 int bonus;int packets;void*list;bool detonated;char p81[3];float scale;
};
UpdateSleepTime BezierProjectileBehavior::update() {
 const BezierProjectileBehaviorModuleData *d=data;Object*obj=object;
 if(!d || !obj) return UPDATE_SLEEP_FOREVER;
 int count=path.size();
 if(step>=count) { hit(0);return (UpdateSleepTime)((Gen_001EFCE0*)this)->bfmeCost(); }
 if(d->nearEndFrames && step==count-d->nearEndFrames) {
  obj->setCondition(155);
  if(d->effect!=-1) {
   int relation=2;if(d->includeAllies)relation=6;relation|=1;
   if(TheGlobalData->debug) { Coord3D p;p.x=end.x;p.y=end.y;p.z=end.z;p.z=TheTerrainLogic->getGroundHeight(p.x,p.y,0);TheDisplay->drawCircle(&p,d->effectRadius,0xffff00ff); }
   BfmeWideResult result=ThePartitionManager->iterateObjectsInRange(&end,d->effectRadius,1,
    Rva00260EB1Filter(obj,relation,false).link(Rva0026119DFilter().link(&Rva002611BFFilter(obj))),1);
   Object *other;while((other=result.next())!=0) { if(other!=obj) other->rva0028EC68(d->effect,obj,1); }
  }
 }
 if(victim!=0 && d->adjustDistance>0.0f) {
  Object*target=TheGameLogic->findObjectByID(victim);
  if(target) {
   Coord3D newPos=getAimPositionValue(weapon,obj,target);
   Coord3D delta;delta.x=newPos.x-end.x;delta.y=newPos.y-end.y;delta.z=newPos.z-end.z;
   float sq=delta.x*delta.x+delta.y*delta.y+delta.z*delta.z;
   if(sq>0.1f) {
    float distance=(float)sqrt(sq);if(distance>d->adjustDistance)distance=d->adjustDistance;
    delta.normalize();end.x+=distance*delta.x;end.y+=distance*delta.y;end.z+=distance*delta.z;
    if(!calcFlightPath(false)) { rva0045C026();return (UpdateSleepTime)((Gen_001EFCE0*)this)->bfmeCost(); }
   }
  }
 }
 const Coord3D *flight=&path[step];
 if(d->orient && !d->tumble) {
  Coord3D previous,next;
  float length=scale*20.0f;
  if(step>0) previous=path[step-1];else { previous=path[step];previous.z-=length; }
  if(step<count-1)next=path[step+1];else {next=path[step];next.z-=length;}
  Coord3D delta;delta.x=next.x-previous.x;delta.y=next.y-previous.y;delta.z=next.z-previous.z;
  float sq=delta.x*delta.x+delta.y*delta.y+delta.z*delta.z;
  if(sq!=0) { float inv=WWMath::Inv_Sqrt(sq);delta.x*=inv;delta.y*=inv;delta.z*=inv; }
  Coord3D position;position.x=flight->x;position.y=flight->y;position.z=flight->z;
  Matrix3D matrix;matrix.buildTransformMatrix(*(Vector3*)&position,*(Vector3*)&delta);obj->setTransformMatrix(&matrix);
 }else obj->setPosition(flight);
 Coord3D next;
 const Coord3D *nextPtr;
 if(step<count-1)nextPtr=&path[step+1];else {
  next.x=flight->x*2.0f-obj->pos.x;next.y=flight->y*2.0f-obj->pos.y;next.z=flight->z*2.0f-obj->pos.z;nextPtr=&next;
 }
 obj->nextValid=true;obj->nextPos=*nextPtr;
 if(victim!=0) {
  Object*target=TheGameLogic->findObjectByID(victim);
  if(target) {
   Coord3D p;p.x=target->pos.x;p.y=target->pos.y;p.z=target->pos.z;
   p.z+=target->geometry.getMaxHeightAbovePosition()*0.5f;
   float radius=target->geometry.radius;
   if(p.length()<radius+collisionRadius)hit(target);
  }
 }
 int oldLayer=obj->rva0028B511();int newLayer=TheTerrainLogic->getHighestLayerForDestination(&obj->pos,false);
 obj->rva0028B4CE((PathfindLayerEnum)newLayer);
 if(oldLayer!=1 && newLayer==1) {
  Coord3D p;p.x=obj->pos.x;p.y=obj->pos.y;p.z=9999.0f;
  int test=TheTerrainLogic->getHighestLayerForDestination(&p,false);
  if(test==oldLayer) {
   p.z=TheTerrainLogic->getLayerHeight(p.x,p.y,test,0,true)+2.0f;obj->setPosition(&p);
   rva0045C026();return (UpdateSleepTime)((Gen_001EFCE0*)this)->bfmeCost();
  }
 }
 ++step;return (UpdateSleepTime)((Gen_001EFCE0*)this)->bfmeCost();
}
