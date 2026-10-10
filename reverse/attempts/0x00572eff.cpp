// ?findBestTarget@AITargetHeuristicTechBuilding@@QAEXPAVAITarget@@PAVPlayer@@1@Z
// partial score=0.8950408658383964 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/Libraries/Include
// stlport
#include "GameLogicObjectLookupView.h"
#include "PartitionRangeQueryCallView.h"
#include "Lib/Coord3D.h"
#include <stdlib.h>
namespace _STL{void __cdecl free(void*);}
#define free _STL::free
#include <vector>
#undef free
enum Relationship{ENEMIES=0,NEUTRAL=1,ALLIES=2};
class Player{public:Relationship getRelationship(const Object*)const;};
class Rva004EBF4B{public:Coord3D rva004EBF4B();};
struct TacticalAI{char pad[0x20];void *begin,*end;};
struct Rva002A8AB1Record:public Rva004EBF4B{char pad[0x164];TacticalAI *tactics;char pad168[4];int mode;};
class Rva002A8F24{public:Rva002A8AB1Record *rva002A8AB1(void*);char pad[0x884];float fallbackWeight;char pad888[0x934-0x888];_STL::vector<ObjectID> techBuildings;};
extern Rva002A8F24 *g_tacticalAIRegistry;
extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;
struct TemplateView{char pad[0x120];unsigned char flag120,flag121;};
class Object{public:char pad0[4];TemplateView *type;char pad8[0x38-8];Coord3D pos;};
class BfmeFixedStorage0004543D{char bytes[28];public:BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D&)throw();};
class Rva00045411BitSet{char bytes[28];public:Rva00045411BitSet(int,int);};
class Rva000421C8{public:Rva000421C8():next(0){};virtual ~Rva000421C8(){};virtual bool allow(Object*)=0;virtual int getPlayerMask(){return -1;}Rva000421C8 *next;};
class Rva0004584D:public Rva000421C8{public:Rva0004584D(const BfmeFixedStorage0004543D&,const BfmeFixedStorage0004543D&);virtual ~Rva0004584D(){};virtual bool allow(Object*);BfmeFixedStorage0004543D a,b;};
template<int N>class BitFlags{public:unsigned bits[7];};
extern BitFlags<116> KINDOFMASK_NONE;
class AITarget{public:void setTarget(Object*,float);};
static __forceinline float Distance2(const Coord3D&a,const Coord3D&b){float dx=a.x-b.x;float dy=a.y-b.y;return dx*dx+dy*dy;}
class AITargetHeuristicTechBuilding{public:void findBestTarget(AITarget*,Player*,Player*);};
void AITargetHeuristicTechBuilding::findBestTarget(AITarget *target,Player *owner,Player *unused){
 Rva002A8AB1Record *stats=g_tacticalAIRegistry->rva002A8AB1(owner);
 int value=stats->mode;bool mode=value!=0;
 _STL::vector<ObjectID> buildings=g_tacticalAIRegistry->techBuildings;
 TacticalAI *tactics=stats->tactics;
 Coord3D center=stats->rva004EBF4B();
 Object *best=0;float bestDistance=0.0f;
 for(_STL::vector<ObjectID>::iterator i=buildings.begin();i!=buildings.end();++i){
  Object *obj=TheGameLogic->findObjectByID(*i);
  if(owner->getRelationship(obj)==2)continue;
  bool good=false;
  if(obj->type->flag121&0x10){
   Object *near=ThePartitionManager->getClosestObject(&obj->pos,150.0f,1,&Rva0004584D(*(const BfmeFixedStorage0004543D*)&Rva00045411BitSet(0,50),*(const BfmeFixedStorage0004543D*)&KINDOFMASK_NONE));
   if(near && owner->getRelationship(near)!=2){if(!mode || (mode && (near->type->flag120&0x10)) || tactics->begin==tactics->end)good=true;}
  }else{if(!mode || (mode && (obj->type->flag120&0x10)) || tactics->begin==tactics->end)good=true;}
  if(good){float d=Distance2(obj->pos,center);if(!best || bestDistance>d){float dd=Distance2(obj->pos,center);if((!best || bestDistance>dd)&&dd<=1000000.0f){bestDistance=dd;best=obj;}}}
 }
 if(best)target->setTarget(best,g_tacticalAIRegistry->fallbackWeight);
}
