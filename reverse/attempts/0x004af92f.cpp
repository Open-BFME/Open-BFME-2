// ?update@RespawnUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.995 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// WB RespawnUpdate::update and native4AF92F..4AFB01 establish identity.
// Factory4AF8F6/ctor4AF096 prove44B module and secondary update at10;
// vtableC556A4 entry0 is VA8AF92F. BF1 RespawnUpdate9cbfb551 condition
// helpers plus matched BFME2 death/rule units guide state semantics.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
enum UpdateSleepTime {UPDATE_SLEEP_FOREVER=0x3fffffff};
enum DisabledType;
enum ObjectStatusTypes;
class Player;class ExitInterface;class BodyModuleInterface;class FXList;
template<int N> class RespawnAISlots:public RespawnAISlots<N-1> {public:virtual void gap(char (*)[N])=0;};
template<> class RespawnAISlots<0> {};
class AIUpdateInterface:public RespawnAISlots<110> {public:virtual bool isAutoDock()=0;int rva00260DED() const;};
class Object {public:
 ExitInterface *getObjectExitInterface() const;
 void restoreObjectToWorld(const Coord3D *);
 void rva001E42F2(const int *);
 void rva001E431E(const int *);
 void setStatus(ObjectStatusTypes,bool);
 bool clearDisabled(DisabledType);
 void setDisabledUntil(DisabledType,unsigned);
 Player *getControllingPlayer() const;
 __forceinline const Coord3D *getPosition() const {return &position;}
 char pad00[0x38];Coord3D position;char pad44[0x78-0x44];ObjectID producer;
 char pad7C[0x254-0x7C];BodyModuleInterface *body;AIUpdateInterface *ai;
 char pad25C[0x45C-0x25C];int handle;
};
class ExitInterface {public:
 virtual void slot0()=0;virtual void slot1()=0;virtual void exitObject(Object *,bool)=0;
 virtual void slot3()=0;virtual void slot4()=0;virtual void slot5()=0;virtual void slot6()=0;virtual void slot7()=0;virtual void slot8()=0;
 virtual void getExitPosition(Coord3D *,bool)=0;
};
class BodyModuleInterface {public:
virtual void slot0()=0;
virtual void slot1()=0;
virtual void slot2()=0;
virtual void slot3()=0;
virtual void slot4()=0;
virtual void slot5()=0;
virtual void slot6()=0;
virtual void slot7()=0;
virtual void slot8()=0;
virtual void slot9()=0;
virtual void slot10()=0;
virtual void slot11()=0;
virtual void slot12()=0;
virtual void slot13()=0;
virtual void slot14()=0;
virtual void slot15()=0;
virtual void slot16()=0;
virtual void slot17()=0;
virtual void slot18()=0;
virtual void slot19()=0;
virtual void slot20()=0;
virtual void setInitialHealth(float,bool)=0;
};
class FXList {public:static void doFXObj(const FXList *,const Object *,const Object *);};
class RespawnUpdateModuleData {public:
 char pad00[0x58];int conditions58[19];int conditionsA4[19];const FXList *deathFX,*reviveFX;char padF8[8];unsigned reviveTime;
};
class ObjectModule {public:virtual ~ObjectModule();const RespawnUpdateModuleData *data;Object *object;};
class BehaviorModuleInterface {public:virtual void slot0()=0;};
class BehaviorModule:public ObjectModule,public BehaviorModuleInterface {public:virtual ~BehaviorModule();};
class UpdateModuleInterface {public:virtual UpdateSleepTime update()=0;};
class UpdateModule:public BehaviorModule,public UpdateModuleInterface {public:virtual ~UpdateModule();protected:void setWakeFrame(Object *,UpdateSleepTime);private:unsigned nextWake;int index,reserved;};
class RespawnUpdate:public UpdateModule {public:
 virtual UpdateSleepTime update();
 Object *searchForSuitableSpawnAtObject();
 float health;unsigned at24,at28,state;ObjectID spawnAt;unsigned at34,at38,at3C;bool at40,at41;
};
class PlayerList {public:__forceinline Player *getLocalPlayer() const{return local;}char pad[0x10];Player *local;};extern PlayerList *ThePlayerList;
class ControlBar {public:char pad[0x28];bool dirty;};extern ControlBar *TheControlBar;
// ?update@RespawnUpdate@@UAE?AW4UpdateSleepTime@@XZ present-unmatched
UpdateSleepTime RespawnUpdate::update() {
 Object *obj=object;
 const RespawnUpdateModuleData *d=data;
 switch(state) {
 case 2:return UPDATE_SLEEP_FOREVER;
 case 3: {
  Object *at=TheGameLogic->findObjectByID(spawnAt);
  if(!at) at=searchForSuitableSpawnAtObject();
  Coord3D pos={obj->position.x,obj->position.y,obj->position.z};
  if(at) {
   pos=*at->getPosition();
   ExitInterface *exit=at->getObjectExitInterface();
   if(exit) exit->getExitPosition(&pos,true);
  }
  obj->restoreObjectToWorld(&pos);
  obj->rva001E431E(d->conditions58);
  FXList::doFXObj(d->reviveFX,obj,0);
  obj->setDisabledUntil((DisabledType)4,TheGameLogic->getFrame()+d->reviveTime);
  state=4;
  obj->body->setInitialHealth(health*100.0f,false);
  at34=(unsigned)-1;at38=(unsigned)-1;
  if(ThePlayerList->getLocalPlayer()==obj->getControllingPlayer()) TheControlBar->dirty=true;
  (void)obj->getControllingPlayer();
  return (UpdateSleepTime)d->reviveTime;
 }
 case 4: {
  obj->rva001E42F2(d->conditions58);
  obj->rva001E42F2(d->conditionsA4);
  obj->setStatus((ObjectStatusTypes)3,false);
  obj->clearDisabled((DisabledType)4);
  state=0;
  Object *at=TheGameLogic->findObjectByID(obj->producer);
  AIUpdateInterface *ai=object->ai;
  if(at && ai && (ai->isAutoDock() || ai->rva00260DED()==16)) {
   ExitInterface *exit=at->getObjectExitInterface();
   if(exit) {
    int h=obj->handle;
    exit->exitObject(obj,false);
    if(h) TheGameLogic->rva0023D0C2(obj,h);
   }
  }
  return UPDATE_SLEEP_FOREVER;
 }
 default:return UPDATE_SLEEP_FOREVER;
 }
}
