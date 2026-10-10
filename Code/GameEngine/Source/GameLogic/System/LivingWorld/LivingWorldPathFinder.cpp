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
enum ObjectID { INVALID_ID=0 };
struct Rva003EF6A0Entry {int key;char pad04[24];float f1c,f20,f24;Rva003EF6A0Entry *prev;};
struct Rva003EF6A0Span;struct Rva003EF9DCNode;struct Rva003EF634Node;
class Rva003C5890Item;
class LivingWorldSearchCallback {public:virtual void slot00();virtual void slot04();virtual void slot08(Rva003EF6A0Entry*);virtual bool slot0c(Rva003EF6A0Entry*,Rva003EF6A0Entry*);};
class BfmeVecAG {public:void bfmeErase(int*);};
class Rva003EF8E1{public:
 void Rva003EF9DCFill(Rva003EF9DCNode*,_STL::vector<ObjectID>*);
 int Rva003EF634Count(Rva003EF634Node*);
 int FindShortestPath(LivingWorldSearchCallback*,int,int,int,_STL::vector<ObjectID>*,bool);
 bool Pathfind(LivingWorldSearchCallback*,int,_STL::vector<ObjectID>*,int*,bool);
 Rva003EF6A0Entry *rva003EF6A0(Rva003EF6A0Span *,int);
 void rva003EF8E1(Rva003EF5FBNode*,int,bool);
 bool contains(Rva003EF6D6Span*,Rva003EF6D6Entry*);
 void remove(Rva003C4CF0Span*,int);
 void insertSorted(_STL::vector<Rva002C589B*>*,Rva002C589B*);
 char padding[12];Rva003EF5FBNode *start,*goal;
 _STL::vector<Rva003C5890Item*> open,closed;
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
 _STL::vector<Rva003EF5FBNode*> &openRef=*(_STL::vector<Rva003EF5FBNode*>*)&open;
 ((BfmeSlotVecG*)&openRef)->bfmeErase((void**)openRef.begin(),(void**)openRef.end());
 BfmeSlotVecG *closedVec=(BfmeSlotVecG*)&closed;
 closedVec->bfmeErase((void**)closedVec->begin,(void**)closedVec->end);
 rva003EF8E1(start,-1,true);
 out->reserve(openRef.size());
 for(_STL::vector<Rva003EF5FBNode*>::iterator it=openRef.begin();it!=(_STL::vector<Rva003EF5FBNode*>::iterator)open.end();++it){
  ScienceType id=(ScienceType)(*it)->key;
  out->push_back(id);
 }
}

// WB01039460 named FindShortestPath and native003EFA0A complete292 RET24.
// Callback vslots08/0C notify and goal-test extend donor575ba2b0's open/closed
// semantic guide; output ObjectID spelling is an owned four-byte ABI carrier.
// Retail hoists this ECX before either goal-result arm: Fill46 and Count20
// therefore use this owner as well as Relax251; their unused receiver leaves
// the separately verified provider bytes unchanged.
// ?FindShortestPath@Rva003EF8E1@@QAEHPAVLivingWorldSearchCallback@@HHHPAV?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@_N@Z
int Rva003EF8E1::FindShortestPath(LivingWorldSearchCallback *cb,int opaque,int from,int to,_STL::vector<ObjectID> *out,bool flags) {
 metric=(Rva003F71D4Metric*)cb;
 if(from==to) { if(out) { out->clear(); out->push_back((ObjectID &)from); } return 0; }
 BfmeSlotVecG *openSpan=(BfmeSlotVecG*)&open;
 openSpan->bfmeErase(openSpan->begin,(void**)openSpan->end);
 BfmeSlotVecG *closedSpan=(BfmeSlotVecG*)&closed;
 closedSpan->bfmeErase(closedSpan->begin,(void**)closedSpan->end);
 if(out) out->clear();
 Rva003EF6A0Entry *first=rva003EF6A0((Rva003EF6A0Span *)this,from);
 start=(Rva003EF5FBNode*)first;
 goal=(Rva003EF5FBNode*)rva003EF6A0((Rva003EF6A0Span *)this,to);
 if(first && goal) {
  first->f1c=0.0f;first->f20=0.0f;first->f24=0.0f;
  start->previous28=0;
  open.push_back((Rva003C5890Item *const &)start);
  while(open.size()) {
   Rva003EF6A0Entry *current=(Rva003EF6A0Entry *)open[0];
   ((BfmeVecAG *)&open)->bfmeErase((int *)open.begin());
   ((LivingWorldSearchCallback*)metric)->slot08(current);
   if(((LivingWorldSearchCallback*)metric)->slot0c(current,(Rva003EF6A0Entry*)goal)) {
    if(out) { Rva003EF9DCFill((Rva003EF9DCNode *)current,out); return out->size()-1; }
    return Rva003EF634Count((Rva003EF634Node *)current);
   }
   rva003EF8E1((Rva003EF5FBNode*)current,opaque,flags);
   closed.push_back((Rva003C5890Item *const &)current);
  }
 }
 return -1;
}


