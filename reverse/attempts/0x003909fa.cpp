// ?consume@Rva003909FAObj@@QAEXPAXHH@Z
// partial score=0.866 date=2026-10-09
// cl: /O1 /G6 /Oy- /arch:SSE /MD /GX- /ICode/Libraries/Include/Lib
#include "Coord3D.h"
#include <math.h>
enum UpdateSleepTime {UPDATE_SLEEP_NONE=1, UPDATE_SLEEP_FOREVER=0x3fffffff};
enum ObjectStatusTypes {STATUS70=70};
enum PathfindLayerEnum {LAYER_INVALID=0};
enum CommandSourceType {COMMAND2=2};
class Object;
class AICommandInterface {public:void aiIdle(CommandSourceType);};
template<int N> class FlingSlotsP4 : public FlingSlotsP4<N-1> {public:virtual void slot(char(*)[N])=0;};
template<> class FlingSlotsP4<0> {};
class AIUpdateInterface : public FlingSlotsP4<91> {
public:virtual bool slot91()=0;void rva0026331C();
};
struct PhysicsFlingTemplateP4 {char pad00[0x115];unsigned char flags115;};
class Object {
public:
 bool testStatus(ObjectStatusTypes) const;
 void rva00293105();
 int rva0028B511() const;
 unsigned vptr; PhysicsFlingTemplateP4 *type;
 char pad08[0x38-8];Coord3D position;
 char pad44[0x258-0x44];AIUpdateInterface *ai;
 char pad25c[0x274-0x25c];Object *holder;
};
class UpdateModule {protected:void setWakeFrame(Object*,UpdateSleepTime);};
class TerrainLogic : public FlingSlotsP4<7> {
public:
 virtual float getLayerHeight(float,float,PathfindLayerEnum,Coord3D*,bool) const=0;
 PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*);
};
extern TerrainLogic *TheTerrainLogic;
class GlobalData {public:char pad00[0xc4];float gravity;};
extern GlobalData *TheWritableGlobalData;
extern int g_Va00DBA4E4;
class Pathfinder {public:void AdjustFlingDestination(Object*,const Coord3D*,Coord3D*);};
class AI {public:char pad00[0x10];Pathfinder *pathfinder;};
extern AI *TheAI;
struct PhysicsFlingDataP4 {char pad00[0x4c];float factor;};
class PhysicsBehavior {public:void rva00390557(const Coord3D*,float,float,int,int);};
class Rva003909FAObj : public UpdateModule {
public:
 void consume(void *force,int source,int weapon);
 __forceinline PhysicsFlingDataP4 *getData() const {return data;}
 __forceinline Object *getObject() const {return object;}
 char pad00[4];PhysicsFlingDataP4 *data;Object *object;
};
void Rva003909FAObj::consume(void *force,int source,int weapon)
{
 PhysicsFlingDataP4 *d=getData();
 Object *obj=getObject();
 Object *holder=obj->holder;
 if(holder && !(holder->type->flags115 & 0x20)) {setWakeFrame(obj,UPDATE_SLEEP_FOREVER);return;}
 if(obj->testStatus(STATUS70)) obj->rva00293105();
 AIUpdateInterface *ai=obj->ai;
 if(ai && !ai->slot91()) {
  ai->rva0026331C();
  ((AICommandInterface*)((char*)ai+0x20))->aiIdle(COMMAND2);
 }
 setWakeFrame(obj,UPDATE_SLEEP_NONE);
 Coord3D delta; delta.x=obj->position.x;delta.y=obj->position.y;delta.z=obj->position.z;
 float above=delta.z-TheTerrainLogic->getLayerHeight(delta.x,delta.y,(PathfindLayerEnum)obj->rva0028B511(),0,true);
 if(above<0.0f) above=0.0f;
 int hops=0;
 float height=above;
 for(; hops<3*g_Va00DBA4E4 && height>0.0f; ++hops) {
  height += (TheWritableGlobalData->gravity*d->factor)*(float)hops;
 }
 Coord3D *f=(Coord3D*)force;
 float vertical=f->z;
 if(f->length()*0.25f>vertical && hops<2) vertical=f->length()*0.25f;
 unsigned ticks=(unsigned)fabs((double)((vertical+vertical)/(TheWritableGlobalData->gravity*d->factor)));
 if(ticks<1) ticks=1;
 float count=(float)(ticks+hops);
 float cap=(count*0.5f)*(vertical*0.5f);
 if(cap<0.0f) cap=0.0f;
 float dx=f->x,dy=f->y,dz=0.0f;
 Coord3D dest=obj->position;
 delta.x=dx*count;delta.y=dy*count;delta.z=dz*count;
 dest.x +=delta.x;dest.y+=delta.y;dest.z+=delta.z;
 TheAI->pathfinder->AdjustFlingDestination(obj,&obj->position,&dest);
 dest.z+=10.0f;
 dest.z=TheTerrainLogic->getLayerHeight(dest.x,dest.y,TheTerrainLogic->getLayerForDestination(0,&dest),0,true);
 float speed=(delta.length()+(cap+cap)+above)/count;
 if(-TheWritableGlobalData->gravity>speed) speed=-TheWritableGlobalData->gravity;
 ((PhysicsBehavior*)this)->rva00390557(&dest,cap,speed,source,weapon);
}
