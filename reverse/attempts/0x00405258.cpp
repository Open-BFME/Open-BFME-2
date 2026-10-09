// ?rva00405258@VictorySystemGridUpdateView@@QAEXXZ
// partial score=0.82 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD
// BFME1 semantic source: VictorySystemApplyCells.cpp at
// 9cbfb551fe20dae985f91f2319d8997287b6a705. Target independently fixes
// root cell +78, twenty player slots, grids12C/130 and values at grid+18.
// Native callbacks 4050CE..4051BC and 405258..405315 use rowed Object,
// root-cell and CellGrid providers. Original method names remain unknown.
class Object;
class Player { public: char pad[0x54]; int index; };
struct VictoryObjectTemplate { char pad[0x109]; unsigned char flags109; char pad10a[9]; unsigned char flags113; };
class Object { public: Player *getControllingPlayer() const; char pad0[4]; VictoryObjectTemplate *tmpl; char pad8[0x438-8]; unsigned char flags438; };
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
struct VictoryDeathInfo { char pad[8]; ObjectID killer; };
struct Vec3 { float x,y,z; };
#include "Code/Libraries/Include/Lib/Coord3D.h"
class Rva00404781 { public: void rva00404781(float,int,int); int rva00404CF5(bool); float a[20],b[20]; unsigned int masks[2]; };
class Rva0056C4D3 { public: void rva0056C4D3(void*,float,int,int); };
class Rva0056C0F0 { public: void rva0056C0F0(unsigned int,Vec3*); };
class Rva004051BC { public: void rva004051BC(int,const Coord3D*); };
class CellGrid { public: int rva0056C16D(); unsigned width,height,count; float size,offset; Rva00404781 *cells; unsigned int *values; };
struct VictoryGridParameter { float fields[5]; float weight; };
class VictorySystemGridUpdateView {
public: void rva004050CE(Object*,const VictoryDeathInfo*); void rva00405258();
private:
 char pad0[0x28]; int playerIndices[20]; Rva00404781 root;
 VictoryGridParameter *parameters,*parametersEnd,*parametersCapacity;
 CellGrid *grids[2];
};
void VictorySystemGridUpdateView::rva004050CE(Object *victim,const VictoryDeathInfo *info) {
 if (!victim || !info || (victim->flags438 & 8)) return;
 Player *victimPlayer;
 Object *killer=TheGameLogic->findObjectByID(info->killer);
 if (!killer) return;
 victimPlayer=victim->getControllingPlayer();
 Player *killerPlayer=killer->getControllingPlayer();
 if (!victimPlayer || !killerPlayer) return;
 int victimIndex=victimPlayer->index;
 int parameterIndex=playerIndices[victimIndex];
 if ((unsigned)parameterIndex & 0x80000000) return;
 VictoryGridParameter *parameter=&parameters[parameterIndex];
 float weight;
 if ((victim->tmpl->flags109 & 4) || (victim->tmpl->flags113 & 4)) weight=parameter->weight;
 else weight=1.0f;
 root.rva00404781(weight,victimIndex,killerPlayer->index);
 for (unsigned i=0;i<2;++i) {
  if (grids[i]) ((Rva0056C4D3*)grids[i])->rva0056C4D3(victim,weight,victimPlayer->index,killerPlayer->index);
 }
}
void VictorySystemGridUpdateView::rva00405258() {
 if (!root.rva00404CF5(false)) return;
 unsigned int invalid=0x7fffffff;
 unsigned int best=invalid;
 unsigned counts[2];
 CellGrid **grid=grids;
 for (unsigned i=0;i<2;++i,++grid) {
  counts[i]=(*grid)->rva0056C16D();
  if (counts[i] && (best==invalid || counts[i]>counts[best])) best=i;
 }
 if (best==invalid) return;
 unsigned *values=grids[best]->values;
 for (unsigned cell=0;cell<grids[best]->count;++cell,++values) {
  if (*values) {
   Vec3 position;
   ((Rva0056C0F0*)grids[best])->rva0056C0F0(cell,&position);
   for (unsigned player=0;player<20;++player) {
    if (*values & (1U<<player)) ((Rva004051BC*)this)->rva004051BC(player,(const Coord3D*)&position);
   }
  }
 }
}
