// ?CreateArmyIcons@Impl@RegionDetailsArmiesPage@StrategicInGameUI@@QAEXXZ
// partial score=0.78 date=2026-10-09
// ?CreateArmyIcons@Impl@RegionDetailsArmiesPage@StrategicInGameUI@@QAEXXZ
// partial score=0.78 date=2026-10-09
// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native9E1B4E..9E1B9A complete76B. WB15F0DD0 names PopulateIconSlots.
// Existing42-byte Update shares this one partial class view; no class layout inferred beyond observed fields.
// Prior false-boundary refusal used a VA interpretation; direct native call
// 9E1BA3 targets9E1B4E and this RVA begins push ECX.

#include "unicode_string.h"
#include <vector>
struct Rva005E1BD5Owner;
class Rva005E1BD5 {public:Rva005E1BD5(Rva005E1BD5Owner*,void*);virtual ~Rva005E1BD5();private:char storage[0x20];};
struct TargetRef00217D4C {void *vtable;int refs;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct Rva005E1E9BElement {
 Rva005E1BD5 *ptr;
 Rva005E1E9BElement(Rva005E1BD5*p):ptr(p){if(ptr)++((TargetRef00217D4C*)ptr)->refs;}
 Rva005E1E9BElement(const Rva005E1E9BElement&);
 ~Rva005E1E9BElement(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}
};
class Rva005E19CAInterface;
class Rva005EFF60 {public:void rva005EFF60(int);};
class Rva005EF3CE {public:int rva005EF3CE(int);};
class Rva005E1B41Primary {public:void rva005E1AB6(int);};
namespace StrategicInGameUI {class RegionDetailsArmiesPage {public:class Impl;};}
class StrategicInGameUI::RegionDetailsArmiesPage::Impl {public:void CreateArmyIcons();void PopulateIconSlots();void Update();void rva005E19CA(int);private:
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
 virtual void f0();virtual void f1();virtual void f2();virtual void f3();virtual void f4();virtual void f5();virtual void f6();
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

struct Rva005E1ED2Record {int a,b;};
struct Rva005E1ED2Catalog {char pad00[0x40];Rva005E1ED2Record *first,*last;};
class Rva00318C32 {public:int rva00318C32();char pad00[0x78];Rva005E1ED2Catalog *catalog;};
struct Rva005E1ED2Player {char pad00[0x1B8];Rva00318C32 **first,**last;};
struct Rva0059E647World {char pad00[0x98];Rva005E1ED2Player *player;};
extern Rva0059E647World *g_rva0059E647World;
void StrategicInGameUI::RegionDetailsArmiesPage::Impl::CreateArmyIcons(){
 Rva005E1ED2Player *player=g_rva0059E647World->player;
 if(!player)return;
 Rva00318C32 **const end=player->last;
 Rva00318C32 **i=player->first;
 for(;i!=end;++i){
  Rva00318C32 *army=*i;
  if(army->rva00318C32()==(int)region){
   Rva005E1ED2Catalog *catalog=army->catalog;
   Rva005E1BD5 *icon=0;
   if(catalog!=(Rva005E1ED2Catalog*)icon && (unsigned)(catalog->last-catalog->first)){
   icon=new Rva005E1BD5((Rva005E1BD5Owner*)this,army);
   icons.push_back(Rva005E1E9BElement(icon));
   if(icons.size()>=4)break;
   }
  }
 }
 dirty=!icons.empty();
}
