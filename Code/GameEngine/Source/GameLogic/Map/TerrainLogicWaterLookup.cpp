// cl: /O1 /G7 /Oy- /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Native28170E..2817F2 RET12 selects the first registered area with strictly
// greater height than the running lower bound and containing (x,y). Target
// establishes collection50, eight-byte records+14/+18 and secondary shape
// vbtable18/+4. WB C4A850 independently confirms iteration and height role.
// ZH TerrainLogic.cpp getWaterHandle is a semantic guide; its polygon linked
// list and gridded-water fallback differ, so original target name is unresolved.
// The rowed29B STLport equality provider at7E394 compares two words only; the
// iterator cast is its existing ABI spelling, not a claim that these target
// iterators are source-level STL pairs. All offsets and slots are target facts.
#include <utility>
#include <vector>
#include "../../../../Libraries/Include/Lib/Coord2D.h"
struct Rva0007E394Element {unsigned opaque;bool operator<(const Rva0007E394Element&)const;bool operator==(const Rva0007E394Element&)const;};
struct Rva0028170EIterator {void *set;int index;Rva0028170EIterator(void *p,int i):set(p),index(i){} };
bool Rva0030D111Contains(class Rva0030D111Shape*,const Coord2D*);
class Rva0030D111Shape {public:virtual int count();virtual void point();virtual int height();};
struct Rva0028170EArea {
 char pad00[0x18];int *baseOffsets;
 Rva0030D111Shape *shape(){return reinterpret_cast<Rva0030D111Shape*>(reinterpret_cast<char*>(this)+0x18+baseOffsets[1]);}
};
struct Rva0028170EEntry {unsigned key;Rva0028170EArea *area;};
struct Rva0028170ESet {char pad00[0x14];_STL::vector<Rva0028170EEntry> entries; Rva0028170EIterator begin(){return Rva0028170EIterator(this,0);} Rva0028170EIterator end(){return Rva0028170EIterator(this,entries.size());} };
class Rva0028170EHost {char pad00[0x50];Rva0028170ESet *areas;public:Rva0028170EArea *rva0028170E(float x,float y,float minHeight);};
typedef _STL::pair<const unsigned,Rva0007E394Element*> BfmeEqualityWords;
static __forceinline bool EqualIterators(const Rva0028170EIterator &a,const Rva0028170EIterator &b) {
 return *reinterpret_cast<const BfmeEqualityWords*>(&a)==*reinterpret_cast<const BfmeEqualityWords*>(&b);
}
Rva0028170EArea *Rva0028170EHost::rva0028170E(float x,float y,float minHeight) {
 Rva0028170EArea *chosen=0;
 float height=minHeight;
 Rva0028170EIterator current=areas->begin();
 for(;!EqualIterators(current,areas->end());++current.index) {
  Rva0028170EArea *area=reinterpret_cast<Rva0028170ESet*>(current.set)->entries[current.index].area;
  float h=(float)area->shape()->height();
  if(h>height){
   Rva0030D111Shape *shape=area->shape();
   Coord2D point;point.x=x;point.y=y;
   if(Rva0030D111Contains(shape,&point)){height=h;chosen=area;}
  }
 }
 return chosen;
}
