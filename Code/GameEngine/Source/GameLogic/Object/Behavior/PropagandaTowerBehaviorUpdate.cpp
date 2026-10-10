// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE /ICode/GameEngine/Source/Common
// ?update@PropagandaTowerBehavior@@UAE?AW4UpdateSleepTime@@XZ
// Retail 0x00481C0C..0x00481D4C, 320 bytes. Reference: Zero Hour
// GeneralsMD PropagandaTowerBehavior.cpp update, BFME1 revision 575ba2b04.
// Target vtable/neighbour class evidence: pool key, ctor and slot13
// removeAllInfluence / slot14 doScan. Native entry is the +0x10 update
// interface: module data at this-0x0C, owner at this-8, frame at this+0x14,
// tracker list at this+0x18; its primary vtable starts at this-0x10.
// Target Object disability+0x1C8, containment+0x274, dead byte+0x438,
// and template kind word+0x10C are established by this body's accesses.
// Kind bit meanings are kept unspecified. Splitting its four-bit mask
// into low-byte and high-byte groups reproduces retail's test cl/test ch.
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
enum ObjectStatusTypes { STATUS_BUILDING=2,STATUS_SOLD=19 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1,UPDATE_SLEEP_FOREVER=0x3fffffff };
template<int N>class BitFlags {public:enum BogusInitType{kInit=0};BitFlags(BogusInitType,int);bool any()const;bool test(const void *)const;unsigned words[1];};
struct ObjectTemplate {char pad[0x10c];unsigned kind;};
class Object {public:bool testStatus(ObjectStatusTypes)const;char p00[4];ObjectTemplate *tmpl;char p08[0x1c8-8];BitFlags<11>disabled;char p1cc[0x274-0x1cc];Object*containedBy;char p278[0x438-0x278];unsigned char dead;};
class PropagandaTowerBehaviorModuleData {public:char pad[0xc];unsigned scanDelay;};
class ObjectTracker {public:virtual ~ObjectTracker();ObjectID objectID;ObjectTracker*next;};
class Rva00481C0CPrimary {public:
virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void s18();virtual void s1C();virtual void s20();virtual void s24();virtual void s28();virtual void s2C();virtual void s30();virtual void removeAllInfluence();virtual void doScan();virtual void effectLogic(Object*,bool,const PropagandaTowerBehaviorModuleData*);
};
class PropagandaTowerBehavior {public:
virtual UpdateSleepTime update();
char pad04[0x14-4];unsigned lastScanFrame;ObjectTracker *insideList;
const PropagandaTowerBehaviorModuleData *data()const{return *(const PropagandaTowerBehaviorModuleData *const *)((const char*)this-0xc);}
Object *owner()const{return *(Object *const *)((const char*)this-8);}
Rva00481C0CPrimary *primary(){return (Rva00481C0CPrimary*)((char*)this-0x10);}
};
UpdateSleepTime PropagandaTowerBehavior::update()
{
 const PropagandaTowerBehaviorModuleData *modData=data();
 Object *self=owner();
 if(self->testStatus(STATUS_BUILDING))return UPDATE_SLEEP_NONE;
 if(self->testStatus(STATUS_SOLD)){primary()->removeAllInfluence();return UPDATE_SLEEP_FOREVER;}
 if(self->dead&1)return UPDATE_SLEEP_FOREVER;
 if(self->disabled.any()) {
  BitFlags<11> allButHeld(BitFlags<11>::kInit,3);
  allButHeld.words[0]=~allButHeld.words[0];
  if(allButHeld.test(&self->disabled)){primary()->removeAllInfluence();return UPDATE_SLEEP_NONE;}
 }
 if(self->containedBy&&self->containedBy->containedBy){primary()->removeAllInfluence();return UPDATE_SLEEP_NONE;}
 unsigned currentFrame=TheGameLogic->getFrame();
 if(currentFrame-lastScanFrame>=modData->scanDelay){primary()->doScan();lastScanFrame=currentFrame;}
 ObjectTracker *prev=0;
 for(ObjectTracker *curr=insideList,*next;curr;curr=next){
  next=curr->next;
  Object *obj=TheGameLogic->findObjectByID(curr->objectID);
  if(obj&&((obj->tmpl->kind&0xa0)||(obj->tmpl->kind&0x300))){
   primary()->effectLogic(obj,true,data());prev=curr;
  }else{
   if(prev)prev->next=next;else insideList=next;
   ::delete curr;
  }
 }
 return UPDATE_SLEEP_NONE;
}
