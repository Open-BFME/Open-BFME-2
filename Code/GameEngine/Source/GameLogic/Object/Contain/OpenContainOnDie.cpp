// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// stlport
// Native 004641B1..00464286 (213B), OpenContain die-interface at +28.
// OpenContain dtor 464692 installs C46F78 at +28; its slot0 is 8641B1.
// WB 11964A0 establishes the die check and target kill-contents branch;
// ZH OpenContain::onDie supplies only the die-callback semantic lead.
// Target accesses: module data this-24, owner this-20, death flag this+B8,
// contained list this+2C, module damage fraction +6C and branch flag +82.
#include "../../../../Include/GameLogic/ContainmentListView.h"
#include "../../../Common/GameLogicObjectLookupView.h"
namespace _STL {
template<class T, class Traits> static inline bool operator!=(const _List_iterator<T,Traits>& a,const _List_iterator<T,Traits>& b)
{ return a._M_node != b._M_node; }
template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();
}
class DamageInfo;
class Object;
class Drawable;
class DieMuxData {
public: bool isDieApplicable(const Object*,const DamageInfo*) const;
};
class Thing { public: Drawable *getDrawable() const; };
class Object : public Thing {};
class Rva002716Holder { public: void rva00271601(unsigned char); };
extern GameLogic *TheGameLogic;
struct OpenContainDieData {
 char unknown00[8];
 DieMuxData dieMux;
 char unknown09[0x6C-9];
 float damageFraction;
 char unknown70[0x82-0x70];
 bool releaseContents;
};
template<int N> class OpenContainDieSlots : public OpenContainDieSlots<N-1> { public: virtual void gap(char (*)[N])=0; };
template<> class OpenContainDieSlots<0> {};
class OpenContainPrimaryDieView : public OpenContainDieSlots<25> { public: virtual void slot25()=0; };
class OpenContainInterfaceDieView : public OpenContainDieSlots<42> {
public:
 virtual void removeAllContained(bool)=0;
 virtual void slot43()=0;
 virtual void slot44()=0;
 virtual void slot45()=0;
 virtual void slot46()=0;
 virtual void slot47()=0;
 virtual void slot48()=0;
 virtual void slot49()=0;
 virtual void slot50()=0;
 virtual void slot51()=0;
 virtual void slot52()=0;
 virtual void slot53()=0;
 virtual void slot54()=0;
 virtual void slot55()=0;
 virtual void slot56()=0;
 virtual void slot57()=0;
 virtual void slot58()=0;
 virtual void slot59()=0;
 virtual void slot60()=0;
 virtual void slot61()=0;
 virtual void slot62()=0;
 virtual void slot63()=0;
 virtual void slot64()=0;
 virtual void slot65()=0;
 virtual void slot66()=0;
 virtual void slot67()=0;
 virtual void slot68()=0;
 virtual void slot69()=0;
 virtual void slot70()=0;
 virtual void slot71()=0;
 virtual void slot72()=0;
 virtual void slot73()=0;
 virtual void slot74()=0;
 virtual void slot75()=0;
 virtual void slot76()=0;
 virtual void slot77()=0;
 virtual void slot78()=0;
 virtual void slot79()=0;
 virtual void slot80()=0;
 virtual void slot81()=0;
 virtual void slot82()=0;
};
class OpenContain {
public:
 virtual void onDie(const DamageInfo*);
 OpenContainDieData *data() const { return *reinterpret_cast<OpenContainDieData *const *>(reinterpret_cast<const char*>(this)-0x24); }
 Object *owner() const { return *reinterpret_cast<Object *const *>(reinterpret_cast<const char*>(this)-0x20); }
 OpenContainPrimaryDieView *primary() { return reinterpret_cast<OpenContainPrimaryDieView*>(reinterpret_cast<char*>(this)-0x28); }
 OpenContainInterfaceDieView *contain() { return reinterpret_cast<OpenContainInterfaceDieView*>(reinterpret_cast<char*>(this)-8); }
 char unknown04[0x2C-4];
 ContainmentList contents;
 char unknown30[0xB8-0x30];
 bool dying;
};
// ?onDie@OpenContain@@UAEXPBVDamageInfo@@@Z
void OpenContain::onDie(const DamageInfo *damageInfo)
{
 dying=true;
 if (!data()->dieMux.isDieApplicable(owner(),damageInfo)) return;
 if (data()->releaseContents) {
  if (data()->damageFraction > 0.0f) contain()->slot82();
  primary()->slot25();
  contain()->removeAllContained(false);
 } else {
  ContainmentList copy(contents);
  for (ContainmentList::iterator it=copy.begin();it!=copy.end();++it) {
   Object *object=reinterpret_cast<Object*>(containmentFirstWord(*it));
   if (object) {
    if (object->getDrawable()) reinterpret_cast<Rva002716Holder*>(object->getDrawable())->rva00271601(1);
    TheGameLogic->destroyObject(object);
   }
  }
 }
}
