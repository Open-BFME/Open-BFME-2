// ?rva00390E61@PhysicsBehavior@@QAEX_N@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// stlport
// BFME1 PhysicsBehaviorRva0029B4E0.cpp at donor9cbfb551 is the semantic
// source for native completion390FAF. Primary constructor/xfer/callers
// prove the target PhysicsBehavior receiver and 12B Coord3D trajectory.
// Original completion/rebound method names remain unasserted. Model bits
//72/122/127/62/128 below are native masks; their names are not donor facts.
#include <vector>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class PhysicsModelBits {
 unsigned int words[19];
public:
 __forceinline bool test(int bit) const { return (words[bit>>5] & (1U<<(bit&31)))!=0; }
 __forceinline unsigned int mask(int bit) const { return words[bit>>5] & (1U<<(bit&31)); }
 __forceinline void set(int bit) { words[bit>>5] |= 1U<<(bit&31); }
 __forceinline void reset(int bit) { words[bit>>5] &= ~(1U<<(bit&31)); }
};
class Drawable { public: void rva00274176(bool); };
class Object {
public:
 void rva0028AE6D();
 Drawable *getDrawable() const;
 char pad00[0x38]; Coord3D position;
 char pad44[0x10C-0x44]; PhysicsModelBits conditions;
 char pad158[0x438-0x158]; unsigned char status438;
};
class Vector3 { public: float X,Y,Z; Vector3() {} Vector3(float x,float y,float z):X(x),Y(y),Z(z) {} };
class Matrix3D { public: void buildTransformMatrix(const Vector3 &,const Vector3 &); float values[12]; };
class Thing { public: void setPosition(const Coord3D *); void setTransformMatrix(const Matrix3D *); };
class TerrainLogic { public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4(); virtual void slot5();
 virtual float getGroundHeight(float,float,Coord3D *);
};
extern TerrainLogic *TheTerrainLogic;
class WWMath { public: static float __fastcall Inv_Sqrt(float); };

class FXList { public: static void doFXPos(const FXList *,const Coord3D *,const Matrix3D *,float,const Coord3D *); };
int GetGameLogicRandomValue(int,int,char *,int);
struct PhysicsTrajectoryConfig {
 char pad00[0x18]; int delayMin,delayMax,phaseFrames,maxBounces;
 char pad28[0x18]; bool at40,at41; char pad42[10]; float at4C; FXList *completionFX; char pad54[4]; bool at58;
};
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff };
class ObjectModule {
public:
 virtual ~ObjectModule();
 const PhysicsTrajectoryConfig *data; Object *object;
};
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
 void rva00390557(const Coord3D *,float,float,int,int);
 void rva00390FAF();
 void rva00390E61(bool);
 void rva00390CCA(bool);
 _STL::vector<Coord3D> points;
 Coord3D start,end; float at44,at48; int at4C,index,bounces,phaseTimer;
 bool active,repeat,dirty,at5F; int at60,at64;
};
static __forceinline void setCondition(Object *o,int bit) {
 if(!o->conditions.mask(bit)) { o->conditions.set(bit); o->rva0028AE6D(); }
}
static __forceinline void resetCondition(Object *o,int bit) {
 if(o->conditions.mask(bit)) { o->conditions.reset(bit); o->rva0028AE6D(); }
}
void PhysicsBehavior::rva00390FAF()
{
 if(points.size()<=0) return;
 const PhysicsTrajectoryConfig *d=data;
 Object *obj=object;
 FXList::doFXPos(d->completionFX,&obj->position,0,0.0f,0);
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
   phaseTimer=GetGameLogicRandomValue(d->delayMin,d->delayMax,
    "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\PhysicsUpdate.cpp",752);
   changed=true;
  }
 }
 if(changed && obj->getDrawable()) obj->getDrawable()->rva00274176(0);
 if((repeat || d->at58) && bounces<d->maxBounces) { rva00390E61(false);return; }
 rva00390CCA(true);
}

// Rebound derived from target334B and BFME1 completion's rva0029B350 edge;
// direction normalization uses the same WWMath/Coord3D math as the donor.
// The .35/.85 attenuation constants and ground query are target facts.
// ?rva00390E61@PhysicsBehavior@@QAEX_N@Z present-unmatched
void PhysicsBehavior::rva00390E61(bool skipWake)
{
 Object *obj=object;
 if(!skipWake) setWakeFrame(obj,UPDATE_SLEEP_NONE);
 ++bounces;
 int count=points.size();
 if(count<2) { rva00390CCA(skipWake);return; }
 Coord3D next;
 Vector3 direction;
 direction.X=points[count-1].x-points[count-2].x;
 direction.Y=points[count-1].y-points[count-2].y;
 direction.Z=0.0f;
 float sq=direction.X*direction.X+direction.Y*direction.Y;
 if(sq!=0.0f) {
  float inv=WWMath::Inv_Sqrt(sq);
  direction.X*=inv;direction.Y*=inv;
 }
 float dx=end.x-start.x;
 float dy=end.y-start.y;
 next.x=dx;next.y=dy;next.z=0;
 float distance=next.length()*0.5f;
 TerrainLogic *terrain=TheTerrainLogic;
 next.x=obj->position.x+direction.X*distance;
 next.y=obj->position.y+direction.Y*distance;
 next.z=terrain->getGroundHeight(next.x,next.y,0);
 rva00390557(&next,at48*0.35f,at44*0.85f,0,0);
 dirty=true;
}
