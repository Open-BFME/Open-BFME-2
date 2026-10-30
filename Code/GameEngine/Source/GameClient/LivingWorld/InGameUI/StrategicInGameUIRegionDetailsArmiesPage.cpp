// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Native9E1B4E..9E1B9A complete76B. WB15F0DD0 names PopulateIconSlots.
// Existing42-byte Update shares this one partial class view; no class layout inferred beyond observed fields.
// Prior false-boundary refusal used a VA interpretation; direct native call
// 9E1BA3 targets9E1B4E and this RVA begins push ECX.

// Keep vector growth's unsigned comparison local. Its standalone template
// copy differs from retail; all uses in this unit are already inlined.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
 return a < b ? b : a;
}
}
#include "unicode_string.h"
#include <vector>
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}
struct Rva005E1BD5Owner;
class Rva005E1BD5 {public:Rva005E1BD5(Rva005E1BD5Owner*,void*);virtual ~Rva005E1BD5();private:char storage[0x20];};
struct TargetRef00217D4C {void *vtable;int refs;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct Rva005E1E9BElement {
 Rva005E1BD5 *ptr;
 Rva005E1E9BElement(Rva005E1BD5*p):ptr(p){if(ptr)++((TargetRef00217D4C*)ptr)->refs;}
 Rva005E1E9BElement(const Rva005E1E9BElement&other):ptr(other.ptr){if(ptr)++((TargetRef00217D4C*)ptr)->refs;}
 // Retail has no out-of-line body: the release is inlined into the
 // element's scalar deleting dtor 0x005F8FCC.
 ~Rva005E1E9BElement(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}
};
// The existing STL element name is a storage view of this counted handle.
struct RegionArmyIconRef {
 Rva005E1BD5 *ptr;
 RegionArmyIconRef(Rva005E1BD5 *p):ptr(p){if(ptr)++((TargetRef00217D4C*)ptr)->refs;}
 ~RegionArmyIconRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}
 operator const Rva005E1E9BElement &() const { return *(const Rva005E1E9BElement*)this; }
};
namespace _STL { template<> inline __declspec(noinline) __declspec(nothrow) void _Construct<Rva005E1E9BElement,Rva005E1E9BElement>(Rva005E1E9BElement *p,const Rva005E1E9BElement &v) { new(p) Rva005E1E9BElement(v); } }

class Rva005E19CAInterface;
class Rva005EFF60 {public:void rva005EFF60(int);};
class Rva005EF3CE {public:int rva005EF3CE(int);};
class Rva005E1B41Primary {public:void rva005E1AB6(int);};
namespace StrategicInGameUI {class RegionDetailsArmiesPage {public:class Impl;};}
class StrategicInGameUI::RegionDetailsArmiesPage::Impl {public:class ArmyIcon;friend class ArmyIcon;void CreateArmyIcons();void PopulateIconSlots();void Update();void rva005E19CA(int);private:
 Rva005E19CAInterface *ui;void *region,*owner;char clip[8];_STL::vector<Rva005E1E9BElement> icons;bool dirty;char unknown21[3];int selected;int pending;
};
void StrategicInGameUI::RegionDetailsArmiesPage::Impl::PopulateIconSlots(){
 int count=icons.size();
 Rva005EFF60 *view=(Rva005EFF60*)clip;
 view->rva005EFF60(count);
 for(int index=0;index<count;++index){
  Rva005E1B41Primary *icon=(Rva005E1B41Primary*)icons[index].ptr;
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
class Rva005EF3DE {public:void hideArmyName();};
class Rva005EF3EE {public:void hideCommandPoints();};
class Rva005EF3E6 {public:void showCommandPoints(int,int);};
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
  view->hideArmyName();((Rva005EF3EE*)view)->hideCommandPoints();
  ((Rva005E187A*)selected)->rva005E187A(false);
 }
 selected=next;
 if(!next)return;
 ((Rva005E187A*)next)->rva005E187A(true);
 void *army=((Rva005E19CAEntry*)selected)->army;
 ((Rva005EF5C2*)clip)->rva005EF5C2(StrategicInGameUI::GetDisplayName(army));
 Rva005EF3E6 *view=(Rva005EF3E6*)clip;
 ((Rva005EF3E6*)view)->showCommandPoints(((Rva00318FBE*)army)->rva00318FBE(),GetMaxCommandPoints(army));
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

// WB15F0A60 lines333..346. The player owns the army vector at +1B8.
// Keep its vector reference and the visible intrusive copy helper: both affect
// retail register allocation while push_back stays out of line.
struct Rva005E1ED2Record {int a,b;};
struct Rva005E1ED2Catalog {char pad00[0x40];Rva005E1ED2Record *first,*last;};
class Rva00318C32Ret;
class Rva00318C79Owner {public:Rva00318C32Ret *rva00318C32();char pad00[0x78];Rva005E1ED2Catalog *catalog;};
struct Rva005E1ED2Player {char pad00[0x1B8];_STL::vector<Rva00318C79Owner*> armies;};
struct Rva0059E647World {char pad00[0x98];Rva005E1ED2Player *player;};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
void StrategicInGameUI::RegionDetailsArmiesPage::Impl::CreateArmyIcons(){
 Rva005E1ED2Player *player=((Rva0059E647World*)TheLivingWorldLogic)->player;
 if(player){
  _STL::vector<Rva00318C79Owner*> &armies=player->armies;
  Rva00318C79Owner **const end=armies.end();
  for(Rva00318C79Owner **i=armies.begin();i!=end;++i){
   Rva00318C79Owner *army=*i;
   if(army->rva00318C32()!=region) continue;
   Rva005E1ED2Catalog *catalog=army->catalog;
   if(!catalog || !(unsigned)(catalog->last-catalog->first)) continue;
   icons.push_back(RegionArmyIconRef(new Rva005E1BD5((Rva005E1BD5Owner*)this,army)));
   if(icons.size()>=4)break;
  }
  dirty=!icons.empty();
 }
}
