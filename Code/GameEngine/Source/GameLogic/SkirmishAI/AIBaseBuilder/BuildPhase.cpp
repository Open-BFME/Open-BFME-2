// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /Ireference/shims/bfme2_ascii
// Native5DCCFB..5DCDD9 complete222; WB15D2AF0 BuildPhase::update.
// stlport
#include <vector>
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"
// WB15D2AF0 names this BuildPhase::update in BuildPhase.cpp; the complete
// native entry5DCCFB..5DCDD9 is222 bytes. Explicit RVA disassembly disproves
// the older false-boundary verdict: the complete entry
// starts with PUSH ESI and agrees with all three loops and the helper call.
// Retain the existing linker-facing Rva005DCE08 member used by AIBase.
// Fields and virtual slots below are target facts; their labels are descriptive.
// The final empty test reads current bounds while its loop uses the end pointer
// captured before the preceding loop, exactly as retail does.
struct Rva002A8AB1Record {char pad[0x16c];int phase;};
#include "../../../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;
extern GameLogic *TheGameLogic;
class Rva004E9378 {public:bool rva004E9378();};
class Rva00573F03 {public:
 virtual void slot00();virtual void slot04();virtual float slot08();
 virtual void slot0c();virtual void slot10();virtual void slot14();
 virtual void slot18(void *,int);virtual void slot1c(int);
 float cost;int retries;AsciiString templateName;int state;char pad14[0x54-0x14];bool required;
 char pad55[3];unsigned deadline;unsigned attempts;
};
class Rva005AD9C0Hit;
class BuildPhase {public:
 bool complete,started,costsSet;_STL::vector<Rva00573F03*> orders;int phase;void *player;
 void update();
 void rva005DCC60();	// 0x005DCC60 (Rva005DCC60.cpp): starts each pending order
};
class Rva005DCE08 : public BuildPhase {public:
 Rva005AD9C0Hit*rva005DCC86(void*);
};
void BuildPhase::update(){
 Rva002A8AB1Record *ai=TheSkirmishAIManager->rva002A8AB1(player);
 if(phase>ai->phase)return;
 if(!started){rva005DCC60();started=true;}
 if(phase<ai->phase && !complete && !costsSet){
  Rva00573F03 **last=orders.end();
  for(Rva00573F03 **it=orders.begin();it!=last;++it){if((*it)->state==0)(*it)->cost=(*it)->slot08();}
  costsSet=true;
 }
 Rva00573F03 **last=orders.end();
 for(Rva00573F03 **it=orders.begin();it!=last;++it){
  if((*it)->state==3 && (*it)->attempts<10 && TheGameLogic->getFrame()>=(*it)->deadline){
   (*it)->slot1c(0);(*it)->retries=0;(*it)->slot18(player,0);
  }
 }
 if(!complete){
  if(!orders.empty()){
   for(Rva00573F03 **it=orders.begin();it!=last;++it){
    if((*it)->required && !((Rva004E9378*)*it)->rva004E9378())return;
   }
  }
  complete=true;
 }
}

class ThingTemplate;
class ThingFactory;
extern ThingFactory*TheThingFactory;
#include "../../../../Include/Common/ThingFactory.h"
#include "../../../../Include/Common/BuildAssistantClass.h"
extern BuildAssistant*TheBuildAssistant;
// Native5DCC86..5DCCFB full117 RET4; BuildPhase vector4/8 and
// order template-name0C are read directly from retail. AITactic/AIBase
// lookup siblings guide the registry and build-compatibility calls; no clean
// BFME1/ZH BuildPhase source exists at f98983a7d3bb. Preserve the established
// opaque input and hit-pointer ABI: the registry consumes the input as a
// string key and the outer AIBase caller only tests the returned pointer.
// Native loop deliberately returns the LAST compatible unfinished order.
Rva005AD9C0Hit*Rva005DCE08::rva005DCC86(void*key) {
 Rva00573F03*selected=0;
 for(Rva00573F03**it=orders.begin();it!=orders.end();++it) {
  Rva00573F03*order=*it;
  if(!((Rva004E9378*)order)->rva004E9378()) {
   const ThingTemplate*first=TheThingFactory->findTemplate(order->templateName);
   const ThingTemplate*second=TheThingFactory->findTemplate(*((const AsciiString*)key));
   if(first&&second&&TheBuildAssistant->rva00391AA1(first,second))selected=order;
  }
 }
 return (Rva005AD9C0Hit*)selected;
}
