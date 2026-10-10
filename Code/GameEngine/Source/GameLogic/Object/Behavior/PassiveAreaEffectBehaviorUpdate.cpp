// cl: /O1 /Ob1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /ICode/GameEngine/Source
// stlport
// Native484B6B..484C3C RET0. Constructor484A67 installs secondary
// update table84A438 at complete+10. The preceding owned destructor ends
// at484B6B and the next deleting destructor starts at484C3C, proving extent.
// BF1 clean PassiveAreaEffectBehavior_update.cpp at575ba2b04 is the guide;
// target adds upgrade gating and returns nonzero module delay instead of1.
#include <list>
#include "ascii_string.h"
#include "Common/GameLogicObjectLookupView.h"
enum UpdateSleepTime {UPDATE_SLEEP_INVALID=0,UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff};
class UpgradeTemplate;
class UpgradeCenter {public:const UpgradeTemplate *findUpgrade(const AsciiString&)const;};
extern UpgradeCenter *TheUpgradeCenter;
enum ObjectStatusTypes{status2=2};
class Object {public:
 void *rva0028BD17()const;bool testStatus(ObjectStatusTypes)const;
 bool rva00290D2B(const UpgradeTemplate*)const;
 char pad[0x438];unsigned char dead438;
};
// Existing Object::testStatus uses the enum spelling below.
class Rva00484B6BCheckInterface {public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void s18();virtual void s1C();virtual void s20();virtual void s24();virtual void s28();virtual bool s2C();
};
struct AreaUpdateData {char pad[0x10];unsigned delay;char pad14[0x24-0x14];AsciiString upgrade;};
class Rva00484B6BPrimary {public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void s18();virtual void s1C();virtual void s20();virtual void s24();virtual void s28();virtual void s2C();virtual void s30();virtual void s34();virtual void s38(Object*);
};
extern GameLogic *TheGameLogic;
class PassiveAreaEffectBehavior {public:virtual UpdateSleepTime update();virtual void updateSlot1();};
UpdateSleepTime PassiveAreaEffectBehavior::update()
{
 char *secondary=(char*)this;
 AreaUpdateData *data=*(AreaUpdateData**)(secondary-0xC);
 Object *owner=*(Object**)(secondary-8);
 unsigned delay=data->delay;
 if(!delay)delay=1;
 if(!data->upgrade.isEmpty()){
  const UpgradeTemplate *upgrade=TheUpgradeCenter->findUpgrade(data->upgrade);
  if(!upgrade||!owner->rva00290D2B(upgrade))return (UpdateSleepTime)delay;
 }
 Rva00484B6BCheckInterface *iface=(Rva00484B6BCheckInterface*)owner->rva0028BD17();
 if(iface){if(iface->s2C())return (UpdateSleepTime)delay;}else if(owner->testStatus(status2))return (UpdateSleepTime)delay;
 if(owner->dead438&1)return UPDATE_SLEEP_FOREVER;
 unsigned frame=TheGameLogic->getFrame();
 if(frame-*(unsigned*)(secondary+0x10)>=data->delay){
  ((Rva00484B6BPrimary*)(secondary-0x10))->s34();
  *(unsigned*)(secondary+0x10)=frame;
 }
 _STL::list<int> *ids=(_STL::list<int>*)(secondary+0x14);
 for(_STL::list<int>::iterator it=ids->begin();it!=ids->end();++it){
  Object *affected=TheGameLogic->findObjectByID((ObjectID)*it);
  if(affected)((Rva00484B6BPrimary*)(secondary-0x10))->s38(affected);
 }
 return (UpdateSleepTime)delay;
}
