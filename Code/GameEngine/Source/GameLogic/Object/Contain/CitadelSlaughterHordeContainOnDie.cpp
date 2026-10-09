// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// stlport
// CitadelSlaughterHordeContain ctor48059F installs C48910 at +28;
// slot0 there is 480821. Full native199B RET4 ignores its damage argument.
// WB11B54B0 supplies nested-list behavior: horde children are transferred
// through contain slot39. Primary containment view is this-8 (+20).
// BFME1 f989 SlaughterHordeContain class hierarchy is a provenance lead;
// target table slots and template kind bit109 establish the actual views.
#include "../../../../Include/GameLogic/ContainmentListView.h"
namespace _STL {
template<class T,class Traits> static inline bool operator!=(const _List_iterator<T,Traits>&a,const _List_iterator<T,Traits>&b)
{ return a._M_node!=b._M_node; }
template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();
}
class DamageInfo;
class Object;
template<int N> class CitadelDieSlots : public CitadelDieSlots<N-1> {public:virtual void gap(char(*)[N])=0;};
template<> class CitadelDieSlots<0> {};
class CitadelContainedView : public CitadelDieSlots<67> {public:virtual void slot67(ContainmentList&)=0;};
class ThingTemplate {public:char unknown00[0x115];unsigned char kindByte;};
class Object {
public:
 void *rva0028C197() const;
 void *vptr;
 const ThingTemplate *thingTemplate;
};
class CitadelContainDieView : public CitadelDieSlots<39> {
public:
 virtual void slot39(Object*)=0;
 virtual void slot40()=0;
 virtual void slot41()=0;
 virtual void slot42()=0;
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
 virtual Rva0036AE51ListView slot70()=0;
};
class CitadelSlaughterHordeContain {
public:
 virtual void onDie(const DamageInfo*);
 CitadelContainDieView *contain() { return reinterpret_cast<CitadelContainDieView*>(reinterpret_cast<char*>(this)-8); }
};
// ?onDie@CitadelSlaughterHordeContain@@UAEXPBVDamageInfo@@@Z
void CitadelSlaughterHordeContain::onDie(const DamageInfo*)
{
 ContainmentList objects=contain()->slot70().rva0036AE51();
 for (ContainmentList::iterator it=objects.begin();it!=objects.end();++it) {
  Object *object=reinterpret_cast<Object*>(containmentFirstWord(*it));
  if (object && (object->thingTemplate->kindByte & 0x20)) {
   CitadelContainedView *nested=reinterpret_cast<CitadelContainedView*>(object->rva0028C197());
   if (nested) {
    ContainmentList children;
    nested->slot67(children);
    for (ContainmentList::iterator child=children.begin();child!=children.end();++child) {
     Object *member=reinterpret_cast<Object*>(containmentFirstWord(*child));
     if (member) contain()->slot39(member);
    }
   }
  }
 }
}
