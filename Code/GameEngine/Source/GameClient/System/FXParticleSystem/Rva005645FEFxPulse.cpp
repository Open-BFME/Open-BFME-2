// cl: /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /MD
// Native 0x005645FE..0x0056468E, 144B, RET0. Shared virtual entry in
// retail tables at RVA81C6A8/81CF6C/81D77C, each immediately before9644A9.
// Target: system+4 (or real null factory1FCBD7), position via1F385A,
// pending+40 and FX+38, terrain virtual+18 ground-height comparison,
// static FXList::doFXPos then optional system+128 flag from receiver+1D.
// Target fields and ABI above are established from this body and its vtables;
// the address-derived receiver does not assert a full particle-module identity.
// Existing FXList static provider fixes the prior int/float/pointer call-view
// wall: arguments are FXList*, Coord3D*, Matrix3D*, float zero, Coord3D* zero.
// TerrainLogic owner is carried from the existing TheTerrainLogic data row;
// only virtual slot18 is used here. Placeholder slots are not recovered bodies.
// /arch:SSE enables native x87 FCOMIP; null-first inline accessor preserves
// the retail late ESI reuse. No new symbols.csv pin or emitted byte machinery.
#include "Coord3D.h"
class Matrix3D;
class FXList {public: static void doFXPos(const FXList *, const Coord3D *,const Matrix3D *,float,const Coord3D *);};
class Rva001F385A {public:void rva001F385A(void *);};
class ParticleSystem;
ParticleSystem *Make001FCBD7();
class TerrainLogic {public:
virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();
virtual float height(float x,float y,int flag);
};
extern TerrainLogic *TheTerrainLogic;
struct ParticleFlagView {char pad[0x128];int flag;};
class Rva005645FE {public:void rva005645FE();
__forceinline Rva001F385A *getSystem() { if(!system) return (Rva001F385A *)Make001FCBD7(); return system; }
private:
void *vptr; Rva001F385A *system; char pad8[0x1D-8];bool flag1D;
char pad1E[0x38-0x1E];const FXList *fx;int field3C;bool pending;
};
void Rva005645FE::rva005645FE() {
 Rva001F385A *p=getSystem();
 Coord3D pos; p->rva001F385A(&pos);
 if(pending && fx && TheTerrainLogic->height(pos.x,pos.y,0)>=pos.z) {
  FXList::doFXPos(fx,&pos,0,0.0f,0);
  pending=false;
  if(flag1D) {
   ((ParticleFlagView *)getSystem())->flag=1;
  }
 }
}
