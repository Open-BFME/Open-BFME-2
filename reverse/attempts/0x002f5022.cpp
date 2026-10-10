// ?rva002F5022@Pathfinder@@QAEXABUICoord2D@@0PAVPathfindCell@@1GPAGAAHH3@Z
// partial score=0.8217747378020976 date=2026-10-10
// ?rva002F5022@Pathfinder@@QAEXABUICoord2D@@0PAVPathfindCell@@1GPAGAAHH3@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native2F5022..2F52A7 RET36; BF1 pinned575 PathfinderProcessHierarchicalCell.cpp
// and ZH AIPathfind.cpp7346 give purpose/semantic structure only. Native
// independently proves extent14..20, closed-list34, zone manager460,16B cells,
// neighbor zone test and two CalcCostToHierGoal calls. Original spelling unknown.
typedef unsigned short Zone;
struct ICoord2D { int x,y; };
struct IRegion2D { ICoord2D lo,hi; };
struct In002E6BA1 {int x,y;};
class MixFileInfoBuffer {
public:
 char pad0[0xC];int previous;
 unsigned short totalCost,costSoFar;
 char pad14[0x2C-0x14];unsigned flags;
};
extern int TheMixFileInfoPool;
void Rva0052DBCDInit();
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer**,int,In002E6BA1*);
class Rva002E6AF3 {public:int get()const;};
class Rva002E6B06 {public:int rva002E6B06();};
class Rva003F69C0Object {public:void set(int*,int);};
class PathfindCell {
public:
 bool getOpen()const{return (unsigned char)((const Rva002E6AF3*)this)->get()!=0;}
 bool getClosed(){return (unsigned char)((Rva002E6B06*)this)->rva002E6B06()!=0;}
 bool getPinched()const{return ((flags>>16)&1)!=0;}
 bool getBit23()const{return ((flags>>23)&1)!=0;}
 __forceinline void allocateInfo(const ICoord2D &coord) {
  if(!info){if(!TheMixFileInfoPool)Rva0052DBCDInit();info=Rva002E8B7AInit((MixFileInfoBuffer**)&TheMixFileInfoPool,(int)this,(In002E6BA1*)&coord);}
  else info->previous=0;
 }
 void PutOnClosedList(MixFileInfoBuffer**);
 int CalcCostToHierGoal(PathfindCell*);
 void setParent(PathfindCell *p){((Rva003F69C0Object*)this)->set((int*)p,0);}
 MixFileInfoBuffer *info;char pad4[8];unsigned flags;
};
struct Rva00532041Record;
class Rva002E99F9Sub460 {
public:unsigned short rva00532041(int,int,int,Rva00532041Record**);
 bool rva005318DB(void*,void*,void*);
};
enum PathfindLayerEnum {PATHFIND_LAYER_OBSERVED_1=1};
class Pathfinder {
public:
 PathfindCell *getCell(PathfindLayerEnum,int,int);
 void AddToOpenList(PathfindCell*);
 void rva002F5022(const ICoord2D&,const ICoord2D&,PathfindCell*,PathfindCell*,Zone,Zone*,int&,int,int&);
 char pad0[0x10];PathfindCell **map;IRegion2D extent;
 char pad24[0x34-0x24];MixFileInfoBuffer *closed;
 char pad38[0x460-0x38];Rva002E99F9Sub460 zoneManager;
};
void Pathfinder::rva002F5022(const ICoord2D &scan,const ICoord2D &delta,PathfindCell *parent,PathfindCell *goal,Zone parentZone,Zone *examined,int &examinedCount,int profile,int &cellCount)
{
 if(scan.x<extent.lo.x || scan.x>extent.hi.x || scan.y<extent.lo.y || scan.y>extent.hi.y)return;
 if(parentZone==zoneManager.rva00532041(profile,scan.x,scan.y,(Rva00532041Record**)map)) {
  PathfindCell *first=getCell(PATHFIND_LAYER_OBSERVED_1,scan.x,scan.y);
  if(first->getOpen() || first->getClosed())return;
  ICoord2D adjacent=scan;adjacent.x+=delta.x;adjacent.y+=delta.y;
  if(adjacent.x<extent.lo.x || adjacent.x>extent.hi.x || adjacent.y<extent.lo.y || adjacent.y>extent.hi.y)return;
  PathfindCell *next=getCell(PATHFIND_LAYER_OBSERVED_1,adjacent.x,adjacent.y);
  if(next->getOpen() || next->getClosed())return;
  Zone nextZone=zoneManager.rva00532041(profile,adjacent.x,adjacent.y,(Rva00532041Record**)map);
  int count=examinedCount;for(int j=0;j<count;++j) {
   if(examined[j]==nextZone){next->allocateInfo(adjacent);next->PutOnClosedList(&closed);return;}
  }
  if(!zoneManager.rva005318DB((void*)profile,first,next))return;
  first->allocateInfo(scan);
  if(!first->getClosed() && !first->getOpen())first->PutOnClosedList(&closed);
  next->allocateInfo(adjacent);++cellCount;
  int currentCost=next->CalcCostToHierGoal(parent);
  int remainingCost=next->CalcCostToHierGoal(goal);
  if(next->getPinched() || first->getPinched() || next->getBit23() || first->getBit23())currentCost+=20;
  else {examined[examinedCount]=nextZone;++examinedCount;}
  next->info->costSoFar=parent->info->costSoFar+currentCost;
  next->info->totalCost=next->info->costSoFar+remainingCost;
  next->setParent(parent);AddToOpenList(next);
 }
}
