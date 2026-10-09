// ??0Impl@RegionDetailsArmiesPage@StrategicInGameUI@@QAE@PAX00ABUPageContext@@@Z
// partial score=0.94 date=2026-10-09
// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native9E1B4E..9E1B9A complete76B. WB15F0DD0 names PopulateIconSlots.
// Existing42-byte Update shares this one partial class view; no class layout inferred beyond observed fields.
// Prior false-boundary refusal used a VA interpretation; direct native call
// 9E1BA3 targets9E1B4E and this RVA begins push ECX.

#include "unicode_string.h"
#include <vector>
struct TreeHintRef00217D4C {void *m_target;~TreeHintRef00217D4C();};
struct PageContext {void *region,*page,*owner;};
class Rva005EFDDB {public:Rva005EFDDB(unsigned,const void*,int);virtual ~Rva005EFDDB();private:void *impl;};
class Rva005E19CAInterface;
class Rva005EFF60 {public:void rva005EFF60(int);};
class Rva005EF3CE {public:int rva005EF3CE(int);};
class Rva005E1B41Primary {public:void rva005E1AB6(int);};
namespace StrategicInGameUI {class RegionDetailsArmiesPage {public:class Impl;};}
class StrategicInGameUI::RegionDetailsArmiesPage::Impl {public:Impl(void*,void*,void*,const PageContext&);void CreateArmyIcons();void PopulateIconSlots();void Update();void rva005E19CA(int);private:
 Rva005E19CAInterface *ui;void *region,*owner;Rva005EFDDB clip;_STL::vector<TreeHintRef00217D4C> icons;bool dirty;char unknown21[3];int selected;int pending;
};
void StrategicInGameUI::RegionDetailsArmiesPage::Impl::PopulateIconSlots(){
 int count=icons.size();
 Rva005EFF60 *view=(Rva005EFF60*)&clip;
 view->rva005EFF60(count);
 for(int index=0;index<count;++index){
  Rva005E1B41Primary *icon=(Rva005E1B41Primary*)icons[index].m_target;
  icon->rva005E1AB6(((Rva005EF3CE*)view)->rva005EF3CE(index));
 }
 dirty=false;
}

class Rva005EF3F6 {public:void rva005EF3F6();};
void StrategicInGameUI::RegionDetailsArmiesPage::Impl::Update(){
 if(dirty) PopulateIconSlots();
 int value=pending;
 if(value){rva005E19CA(value);pending=0;}
 ((Rva005EF3F6*)&clip)->rva005EF3F6();
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
  Rva005EF3DE *view=(Rva005EF3DE*)&clip;
  view->rva005EF3DE();((Rva005EF3EE*)view)->rva005EF3EE();
  ((Rva005E187A*)selected)->rva005E187A(false);
 }
 selected=next;
 if(!next)return;
 ((Rva005E187A*)next)->rva005E187A(true);
 void *army=((Rva005E19CAEntry*)selected)->army;
 ((Rva005EF5C2*)&clip)->rva005EF5C2(StrategicInGameUI::GetDisplayName(army));
 Rva005EF3E6 *view=(Rva005EF3E6*)&clip;
 ((Rva005EF3E6*)view)->rva005EF3E6(((Rva00318FBE*)army)->rva00318FBE(),GetMaxCommandPoints(army));
 if(ui->active)((Rva005E18B9*)this)->rva005E18B9();
}

struct RGBColor {int getAsInt()const;float r,g,b;};
struct Rva005E1FF7ColorOwner {char unknown00[0x184];RGBColor color;const RGBColor &getColor()const{return color;}};
struct Rva0059E647World {char unknown00[0x98];Rva005E1FF7ColorOwner *player;};
extern Rva0059E647World *g_rva0059E647World;
StrategicInGameUI::RegionDetailsArmiesPage::Impl::Impl(void *page,void *level,void *name,const PageContext &context)
:ui((Rva005E19CAInterface*)page),region(context.region),owner(context.owner),clip((unsigned)level,name,g_rva0059E647World->player->getColor().getAsInt()|0xff000000),dirty(false),selected(0),pending(0){
 CreateArmyIcons();
 void *army=context.page;
 if(army){
  _STL::vector<TreeHintRef00217D4C>::iterator i=icons.begin();
  _STL::vector<TreeHintRef00217D4C>::iterator end=icons.end();
  for(;i!=end;++i){
   if(((Rva005E19CAEntry*)i->m_target)->army==army){pending=(int)i->m_target;break;}
  }
 }
}
