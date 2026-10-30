// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// stlport
// BFME1 PhysicsBehaviorRva0029B4E0.cpp at donor9cbfb551 is the semantic
// source for native completion390FAF. Primary constructor/xfer/callers
// prove the target PhysicsBehavior receiver and 12B Coord3D trajectory.
// Original completion/rebound method names remain unasserted. Model bits
//72/122/127/62/128 below are native masks; their names are not donor facts.
// update 0x39114B is slot0 of the UpdateModuleInterface vtable C19F68 the
// primary constructor 0x3907A6 stores at +0x10; it steps the trajectory
// points (Object::setPosition or a Vector3-normalised transform), hands the
// next point to the Object and the pathfinder and finishes through 390FAF.
#include <vector>
#define COORD3D_VIEW_INLINE
#include "../../../../../Libraries/Include/Lib/Coord3DCtorView.h"

class PhysicsModelBits {
 unsigned int words[19];
public:
 __forceinline bool test(int bit) const { return (words[bit>>5] & (1U<<(bit&31)))!=0; }
 __forceinline unsigned int mask(int bit) const { return words[bit>>5] & (1U<<(bit&31)); }
 __forceinline void set(int bit) { words[bit>>5] |= 1U<<(bit&31); }
 __forceinline void reset(int bit) { words[bit>>5] &= ~(1U<<(bit&31)); }
};
struct Rva00390557Template { unsigned char pad[0x115]; unsigned char flags115; };
class Drawable { public: void rva00274176(bool); };
class Object {
public:
 void rva0028AE6D();
 Drawable *getDrawable() const;
 void rva0023D3AF(void *frame);
 char pad00[4]; struct Rva00390557Template *tmpl; char pad08[0x38-8]; Coord3D position;
 char pad44[0x10C-0x44]; PhysicsModelBits conditions;
 char pad158[0x198-0x158]; Coord3D nextPosition;
 char pad1A4[2]; bool nextDirty; char pad1A7[0x274-0x1A7]; Object *holder274; char pad278[0x438-0x278]; unsigned char status438;
 __forceinline void setNextPosition(const Coord3D *p) { nextDirty=true;nextPosition=*p; }
};
class WWMath { public: static float __fastcall Inv_Sqrt(float); };
class Vector3 {
public:
 float X,Y,Z;
 Vector3() {}
 Vector3(float x,float y,float z) { X=x;Y=y;Z=z; }
 float Length2() const { return X*X+Y*Y+Z*Z; }
 __forceinline void Normalize() {
  float len2=Length2();
  if(len2!=0.0f) { float inv=WWMath::Inv_Sqrt(len2); X*=inv;Y*=inv;Z*=inv; }
 }
 // LINK: same-body helper under a TU-unique name (identical inlined bytes); the Normalize copy loses to the first-in-order copy. No flags touched.
 __forceinline void bfme_Normalize_05402() {
  float len2=Length2();
  if(len2!=0.0f) { float inv=WWMath::Inv_Sqrt(len2); X*=inv;Y*=inv;Z*=inv; }
 }
};
class Matrix3D { public: void buildTransformMatrix(const Vector3 &,const Vector3 &); float values[12]; };
class Thing { public: void setPosition(const Coord3D *); void setTransformMatrix(const Matrix3D *); };
class FXList { public: static void doFXPos(const FXList *,const Coord3D *,const Matrix3D *,float,const Coord3D *); };
int GetGameLogicRandomValue(int,int,char *,int);
struct PhysicsTrajectoryConfig {
 char pad00[0x18]; int delayMin,delayMax,phaseFrames,maxBounces;
 char pad28[0x18]; bool at40,at41; char pad42[10]; float at4C; FXList *completionFX; char pad54[4]; bool at58;
};
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff };
#include "../../../../Include/Common/ObjectModule.h"
class BehaviorModuleInterface { public: virtual void slot0()=0; };
class BehaviorModule : public ObjectModule,public BehaviorModuleInterface { public: virtual ~BehaviorModule(); };
class UpdateModuleInterface { public: virtual UpdateSleepTime update()=0; };
class UpdateModule : public BehaviorModule,public UpdateModuleInterface {
public:
 virtual ~UpdateModule();
protected:
 void setWakeFrame(Object *,UpdateSleepTime);
private: unsigned nextWake; int indexInLogic,reserved1C;
};
class PhysicsBehavior : public UpdateModule {
public:
 virtual UpdateSleepTime update();
 UpdateSleepTime rva00390601();
 void rva00390FAF();
 void rva00390E61(bool);
 void rva00390CCA(bool);
 void rva00390629(bool);
 void rva00390557(const Coord3D *,float,float,int,int);
 bool calcFlightPath(bool,float); // row 0x003901DA
 _STL::vector<Coord3D> points;
 Coord3D start,end; float at44,at48; int at4C,index,bounces,phaseTimer;
 bool active,repeat,dirty,at5F; int at60,at64;
};
static __forceinline void setCondition(Object *object,int bit) {
 if(!object->conditions.mask(bit)) { object->conditions.set(bit); object->rva0028AE6D(); }
}
static __forceinline void resetCondition(Object *object,int bit) {
 if(object->conditions.mask(bit)) { object->conditions.reset(bit); object->rva0028AE6D(); }
}
void PhysicsBehavior::rva00390FAF()
{
 if(points.size()<=0) return;
 const PhysicsTrajectoryConfig *physicsTrajectoryConfig=static_cast<const PhysicsTrajectoryConfig *>(static_cast<const void *>(m_moduleData));
 Object *obj=m_object;
 FXList::doFXPos(physicsTrajectoryConfig->completionFX,&obj->position,0,0.0f,0);
 bool changed=false;
 if(obj->conditions.test(72)) {
  setCondition(obj,122);
  resetCondition(obj,72);
  resetCondition(obj,127);
  changed=true;
 }
 if(active && (phaseTimer<=0 || (obj->status438&1))) {
  resetCondition(obj,127);
  resetCondition(obj,72);
  if(obj->status438&1) { setCondition(obj,62);setCondition(obj,122); }
  else {
   setCondition(obj,128);
   phaseTimer=GetGameLogicRandomValue(physicsTrajectoryConfig->delayMin,physicsTrajectoryConfig->delayMax,
    "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\PhysicsUpdate.cpp",752);
   changed=true;
  }
 }
 if(changed && obj->getDrawable()) obj->getDrawable()->rva00274176(0);
 if((repeat || physicsTrajectoryConfig->at58) && bounces<physicsTrajectoryConfig->maxBounces) { rva00390E61(false);return; }
 rva00390CCA(true);
}

