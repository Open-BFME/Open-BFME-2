// ?exitObjectViaDoor@SiegeEngineContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /Ob2 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/Libraries/Include /ICode/GameEngine/Source/Common
// stlport
// BF1 f989 OpenContainExitObjectViaDoor.cpp provides containment/path semantics.
// Independently named WB11A9380 and native47C4F2..47C927 prove SiegeEngine exit.
// Receiver is primary+30: owner-28 data-2C closed F4; contain slot41 at-10.
// Target adds filter/D4 radius wall exits, Ladder04 and deployed siege gating.
#include <vector>
#include "Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
enum ExitDoorType { DOOR_1=0 };
enum CommandSourceType { CMD_FROM_AI=2 };
enum PathfindLayerEnum { LAYER_WALL=17 };
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
class Player {public:char pad[0x5c];int type;};
class Module;
class Matrix3D {public:float m[3][4];};
class LocomotorSet;
class Rva0035149F;
class AICommandInterface {public:void rva0036EE16(const Rva0035149F *,Object *,CommandSourceType);void aiHunt(CommandSourceType);void aiIdle(CommandSourceType);};
class AIUpdateInterface {public:
 void ignoreObstacle(const Object *);
 const LocomotorSet &set()const{return *reinterpret_cast<const LocomotorSet*>(reinterpret_cast<const char*>(this)+0x1cc);}
 AICommandInterface *commands(){return reinterpret_cast<AICommandInterface*>(reinterpret_cast<char*>(this)+0x20);}
 char pad[0x178];unsigned int movementFrame;
};
class Thing {public:const Coord3D *getUnitDirectionVector2D()const;void setOrientation(float);};
class Rva004C5772CmpBoolField {public:bool get()const;};
struct SiegeExitTemplate {char pad[0x108];unsigned int kinds[7];};
class Object:public Thing {public:
 Player *getControllingPlayer()const;
 Module *findModule(NameKeyType)const;
 bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*)const;
 void rva0028AE6D();void rva0028D412(const Matrix3D*);void rva0028B4CE(PathfindLayerEnum);
 void teleportTo(const Coord3D*,bool);void rva0028ACDC(const Coord3D*);
 char pad[4];SiegeExitTemplate *tmplate;char pad8[0x38-8];Coord3D position;float orientation;
 char pad48[0xcc-0x48];float radius;char padD0[0x118-0xd0];unsigned int flag118;
 char pad11C[0x258-0x11c];AIUpdateInterface *ai;
};
class Rva2225E0Filter {public:bool accepts(Object*,Player*);};
struct SiegeExitData {char pad[0x18c];Rva2225E0Filter filter;char pad18d[3];int count;};
class Pathfinder {public:void AddObjectToPathfindMap(Object*);bool adjustToPossibleDestination(Object*,const LocomotorSet&,Coord3D*);float GetWallHeight(PathfindLayerEnum,const Coord3D*,Coord3D*);};
class AI {public:char pad[0x10];Pathfinder *pathfinder;};
extern AI *TheAI;extern GameLogic *TheGameLogic;
extern int g_00DBA4E4;
template<int N>class SiegeExitSlots:public SiegeExitSlots<N-1>{public:virtual void gap(char(*)[N]);};
template<>class SiegeExitSlots<0>{};
class SiegeExitRemove:public SiegeExitSlots<41>{public:virtual void remove(Object*,bool);};
class OpenContain {public:virtual void exitObjectViaDoor(Object*,ExitDoorType);};
class SiegeEngineContain {public:virtual void exitObjectViaDoor(Object*,ExitDoorType);
 Object *object()const{return *reinterpret_cast<Object *const*>(reinterpret_cast<const char*>(this)-0x28);}
 const SiegeExitData *data()const{return *reinterpret_cast<const SiegeExitData *const*>(reinterpret_cast<const char*>(this)-0x2c);}
 void remove(Object *o){reinterpret_cast<SiegeExitRemove*>(reinterpret_cast<char*>(this)-0x10)->remove(o,false);}
 char pad4[0xf4-4];bool closed;
};
void Rva00030830FreeAllocation(void*);
namespace _STL {template<>void vector<Coord3D>::push_back(const Coord3D&);
template<> __forceinline void allocator<Coord3D>::deallocate(Coord3D *p,unsigned)const {if(p)Rva00030830FreeAllocation(p);}
}
void SiegeEngineContain::exitObjectViaDoor(Object *exitObj,ExitDoorType door)
{
 if(closed)return;
 static NameKeyType key=TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
 Rva004C5772CmpBoolField *deploy=(Rva004C5772CmpBoolField*)object()->findModule(key);
 Object *me=object();const SiegeExitData *md=data();
 if(const_cast<Rva2225E0Filter&>(md->filter).accepts(exitObj,me->getControllingPlayer()) && md->count>0){
   remove(exitObj);
   Coord3D pos;pos.x=exitObj->position.x;pos.y=exitObj->position.y;pos.z=exitObj->position.z;
   {Coord3D diff;diff.x=pos.x-me->position.x;diff.y=pos.y-me->position.y;diff.z=pos.z-me->position.z;
   diff.normalize();float dx=diff.x*50.0f,dy=diff.y*50.0f;pos.x+=dx;pos.y+=dy;pos.z=0;}
   AIUpdateInterface *ai=exitObj->ai;
   TheAI->pathfinder->AddObjectToPathfindMap(exitObj);
   if(ai){
     ai->ignoreObstacle(0);ai->movementFrame=TheGameLogic->getFrame()+g_00DBA4E4;
     Pathfinder *pathfinder=TheAI->pathfinder;pathfinder->adjustToPossibleDestination(exitObj,ai->set(),&pos);
     _STL::vector<Coord3D> path;path.push_back(pos);path.push_back(pos);
     ai->commands()->rva0036EE16(reinterpret_cast<const Rva0035149F*>(&path),me,CMD_FROM_AI);
     exitObj->rva0028ACDC(&pos);
   }
 }else if(deploy && deploy->get()){
   remove(exitObj);Object *me=object();Coord3D pos;
   if(me->tmplate->kinds[4]&0x800){Matrix3D transform;
     me->getSingleLogicalBonePosition("Ladder04",&pos,&transform);
     if(exitObj->flag118&1){exitObj->flag118&=~1;exitObj->rva0028AE6D();}
     exitObj->rva0028D412(&transform);exitObj->rva0028B4CE(LAYER_WALL);
     AIUpdateInterface *ai=exitObj->ai;TheAI->pathfinder->AddObjectToPathfindMap(exitObj);
     if(ai){if(exitObj->getControllingPlayer()->type==1){ai->ignoreObstacle(0);ai->commands()->aiHunt(CMD_FROM_AI);}else ai->commands()->aiIdle(CMD_FROM_AI);}
   }else{
     Coord3D dest;{pos=me->position;Coord3D direction;const Coord3D *dir=me->getUnitDirectionVector2D();direction.x=dir->x;direction.y=dir->y;
     const float &radius=me->radius;pos.x+=direction.x*radius;pos.y+=direction.y*radius;
     pos.z=TheAI->pathfinder->GetWallHeight(LAYER_WALL,&pos,0);
     dest=pos;pos.x+=direction.x*20.0f;pos.y+=direction.y*20.0f;
     dest.x+=direction.x*40.0f;dest.y+=direction.y*40.0f;}
     exitObj->teleportTo(&pos,false);exitObj->setOrientation(me->orientation);exitObj->rva0028B4CE(LAYER_WALL);
     AIUpdateInterface *ai=exitObj->ai;TheAI->pathfinder->AddObjectToPathfindMap(exitObj);
     if(ai){ai->ignoreObstacle(0);ai->movementFrame=TheGameLogic->getFrame()+g_00DBA4E4;Pathfinder *pathfinder=TheAI->pathfinder;pathfinder->adjustToPossibleDestination(exitObj,ai->set(),&dest);}
     {_STL::vector<Coord3D> path;path.push_back(dest);path.push_back(dest);
     if(ai){ai->commands()->rva0036EE16(reinterpret_cast<const Rva0035149F*>(&path),me,CMD_FROM_AI);exitObj->rva0028ACDC(&dest);}}
   }
 }else reinterpret_cast<OpenContain*>(this)->OpenContain::exitObjectViaDoor(exitObj,door);
}
