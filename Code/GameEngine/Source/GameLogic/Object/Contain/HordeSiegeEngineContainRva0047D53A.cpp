// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /I.
//
// ?rva0047D53A@HordeSiegeEngineContain@@QAEXPAVObject@@W4ExitDoorType@@@Z, retail 0x0047d53a, 978 bytes. Banked partial (score 0.9980584085843616) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include <vector>
namespace _STL {
template <> __declspec(dllimport) __forceinline _Vector_base<Coord3D, allocator<Coord3D> >::~_Vector_base()
{ if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); }
}

namespace _STL {template <> __declspec(noinline) void vector<Coord3D>::push_back(const Coord3D&);}
class Player;class Module;class Object;class LocomotorSet;
enum NameKeyType {INVALID_KEY=0};
enum PathfindLayerEnum {LAYER17=17};
enum ObjectStatusTypes {STATUS60=60};
enum CommandSourceType {COMMAND2=2};
enum ExitDoorType {DOOR0=0};
#include "../../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"

#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva2225E0Filter {public:bool accepts(Object*,Player*);};
class Rva0035149F;
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../Common/Thing/thing.h"
#include "../../../../Include/Common/ThingTemplate.h"
class Object:public Thing {protected:friend class HordeSiegeEngineContain;Module*findModule(NameKeyType) const;public:Player*getControllingPlayer() const;bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*) const;void rva0028D412(const Matrix3D*);void setLayer(PathfindLayerEnum);void setStatus(ObjectStatusTypes,bool);void rva0028ACDC(int);
 char pad60[0xcc-0x60];float radius;char padd0[0x258-0xd0];AIUpdateInterface *ai;};
#include "../../../../Include/GameLogic/AIPathfind.h"
#include "../../../../Include/GameLogic/AI.h"
extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond;
class Rva004C5772CmpBoolField {public:bool get() const;};
class Rva00463509 {public:void removeFromContain(Object*,bool);};
class HordeTransportContain {public:virtual void exitObjectViaDoor(Object*,ExitDoorType);};
template<int N>class ExitSlots:public ExitSlots<N-1>{public:virtual void gap(char(*)[N]);};template<>class ExitSlots<0>{};
class ExitInterface:public ExitSlots<41>{public:virtual void remove(Object*,bool);};
struct SiegeContainData {char pad[0x18c];Rva2225E0Filter filter;char pad18d[3];int active;};
class HordeSiegeEngineContain {public:void rva0047D53A(Object*,ExitDoorType);void *vtable;SiegeContainData *data;Object *owner;};
void HordeSiegeEngineContain::rva0047D53A(Object *rider,ExitDoorType arg)
{
 static NameKeyType key=TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
 Module *deployment=owner->findModule(key);
 Object *me=owner;
 SiegeContainData *md=data;
 if(md->filter.accepts(rider,me->getControllingPlayer()) && md->active>0){
  ((Rva00463509*)((char*)this+0x20))->removeFromContain(rider,false);
  Coord3D destination;destination.x=rider->m_cachedPos.x;destination.y=rider->m_cachedPos.y;destination.z=rider->m_cachedPos.z;
  { Coord3D delta;delta.x=destination.x-me->m_cachedPos.x;delta.y=destination.y-me->m_cachedPos.y;delta.z=destination.z-me->m_cachedPos.z;
  delta.normalize();
  float dx=delta.x*50.0f;float dy=delta.y*50.0f;destination.x+=dx;destination.y+=dy;destination.z=0; }
  AIUpdateInterface *ai=rider->ai;
  TheAI->m_pathfinder->AddObjectToPathfindMap(rider);
  if(ai){
   ai->ignoreObstacle(0);
   ai->m_ignoreCollisionsUntil=TheGameLogic->getFrame()+BfmeLogicFramesPerSecond;
   Pathfinder *finder=TheAI->m_pathfinder;finder->adjustToPossibleDestination(rider,ai->getLocomotorSet(),&destination);
   _STL::vector<Coord3D> path;path.push_back(destination);path.push_back(destination);
   ai->rva0036EE16((const Rva0035149F*)&path,me,COMMAND2);
   rider->rva0028ACDC((int)&destination);
  }
 }else if(deployment && ((const Rva004C5772CmpBoolField*)deployment)->get()){
  ((ExitInterface*)((char*)this+0x20))->remove(rider,false);
  float angle=me->m_cachedAngle;
  Coord3D position;
  if(me->m_template->m_kindof[2]&0x20000000){
   Matrix3D transform;
   me->getSingleLogicalBonePosition("Ladder04",&position,&transform);
   rider->rva0028D412(&transform);
   rider->setLayer(LAYER17);
   AIUpdateInterface *ai=rider->ai;
   TheAI->m_pathfinder->AddObjectToPathfindMap(rider);
   if(ai){ai->ignoreObstacle(0);ai->m_ignoreCollisionsUntil=TheGameLogic->getFrame()+BfmeLogicFramesPerSecond;ai->aiHunt(COMMAND2);}
  }else{
   position=me->m_cachedPos;
   Coord3D direction;const Coord3D *dir=me->getUnitDirectionVector2D();float radius=me->radius;direction.x=dir->x;direction.y=dir->y;
   position.x+=direction.x*radius;position.y+=direction.y*radius;
   Pathfinder *wallFinder=TheAI->m_pathfinder;position.z=wallFinder->GetWallHeight(LAYER17,&position,0);
   Coord3D start=position;
   position.x+=direction.x*20.0f;position.y+=direction.y*20.0f;
   start.x+=direction.x*40.0f;start.y+=direction.y*40.0f;
   rider->setPosition(&start);rider->setPosition(&start);rider->setOrientation(angle);rider->setLayer(LAYER17);
   TheAI->m_pathfinder->AddObjectToPathfindMap(rider);
   AIUpdateInterface *ai=rider->ai;
   if(ai){ai->m_ignoreCollisionsUntil=TheGameLogic->getFrame()+3*BfmeLogicFramesPerSecond;ai->ignoreObstacle(0);ai->aiHunt(COMMAND2);}
  }
  if(rider->m_template->m_kindof[3]&0x2000)rider->setStatus(STATUS60,false);
 }else{
  ((HordeTransportContain*)((char*)this+0x30))->HordeTransportContain::exitObjectViaDoor(rider,arg);
 }
}
