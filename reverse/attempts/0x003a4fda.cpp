// ?update@StrafeAreaUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.9054787782177982 date=2026-10-10
// ?update@StrafeAreaUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.88 date=2026-10-09
// cl: /I. /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Target3A4FDA..3A538E and WB StrafeAreaUpdate.cpp:171/173 prove update.
// Constructor3A4D23/initializer3A4F21 establish primary layout; update
// operates on the secondary interface at10 (vtableC1B158 slot0).
// BFME strafe module has no clean BF1/ZH source counterpart; recovered
// initializer and WB/native control flow supply the structural guide.
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "ascii_string.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
enum CommandSourceType {CMD_FROM_AI=2};
class AICommandInterface {public:void aiMoveToPosition(const Coord3D *,CommandSourceType);};
template<int N> class StrafeAISlots:public StrafeAISlots<N-1> {public:virtual void gap(char (*)[N])=0;};template<> class StrafeAISlots<0> {};
class AIUpdateInterface:public StrafeAISlots<98> {public:virtual AIUpdateInterface *rvaSlot98()=0;
virtual void gap99()=0;
virtual void gap100()=0;
virtual void gap101()=0;
virtual void gap102()=0;
virtual void gap103()=0;
virtual void gap104()=0;
virtual void gap105()=0;
virtual void gap106()=0;
virtual void gap107()=0;
virtual void gap108()=0;
virtual void gap109()=0;
virtual bool rvaSlot110()=0;
virtual void gap111()=0;
virtual void gap112()=0;
virtual void gap113()=0;
virtual void gap114()=0;
virtual void gap115()=0;
virtual void gap116()=0;
virtual void gap117()=0;
virtual void gap118()=0;
virtual void gap119()=0;
virtual void gap120()=0;
virtual void gap121()=0;
virtual void gap122()=0;
virtual void gap123()=0;
virtual void gap124()=0;
virtual void gap125()=0;
virtual void gap126()=0;
virtual void gap127()=0;
virtual void gap128()=0;
virtual void gap129()=0;
virtual void gap130()=0;
virtual void gap131()=0;
virtual void gap132()=0;
virtual void gap133()=0;
virtual void gap134()=0;
virtual void gap135()=0;
virtual void gap136()=0;
virtual void gap137()=0;
virtual void gap138()=0;
virtual void gap139()=0;
virtual void gap140()=0;
virtual void gap141()=0;
virtual bool chooseLocomotorSet(int)=0;char pad[0x1C];AICommandInterface commands;};
class Thing {public:const Coord3D *getUnitDirectionVector2D() const;};
enum DamageType {DAMAGE_UNRESISTABLE=8};enum DeathType {DEATH_ANONYMOUS=22};
class StrafeModelFlags {public:
 unsigned test(unsigned bit) const{return words[bit>>5]&(1U<<(bit&31));}
 void set(unsigned bit){words[bit>>5]|=1U<<(bit&31);}
 void reset(unsigned bit){words[bit>>5]&=~(1U<<(bit&31));}
 unsigned words[19];
};
class Object:public Thing {public:
 void rva0028AE6D();void kill(DamageType,DeathType);
 __forceinline void setFiring(){if(conditions.test(37)==0){conditions.set(37);rva0028AE6D();}}
 __forceinline void clearFiring(){if(conditions.test(37)!=0){conditions.reset(37);rva0028AE6D();}}
 char pad00[0x38];Coord3D position;char pad44[0x10C-0x44];StrafeModelFlags conditions;char pad158[0x258-0x158];AIUpdateInterface *ai;char pad25C[0x438-0x25C];unsigned char status;
};
struct StrafeAreaUpdateModuleData {char pad[8];AsciiString weaponName;float radius,frequency,amplitude,slope,initialPhase;};
struct StrafeDirection:public Coord3D {
 __forceinline StrafeDirection scaled(float a) const {return StrafeDirection(x*a,y*a,z*a);}
 __forceinline StrafeDirection plus(const StrafeDirection &v) const {return StrafeDirection(x+v.x,y+v.y,z+v.z);}

