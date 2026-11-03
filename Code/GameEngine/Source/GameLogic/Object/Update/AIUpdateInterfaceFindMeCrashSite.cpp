// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /ICode/GameEngine/Source /ICode/Libraries/Include
//
// ?findMeACrashSite@AIUpdateInterface@@QAE_NMPBUCoord3D@@PAU2@VBfmeFixedStorage0004543D@@@Z
// retail 0x0026B088 (466B). Names/semantics: WorldBuilder AIUpdateInterface::findMeACrashSite
// (ring search around startPos for a spot clear of other objects, spacing = max(10, radius)).
// Evidence classes: native algorithm and layouts are target-derived; the helper and
// view names (Rva0004584D filter, HitRange payload) are descriptive views, not original names.
//
// Codegen: the spacing helper reads its second reference parameter into a named
// temporary and returns the parameter itself on the false arm ('float t=b; return
// a>t?a:b'). cl then keeps the radius in XMM1 (one load, register compare
// 'comiss xmm0,xmm1; ja') like retail instead of folding the load into the compare.
#include "Common/PartitionRangeQueryCallView.h"
#include "Lib/Coord3D.h"
float Sin(float);
float Cos(float);
#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
class Rva000421C8 { public: virtual ~Rva000421C8() {} virtual bool allow(Object*)=0; virtual int getPlayerMask() {return -1;} Rva000421C8 *next; };
class Rva0004584D: public Rva000421C8 { public: Rva0004584D(const BfmeFixedStorage0004543D &, const BfmeFixedStorage0004543D &); virtual ~Rva0004584D() {} virtual bool allow(Object*); BfmeFixedStorage0004543D accepted,rejected; };
extern PartitionManager *ThePartitionManager;
class Object {public: char pad[0x38];Coord3D position;char beforeRadius[0xbc-0x44];float radius;
 __forceinline float Get2DCenterDistanceSquared(const Coord3D *pos) const {float dx=position.x-pos->x,dy=position.y-pos->y;return dx*dx+dy*dy;}
};
struct HitRange {void *begin,*end;char opaque[4];void *cursor;};
static __forceinline float crashSpacing(const float &minimum,const float &b) { float t=b; return minimum>t?minimum:b; }
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
bool AIUpdateInterface::findMeACrashSite(float maxRange,const Coord3D *startPos,Coord3D *output,BfmeFixedStorage0004543D mask) {
 Object *self=m_object;if(!self)return false;
 float spacing=crashSpacing(10.0f,self->radius);
 BfmeWideResult hits=ThePartitionManager->iterateObjectsInRange(startPos,maxRange,0,&Rva0004584D(mask,*reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE)),1);
 for(float range=spacing;range<=maxRange;range+=spacing) {
  float numPoints=(6.2831855f*range)/spacing;
  float step=6.2831855f/numPoints;
  for(float angle=-3.1415927f;angle<=3.1415927f;angle+=step) {
   Coord3D candidate;candidate.x=startPos->x;candidate.y=startPos->y;candidate.z=startPos->z;
   candidate.x+=Sin(angle)*range;
   candidate.y+=Cos(angle)*range;
   bool clear=true;
   HitRange *payload=static_cast<HitRange*>(hits.m_value);payload->cursor=payload->begin;
   for(Object *ob=hits.next();ob;ob=hits.next()) {
    float size=ob->radius+spacing;
    float limit=size*size;
    if(ob->Get2DCenterDistanceSquared(&candidate)<limit){clear=false;break;}
   }
   if(clear){*output=candidate;return true;}
  }
 }
 return false;
}
