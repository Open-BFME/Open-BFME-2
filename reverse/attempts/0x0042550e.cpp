// ?optimizeUnits@Formation@@QAEXPBUCoord3D@@@Z
// partial score=0.96 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Formation::optimizeUnits, WB 0x0113B070 FormationAssistant.cpp:431.
// Retail 0x0042550E..0x004256D5, RET4. No BF1/ZH FormationAssistant donor
// is available. STLport is the reference for vector storage and algorithms;
// retail establishes the record stride, object-ID field, pairwise swap cost,
// iteration limit, and position helper ABI. Remaining fields are unnamed.
#include <vector>
#include <algorithm>

#include "../Code/Libraries/Include/Lib/Coord3D.h"
#include "../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Rva00422CA8 { public: bool operator()(int,int) const; };
void __cdecl rva004216A2(float *out,const float *base,const float *slot);
float __cdecl Rva004219F4DistSquared(const float *small,const float *object);
struct BfmeFormationSlot {
 int unknown00;
 ObjectID objectId;
 unsigned char unknown08[0x18];
};
class Formation {
 _STL::vector<BfmeFormationSlot> slots;
public:
 void optimizeUnits(const Coord3D *base);
};
void Formation::optimizeUnits(const Coord3D *base) {
 _STL::vector<long> order;
 order.reserve(slots.size());
 for(BfmeFormationSlot *slot=slots.begin();slot!=slots.end();++slot)
  order.push_back((long)slot);
 _STL::sort((int*)order.begin(),(int*)order.end(),Rva00422CA8());
 int limit=order.size()*order.size();
 long *first=order.begin();
 while(first!=order.end()) {
  long *last=(long*)_STL::upper_bound((int*)first,(int*)order.end(),*(int*)first,Rva00422CA8());
  for(long *current=first;current!=last;++current) {
   long *next=current+1;
   if(next==last)continue;
   BfmeFormationSlot *slot=(BfmeFormationSlot*)*current;
   Coord3D pos;
   rva004216A2(&pos.x,&base->x,(const float*)slot);
   Object *object=TheGameLogic->findObjectByID(slot->objectId);
   if(!object)continue;
   float original=Rva004219F4DistSquared(&pos.x,(const float*)object);
   while(next!=last) {
    BfmeFormationSlot *other=(BfmeFormationSlot*)*next;
    Coord3D otherPos;
    rva004216A2(&otherPos.x,&base->x,(const float*)other);
    ObjectID otherId=other->objectId;
    Object *otherObject=TheGameLogic->findObjectByID(otherId);
    if(otherObject) {
     float currentCost=original+Rva004219F4DistSquared(&otherPos.x,(const float*)otherObject);
     float crossCost=Rva004219F4DistSquared(&pos.x,(const float*)otherObject);
     if(currentCost > crossCost+Rva004219F4DistSquared(&otherPos.x,(const float*)object)) {
      if(--limit<0)return;
      ObjectID old=((BfmeFormationSlot*)*current)->objectId;
      ((BfmeFormationSlot*)*current)->objectId=otherId;
      ((BfmeFormationSlot*)*next)->objectId=old;
      object=otherObject;
      next=current;
      original=Rva004219F4DistSquared(&pos.x,(const float*)object);
     }
    }
    ++next;
   }
  }
  first=last;
 }
}