 StrafeDirection() {}
 __forceinline StrafeDirection(float a,float b,float c){x=a;y=b;z=c;}
 __forceinline Coord3D *coord(){return this;}
 __forceinline void scale(float a){x*=a;y*=a;z*=a;}
 __forceinline void add(const StrafeDirection &v){x+=v.x;y+=v.y;z+=v.z;}
 __forceinline void add(const Coord3D &v){x+=v.x;y+=v.y;z+=v.z;}
 __forceinline StrafeDirection(const Coord3D &v){x=v.x;y=v.y;z=v.z;}
 __forceinline void sub(const Coord3D &v){x-=v.x;y-=v.y;z-=v.z;}
};
enum UpdateSleepTime {UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff};
class ObjectModule {public:virtual ~ObjectModule();const StrafeAreaUpdateModuleData *data;Object *object;};
class BehaviorModuleInterface {public:virtual void slot0()=0;};
class BehaviorModule:public ObjectModule,public BehaviorModuleInterface {public:virtual ~BehaviorModule();};
class UpdateModuleInterface {public:virtual UpdateSleepTime update()=0;};
class UpdateModule:public BehaviorModule,public UpdateModuleInterface {public:virtual ~UpdateModule();private:unsigned nextWake;int index,reserved;};
class StrafeAreaUpdate:public UpdateModule {public:
 virtual UpdateSleepTime update();
 Coord3D target,start;float phase;unsigned state;bool started;unsigned nextFire;
};
class WeaponTemplate;
class WeaponStore {public:const WeaponTemplate *findWeaponTemplate(const AsciiString &) const;void createAndFireTempWeapon(const WeaponTemplate *,const Object *,const Coord3D *);};extern WeaponStore *TheWeaponStore;
class TerrainLogic {public:virtual void s0()=0;virtual void s1()=0;virtual void s2()=0;virtual void s3()=0;virtual void s4()=0;virtual void s5()=0;virtual float getGroundHeight(float,float,Coord3D *normal=0)=0;virtual void s7()=0;virtual void s8()=0;virtual void s9()=0;virtual void s10()=0;virtual void s11()=0;virtual void s12()=0;virtual void rvaSlot13(Coord3D *,const Coord3D *)=0;};extern TerrainLogic *TheTerrainLogic;
extern "C" double sin(double);
// ?update@StrafeAreaUpdate@@UAE?AW4UpdateSleepTime@@XZ present-unmatched
#include <math.h>
inline __declspec(noinline) float Coord3D::length() const
{
    return (float)sqrt(x * x + y * y + z * z);
}
inline __declspec(noinline) void Coord3D::normalize()
{
    float len = length();
    if (len != 0.0f) {
        float scale = 1.0f / len;
        x *= scale;
        y *= scale;
        z *= scale;
    }
}

UpdateSleepTime StrafeAreaUpdate::update() {
 const StrafeAreaUpdateModuleData *d=data;Object *obj=object;
 AIUpdateInterface *ai=obj->ai;
 if(!ai) return UPDATE_SLEEP_FOREVER;
 AIUpdateInterface *aircraft=ai->rvaSlot98();
 if(!aircraft) return UPDATE_SLEEP_FOREVER;
 StrafeDirection delta(target);delta.sub(obj->position);delta.z=0.0f;
 float distance=delta.coord()->length();
 switch(state) {
 case 0:
  aircraft->chooseLocomotorSet(6);
  if(distance<=d->radius+d->slope*2.0f) obj->setFiring();
  if(distance<=d->radius+d->slope) {
   aircraft->chooseLocomotorSet(0);state=1;nextFire=TheGameLogic->getFrame()+12;
  }
  break;
 case 1: {
  const WeaponTemplate *weapon=TheWeaponStore->findWeaponTemplate(d->weaponName);
  if(weapon && TheGameLogic->getFrame()>=nextFire) {
   StrafeDirection firingPosition(obj->position);
   StrafeDirection direction(*obj->getUnitDirectionVector2D());direction.coord()->normalize();
   StrafeDirection perpendicular(direction.y,-direction.x,0.0f);
   phase+=d->frequency;
   float offset=(float)(sin(phase)*d->amplitude);
   firingPosition.add(direction.scaled(d->slope));
   perpendicular.scale(offset);firingPosition.add(perpendicular);
   firingPosition.z=TheTerrainLogic->getGroundHeight(firingPosition.x,firingPosition.y);
   TheWeaponStore->createAndFireTempWeapon(weapon,obj,firingPosition.coord());
  }
  obj->setFiring();
  if(started && distance>d->radius-d->slope) {
   state=2;aircraft->chooseLocomotorSet(6);obj->clearFiring();break;
  }
  if(distance<d->radius/12.0f && aircraft->rvaSlot110()) {
   StrafeDirection onward(target);onward.sub(start);onward.coord()->normalize();onward.scale(500.0f);onward.add(target);
   Coord3D adjusted;TheTerrainLogic->rvaSlot13(&adjusted,onward.coord());
   aircraft->commands.aiMoveToPosition(&adjusted,CMD_FROM_AI);started=true;
  }
  break;
 }
 case 2:
  if(distance>d->radius && aircraft->rvaSlot110() && !(obj->status&1)) obj->kill(DAMAGE_UNRESISTABLE,DEATH_ANONYMOUS);
  break;
 }
 return UPDATE_SLEEP_NONE;
}