class TerrainLogic { public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4(); virtual void slot5();
 virtual float getGroundHeight(float,float,Coord3D *);
};
extern TerrainLogic *TheTerrainLogic;
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
// Visible copy of the rowed 0x00390557 body (PhysicsBehaviorRva00390601.cpp).
inline __declspec(noinline) void PhysicsBehavior::rva00390557(const Coord3D *where,float strength,float value44,int value60,int value64)
{
 Object *obj=m_object;
 Object *holder=obj->holder274;
 if(holder && !(holder->tmpl->flags115&0x20)) {
  setWakeFrame(obj,UPDATE_SLEEP_FOREVER);
  return;
 }
 end=*where;
 start=obj->position;
 at44=value44;
 if(calcFlightPath(true,strength)) {
  index=0;
  if(value60) at60=value60;
  if(value64) at64=value64;
  static_cast<UpdateModuleInterface *>(this)->update();
  m_object->rva0023D3AF(reinterpret_cast<void *>(TheGameLogic->getFrame()));
  static_cast<UpdateModuleInterface *>(this)->update();
  setWakeFrame(m_object,UPDATE_SLEEP_NONE);
 }
}
// Rebound 0x00390E61..0x00390FAF (334 B, RET 4), called by the completion
// 390FAF above. Target facts: WB twin 0x00F91440 gives the statement shape:
// a Vector3 direction from the last two trajectory points with Z cleared
// and normalised, a Coord3D copy of the end point minus the start with Z
// cleared whose length is halved in a separate statement, and a Vector3
// next point (the Object position plus direction times that distance, its
// Z from the terrain ground height) handed to 390557 with the .35/.85
// attenuated +48/+44 values. Retail shares one stack slot between the
// delta and next points (disjoint scopes here). The visible 390557 copy
// above (byte-identical to its row) gives cl its effect on this caller's
// scheduling. Original method names remain unasserted.
void PhysicsBehavior::rva00390E61(bool skipWake)
{
 Object *obj=m_object;
 if(!skipWake) setWakeFrame(obj,UPDATE_SLEEP_NONE);
 ++bounces;
 int count=points.size();
 if(count<2) { rva00390CCA(skipWake); return; }
 Vector3 direction;
 direction.X=points[count-1].x-points[count-2].x;
 direction.Y=points[count-1].y-points[count-2].y;
 direction.Z=0.0f;
 direction.bfme_Normalize_05402();
 const Coord3D *pos=&obj->position;
 float distance;
 {
  Coord3D delta(end);
  delta.sub(&start);
  delta.z=0.0f;
  distance=delta.length();
 }
 distance*=0.5f;
 {
  Vector3 next;
  next.X=direction.X*distance+pos->x;
  next.Y=direction.Y*distance+pos->y;
  next.Z=TheTerrainLogic->getGroundHeight(next.X,next.Y,0);
  rva00390557((const Coord3D *)&next,at48*0.35f,at44*0.85f,0,0);
 }
 dirty=true;
}

