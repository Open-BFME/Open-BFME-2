// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /I.
//
// ?rva0047D53A@HordeSiegeEngineContain@@QAEXPAVObject@@W4ExitDoorType@@@Z, retail 0x0047d53a, 978 bytes. Banked partial (score 0.9980584085843616) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include <vector>
namespace _STL {template <> __declspec(noinline) void vector<Coord3D>::push_back(const Coord3D&);}
class Player;class Module;class Object;class LocomotorSet;
enum NameKeyType {INVALID_KEY=0};
enum PathfindLayerEnum {LAYER17=17};
enum ObjectStatusTypes {STATUS60=60};
enum CommandSourceType {COMMAND2=2};
enum ExitDoorType {DOOR0=0};
class Matrix3D {float matrix[3][4];};
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};extern NameKeyGenerator *TheNameKeyGenerator;
class Rva2225E0Filter {public:bool accepts(Object*,Player*);};
class AIUpdateInterface {public:void ignoreObstacle(const Object*);char pad[0x178];unsigned ignoreUntil;char pad17c[0x1cc-0x17c];LocomotorSet *locomotorView(){return (LocomotorSet*)((char*)this+0x1cc);}};
class Rva0035149F;
class AICommandInterface {public:void rva0036EE16(const Rva0035149F*,Object*,CommandSourceType);void aiHunt(CommandSourceType);};
class Thing {public:void setPosition(const Coord3D*);void setOrientation(float);const Coord3D *getUnitDirectionVector2D() const;};
class Object:public Thing {protected:friend class HordeSiegeEngineContain;Module*findModule(NameKeyType) const;public:Player*getControllingPlayer() const;bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*) const;void setTransformMatrix(const Matrix3D*);void rva0028B4CE(PathfindLayerEnum);void setStatus(ObjectStatusTypes,bool);void rva0028ACDC(int);
 void *vtable;void *type;char pad8[0x38-8];Coord3D position;float angle;char pad48[0xcc-0x48];float radius;char padd0[0x258-0xd0];AIUpdateInterface *ai;};
class Pathfinder {public:void AddObjectToPathfindMap(Object*);bool adjustToPossibleDestination(Object*,const LocomotorSet&,Coord3D*);float GetWallHeight(PathfindLayerEnum,const Coord3D*,Coord3D*);};
class AI {public:char pad[0x10];Pathfinder *pathfinder;};extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;
class Rva004C5772CmpBoolField {public:bool get() const;};
class Rva00463509 {public:void rva00463509(Object*,bool);};
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
  ((Rva00463509*)((char*)this+0x20))->rva00463509(rider,false);
  Coord3D destination;destination.x=rider->position.x;destination.y=rider->position.y;destination.z=rider->position.z;
  { Coord3D delta;delta.x=destination.x-me->position.x;delta.y=destination.y-me->position.y;delta.z=destination.z-me->position.z;
  delta.normalize();
  float dx=delta.x*50.0f;float dy=delta.y*50.0f;destination.x+=dx;destination.y+=dy;destination.z=0; }
  AIUpdateInterface *ai=rider->ai;
  TheAI->pathfinder->AddObjectToPathfindMap(rider);
  if(ai){
   ai->ignoreObstacle(0);
   ai->ignoreUntil=TheGameLogic->getFrame()+g_Va00DBA4E4;
   Pathfinder *finder=TheAI->pathfinder;finder->adjustToPossibleDestination(rider,*ai->locomotorView(),&destination);
   _STL::vector<Coord3D> path;path.push_back(destination);path.push_back(destination);
   ((AICommandInterface*)((char*)ai+0x20))->rva0036EE16((const Rva0035149F*)&path,me,COMMAND2);
   rider->rva0028ACDC((int)&destination);
  }
 }else if(deployment && ((const Rva004C5772CmpBoolField*)deployment)->get()){
  ((ExitInterface*)((char*)this+0x20))->remove(rider,false);
  float angle=me->angle;
  Coord3D position;
  if(*((unsigned char*)me->type+0x113)&0x20){
   Matrix3D transform;
   me->getSingleLogicalBonePosition("Ladder04",&position,&transform);
   rider->setTransformMatrix(&transform);
   rider->rva0028B4CE(LAYER17);
   AIUpdateInterface *ai=rider->ai;
   TheAI->pathfinder->AddObjectToPathfindMap(rider);
   if(ai){ai->ignoreObstacle(0);ai->ignoreUntil=TheGameLogic->getFrame()+g_Va00DBA4E4;((AICommandInterface*)((char*)ai+0x20))->aiHunt(COMMAND2);}
  }else{
   position=me->position;
   Coord3D direction;const Coord3D *dir=me->getUnitDirectionVector2D();float radius=me->radius;direction.x=dir->x;direction.y=dir->y;
   position.x+=direction.x*radius;position.y+=direction.y*radius;
   Pathfinder *wallFinder=TheAI->pathfinder;position.z=wallFinder->GetWallHeight(LAYER17,&position,0);
   Coord3D start=position;
   position.x+=direction.x*20.0f;position.y+=direction.y*20.0f;
   start.x+=direction.x*40.0f;start.y+=direction.y*40.0f;
   rider->setPosition(&start);rider->setPosition(&start);rider->setOrientation(angle);rider->rva0028B4CE(LAYER17);
   TheAI->pathfinder->AddObjectToPathfindMap(rider);
   AIUpdateInterface *ai=rider->ai;
   if(ai){ai->ignoreUntil=TheGameLogic->getFrame()+3*g_Va00DBA4E4;ai->ignoreObstacle(0);((AICommandInterface*)((char*)ai+0x20))->aiHunt(COMMAND2);}
  }
  if(*((unsigned char*)rider->type+0x115)&0x20)rider->setStatus(STATUS60,false);
 }else{
  ((HordeTransportContain*)((char*)this+0x30))->HordeTransportContain::exitObjectViaDoor(rider,arg);
 }
}
