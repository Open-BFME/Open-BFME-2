// ?update@GettingBuiltBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=1.0 date=2026-10-09
// cl: /O1 /Ob2 /arch:SSE /DNDEBUG /MD /EHsc
// BF1f989 GettingBuiltBehavior_update.cpp is the semantic guide.
// Native454DF9..455050 and WB116A1E0 prove the +0x10 update interface,
// data/object at +4/+8, primary callbacks and BF2 progress/path-map additions.
// Retail table 0x00C40434, installed at +0x10 by the rowed ctor 0x004542FA and
// dtor 0x0045448F, holds this body in slot 0: it is GettingBuiltBehavior's
// override, which MSVC compiles with this at that subobject.
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
extern GameLogic *TheGameLogic;
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };
class Player;
class WeaponTemplate;
class ThingTemplate {public:unsigned char pad[0x108];unsigned int kind[7];};
class GettingBuiltUpdateBody {
public:
 virtual void v0();virtual void v1();virtual void v2();virtual void v3();
 virtual float health();virtual float fraction();virtual float maxHealth();
 virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();
 virtual void v12();virtual void v13();virtual void v14();virtual void v15();virtual void v16();
 virtual void v17();virtual void v18();virtual void v19();virtual void v20();virtual void v21();
 virtual void v22();virtual void v23();virtual void v24();virtual void v25();virtual void v26();
 virtual void v27();virtual void v28();virtual void v29();virtual void v30();virtual void v31();
 virtual void v32();virtual void v33();virtual void v34();virtual void v35();virtual void clearRecent();
};
class Object {
public:
 bool rva0028C264(int *,int);
 Player *getControllingPlayer()const;
 bool attemptHealingFromSoleBenefactor(float,const Object *,unsigned int);
 unsigned char pad0[4];ThingTemplate *tmplate;
 unsigned char pad8[0x38-8];Coord3D position;
 float orientation;unsigned char pad48[0x74-0x48];ObjectID id,producer,builder;
 unsigned char pad80[0x254-0x80];GettingBuiltUpdateBody *body;
 unsigned char pad258[0x280-0x258];float progress;
 unsigned char pad284[0x438-0x284];unsigned char privateStatus;
};
class WeaponStore {public:void createAndFireTempWeapon(const WeaponTemplate *,const Object *,const Coord3D *);};
extern WeaponStore *TheWeaponStore;
class Pathfinder {public:void RemoveObjectFromPathfindMap(Object *);void AddObjectToPathfindMap(Object *);};
class AI {public:unsigned char pad[0x10];Pathfinder *pathfinder;};
extern AI *TheAI;
class BuildAssistant {public:bool moveObjectsForConstruction(const ThingTemplate *,const Coord3D *,float,Player *);};
extern BuildAssistant *TheBuildAssistant;
extern int BfmeLogicFramesPerSecond;
class GettingBuiltUpdateSecondary {
public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();
 virtual void v4();virtual void cleanup();virtual bool active();
};
class BfmeThingE63 { public: bool isValid(); };
class ModuleData;
class BehaviorModuleBase {
public:virtual ~BehaviorModuleBase();
protected:const ModuleData *m_moduleData;Object *m_object;
};
class BehaviorModuleOther {public:virtual void behaviorModuleOtherAnchor();};
class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther {};
class UpdateModuleInterface {public:virtual UpdateSleepTime update()=0;};
class UpdateModule : public BehaviorModule, public UpdateModuleInterface {
protected:unsigned m_nextCallFrameAndPhase;int m_indexInLogic;int m_bfmeReserved;
};
struct GettingBuiltUpdateData {
 unsigned char pad[0x20];union {float duration;unsigned int durationBits;};
 unsigned char pad24[4];const WeaponTemplate *weapon;bool rebuild;
};
class GettingBuiltBehavior : public UpdateModule, public GettingBuiltUpdateSecondary {
 bool rva004541AB();bool rva00453124();
public:void rva00454B5C();void rva0045479A();
 virtual UpdateSleepTime update();
private:
 unsigned int m_x24;
 unsigned int m_durationBits; // +0x28
 unsigned int m_x2C;
 bool m_b30,m_wasDead,m_b32,m_b33,m_firedWeapon,m_b35,m_b36;
 int m_x38;
 bool m_b3C;
};
UpdateSleepTime GettingBuiltBehavior::update()
{
 const GettingBuiltUpdateData *data=(const GettingBuiltUpdateData *)m_moduleData;
 Object *obj=m_object;
 bool dead=(obj->privateStatus&1)!=0;
 if(m_wasDead!=dead && data->rebuild){
   m_wasDead=dead;
   m_durationBits=data->durationBits;
   if(dead)m_b30=true;
 }
 int out=0;
 bool busy=!m_b35 && obj->rva0028C264(&out,4);
 GettingBuiltBehavior *primary=this;
 bool handled=primary->rva004541AB();
 // The +0x20 interface base by address: a converted this would add a null test.
 GettingBuiltUpdateSecondary *secondary=(GettingBuiltUpdateSecondary *)((char *)this+0x20);
 bool active=secondary->active();
 bool worker=false;
 if(obj->builder!=obj->id && !m_b3C){
   Object *builder=TheGameLogic->findObjectByID(obj->builder);
   if(builder && !(builder->tmplate->kind[4]&0x10000000))worker=true;
 }
 if(!dead){
   if(data->duration>=0.0f && busy && !m_b36)goto cleanup;
   if(!active || worker || ((BfmeThingE63 *)primary)->isValid())goto handled_or_cleanup;
   if(!m_b36 && handled)return UPDATE_SLEEP_NONE;
   if(!m_firedWeapon && obj->progress>=75.0f){
     m_firedWeapon=true;
     if(data->weapon)TheWeaponStore->createAndFireTempWeapon(data->weapon,obj,&obj->position);
   }
   GettingBuiltUpdateBody *body=obj->body;
   if(body){
     float health=body->maxHealth()/(float)m_x2C;
     if(obj->tmplate->kind[5]&0x20000000){
       float minimum=body->maxHealth()*0.2f;
       if(body->health()>=minimum && body->health()<minimum+health){
         TheAI->pathfinder->RemoveObjectFromPathfindMap(obj);
         TheAI->pathfinder->AddObjectToPathfindMap(obj);
         float orientation=obj->orientation;
         const ThingTemplate *thingTemplate=obj->tmplate;
         Player *player=obj->getControllingPlayer();
         TheBuildAssistant->moveObjectsForConstruction(thingTemplate,&obj->position,orientation,player);
       }
     }
     obj->attemptHealingFromSoleBenefactor(health,obj,2);
     obj->progress=body->fraction()*100.0f;
     if(!m_b35)body->clearRecent();
   }
   primary->rva00454B5C();return UPDATE_SLEEP_NONE;
 }
cleanup:
 secondary->cleanup();
finish:
 primary->rva00454B5C();primary->rva0045479A();
 return (UpdateSleepTime)BfmeLogicFramesPerSecond;
handled_or_cleanup:
 if(handled)return UPDATE_SLEEP_NONE;
 goto finish;
}