class GlobalData { public: char pad00[0xC4]; float gravity; };
extern GlobalData *TheWritableGlobalData;
class Pathfinder { public: void AdjustLayer(Object *); };
class AI { public: char pad00[0x10]; Pathfinder *pathfinder; };
extern AI *TheAI;
// Select-any like the PhysicsUpdate.cpp donor copy (this retail body comes
// first in link order, so it is the copy the link keeps); the anchor keeps the
// body emitted.
inline UpdateSleepTime PhysicsBehavior::update()
{
 const PhysicsTrajectoryConfig *physicsTrajectoryConfig=static_cast<const PhysicsTrajectoryConfig *>(static_cast<const void *>(m_moduleData));
 Object *obj=m_object;
 dirty=false;
 bool changed=false;
 if(active && phaseTimer>0 && !(obj->status438&1)) {
  if(--phaseTimer<=0) {
   if(obj->conditions.test(128)) {
    resetCondition(obj,128);
    setCondition(obj,163);
    phaseTimer=physicsTrajectoryConfig->phaseFrames;
    changed=true;
   } else if(obj->conditions.test(163)) {
    resetCondition(obj,163);
    rva00390629(false);
   } else {
    rva00390629(false);
   }
  }
 }
 if(index>=points.size()) { rva00390FAF(); return rva00390601(); }
 if(changed && obj->getDrawable()) obj->getDrawable()->rva00274176(false);
 const Coord3D *current=&points[index];
 if(physicsTrajectoryConfig->at41 && !physicsTrajectoryConfig->at40 && index>0) {
  const Coord3D *previous=&points[index-1];
  Vector3 direction(current->x-previous->x,current->y-previous->y,current->z-previous->z);
  if(bounces>0) direction.Z=TheWritableGlobalData->gravity*physicsTrajectoryConfig->at4C*100.0f;
  direction.bfme_Normalize_05402();
  Vector3 position(current->x,current->y,current->z);
  Matrix3D transform;
  transform.buildTransformMatrix(position,direction);
  ((Thing *)m_object)->setTransformMatrix(&transform);
 } else {
  ((Thing *)m_object)->setPosition(current);
 }
 Coord3D next;
 const Coord3D *nextPoint;
 if(index<points.size()-1) {
  nextPoint=&points[index+1];
 } else {
  // Past the last point: reflect the Object's position through it.
  Vector3 a(current->x,current->y,current->z),p(obj->position.x,obj->position.y,obj->position.z);
  a.X*=2.0f; a.Y*=2.0f; a.Z*=2.0f;
  a.X-=p.X; a.Y-=p.Y; a.Z-=p.Z;
  next.x=a.X; next.y=a.Y; next.z=a.Z;
  nextPoint=&next;
 }
 obj->setNextPosition(nextPoint);
 TheAI->pathfinder->AdjustLayer(m_object);
 ++index;
 return rva00390601();
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitPhysicsBehaviorUpdate@@YAXPAVPhysicsBehavior@@@Z absent-from-retail
void bfmeEmitPhysicsBehaviorUpdate(PhysicsBehavior *physicsBehavior)
{
	physicsBehavior->PhysicsBehavior::update();
}
