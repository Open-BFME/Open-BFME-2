// cl: /O1 /G7 /MD /EHsc
// Native5E1BD5..5E1C6F complete154B destructor. Primary0 counted base8,
// observer8 and callbackC interfaces proven by native vtable stores/dispatch;
// owner10, army14, owned slot18 and counted help1C proven by neighbouring methods.
#include "../../Include/Common/Rva0007DF07.h"
class Rva0083702CObserver {public:
 // Retail table 0x00C3702C holds the shared `ret 4` body 0x0047A69C in slot 0.
 virtual void observer0(int){}virtual void observer1(void*,void*){};virtual void observer2()=0;virtual void observer3()=0;virtual void observer4()=0;
 ~Rva0083702CObserver(){}
};
class Rva0086E330Callback {public:
 virtual void callback0(int){}virtual void callback1(int){}virtual void callback2(int){}virtual void callback3(int){}virtual void callback4(int){}
 ~Rva0086E330Callback(){}
};
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
struct DestructorHelpRef {TargetRef00217D4C *ptr;DestructorHelpRef():ptr(0){}~DestructorHelpRef(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}};
class Rva005E197E {public:void rva005E197E();};
class CreateAHeroData;
#include "../../Include/Common/Rva002B7250.h"
namespace StrategicInGameUI {class RegionDetailsArmiesPage {public:class Impl;};}
class StrategicInGameUI::RegionDetailsArmiesPage::Impl {public:void rva005E19CA(int);};
class Rva005E1BD5;
struct Rva005E1BD5Owner {char unknown00[0x24];Rva005E1BD5 *selected,*pending;};
class Rva005E1BD5Slot {public:virtual void f0();virtual void cleanup(int);};
class Rva005E1BD5:public Rva0007DF07,public Rva0083702CObserver,public Rva0086E330Callback {
public:Rva005E1BD5(Rva005E1BD5Owner*,void*);virtual ~Rva005E1BD5();
 void observer0(int);
 void callback0(int);void callback1(int);void callback2(int);void callback3(int);void callback4(int);
private:Rva005E1BD5Owner *owner;void *army;Rva005E1BD5Slot *slot;DestructorHelpRef help;bool active;
};
Rva005E1BD5::~Rva005E1BD5(){
 ((Rva005E197E*)this)->rva005E197E();
 if(owner->selected==this)((StrategicInGameUI::RegionDetailsArmiesPage::Impl*)owner)->rva005E19CA(0);
 if(owner->pending==this)owner->pending=0;
 if(slot)slot->cleanup(0);
 ((Rva002B7250*)((char*)army+8))->rva002B7250((CreateAHeroData*)(Rva0083702CObserver*)this);
}

struct Rva002BA8F1Listener;
#include "../../Include/Common/Rva005A0B4CList.h"
Rva005E1BD5::Rva005E1BD5(Rva005E1BD5Owner *page,void *object):owner(page),army(object),slot(0),active(false){
 ((Rva005A0B4CList*)((char*)army+8))->append((Rva002BA8F1Listener*)(Rva0083702CObserver*)this);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?callback0@Rva005E1BD5@@UAEXH@Z=?OnDestroyingRegionDetailsArmiesIconSlot@ArmyIcon@Impl@RegionDetailsArmiesPage@StrategicInGameUI@@UAEXAAVRva005EEF2F@@@Z")
#pragma comment(linker, "/alternatename:?callback1@Rva005E1BD5@@UAEXH@Z=?OnRegionDetailsArmiesIconSlotLeftClicked@ArmyIcon@Impl@RegionDetailsArmiesPage@StrategicInGameUI@@UAEXAAVRva005EEF2F@@@Z")
#pragma comment(linker, "/alternatename:?callback2@Rva005E1BD5@@UAEXH@Z=?OnRegionDetailsArmiesIconSlotRightClicked@ArmyIcon@Impl@RegionDetailsArmiesPage@StrategicInGameUI@@UAEXAAVRva005EEF2F@@@Z")
#pragma comment(linker, "/alternatename:?callback3@Rva005E1BD5@@UAEXH@Z=?OnRegionDetailsArmiesIconSlotRollOut@ArmyIcon@Impl@RegionDetailsArmiesPage@StrategicInGameUI@@UAEXAAVRva005EEF2F@@@Z")
#pragma comment(linker, "/alternatename:?callback4@Rva005E1BD5@@UAEXH@Z=?OnRegionDetailsArmiesIconSlotRollOver@ArmyIcon@Impl@RegionDetailsArmiesPage@StrategicInGameUI@@UAEXAAVRva005EEF2F@@@Z")
#pragma comment(linker, "/alternatename:?observer0@Rva005E1BD5@@UAEXH@Z=?rva005E1CF8@Rva005E1CF8@@UAEXH@Z")
