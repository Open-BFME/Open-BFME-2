// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// Native5D1BA1..5D1CAF full270B RET12, WB15B ownership checklist ctor.
// Preserve the established Rva005D1ADE owner used by its rowed11B dtor
// and40B subclass ctor. Native stores establish primarybase12/plannerC
// and dispute10; dispute region ID4 is read before managerB0 lookup.
// Two label pointers at nativeC75724 and their full strings are target
// facts, represented by resolveOwnershipLabels. All called bodies use
// their current providers. Cached region ID then manager restores native
// load order. BF1 revision575ba2b04743 has no compatible clean donor.
#include "unicode_string.h"
#include "Coord2D.h"
#include "Coord3D.h"
class Rva005CCDDD {public:Rva005CCDDD();virtual ~Rva005CCDDD();int unknown4;void *payload;};
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
struct RetreatWorldView {char unknown[0xb0];LivingWorldRegionManager*regions;};
class GameTextInterface;
extern GameTextInterface*TheGameText;
class RetreatGameText {public:virtual void s00();virtual void s04();virtual void s08();virtual void s0c();virtual void s10();virtual void s14();virtual void s18();virtual void s1c();virtual void s20();virtual void s24();virtual void s28();virtual void s2c();virtual void s30();virtual void s34();virtual void s38();virtual UnicodeString fetch(const char*,bool*);};

class Rva0020EAF6View {public:Rva0020E89C*rva0020EAF6(int);};
struct OwnershipWorldView {char unknown[0xb0];Rva0020EAF6View*regions;};
static const char *const resolveOwnershipLabels[]={"STRATEGICHUD:ResolveRegionOwnershipChecklistItem","STRATEGICHUD:ResolveRegionOwnershipAfterBattleChecklistItem"};
struct OwnershipDisputeView {int unknown;int regionID;};
class Rva005D1ADE:public Rva005CCDDD {public:Rva005D1ADE(void*,void*,int);virtual ~Rva005D1ADE();void*planner;void*dispute;};
Rva005D1ADE::Rva005D1ADE(void*p,void*a,int kind):planner(p),dispute(a) {
 bool exists;
 UnicodeString label=((RetreatGameText*)TheGameText)->fetch(resolveOwnershipLabels[kind],&exists);
 UnicodeString text;
 if(exists) {
  int regionID=((OwnershipDisputeView*)dispute)->regionID;
  Rva0020EAF6View *manager=((OwnershipWorldView*)TheLivingWorldLogic)->regions;
  Rva0020E89C*region=manager->rva0020EAF6(regionID);
  UnicodeString name=Rva005C95ECGet(region);
  text.format(label.str(),name.str(),name.str());
 }
 ((Rva005CCE13*)this)->rva005CCE13(text);
 ((Rva005CCB73*)this)->rva005CCB73((void*)1);
 ((Rva005CCB7B*)this)->rva005CCB7B(false);
 ((Rva005CCB83*)this)->rva005CCB83((void*)20);
}
