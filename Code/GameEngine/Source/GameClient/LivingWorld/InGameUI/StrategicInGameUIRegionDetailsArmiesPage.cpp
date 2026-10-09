// cl: /O1 /G7 /MD /EHsc
// Native9E1B4E..9E1B9A complete76B. WB15F0DD0 names PopulateIconSlots.
// Existing42-byte Update shares this one partial class view; no class layout inferred beyond observed fields.
// Prior false-boundary refusal used a VA interpretation; direct native call
// 9E1BA3 targets9E1B4E and this RVA begins push ECX.
class Rva005EFF60 {public:void rva005EFF60(int);};
class Rva005EF3CE {public:int rva005EF3CE(int);};
class Rva005E1B41Primary {public:void rva005E1AB6(int);};
namespace StrategicInGameUI {class RegionDetailsArmiesPage {public:class Impl;};}
class StrategicInGameUI::RegionDetailsArmiesPage::Impl {public:void PopulateIconSlots();void Update();private:
 char unknown00[0xC];char clip[8];Rva005E1B41Primary **first,**last;char unknown1C[4];bool dirty;char unknown21[7];int pending;
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

class Rva005E19CA {public:void rva005E19CA(int);};
class Rva005EF3F6 {public:void rva005EF3F6();};
void StrategicInGameUI::RegionDetailsArmiesPage::Impl::Update(){
 if(dirty) PopulateIconSlots();
 int value=pending;
 if(value){((Rva005E19CA*)this)->rva005E19CA(value);pending=0;}
 ((Rva005EF3F6*)clip)->rva005EF3F6();
}
