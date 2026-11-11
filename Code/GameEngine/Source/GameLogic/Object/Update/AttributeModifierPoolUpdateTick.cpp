// cl: /ICode /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// Native403CA8..403E3B RET0: AttributeModifierPoolUpdate update slot.
// Native receiver is the update interface at object+10. The rowed constructor
// and factory establish vector20, next-frame2C, names30 and counts6C (hex).
// BF1 cee35b7d AttributeModifierPoolUpdate_update supplied the source lead;
// target reads establish frame40, nineteen condition words and deferred keys.
// Original four-byte deque key type remains unknown; BfmeWordValue4 preserves
// its observed scalar bits and trivial teardown without claiming a name.
// Explicit argument snapshots and a separate min candidate preserve native
// push ordering and CMOV. The small20B min provider belongs to these records.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <deque>
#include <vector>
#include "ascii_string.h"
#include "GameEngine/Source/Common/GameLogicObjectLookupView.h"
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
// bfme link decl-only end
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}
extern GameLogic *TheGameLogic;
#include "../../../../Include/GameLogic/Module/Rva001E42F2.h"
class Object {public:void rva00293077(const void *);};
class Rva00297360Element {public:
 ~Rva00297360Element();
 int index;AsciiString name;unsigned expiration,upgrade;
};
class Rva0040314A {public:unsigned rva0040314A();private:char pad[8];unsigned m_08,m_0c;};
__declspec(noinline) unsigned Rva0040314A::rva0040314A(){if(m_0c>0)return m_08<m_0c?m_08:m_0c;return m_08;}

namespace _STL {
template<> Rva00297360Element *vector<Rva00297360Element>::erase(Rva00297360Element*);
}
struct BfmeWordValue4 {unsigned bits;};
namespace _STL {template<>struct __type_traits<BfmeWordValue4>:__type_traits_aux<1>{};}
namespace _STL {
template<> __declspec(noinline) inline void deque<BfmeWordValue4>::push_back(const BfmeWordValue4 &x) {
 if(this->_M_finish._M_cur != this->_M_finish._M_last-1) {_Construct(this->_M_finish._M_cur,x);++this->_M_finish._M_cur;}else _M_push_back_aux_v(x);
}
template<> __declspec(noinline) inline void deque<BfmeWordValue4>::pop_front() {
 if(this->_M_start._M_cur != this->_M_start._M_last-1) {_STLP_STD::_Destroy(this->_M_start._M_cur);++this->_M_start._M_cur;}else _M_pop_front_aux();
}
template<> _Deque_base<BfmeWordValue4,allocator<BfmeWordValue4> >::~_Deque_base();
}
struct AttributeConditionWords {int words[19];};
#include "../../../../Include/GameLogic/AttributeModifierStore.h"
extern AttributeModifierStore *TheAttributeModifierStore;
class FXList {public:static void doFXObj(const FXList *,const Object *,const Object *);};
struct CategoryView {char unknown00[12];int category;};
struct DelayedUpgradeView {void *upgrade;unsigned delay;};
enum UpdateSleepTime {UPDATE_SLEEP_FOREVER=0x3fffffff};
class AttributeDeepBase {public:virtual ~AttributeDeepBase();void *data;Object *object;};
class AttributeBehaviorInterface {public:virtual void slot0()=0;};
class AttributeUpdateInterface {public:virtual UpdateSleepTime update()=0;};
class AttributeUpdateBase:public AttributeDeepBase,public AttributeBehaviorInterface,public AttributeUpdateInterface {
public:unsigned wake;int index,reserved;
};
class AttributeModifierPoolUpdate:public AttributeUpdateBase {public:
 virtual UpdateSleepTime update();
 _STL::vector<Rva00297360Element> modifiers;
 unsigned maxFrame;
 AsciiString names[15];
 unsigned counts[15];
 Object *getObject() const {return object;}
};
UpdateSleepTime AttributeModifierPoolUpdate::update()
{
 unsigned frame=TheGameLogic->getFrame();
 unsigned next=UPDATE_SLEEP_FOREVER;
 _STL::deque<BfmeWordValue4> pending;
 for(Rva00297360Element *it=modifiers.begin();it!=modifiers.end();) {
   Rva00297360Element *entry=it;
   unsigned &upgrade=entry->upgrade;
   if(upgrade>0 && frame>=upgrade) {
     BfmeWordValue4 key;key.bits=entry->index;
     pending.push_back(key);
     upgrade=0;
   }
   if(frame>=entry->expiration) {
     AttributeConditionWords clear;
     TheAttributeModifierStore->rva00214801(&clear,entry->index);
     ((Rva001E42F2*)getObject())->rva001E42F2(clear.words);
     if(__vref(upgrade)<=frame) {
       Object *obj=getObject();int key=entry->index;const FXList *fx=(const FXList*)TheAttributeModifierStore->getEndFX(key,obj);
       if(fx)FXList::doFXObj(fx,getObject(),0);
       CategoryView *category=(CategoryView*)TheAttributeModifierStore->GetCategoryContainer(entry->index);
       if(category)--counts[category->category];
       it=modifiers.erase(it);
     } else {
       ++it;
       unsigned value=upgrade;value=next<value?next:value;next=value;
       _ReadWriteBarrier();
     }
   } else {
     ++it;
     next=next<((Rva0040314A*)entry)->rva0040314A()?next:((Rva0040314A*)entry)->rva0040314A();
   }
 }
 maxFrame=next<UPDATE_SLEEP_FOREVER?next:UPDATE_SLEEP_FOREVER;
 while(!pending.empty()) {
   DelayedUpgradeView *upgrade=(DelayedUpgradeView*)TheAttributeModifierStore->getDelayedUpgrade((int)pending.front().bits);
   if(upgrade&&upgrade->upgrade)getObject()->rva00293077(upgrade->upgrade);
   pending.pop_front();
 }
 if(maxFrame<UPDATE_SLEEP_FOREVER)return (UpdateSleepTime)(maxFrame-frame);
 maxFrame=UPDATE_SLEEP_FOREVER;
 return UPDATE_SLEEP_FOREVER;
}
