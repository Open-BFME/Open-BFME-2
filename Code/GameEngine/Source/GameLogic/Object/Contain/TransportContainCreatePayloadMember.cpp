// cl: /O1 /G7 /arch:SSE /Oy- /MD /DNDEBUG
// Native complete466FE0..4670D6 RET20,246B. WB lead names
// TransportContain::createPayloadMember; native ctor468559 installs final
// +FC vtable VA C47834 whose slot0 is466FE0. The owned createPayload4670D6
// forwards template, contain view, parent, name text and a mode word there.
// BF1@575ba2b TransportContain.cpp supplies this payload-creator relationship;
// ZH TransportContain supplies payload creation purpose, not BF2 layouts.
// Target offsets/status bit55 and every numbered virtual call are independently
// witnessed. Numbered methods are ABI views, not original EA names; this body
// does not access its own receiver or establish complete TransportContain extent.
// Both direct callees are owned: native CRT memset6291AE and ThingFactory
// newObject2D0A23. Canonical GlobalData/AI/ThingFactory globals; no new pins.
// Inline target-prefix getters preserve native team and parent/body lifetimes.
#include <string.h>
class Object;class Team;class ThingTemplate;
struct CreateMask {unsigned words[4];CreateMask(){memset(words,0,sizeof(words));}};
class ThingFactory {public:Object *newObject(const ThingTemplate*,Team*,const CreateMask*,bool);};
extern ThingFactory *TheThingFactory;
class GlobalData;extern GlobalData *TheWritableGlobalData;
struct PayloadGlobalView {char prefix[0xD45];bool flagD45;};
class AI;extern AI *TheAI;
struct PayloadAiDataView {char prefix[0xBB];bool flagBB;};
struct PayloadAiView {char prefix[0x18];PayloadAiDataView *data;};
struct PayloadTemplateView {char prefix[0x109];unsigned char flag109;char pad10A[9];unsigned char flag113;};
class PayloadInitView {public:virtual void slot0();virtual void slot1();};
class PayloadModuleView {public:virtual void slot0();virtual void slot1();virtual void slot2();virtual PayloadInitView *slot3();};
struct PayloadBehaviorView {char prefix[0xC];PayloadModuleView interface;};
class PayloadBodyView {public:
#define S(n) virtual void slot##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30) S(31) S(32)
#undef S
 virtual void slot33(bool);virtual bool slot34();
};
struct PayloadObjectView {char prefix[0x244];PayloadBehaviorView **modules;char pad248[0xC];PayloadBodyView *body;char pad258[0xAC];Team *team;Team *getTeam()const{return team;}PayloadBodyView *getBody()const{return body;}};
class PayloadContainView {public:
#define S(n) virtual void slot##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30)
#undef S
 virtual void *slot31();
#define S(n) virtual void slot##n();
 S(32) S(33) S(34) S(35) S(36) S(37)
#undef S
 virtual bool slot38(Object*,int,bool);virtual void slot39(Object*);
};
class TransportContain {public:virtual Object *createPayloadMember(const ThingTemplate*,PayloadContainView*,Object*,const char*,int);};
Object *TransportContain::createPayloadMember(const ThingTemplate *what,PayloadContainView *contain,Object *parent,const char *name,int initial) {
 CreateMask status;
 if(contain->slot31()&&!((const PayloadGlobalView*)TheWritableGlobalData)->flagD45&&!(((const PayloadTemplateView*)what)->flag113&4)&&!(((const PayloadTemplateView*)what)->flag109&4)&&((const PayloadAiView*)TheAI)->data->flagBB) ((unsigned char*)status.words)[6]|=0x80;
 Object *made=TheThingFactory->newObject(what,((PayloadObjectView*)parent)->getTeam(),&status,false);
 for(PayloadBehaviorView **m=((PayloadObjectView*)made)->modules;*m;++m) {
  PayloadInitView *hook=(*m)->interface.slot3();if(hook)hook->slot1();
 }
 if(contain->slot38(made,initial,false)) {
  PayloadBodyView *body=((PayloadObjectView*)parent)->getBody();
  if(body&&body->slot34()) {PayloadBodyView *childBody=((PayloadObjectView*)made)->body;if(childBody)childBody->slot33(true);}
  contain->slot39(made);
 }
 return made;
}
