// ?update@GettingBuiltBehaviorUpdateReceiver@@QAE?AW4UpdateSleepTime@@XZ
// partial score=1.0 date=2026-10-09
// cl: /O1 /Ob2 /arch:SSE /DNDEBUG /MD /EHsc
// BF1f989 GettingBuiltBehavior_update.cpp is the semantic guide.
// Native454DF9..455050 and WB116A1E0 prove +10 update-interface receiver,
// data/object at -C/-8, primary callbacks and BF2 progress/path-map additions.
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
 bool rva0028FEA7(float,const Object *,unsigned int);
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
extern int g_Va00DBA4E4;
class GettingBuiltUpdateSecondary {
public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();
 virtual void v4();virtual void cleanup();virtual bool active();
};
class GettingBuiltBehavior {
 friend class GettingBuiltBehaviorUpdateReceiver;
 bool rva004541AB();bool rva00453124();
public:void rva00454B5C();void rva0045479A();
};
struct GettingBuiltUpdateData {
 unsigned char pad[0x20];union {float duration;unsigned int durationBits;};
 unsigned char pad24[4];const WeaponTemplate *weapon;bool rebuild;
};
class GettingBuiltBehaviorUpdateReceiver {
public:UpdateSleepTime update();
};
UpdateSleepTime GettingBuiltBehaviorUpdateReceiver::update()
{
 const GettingBuiltUpdateData *data=*(const GettingBuiltUpdateData **)((char *)this-0xc);
 Object *obj=*(Object **)((char *)this-8);
 bool dead=(obj->privateStatus&1)!=0;
 if(*((bool *)this+0x21)!=dead && data->rebuild){
   *((bool *)this+0x21)=dead;
   *(unsigned int *)((char *)this+0x18)=data->durationBits;
   if(dead)*((bool *)this+0x20)=true;
 }
 int out=0;
 bool busy=!*((bool *)this+0x25) && obj->rva0028C264(&out,4);
 GettingBuiltBehavior *primary=(GettingBuiltBehavior *)((char *)this-0x10);
 bool handled=primary->rva004541AB();
 GettingBuiltUpdateSecondary *secondary=(GettingBuiltUpdateSecondary *)((char *)this+0x10);
 bool active=secondary->active();
 bool worker=false;
 if(obj->builder!=obj->id && !*((bool *)this+0x2c)){
   Object *builder=TheGameLogic->findObjectByID(obj->builder);
   if(builder && !(builder->tmplate->kind[4]&0x10000000))worker=true;
 }
 if(!dead){
   if(data->duration>=0.0f && busy && !*((bool *)this+0x26))goto cleanup;
   if(!active || worker || primary->rva00453124())goto handled_or_cleanup;
   if(!*((bool *)this+0x26) && handled)return UPDATE_SLEEP_NONE;
   if(!*((bool *)this+0x24) && obj->progress>=75.0f){
     *((bool *)this+0x24)=true;
     if(data->weapon)TheWeaponStore->createAndFireTempWeapon(data->weapon,obj,&obj->position);
   }
   GettingBuiltUpdateBody *body=obj->body;
   if(body){
     float health=body->maxHealth()/(float)*(unsigned int *)((char *)this+0x1c);
     if(obj->tmplate->kind[5]&0x20000000){
       float minimum=body->maxHealth()*0.2f;
       if(body->health()>=minimum && body->health()<minimum+health){
         TheAI->pathfinder->RemoveObjectFromPathfindMap(obj);
         TheAI->pathfinder->AddObjectToPathfindMap(obj);
         float orientation=obj->orientation;
         const ThingTemplate *tmplate=obj->tmplate;
         Player *player=obj->getControllingPlayer();
         TheBuildAssistant->moveObjectsForConstruction(tmplate,&obj->position,orientation,player);
       }
     }
     obj->rva0028FEA7(health,obj,2);
     obj->progress=body->fraction()*100.0f;
     if(!*((bool *)this+0x25))body->clearRecent();
   }
   primary->rva00454B5C();return UPDATE_SLEEP_NONE;
 }
cleanup:
 secondary->cleanup();
finish:
 primary->rva00454B5C();primary->rva0045479A();
 return (UpdateSleepTime)g_Va00DBA4E4;
handled_or_cleanup:
 if(handled)return UPDATE_SLEEP_NONE;
 goto finish;
}
