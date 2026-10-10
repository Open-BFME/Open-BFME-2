// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// Native5D1DCB..5D1F14 full329B RET8; WB15B6700 names ResolveBattleChecklistItem.
// Existing87B destructor5D1D38 and scalar destructor establish neutral owner.
// Primarybase12, two-callback observerC, planner10/battle14, region24 and
// point28 are independently measured target accesses, not donor layout.
// A real three-float value constructor evaluates x/y inputs together and
// reproduces native two-XMM scheduling; separate assignments reuse XMM0.
// Existing providers handle observer registration, Unicode title, marker
// projection and checklist setters. No clean compatible BF1/ZH body at575ba2b04743.
#include "unicode_string.h"
#include "Coord2D.h"
#include "Coord3D.h"
class Rva005CCDDD {public:Rva005CCDDD();virtual ~Rva005CCDDD();virtual void slot04();virtual void clickSlot08();virtual void slot0C();virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1C(void*);int unknown4;void *payload;};
class Rva005D1D38Second {public:virtual void observerSlot0(int);virtual void observerSlot1(void*,unsigned);~Rva005D1D38Second(){} };
class Rva00318C32Ret;
class Rva00318C79Owner {public:Rva00318C32Ret*rva00318C32();};
class Rva0020E89C {public:UnicodeString rva0020E89C();};
UnicodeString Rva005C95ECGet(Rva0020E89C*);
namespace StrategicInGameUI {UnicodeString GetDisplayName(void*);}
struct Rva002BA8F1Listener;
class Rva005A0B4CList {public:void append(Rva002BA8F1Listener*);};
class Rva005CCE13 {public:void rva005CCE13(const UnicodeString&);};
class Rva005CCB73 {public:void rva005CCB73(void*);};
class Rva005CCB7B {public:void rva005CCB7B(bool);};
class Rva005CCB83 {public:void rva005CCB83(void*);};
class Rva005CCB90 {public:void rva005CCB90(const void*);};
class LivingWorldRegionManager {public:bool GetRegionCenterPoint(Rva0020E89C*,Coord2D*);};
class Rva002BF5B0Maker {public:void rva002BF5B0(void*,void*);};
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class LivingWorld;extern LivingWorld*TheLivingWorld;
struct RetreatWorldView {char unknown[0xb0];LivingWorldRegionManager*regions;};
class GameTextInterface;
extern GameTextInterface*TheGameText;
class RetreatGameText {public:virtual void s00();virtual void s04();virtual void s08();virtual void s0c();virtual void s10();virtual void s14();virtual void s18();virtual void s1c();virtual void s20();virtual void s24();virtual void s28();virtual void s2c();virtual void s30();virtual void s34();virtual void s38();virtual UnicodeString fetch(const char*,bool*);};

struct ChecklistMarkerPosition:Coord3D{ChecklistMarkerPosition(float a,float b,float c){x=a;y=b;z=c;}ChecklistMarkerPosition(const Coord2D&p){x=p.x;y=p.y;z=0;}};
struct ChecklistBattleView {char unknown[0x24];Rva0020E89C*region;Coord2D point;};
class Rva005D1D38:public Rva005CCDDD,public Rva005D1D38Second {public:Rva005D1D38(void*,void*);virtual ~Rva005D1D38();virtual void clickSlot08();void*planner;void*battle;};
Rva005D1D38::Rva005D1D38(void*p,void*a):planner(p),battle(a) {
 ChecklistBattleView*input=(ChecklistBattleView*)a;
 ((Rva005A0B4CList*)((char*)input+8))->append((Rva002BA8F1Listener*)static_cast<Rva005D1D38Second*>(this));
 Rva0020E89C*region=((ChecklistBattleView*)battle)->region;
 UnicodeString text;
 bool exists;
 UnicodeString label=((RetreatGameText*)TheGameText)->fetch("STRATEGICHUD:ResolveBattleChecklistItem",&exists);
 if(exists)text.format(label.str(),region->rva0020E89C().str());
 ((Rva005CCE13*)this)->rva005CCE13(text);
 ((Rva005CCB73*)this)->rva005CCB73((void*)1);
 ((Rva005CCB7B*)this)->rva005CCB7B(false);
 ((Rva005CCB83*)this)->rva005CCB83((void*)18);
 ChecklistMarkerPosition position(input->point.x,input->point.y,0);
 ((Rva002BF5B0Maker*)TheLivingWorld)->rva002BF5B0(&input->point,&position);
 ((Rva005CCB90*)this)->rva005CCB90(&position);
}

class Rva005CCB5B {public:void rva005CCB5B();};
class Rva002D3627Host {public:void rva002BF09E(const Coord3D*);};
// NativeC75734slot08 ->5D1CD3..5D1D38/101B RET0; WB15B6B50
// confirms the empty base hook then guarded projection/point placement.
void Rva005D1D38::clickSlot08() {
 Rva005CCDDD::clickSlot08();
 if(!battle)return;
 ((Rva005CCB5B*)this)->rva005CCB5B();
 const Coord2D&src=((ChecklistBattleView*)battle)->point;Coord2D point;point.x=src.x;point.y=src.y;
 Coord3D position;position.x=point.x;position.y=point.y;position.z=0;
 ((Rva002BF5B0Maker*)planner)->rva002BF5B0(&point,&position);
 ((Rva002D3627Host*)planner)->rva002BF09E(&position);
}
