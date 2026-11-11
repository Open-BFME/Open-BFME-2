// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
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
class Rva005CCDDD {public:Rva005CCDDD();virtual ~Rva005CCDDD();virtual void slot04() = 0;virtual void clickSlot08();virtual void slot0C() = 0;virtual void slot10() = 0;virtual void slot14() = 0;virtual void slot18() = 0;int unknown4;void *payload;};
class Rva005D1D38Second {public:virtual void observerSlot0(int) = 0;virtual void observerSlot1(void*,unsigned) = 0;~Rva005D1D38Second(){} };
class Rva00318C32Ret;
class Rva0020E89C {public:UnicodeString rva0020E89C();};
UnicodeString Rva005C95ECGet(Rva0020E89C*);
namespace StrategicInGameUI {UnicodeString GetDisplayName(void*);}
struct Rva002BA8F1Listener;
#include "../../../../Include/Common/Rva005A0B4CList.h"
#include "../../../../Include/GameClient/Rva005CCE13.h"
#include "../../../../Include/GameClient/Rva005CCB73.h"
#include "../../../../Include/Common/Rva005CCB7B.h"
#include "../../../../Include/Common/Rva005CCB83.h"
class Rva005CCB90 {public:void rva005CCB90(const void*);};
class Vector3;
#include "../../../../Include/Common/Rva002BF4F3.h"
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class LivingWorld;extern LivingWorld*TheLivingWorld;
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
 ((Rva002BF4F3*)TheLivingWorld)->rva002BF5B0((const Vector3*)&input->point,(Vector3*)&position);
 ((Rva005CCB90*)this)->rva005CCB90(&position);
}

#include "../../../../Include/Common/Rva005CCB5B.h"
class Rva002D3627Host {public:void rva002BF09E(const Coord3D*);};
// NativeC75734slot08 ->5D1CD3..5D1D38/101B RET0; WB15B6B50
// confirms the empty base hook then guarded projection/point placement.
void Rva005D1D38::clickSlot08() {
 Rva005CCDDD::clickSlot08();
 if(!battle)return;
 ((Rva005CCB5B*)this)->rva005CCB5B();
 const Coord2D&src=((ChecklistBattleView*)battle)->point;Coord2D point;point.x=src.x;point.y=src.y;
 Coord3D position;position.x=point.x;position.y=point.y;position.z=0;
 ((Rva002BF4F3*)planner)->rva002BF5B0((const Vector3*)&point,(Vector3*)&position);
 ((Rva002D3627Host*)planner)->rva002BF09E(&position);
}
