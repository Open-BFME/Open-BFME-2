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
class Matrix3D;
class FXList { public: static void doFXPos(const FXList *,const Coord3D *,const Matrix3D *,float,const Coord3D *); };
int GetGameLogicRandomValue(int,int,char *,int);
struct PhysicsTrajectoryConfig {
 char pad00[0x18]; int delayMin,delayMax,phaseFrames,maxBounces;
 char pad28[0x28]; FXList *completionFX; char pad54[4]; bool at58;
};
class PhysicsBehavior {
public:
 void rva00390FAF();
 void rva00390E61(bool);
 void rva00390CCA(bool);
 char pad00[4]; const PhysicsTrajectoryConfig *data; Object *object;
 char pad0C[0x14]; _STL::vector<Coord3D> points;
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
