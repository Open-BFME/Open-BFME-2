// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common
// Native5DCCFB..5DCDD9 complete222; WB15D2AF0 BuildPhase::update.
// stlport
#include <vector>
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
class Rva002A8F24 {public:Rva002A8AB1Record *rva002A8AB1(void *);};
extern Rva002A8F24 *g_00DFEEF8;
extern GameLogic *TheGameLogic;
class Rva005DCC60 {public:void rva005DCC60();};
class Rva004E9378 {public:bool rva004E9378();};
class Rva00573E7C {public:
 virtual void slot00();virtual void slot04();virtual float slot08();
 virtual void slot0c();virtual void slot10();virtual void slot14();
 virtual void slot18(void *,int);virtual void slot1c(int);
 float cost;int retries;char pad0c[4];int state;char pad14[0x54-0x14];bool required;
 char pad55[3];unsigned deadline;unsigned attempts;
};
class Rva005DCE08 {public:
 bool complete,started,costsSet;_STL::vector<Rva00573E7C*> orders;int phase;void *player;
 void rva005DCCFB();
};
void Rva005DCE08::rva005DCCFB(){
 Rva002A8AB1Record *ai=g_00DFEEF8->rva002A8AB1(player);
 if(phase>ai->phase)return;
 if(!started){((Rva005DCC60*)this)->rva005DCC60();started=true;}
 if(phase<ai->phase && !complete && !costsSet){
  Rva00573E7C **last=orders.end();
  for(Rva00573E7C **it=orders.begin();it!=last;++it){if((*it)->state==0)(*it)->cost=(*it)->slot08();}
  costsSet=true;
 }
 Rva00573E7C **last=orders.end();
 for(Rva00573E7C **it=orders.begin();it!=last;++it){
  if((*it)->state==3 && (*it)->attempts<10 && TheGameLogic->getFrame()>=(*it)->deadline){
   (*it)->slot1c(0);(*it)->retries=0;(*it)->slot18(player,0);
  }
 }
 if(!complete){
  if(!orders.empty()){
   for(Rva00573E7C **it=orders.begin();it!=last;++it){
    if((*it)->required && !((Rva004E9378*)*it)->rva004E9378())return;
   }
  }
  complete=true;
 }
}
