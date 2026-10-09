// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// WB1223FD0 and native4AC2A8..4AC5D9 prove RainOfFire update. BF1
// RainOfFire constructor/destructor donor9cbfb551 and matched BFME2 xfer
// establish the module fields. BF1 Vector3/Matrix3D supply math semantics;
// native module-data table offsets and terrain/weapon calls guide this body.
#include "../../../../../../reference/shims/bfme_vector3_ctor_link/vector3.h"
#include "matrix3d.h"
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;
float GetGameLogicRandomValueReal(float,float,char *,int);
float Cos(float);float Sin(float);
enum WeaponSlotType {PRIMARY_WEAPON=0};
enum PathfindLayerEnum {GROUND=0};
class Object;
class Weapon {public:void loadAmmoNow(const Object *);bool fireWeapon(const Object *,const Coord3D *,int *);};
class WeaponSet {public:Weapon *getWeaponInWeaponSlot(WeaponSlotType) const;};
class Thing {public:void setTransformMatrix(const Matrix3D *);};
class Object:public Thing {public:__forceinline Weapon *getWeapon()const{return ((const WeaponSet*)((const char*)this+0x330))->getWeaponInWeaponSlot(PRIMARY_WEAPON);} };
template<int N>class RainSlots:public RainSlots<N-1>{public:virtual void gap(char (*)[N])=0;};template<>class RainSlots<0>{};
// The camera-position global at DFEA3C is the tactical View, as in the reference.
class View:public RainSlots<70>{public:virtual void rvaSlot70(Coord3D *)=0;};extern View *TheTacticalView;
class TerrainLogic:public RainSlots<7>{public:virtual float rvaSlot7(float,float,PathfindLayerEnum,Coord3D *,bool)=0;PathfindLayerEnum getHighestLayerForDestination(const Coord3D *,bool);};extern TerrainLogic *TheTerrainLogic;
struct RainOfFireUpdateModuleData {char pad[8];unsigned startRainTime,darknessFadeTime;float height,darkness,jitter,dpsMin,dpsMax,rampup;Coord2D offset;};
class ObjectModule {public:virtual ~ObjectModule();const RainOfFireUpdateModuleData *data;Object *object;};
class BehaviorModuleInterface {public:virtual void slot0()=0;};
class BehaviorModule:public ObjectModule,public BehaviorModuleInterface {public:virtual ~BehaviorModule();};
enum UpdateSleepTime {UPDATE_SLEEP_FOREVER=0x3fffffff};
class UpdateModuleInterface {public:virtual UpdateSleepTime update()=0;};
class UpdateModule:public BehaviorModule,public UpdateModuleInterface {public:virtual ~UpdateModule();private:unsigned nextWake;int index,reserved;};
class Secondary20 {public:virtual void rvaSlot0(float)=0;};
class RainOfFireUpdate:public UpdateModule,public Secondary20 {public:virtual UpdateSleepTime update();void rva004AC18D(float);unsigned frame;float darkness,scale,pending,ramp;};
UpdateSleepTime RainOfFireUpdate::update() {
 Object *obj=object;const RainOfFireUpdateModuleData *d=data;
 if(!d)return UPDATE_SLEEP_FOREVER;
 unsigned elapsed=TheGameLogic->getFrame()-frame;
 if(elapsed<=d->darknessFadeTime) {
  float value=d->darknessFadeTime ? (float)elapsed/(float)d->darknessFadeTime:1.0f;
  rva004AC18D(value);
 }
 if(elapsed>=d->startRainTime) {
  if(ramp<1.0f) {ramp+=1.0f/d->rampup;if(ramp>1.0f)ramp=1.0f;}
  pending+=GetGameLogicRandomValueReal(d->dpsMin,d->dpsMax,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\RainOfFireUpdate.cpp",125)*scale*ramp/g_Va00DBA4E4;
  Weapon *weapon=obj->getWeapon();
  if(weapon) {
   Coord3D center;TheTacticalView->rvaSlot70(&center);center.z=d->height;
   while(pending>=1.0f) {
    Coord3D pos={center.x,center.y,center.z};
    if(d->jitter>0.0f) {
     float angle=GetGameLogicRandomValueReal(0.0f,6.2831855f,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\RainOfFireUpdate.cpp",142);
     float radius=GetGameLogicRandomValueReal(0.0f,d->jitter,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\RainOfFireUpdate.cpp",143);
     pos.x+=Cos(angle)*radius;pos.y+=Sin(angle)*radius;
    }
    Coord3D target;target.z=pos.z;target.x=pos.x+d->offset.x;target.y=pos.y+d->offset.y;
    PathfindLayerEnum layer=TheTerrainLogic->getHighestLayerForDestination(&target,false);
    target.z=TheTerrainLogic->rvaSlot7(target.x,target.y,layer,0,true);
    Vector3 dir=Vector3(target.x,target.y,target.z)-Vector3(pos.x,pos.y,pos.z);dir.Normalize();
    Matrix3D transform;transform.buildTransformMatrix(Vector3(pos.x,pos.y,pos.z),dir);
    obj->setTransformMatrix(&transform);weapon->loadAmmoNow(obj);weapon->fireWeapon(obj,&target,0);
    pending-=1.0f;
   }
  }else pending=0.0f;
  rva004AC18D(darkness);
 }
 return (UpdateSleepTime)1;
}
