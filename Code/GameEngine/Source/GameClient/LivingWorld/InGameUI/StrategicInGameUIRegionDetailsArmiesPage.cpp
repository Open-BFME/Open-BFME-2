// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native9E1B4E..9E1B9A complete76B. WB15F0DD0 names PopulateIconSlots.
// Existing42-byte Update shares this one partial class view; no class layout inferred beyond observed fields.
// Prior false-boundary refusal used a VA interpretation; direct native call
// 9E1BA3 targets9E1B4E and this RVA begins push ECX.

#include "unicode_string.h"
class Rva005E19CAInterface;
class Rva005EFF60 {public:void rva005EFF60(int);};
class Rva005EF3CE {public:int rva005EF3CE(int);};
class Rva005E1B41Primary {public:void rva005E1AB6(int);};
namespace StrategicInGameUI {class RegionDetailsArmiesPage {public:class Impl;};}
class StrategicInGameUI::RegionDetailsArmiesPage::Impl {public:class ArmyIcon;friend class ArmyIcon;void PopulateIconSlots();void Update();void rva005E19CA(int);private:
 Rva005E19CAInterface *ui;char unknown04[8];char clip[8];Rva005E1B41Primary **first,**last;char unknown1C[4];bool dirty;char unknown21[3];int selected;int pending;
};
void StrategicInGameUI::RegionDetailsArmiesPage::Impl::PopulateIconSlots(){
 int count=last-first;
 Rva005EFF60 *view=(Rva005EFF60*)clip;
 view->rva005EFF60(count);
 for(int index=0;index<count;++index){
  Rva005E1B41Primary *icon=first[index];
  icon->rva005E1AB6(((Rva005EF3CE*)view)->rva005EF3CE(index));
 }
 dirty=false;
}

class Rva005EF3F6 {public:void rva005EF3F6();};
void StrategicInGameUI::RegionDetailsArmiesPage::Impl::Update(){
 if(dirty) PopulateIconSlots();
 int value=pending;
 if(value){rva005E19CA(value);pending=0;}
 ((Rva005EF3F6*)clip)->rva005EF3F6();
}

// Native5E19CA..5E1A87 complete189B; WB15F1090 same page selection flow.
// Method name unresolved; retain address-derived spelling within established page class.
class Rva005E19CAInterface {public:
 virtual void f0();virtual void f1();virtual void f2();virtual void f3();virtual void f4(void *);virtual void f5();virtual void f6();
 char unknown04[4];bool active;
};
class Rva005E187A {public:void rva005E187A(bool);};
class Rva005EF3DE {public:void rva005EF3DE();};
class Rva005EF3EE {public:void rva005EF3EE();};
class Rva005EF3E6 {public:void rva005EF3E6(int,int);};
class Rva005EF5C2 {public:void rva005EF5C2(const UnicodeString &);};
class Rva005E18B9 {public:void rva005E18B9();};
namespace StrategicInGameUI {UnicodeString GetDisplayName(void *);}
int GetMaxCommandPoints(void *);
class Rva00318FBE {public:int rva00318FBE();};
struct Rva005E19CAEntry {char unknown00[0x14];void *army;};
void StrategicInGameUI::RegionDetailsArmiesPage::Impl::rva005E19CA(int next){
 if(next==selected)return;
 if(selected){
  if(ui->active)ui->f6();
  Rva005EF3DE *view=(Rva005EF3DE*)clip;
  view->rva005EF3DE();((Rva005EF3EE*)view)->rva005EF3EE();
  ((Rva005E187A*)selected)->rva005E187A(false);
 }
 selected=next;
 if(!next)return;
 ((Rva005E187A*)next)->rva005E187A(true);
 void *army=((Rva005E19CAEntry*)selected)->army;
 ((Rva005EF5C2*)clip)->rva005EF5C2(StrategicInGameUI::GetDisplayName(army));
 Rva005EF3E6 *view=(Rva005EF3E6*)clip;
 ((Rva005EF3E6*)view)->rva005EF3E6(((Rva00318FBE*)army)->rva00318FBE(),GetMaxCommandPoints(army));
 if(ui->active)((Rva005E18B9*)this)->rva005E18B9();
}

// The native C77A38 listener table and WB assertions at lines257..285
// establish these five ArmyIcon callbacks. Both images receive the listener
// subobject at +0C; the primary receiver has a vptr and two unknown words.
// This callback view covers only +00..+17; the separately matched constructor
// establishes the full36-byte object, including another vptr at +08.
// The slot argument is borrowed and unused after the debug assertion.
class Rva005EEF2F;
class Rva005E197E {public:virtual void primarySlot();void rva005E197E();private:int unknown04,unknown08;};
class Rva005E1928 {public:void rva005E1928();};
class ArmyIconSlotListenerView {
public:
 virtual void OnDestroyingRegionDetailsArmiesIconSlot(Rva005EEF2F &) = 0;
 virtual void OnRegionDetailsArmiesIconSlotLeftClicked(Rva005EEF2F &) = 0;
 virtual void OnRegionDetailsArmiesIconSlotRightClicked(Rva005EEF2F &) = 0;
 virtual void OnRegionDetailsArmiesIconSlotRollOut(Rva005EEF2F &) = 0;
 virtual void OnRegionDetailsArmiesIconSlotRollOver(Rva005EEF2F &) = 0;
protected:
 StrategicInGameUI::RegionDetailsArmiesPage::Impl *owner;
 void *army;
};
class StrategicInGameUI::RegionDetailsArmiesPage::Impl::ArmyIcon : public Rva005E197E,public ArmyIconSlotListenerView {
public:
 void OnDestroyingRegionDetailsArmiesIconSlot(Rva005EEF2F &);
 void OnRegionDetailsArmiesIconSlotLeftClicked(Rva005EEF2F &);
 void OnRegionDetailsArmiesIconSlotRightClicked(Rva005EEF2F &);
 void OnRegionDetailsArmiesIconSlotRollOut(Rva005EEF2F &);
 void OnRegionDetailsArmiesIconSlotRollOver(Rva005EEF2F &);
};
void StrategicInGameUI::RegionDetailsArmiesPage::Impl::ArmyIcon::OnDestroyingRegionDetailsArmiesIconSlot(Rva005EEF2F &){
 ((Rva005E1B41Primary *)static_cast<Rva005E197E *>(this))->rva005E1AB6(0);
}
void StrategicInGameUI::RegionDetailsArmiesPage::Impl::ArmyIcon::OnRegionDetailsArmiesIconSlotLeftClicked(Rva005EEF2F &){
 owner->pending=reinterpret_cast<int>(static_cast<Rva005E197E *>(this));
}
void StrategicInGameUI::RegionDetailsArmiesPage::Impl::ArmyIcon::OnRegionDetailsArmiesIconSlotRightClicked(Rva005EEF2F &){
 owner->ui->f4(army);
}
void StrategicInGameUI::RegionDetailsArmiesPage::Impl::ArmyIcon::OnRegionDetailsArmiesIconSlotRollOut(Rva005EEF2F &){
 rva005E197E();
}
void StrategicInGameUI::RegionDetailsArmiesPage::Impl::ArmyIcon::OnRegionDetailsArmiesIconSlotRollOver(Rva005EEF2F &){
 ((Rva005E1928 *)static_cast<Rva005E197E *>(this))->rva005E1928();
}
