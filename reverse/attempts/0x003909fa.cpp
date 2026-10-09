// ?consume@Rva003909FAObj@@QAEXPAXHH@Z
// partial score=0.94 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /ICode/Libraries/Include
#include "Lib/Coord3D.h"
#include <math.h>
#include <string.h>
#pragma intrinsic(memcpy)
// Native3909FA..390CC8 RET12 consumes a force and two opaque words.
// WB F8F850 corroborates PhysicsBehavior, contained-holder guard, AI wake,
// gravity simulation and AdjustFlingDestination. No original method name is
// established; retain the existing address-derived consume ABI.
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff };
enum ObjectStatusTypes { RVA_STATUS_46=0x46 };
enum CommandSourceType { RVA_COMMAND_SOURCE_2=2 };
enum PathfindLayerEnum { LAYER_INVALID=0,LAYER_GROUND=1 };
class Object;
class UpdateModule { friend class Rva003909FAObj; protected: void setWakeFrame(Object *,UpdateSleepTime); };
class AICommandInterface { public: void aiIdle(CommandSourceType); };
template<int N> struct PhysicsNativeSlotTag {};
template<int N> class PhysicsNativeSlots:public PhysicsNativeSlots<N-1> {public:virtual void unknownSlot(PhysicsNativeSlotTag<N> *);};
template<> class PhysicsNativeSlots<0> {};
class AIUpdateInterface:public PhysicsNativeSlots<91> {
public:
 virtual bool slot16C();
 void rva0026331C();
 char pad04[0x20-4]; AICommandInterface commands;
};
struct Rva003909FATemplate { char pad[0x115]; unsigned char option115; };
class Object {
public:
 bool testStatus(ObjectStatusTypes) const;
 void rva00293105(); int rva0028B511() const;
 char pad00[4]; Rva003909FATemplate *type;
 char pad08[0x38-8]; Coord3D position;
 char pad44[0x258-0x44]; AIUpdateInterface *ai;
 char pad25C[0x274-0x25C]; Object *holder;
};
class TerrainLogic {
public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0C();
 virtual void s10();virtual void s14();virtual void s18();
 virtual float getLayerHeight(float,float,PathfindLayerEnum,Coord3D *,bool);
 PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *);
};
extern TerrainLogic *TheTerrainLogic;
class GlobalData { public: char pad[0xC4]; float gravity; };
extern GlobalData *TheWritableGlobalData;
extern int g_Va00DBA4E4;
class Pathfinder { public: void AdjustFlingDestination(Object *,const Coord3D *,Coord3D *); };
class AI { public: char pad[0x10]; Pathfinder *pathfinder; };
extern AI *TheAI;
struct Rva003909FAData { char pad[0x4C]; float factor; };
class PhysicsBehavior { public: void rva00390557(const Coord3D *,float,float,int,int); };
class Rva003909FAObj {
public:
 void consume(void *force,int source,int weapon);
 char pad00[4]; Rva003909FAData *data; Object *object;
};
void Rva003909FAObj::consume(void *force,int source,int weapon) {
 Rva003909FAData *config=data;
 Object *obj=object;
 if(obj->holder && !(obj->holder->type->option115&0x20)) {
  ((UpdateModule *)this)->setWakeFrame(obj,UPDATE_SLEEP_FOREVER);return;
 }
 if(obj->testStatus(RVA_STATUS_46))obj->rva00293105();
 AIUpdateInterface *ai=obj->ai;
 if(ai && !ai->slot16C()) {ai->rva0026331C();ai->commands.aiIdle(RVA_COMMAND_SOURCE_2);}
 ((UpdateModule *)this)->setWakeFrame(obj,UPDATE_SLEEP_NONE);
 Coord3D position;
 memcpy(&position.x,&obj->position.x,sizeof(float));
 memcpy(&position.y,&obj->position.y,sizeof(float));
 memcpy(&position.z,&obj->position.z,sizeof(float));
 float height=position.z-TheTerrainLogic->getLayerHeight(position.x,position.y,(PathfindLayerEnum)obj->rva0028B511(),0,true);
 if(height<0.0f)height=0.0f;
 float simulatedHeight=height;
 int frames=0;
 for(;frames<3*g_Va00DBA4E4 && simulatedHeight>0.0f;++frames)
  simulatedHeight+=TheWritableGlobalData->gravity*config->factor*frames;
 const Coord3D *velocity=(const Coord3D *)force;
 float vertical=velocity->z;
 if(vertical<velocity->length()*0.25f && frames<2)vertical=velocity->length()*0.25f;
 unsigned duration=(unsigned)fabs(2.0f*vertical/(TheWritableGlobalData->gravity*config->factor));
 if(duration<1)duration=1;
 duration+=frames;
 float count=(float)duration;
 float peak=(vertical*0.5f)*(count*0.5f);
 if(peak<0.0f)peak=0.0f;
 Coord3D destination=obj->position;
 position.x=velocity->x*count;destination.x+=position.x;
 position.y=velocity->y*count;destination.y+=position.y;
 position.z=0.0f*count;destination.z+=position.z;
 TheAI->pathfinder->AdjustFlingDestination(obj,&obj->position,&destination);
 destination.z+=10.0f;
 destination.z=TheTerrainLogic->getLayerHeight(destination.x,destination.y,TheTerrainLogic->getLayerForDestination(0,&destination),0,true);
 float corrected=(position.length()+2.0f*peak+height)/count;
 if(corrected < -TheWritableGlobalData->gravity)corrected=-TheWritableGlobalData->gravity;
 ((PhysicsBehavior *)this)->rva00390557(&destination,peak,corrected,source,weapon);
}
