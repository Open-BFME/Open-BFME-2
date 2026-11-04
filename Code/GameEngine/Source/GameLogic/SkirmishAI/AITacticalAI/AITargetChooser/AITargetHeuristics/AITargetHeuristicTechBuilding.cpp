// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/Libraries/Include
// stlport
//
// ?findBestTarget@AITargetHeuristicTechBuilding@@QAEXPAVAITarget@@PAVPlayer@@1@Z, retail 0x00572EFF, 512 bytes.
// Native tech-building selector: owner record +0x16C mode / +0x164 tactics, registry +0x934 building IDs,
// fallback weight +0x884 passed through the x87 stack. WB 1503190 corroborates owner record, mode and the two
// repeated distance guards. Codegen levers: (float)(double) argument spelling selects the fld/fstp pass,
// equal-arm calls on the iterator keep it register-resident at the loop head, nt keeps near->type off the
// obj type temp, volatile bestDistance holds the 0x18 slot.
#include "GameLogicObjectLookupView.h"
#include "PartitionRangeQueryCallView.h"
#include "Lib/Coord3D.h"
#include <stdlib.h>
namespace _STL

{
 void __cdecl free(void*);
 
}
#include <vector>

// Copy the three-pointer header through the rowed four-byte enum provider.
// The stored values remain ObjectIDs and are converted back at lookup.
enum ScienceType { SCIENCE_NONE = 0 };
namespace _STL {
template<> vector<ScienceType, allocator<ScienceType> >::vector(const vector<ScienceType, allocator<ScienceType> > &);
}

enum Relationship

{
 ENEMIES=0,NEUTRAL=1,ALLIES=2
 
}
;
class Player

{
 public:Relationship getRelationship(const Object*)const;
 
}
;
class Rva004EBF4B

{
 public:Coord3D rva004EBF4B();
 
}
;
struct TacticalAI

{
 char pad[0x20];
 void *begin,*end;
 
}
;
struct Rva002A8AB1Record:public Rva004EBF4B

{
 char pad[0x164];
 TacticalAI *tactics;
 char pad168[4];
 int mode;
 
}
;
class Rva002A8F24

{
 public:Rva002A8AB1Record *rva002A8AB1(void*);
 char pad[0x884];
 float fallbackWeight;
 char pad888[0x934-0x888];
 _STL::vector<ObjectID> techBuildings;
 
}
;
extern Rva002A8F24 *TheSkirmishAIManager;
extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;
struct TemplateView

{
 char pad[0x120];
 unsigned char flag120,flag121;
 
}
;
class Object

{
 public:char pad0[4];
 TemplateView *type;
 char pad8[0x38-8];
 Coord3D pos;
 
}
;
#include "../../../../../../Include/Common/BfmeFixedStorage0004543D.h"
#include "../../../../../../Include/GameLogic/Module/Rva00045411BitSet.h"
#include "../../../../../../Include/GameLogic/PartitionFilter.h"
class Rva0004584D:public Rva000421C8

{
 public:Rva0004584D(const BfmeFixedStorage0004543D&,const BfmeFixedStorage0004543D&);
 virtual ~Rva0004584D()
 
 {
  
 }
 ;
 virtual bool allow(Object*);
 BfmeFixedStorage0004543D a,b;
 
}
;
template<int N>class BitFlags

{
 public:unsigned bits[7];
 
}
;
extern BitFlags<116> KINDOFMASK_NONE;
#include "../../../../../../Include/GameLogic/AITarget.h"
static __forceinline float Distance2(const Coord3D&a,const Coord3D&b)

{
 float dx=a.x-b.x;
 float dy=a.y-b.y;
 return dx*dx+dy*dy;
 
}
class AITargetHeuristicTechBuilding

{
 public:void findBestTarget(AITarget*,Player*,Player*);
 
}
;
void AITargetHeuristicTechBuilding::findBestTarget(AITarget *target,Player *owner,Player *unused)

{
 Rva002A8AB1Record *stats=TheSkirmishAIManager->rva002A8AB1(((&(owner)) ? (owner) : (owner)));
 int value=stats->mode;
 bool mode=value!=0;
 _STL::vector<ScienceType> buildings(*(const _STL::vector<ScienceType> *)&TheSkirmishAIManager->techBuildings);
 TacticalAI *tactics=stats->tactics;
 Coord3D center=stats->rva004EBF4B();
 Object *best=0;
 volatile float bestDistance = 0.0f;
 for(_STL::vector<ScienceType>::iterator i=buildings.begin();i!=buildings.end();++i)
 
 {
  Object *obj=((i != buildings.end()) ? TheGameLogic->findObjectByID((ObjectID)*i) : TheGameLogic->findObjectByID((ObjectID)*i));
  if(owner->getRelationship(obj)==2)continue;
  bool good=false;
  if(obj->type->flag121&0x10)
  
  {
   Object *near=ThePartitionManager->getClosestObject(&obj->pos,150.0f,1,&Rva0004584D(*(const BfmeFixedStorage0004543D*)&Rva00045411BitSet(0,50),*(const BfmeFixedStorage0004543D*)&KINDOFMASK_NONE));
   if(near && owner->getRelationship(near)!=2)
   
   {
    TemplateView *nt;
    if(!mode || (mode && ((nt=near->type)->flag120&0x10)) || tactics->begin==tactics->end)good=true;
    
   }
   
  }
  else
  
  {
   if(!mode || (mode && (obj->type->flag120&0x10)) || tactics->begin==tactics->end)good=true;
   
  }
  if(good)
  
  {
   float distanceSquared=Distance2(obj->pos,center);
   if(!best || bestDistance>distanceSquared)
   
   {
    float dd=Distance2(obj->pos,center);
    if((!best || bestDistance>dd)&&dd<=1000000.0f)
    
    {
     bestDistance=(dd ? dd : dd);
     best=obj;
     
    }
    
   }
   
  }
  
 }
 if(best)target->setTarget(best,(float)(double)TheSkirmishAIManager->fallbackWeight);
 
}
