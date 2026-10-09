// cl: /O1 /G7 /MD /EHsc
// Native5E1BD5..5E1C6F complete154B destructor. Primary0 counted base8,
// observer8 and callbackC interfaces proven by native vtable stores/dispatch;
// owner10, army14, owned slot18 and counted help1C proven by neighbouring methods.
struct RvaSmallVtableZeroBase {void *m_04;};
class Rva0007DF07:public RvaSmallVtableZeroBase {public:virtual ~Rva0007DF07(){}};
class Rva0083702CObserver {public:
 virtual void observer0(int)=0;virtual void observer1(void*,void*){};virtual void observer2()=0;virtual void observer3()=0;virtual void observer4()=0;
 ~Rva0083702CObserver(){}
};
class Rva0086E330Callback {public:
 virtual void callback0(int)=0;virtual void callback1(int)=0;virtual void callback2(int)=0;virtual void callback3(int)=0;virtual void callback4(int)=0;
 ~Rva0086E330Callback(){}
};
struct TargetRef00217D4C {void *vtable;int count;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct DestructorHelpRef {TargetRef00217D4C *ptr;~DestructorHelpRef(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}};
class Rva005E197E {public:void rva005E197E();};
class CreateAHeroData;
class Rva002B7250 {public:void rva002B7250(CreateAHeroData*);};
namespace StrategicInGameUI {class RegionDetailsArmiesPage {public:class Impl;};}
class StrategicInGameUI::RegionDetailsArmiesPage::Impl {public:void rva005E19CA(int);};
class Rva005E1BD5;
struct Rva005E1BD5Owner {char unknown00[0x24];Rva005E1BD5 *selected,*pending;};
class Rva005E1BD5Slot {public:virtual void f0();virtual void cleanup(int);};
class Rva005E1BD5:public Rva0007DF07,public Rva0083702CObserver,public Rva0086E330Callback {
public:virtual ~Rva005E1BD5();
 void observer0(int);
 void callback0(int);void callback1(int);void callback2(int);void callback3(int);void callback4(int);
private:Rva005E1BD5Owner *owner;void *army;Rva005E1BD5Slot *slot;DestructorHelpRef help;
};
Rva005E1BD5::~Rva005E1BD5(){
 ((Rva005E197E*)this)->rva005E197E();
 if(owner->selected==this)((StrategicInGameUI::RegionDetailsArmiesPage::Impl*)owner)->rva005E19CA(0);
 if(owner->pending==this)owner->pending=0;
 if(slot)slot->cleanup(0);
 ((Rva002B7250*)((char*)army+8))->rva002B7250((CreateAHeroData*)(Rva0083702CObserver*)this);
}
