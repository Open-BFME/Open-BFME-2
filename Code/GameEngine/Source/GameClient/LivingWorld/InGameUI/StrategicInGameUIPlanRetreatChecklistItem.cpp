// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// Native5D2184..5D232D complete425B RET8. WB15B2C10 names
// StrategicInGameUI::PlanRetreatChecklistItem constructor and records its
// text-formatting, observer registration and map-position purpose. Keep
// the existing Rva005D2111 owner spelling used by ctor/dtor providers.
// Target primary12B base, secondary5-slot observer atC, planner10/army14
// are independently established by constructor stores, both native vtables
// and the exact43B subclass constructor at576FD3. Observer callbacks are
// declared opaque; the secondary table has no destructor slot.
// Region manager local preserves native receiver evaluation before arguments.
// No compatible clean ZH/BF1 constructor was found at BF1 revision575ba2b04743.
#include "unicode_string.h"
#include "Coord2D.h"
#include "Coord3D.h"
class Rva005CCDDD {public:Rva005CCDDD();virtual ~Rva005CCDDD();int unknown4;void *payload;};
class SecondBase005D2111 {public:virtual void observerSlot0(int);virtual void observerSlot1(void*,unsigned);virtual void observerSlot2(void*);virtual void observerSlot3(void*);virtual void observerSlot4(void*);~SecondBase005D2111(){} };
class Rva00318C32Ret;
class Rva00318C79Owner {public:Rva00318C32Ret*rva00318C32();};
class Rva0020E89C;
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
class Rva005D2111:public Rva005CCDDD,public SecondBase005D2111 {public:Rva005D2111(void*,void*);virtual ~Rva005D2111();void*planner;void*army;};
Rva005D2111::Rva005D2111(void*p,void*a):planner(p),army(a) {
 ((Rva005A0B4CList*)((char*)army+8))->append((Rva002BA8F1Listener*)static_cast<SecondBase005D2111*>(this));
 Rva0020E89C*region=(Rva0020E89C*)((Rva00318C79Owner*)army)->rva00318C32();
 UnicodeString text;
 bool exists;
 UnicodeString label=((RetreatGameText*)TheGameText)->fetch("STRATEGICHUD:PlanRetreatChecklistItem",&exists);
 if(exists) {
  UnicodeString regionName=Rva005C95ECGet(region);
  text.format(label.str(),regionName.str(),StrategicInGameUI::GetDisplayName(army).str(),regionName.str());
 }
 ((Rva005CCE13*)this)->rva005CCE13(text);
 ((Rva005CCB73*)this)->rva005CCB73((void*)1);
 ((Rva005CCB7B*)this)->rva005CCB7B(false);
 ((Rva005CCB83*)this)->rva005CCB83((void*)19);
 Coord2D center;
 LivingWorldRegionManager *manager=((RetreatWorldView*)TheLivingWorldLogic)->regions;
 manager->GetRegionCenterPoint(region,&center);
 Coord3D position;position.x=center.x;position.y=center.y;position.z=0;
 ((Rva002BF5B0Maker*)TheLivingWorld)->rva002BF5B0(&center,&position);
 ((Rva005CCB90*)this)->rva005CCB90(&position);
}
