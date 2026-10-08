// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /ICode/GameEngine/Source/Common
// BFME1 9cbfb551 SpecialPowerModule_startPowerRecharge.cpp supplies the
// template/object/player guards and shared timer semantics. WB1488100 names
// SpecialPowerUpdateModule::startPowerRecharge and native58943A proves this
// adjusted interface receiver, percent ABI, target offsets and attribute path.
// Keep neutral owner pending full class/receiver reconciliation.
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Player;
class Object {public: Player *getControllingPlayer() const;bool rva0028C15E(int,float *,int,int);};
class Overridable {public:const Overridable *friend_getFinalOverride() const;};
class SpecialPowerTemplate;
class Rva002AC6B1PlayerTimers {public:void resetOrStart(const SpecialPowerTemplate *);};
class Rva002AA0B1FloatField {public:float get() const;};
struct RechargeTemplateView {char prefix[0x20];unsigned int duration;char pad[0x59-0x24];bool shared;};
struct RechargeModuleDataView {char prefix[8];const SpecialPowerTemplate *power;};
class Rva005890A6 {
public:
 virtual void v00(); virtual void v01(); virtual float progress() const;
 virtual void v03(); virtual void v04(); virtual void v05();
 virtual const SpecialPowerTemplate *powerTemplate() const;
 void rva0058943A(float percent);
private:unsigned int availableOnFrame;
};
void Rva005890A6::rva0058943A(float percent) {
 const RechargeModuleDataView *data=*(const RechargeModuleDataView **)((char *)this-0x20);
 if(!data->power)return;
 Object *obj=*(Object **)((char *)this-0x1C);
 if(!obj)return;
 Player *player=obj->getControllingPlayer();
 if(!player)return;
 const SpecialPowerTemplate *original=data->power;
 if(((const RechargeTemplateView *)((const Overridable *)original)->friend_getFinalOverride())->shared) {
  ((Rva002AC6B1PlayerTimers *)player)->resetOrStart(original);
 } else {
  float modifier=1.0f;
  obj->rva0028C15E(12,&modifier,0,1);
  float factor=1.0f+((const Rva002AA0B1FloatField *)player)->get();
  unsigned int duration=(unsigned int)(((const RechargeTemplateView *)((const Overridable *)powerTemplate())->friend_getFinalOverride())->duration*factor*modifier);
  if(percent<1.0f) {
   float current=progress();
   if(current==0.0f)return;
   current-=percent;
   if(current<0.0f)current=0.0f;
   availableOnFrame=TheGameLogic->getFrame()+(unsigned int)((1.0f-current)*duration);
  } else availableOnFrame=TheGameLogic->getFrame()+duration;
 }
}
