// ?MoveAllies@Pathfinder@@QAE_NPAVObject@@PAVPath@@_N@Z
// partial score=0.8785282557717079 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native 002F3C09..002F3F7D RET12; WorldBuilder D47470 MoveAllies.
// ZH AIPathfind.cpp moveAllies supplies semantic guide only; native traversal samples each segment and handles harvester/horde branches.
typedef int Int;typedef bool Bool;typedef unsigned int UnsignedInt;
enum ObjectID{INVALID_ID=0};enum KindOfType{MoveKind154=154};enum ObjectStatusTypes{MoveStatus90=90};enum Relationship{ENEMIES,NEUTRAL,ALLIES};enum PathfindLayerEnum{GroundLayer=1};enum CommandSourceType{CMD_FROM_AI=2};
struct Coord3D{float x,y,z;};struct ICoord2D{int x,y;};
struct ThingTemplate{char pad[0x108];union{unsigned kinds[8];unsigned char kindBytes[32];};__forceinline Bool hasKind(unsigned bit)const{return (kindBytes[bit>>3]&(1<<(bit&7)))!=0;} __forceinline unsigned wordKind(unsigned bit)const{return kinds[bit>>5]&(1U<<(bit&31));}};
class AIUpdateInterface;
class Object{public:Relationship getRelationship(const Object *)const;Bool isKindOf(KindOfType)const;Bool testStatus(ObjectStatusTypes)const;Bool rva002931BA();void *vtable;ThingTemplate *m_template;char pad8[0x74-8];ObjectID id,relatedID;char pad7c[0x258-0x7c];AIUpdateInterface *ai;};
class AICommandInterface{public:void rva0026C411(Object *,const Coord3D *,CommandSourceType);};
class AIUpdateInterface{public:ObjectID getIgnoredObstacleID()const;Bool isMoving()const;
 virtual void unusedSlot0();
 virtual void unusedSlot1();
 virtual void unusedSlot2();
 virtual void unusedSlot3();
 virtual void unusedSlot4();
 virtual void unusedSlot5();
 virtual void unusedSlot6();
 virtual void unusedSlot7();
 virtual void unusedSlot8();
 virtual void unusedSlot9();
 virtual void unusedSlot10();
 virtual void unusedSlot11();
 virtual void unusedSlot12();
 virtual void unusedSlot13();
 virtual void unusedSlot14();
 virtual void unusedSlot15();
 virtual void unusedSlot16();
 virtual void unusedSlot17();
 virtual void unusedSlot18();
 virtual void unusedSlot19();
 virtual void unusedSlot20();
 virtual void unusedSlot21();
 virtual void unusedSlot22();
 virtual void unusedSlot23();
 virtual void unusedSlot24();
 virtual void unusedSlot25();
 virtual void unusedSlot26();
 virtual void unusedSlot27();
 virtual void unusedSlot28();
 virtual void unusedSlot29();
 virtual void unusedSlot30();
 virtual void unusedSlot31();
 virtual void unusedSlot32();
 virtual void unusedSlot33();
 virtual void unusedSlot34();
 virtual void unusedSlot35();
 virtual void unusedSlot36();
 virtual void unusedSlot37();
 virtual void unusedSlot38();
 virtual void unusedSlot39();
 virtual void unusedSlot40();
 virtual void unusedSlot41();
 virtual void unusedSlot42();
 virtual void unusedSlot43();
 virtual void unusedSlot44();
 virtual void unusedSlot45();
 virtual void unusedSlot46();
 virtual void unusedSlot47();
 virtual void unusedSlot48();
 virtual void unusedSlot49();
 virtual void unusedSlot50();
 virtual void unusedSlot51();
 virtual void unusedSlot52();
 virtual void unusedSlot53();
 virtual void unusedSlot54();
 virtual void unusedSlot55();
 virtual void unusedSlot56();
 virtual void unusedSlot57();
 virtual void unusedSlot58();
 virtual void unusedSlot59();
 virtual void unusedSlot60();
 virtual void unusedSlot61();
 virtual void unusedSlot62();
 virtual void unusedSlot63();
 virtual void unusedSlot64();
 virtual void unusedSlot65();
 virtual void unusedSlot66();
 virtual void unusedSlot67();
 virtual void unusedSlot68();
 virtual void unusedSlot69();
 virtual void unusedSlot70();
 virtual void unusedSlot71();
 virtual void unusedSlot72();
 virtual void unusedSlot73();
 virtual void unusedSlot74();
 virtual void unusedSlot75();
 virtual void unusedSlot76();
 virtual void unusedSlot77();
 virtual void unusedSlot78();
 virtual void unusedSlot79();
 virtual void unusedSlot80();
 virtual void unusedSlot81();
 virtual void unusedSlot82();
 virtual void unusedSlot83();
 virtual void unusedSlot84();
 virtual void unusedSlot85();
 virtual void unusedSlot86();
 virtual void unusedSlot87();
 virtual void unusedSlot88();
 virtual void unusedSlot89();
 virtual void unusedSlot90();
 virtual void unusedSlot91();
 virtual void unusedSlot92();
 virtual void unusedSlot93();
 virtual void unusedSlot94();
 virtual void unusedSlot95();
 virtual void unusedSlot96();
 virtual void unusedSlot97();
 virtual void unusedSlot98();
 virtual void unusedSlot99();
 virtual void unusedSlot100();
 virtual void unusedSlot101();
 virtual void unusedSlot102();
 virtual void unusedSlot103();
 virtual void unusedSlot104();
 virtual void unusedSlot105();
 virtual void unusedSlot106();
 virtual void unusedSlot107();
 virtual void unusedSlot108();
 virtual void unusedSlot109();
 virtual Bool moveAlliesSlot1B8();
 virtual Bool moveAlliesSlot1BC();
};
struct PathNode{PathNode *next,*previous,*nextOptimized;Coord3D position;PathfindLayerEnum layer;};
class Path{public:int references;PathNode *first,*last;char wordC;Bool blockedByAlly;__forceinline void lock(){references++;}__forceinline void unlock(){if(references)references--;}};
struct CellNode{CellNode *next;void *word4;Object *object;};struct CellInfo{char pad[0x20];CellNode *objects;};class PathfindCell{public:CellInfo *info;};
int __cdecl Rva002E9B31Get(void *);
__declspec(noinline) void __cdecl Rva002EBCD6Split(void *p, int *outHalf, int *outRest)
{
	int v = Rva002E9B31Get(p);
	int h = v / 2;
	*outHalf = h;
	*outRest = v - h;
}
ICoord2D *Rva002E7875WorldToCell(ICoord2D *,Bool,const Coord3D *);
extern "C" int __cdecl abs(int);
template<class T>class LatchRestore{protected:T valueToRestore;T &whereToRestore;public:LatchRestore(T &dest,const T &src):whereToRestore(dest){valueToRestore=dest;dest=src;}virtual ~LatchRestore(){whereToRestore=valueToRestore;}};
class Pathfinder{public:PathfindCell *getCell(PathfindLayerEnum,Int,Int);Bool MoveAllies(Object *,Path *,Bool);char pad[0x1c1bc];Int moveAlliesDepth;};
Bool Pathfinder::MoveAllies(Object *obj,Path *path,Bool force)
{
 ThingTemplate *initialTemplate=obj->m_template;
 Bool harvester=(initialTemplate->kinds[3]>>29)&1;
 if(!initialTemplate->hasKind(0xe) && !initialTemplate->hasKind(0x10) && !harvester && !path->blockedByAlly)return false;
 if(initialTemplate->hasKind(0xbb))return false;
 Int &depth=moveAlliesDepth;LatchRestore<Int> recursiveDepth(depth,depth+1);
 if(moveAlliesDepth>1)return false;
 Int radius,numCellsAbove;Rva002EBCD6Split(obj,&radius,&numCellsAbove);
 ObjectID ignoreId=INVALID_ID;
 if(obj->ai)ignoreId=obj->ai->getIgnoredObstacleID();
 Object *volatile *objectSlot=&obj;
path->lock();Coord3D initialPosition;initialPosition.x=path->last->position.x;initialPosition.y=path->last->position.y;initialPosition.z=path->last->position.z;
 for(PathNode *node=path->last;node && node!=path->first && node->previous;node=node->previous){
  ICoord2D curCell,nextCell;Rva002E7875WorldToCell(&curCell,true,&node->position);Rva002E7875WorldToCell(&nextCell,true,&node->previous->position);
  Int dx=nextCell.x-curCell.x;Int xSize=abs(dx);Int dy=nextCell.y-curCell.y;Int ySize=abs(dy);Int numSteps=xSize>ySize?xSize:ySize;
  for(Int step=0;step<numSteps;step++){
   Int x=dx*step/numSteps+curCell.x,y=dy*step/numSteps+curCell.y;
   for(Int i=x-radius;i<x+numCellsAbove;i++){
    for(Int j=y-radius;j<y+numCellsAbove;j++){
     PathfindCell *cell=getCell(node->layer,i,j);
     if(cell&&cell->info){
      for(CellNode *unitNode=cell->info->objects;unitNode;unitNode=unitNode->next){
       Object *other=unitNode->object;
       if(other==*objectSlot || other->id==ignoreId)continue;
       if((*objectSlot)->m_template->wordKind(0x74)&&other->m_template->wordKind(0x74))continue;
       if(other->m_template->hasKind(0xb6))continue;
       if(other->m_template->wordKind(0x6d)&&other->id==(*objectSlot)->relatedID)continue;
       if(other->isKindOf(MoveKind154)||(*objectSlot)->getRelationship(other)!=ALLIES)continue;
       if((*objectSlot)->m_template->wordKind(0x6d) && (other->m_template->wordKind(0x6d)||other->rva002931BA()))continue;
       if(harvester&&!other->m_template->hasKind(0x7d)){
        if((other->ai->moveAlliesSlot1BC()||other->ai->isMoving())&&!force)continue;
       }else{
        if(!other->ai||other->ai->isMoving()||(!other->ai->moveAlliesSlot1B8()&&!force))continue;
       }
       if(other->testStatus(MoveStatus90))continue;
       ((AICommandInterface *)((char *)other->ai+0x20))->rva0026C411(*objectSlot,&initialPosition,CMD_FROM_AI);
       break;
      }
     }
    }
   }
  }
 }
 path->unlock();return true;
}