// WB010397E0 named Pathfind and native003EFB2E complete238 RET20.
// Same queues and callbacks as292 but Boolean result plus optional path length.
// The void-pointer clear provider for closed retains native LEA-first scheduling
// without keeping a second span pointer across the search loop.
// ?Pathfind@Rva003EF8E1@@QAE_NPAVLivingWorldSearchCallback@@HPAV?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@PAH_N@Z
bool Rva003EF8E1::Pathfind(LivingWorldSearchCallback *cb,int from,_STL::vector<ObjectID> *out,int *length,bool flags) {
 metric=(Rva003F71D4Metric*)cb;
 BfmeSlotVecG *openSpan=(BfmeSlotVecG*)&open;
 openSpan->bfmeErase(openSpan->begin,(void**)openSpan->end);
 ((_STL::vector<void*>*)&closed)->clear();
 if(out) out->clear();
 Rva003EF6A0Entry *first=rva003EF6A0((Rva003EF6A0Span *)this,from);
 start=(Rva003EF5FBNode*)first;
 if(!first) return false;
 first->f1c=0.0f;first->f20=0.0f;first->f24=0.0f;
 start->previous28=0;
 open.push_back((Rva003C5890Item *const &)start);
 while(open.size()) {
  Rva003EF6A0Entry *current=(Rva003EF6A0Entry *)open[0];
  ((BfmeVecAG *)&open)->bfmeErase((int *)open.begin());
  ((LivingWorldSearchCallback*)metric)->slot08(current);
  if(((LivingWorldSearchCallback*)metric)->slot0c(current,(Rva003EF6A0Entry*)goal)) {
   if(out) { Rva003EF9DCFill((Rva003EF9DCNode *)current,out); *length=out->size()-1; }
   else *length=Rva003EF634Count((Rva003EF634Node *)current);
   return true;
  }
  rva003EF8E1((Rva003EF5FBNode*)current,-1,flags);
  closed.push_back((Rva003C5890Item *const &)current);
 }
 return false;
}

// Native003F7198..003F71D4 complete60 RET4; WB01058340 confirms the
// region-key lookup through logic+B0, friend predicate on callback+4, and
// storing a successful region at+8. Original callback/class names unproven.
// Native table008370C4 has four slots:003F7257,004FF363,003F7198,003F718D.
// The constant and goal slots compile whole byte-and-relocation twins of
// their existing owners; the table and local field views are target evidence.
// The base prefix arranges zeroing region before the derived vptr; this
// models native constructor order without asserting original inheritance.
struct Rva003F7198Node {int key;};
class Rva0020E89C {public:char pad[0x13c];int owner;};
class Rva0020EAF6View {public:Rva0020E89C *rva0020EAF6(int);};
struct Rva003F7198LogicPrefix {char pad[0xb0];Rva0020EAF6View *regions;};
class __declspec(novtable) Rva003F7177Base {
public:
 Rva003F7177Base():region(0){}
 virtual float distance(int,int)=0;
 virtual float cost(int,int)=0;
 virtual void visit(Rva003F7198Node*)=0;
 virtual bool found(int,int)=0;
 Rva002E071E *player;
 void *region;
};
class Rva003F7177Callback:public Rva003F7177Base {
public:
 Rva003F7177Callback(Rva002E071E*);
 virtual float distance(int,int);
 virtual float cost(int,int);
 virtual void visit(Rva003F7198Node*);
 virtual bool found(int,int);
};

float Rva003F7177Callback::distance(int,int){return 0.0f;}
float Rva003F7177Callback::cost(int,int){return 1.0f;}
bool Rva003F7177Callback::found(int,int){return region!=0;}
void Rva003F7177Callback::visit(Rva003F7198Node *node){
 int key=node->key;
 Rva0020EAF6View *regions=((Rva003F7198LogicPrefix*)TheLivingWorldLogic)->regions;
 Rva0020E89C *r=regions->rva0020EAF6(key);
 if(r && (unsigned char)player->rva002E0BC0(r->owner))region=r;
}
