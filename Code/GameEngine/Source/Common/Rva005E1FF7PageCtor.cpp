// ??0Impl@RegionDetailsArmiesPage@StrategicInGameUI@@QAE@PAX00ABUPageContext@@@Z
// RVA 0x005E1FF7, 175 bytes. WorldBuilder 15F0DD0 names the page's
// PopulateIconSlots; the ctor and the sibling Update share this class view.
// Retail end-first loop load order is reproduced by declaring `end` before
// `begin`; the volatile read of g_rva0059E647World->player reproduces retail's
// reload of the world pointer inside the clip initializer.
// cl: /O1 /G7 /MD /EHsc /ICode/Libraries/Include/Lib /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport

#include "unicode_string.h"
#include "RGBColor.h"
#include "RGBColor.h"
#include <vector>
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
namespace _STL { template<> vector<TreeHintRef00217D4C>::~vector(); }
#include "../../Include/Common/PageContext.h"
class Rva005EFDDB {public:Rva005EFDDB(unsigned,const void*,int);virtual ~Rva005EFDDB();private:void *impl;};
class Rva005E19CAInterface;
namespace StrategicInGameUI {class RegionDetailsArmiesPage {public:class Impl;};}
class StrategicInGameUI::RegionDetailsArmiesPage::Impl {public:Impl(void*,void*,void*,const PageContext&);void CreateArmyIcons();void PopulateIconSlots();void Update();void rva005E19CA(int);private:
 Rva005E19CAInterface *ui;void *region,*owner;Rva005EFDDB clip;_STL::vector<TreeHintRef00217D4C> icons;bool dirty;char unknown21[3];int selected;int pending;
};

struct Rva005E19CAEntry {char unknown00[0x14];void *army;};
struct Rva005E1FF7ColorOwner {char unknown00[0x184];RGBColor color;const RGBColor &getColor()const{return color;}};
struct Rva0059E647World {char unknown00[0x98];Rva005E1FF7ColorOwner *player;};
extern class LivingWorldLogic *TheLivingWorldLogic;

StrategicInGameUI::RegionDetailsArmiesPage::Impl::Impl(void *page,void *level,void *name,const PageContext &context)
:ui((Rva005E19CAInterface*)page),region(context.region),owner(context.owner),clip((unsigned)level,name,__vref(((Rva0059E647World *)TheLivingWorldLogic)->player)->getColor().getAsInt()|0xff000000),dirty(false),selected(0),pending(0){
 CreateArmyIcons();
 void *army=context.page;
 if(army){
  _STL::vector<TreeHintRef00217D4C>::iterator end=icons.end();
  for(_STL::vector<TreeHintRef00217D4C>::iterator i=icons.begin();i!=end;++i){
   if(((Rva005E19CAEntry*)i->m_ptr)->army==army){pending=(int)i->m_ptr;break;}
  }
 }
}
