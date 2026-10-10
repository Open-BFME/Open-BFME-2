// cl: /O1 /G7 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native003F71D4..003F7209 RET8; vtable007E4340 slots00/04
// both reach this body. Entry points supply node coordinates at10/14;
// native loads the pair before subtracting the second node and calls the
// independently rowed Coord2D::length. Original metric/slot names unproven.
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
struct Rva003F71D4Point {char pad[16];float x,y;};
class Rva003F71D4Metric {
 public:
 virtual float v00(const Rva003F71D4Point *,const Rva003F71D4Point *);
 virtual float v01(const Rva003F71D4Point *,const Rva003F71D4Point *);
 virtual void v02(const Rva003F71D4Point *);
 virtual bool v03(int,int);
};
float Rva003F71D4Metric::v00(const Rva003F71D4Point *a,const Rva003F71D4Point *b) {
 Coord2D d={a->x,a->y};
 d.x-=b->x;
 d.y-=b->y;
 return d.length();
}

// Native table007E4340: slot04 repeats the distance; slot08 is RET4;
// slot0C compares the two node pointers, the independently rowed14B body.
float Rva003F71D4Metric::v01(const Rva003F71D4Point *a,const Rva003F71D4Point *b) {
 Coord2D d={a->x,a->y}; d.x-=b->x; d.y-=b->y; return d.length();
}
void Rva003F71D4Metric::v02(const Rva003F71D4Point *) {}
bool Rva003F71D4Metric::v03(int a,int b) {return a==b ? true : false;}

// Native003EF5FB complete57B RET4 checks node+2C then owner+18.
// Native003EF8E1 calls it with the child in ECX; nested Logic::find RET8
// leaves the outer relation argument on the stack. Returned AL is preserved.
#include <vector>
class LivingWorldLogic;extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002E2903Player;
class Rva002BA8F1Logic{public:Rva002E2903Player *find(int,unsigned*);};
class Rva002E071E{public:int rva002E0BC0(int);};
struct Rva003EF5FBNode {int key;_STL::vector<Rva003EF5FBNode*> adjacent;float x,y;int owner18;float cost1c,estimate20,total24;Rva003EF5FBNode *previous28;bool allowed2c;
 unsigned char rva003EF5FB(int);
};
unsigned char Rva003EF5FBNode::rva003EF5FB(int owner){
 if(!allowed2c)return 0;
 if(owner18==-1 || owner==-1)return 1;
 return (unsigned char)((Rva002E071E*)((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(owner18,0))->rva002E0BC0(owner);
}


// Native003EF8E1 complete251 RET12: receiver12/16 start/goal, vectors20/32,
// callback44; node predecessor40 and costs28/32/36 proven by retail.
// BFME1 donor575ba2b0 LivingWorldPathFinder.cpp guides open/closed semantics;
// target adds permission57 and callback distance slots0/4. Names remain neutral.
// Capture node cost before callback (which can mutate it) and hold an adjacency
// vector reference across iteration; both native scheduling facts are byte-proven.
struct Rva003EF6D6Entry;struct Rva003EF6D6Span;struct Rva003C4CF0Span;class Rva002C589B;
struct Rva003EF6A0Entry;struct Rva003EF6A0Span;
class Rva003EF8E1{public:
 Rva003EF6A0Entry *rva003EF6A0(Rva003EF6A0Span *,int);
 void rva003EF8E1(Rva003EF5FBNode*,int,bool);
 bool contains(Rva003EF6D6Span*,Rva003EF6D6Entry*);
 void remove(Rva003C4CF0Span*,int);
 void insertSorted(_STL::vector<Rva002C589B*>*,Rva002C589B*);
 char padding[12];Rva003EF5FBNode *start,*goal;
 _STL::vector<Rva003EF5FBNode*> open,closed;
 Rva003F71D4Metric *metric;
};
// ?rva003EF8E1@Rva003EF8E1@@QAEXPAURva003EF5FBNode@@H_N@Z
void Rva003EF8E1::rva003EF8E1(Rva003EF5FBNode *node,int owner,bool allowOther){
 _STL::vector<Rva003EF5FBNode*> &adjacent=node->adjacent;
 for(unsigned i=0;i<adjacent.size();++i){
  Rva003EF5FBNode *next=adjacent[i];
  if(next!=goal){
   if(!next->allowed2c)continue;
   if(!next->rva003EF5FB(owner) && !allowOther)continue;
  }
  if(next==node->previous28)continue;
  float baseCost=node->cost1c;
  float cost=baseCost+metric->v01((const Rva003F71D4Point*)node,(const Rva003F71D4Point*)next);
  if((contains((Rva003EF6D6Span*)&open,(Rva003EF6D6Entry*)next)||contains((Rva003EF6D6Span*)&closed,(Rva003EF6D6Entry*)next))&&cost>=next->cost1c)continue;
  remove((Rva003C4CF0Span*)&open,(int)next);remove((Rva003C4CF0Span*)&closed,(int)next);
  next->previous28=node;next->cost1c=cost;
  next->estimate20=metric->v00((const Rva003F71D4Point*)next,(const Rva003F71D4Point*)goal);
  next->total24=next->cost1c+next->estimate20;
  insertSorted((_STL::vector<Rva002C589B*>*)&open,(Rva002C589B*)next);
 }
}

// Native003EFC1C complete136 RET8 clears output then emits keys of adjacent
// reachable nodes after the same251 relaxation. WB01039AE0 proves this order.
// ScienceType names an existing four-byte vector ABI provider (reserve110,
// erase32 and push49), not the original target ID typedef. Host inheritance
// shares our verified prefix view; original source inheritance is unasserted.
enum ScienceType { SCIENCE_NONE=0 };
class BfmeSlotVecG { public: void bfmeErase(void **,void **); void **begin,*end,*limit; };
class Rva003EFC1CHost:public Rva003EF8E1 { public: void rva003EFC1C(int,void*); };
// ?rva003EFC1C@Rva003EFC1CHost@@QAEXHPAX@Z
void Rva003EFC1CHost::rva003EFC1C(int from,void *output) {
 _STL::vector<ScienceType> *out=(_STL::vector<ScienceType>*)output;
 out->clear();
 start=(Rva003EF5FBNode*)rva003EF6A0((Rva003EF6A0Span*)this,from);
 goal=0;
 _STL::vector<Rva003EF5FBNode*> &openRef=open;
 ((BfmeSlotVecG*)&openRef)->bfmeErase((void**)openRef.begin(),(void**)openRef.end());
 BfmeSlotVecG *closedVec=(BfmeSlotVecG*)&closed;
 closedVec->bfmeErase((void**)closedVec->begin,(void**)closedVec->end);
 rva003EF8E1(start,-1,true);
 out->reserve(openRef.size());
 for(_STL::vector<Rva003EF5FBNode*>::iterator it=openRef.begin();it!=open.end();++it){
  ScienceType id=(ScienceType)(*it)->key;
  out->push_back(id);
 }
}
