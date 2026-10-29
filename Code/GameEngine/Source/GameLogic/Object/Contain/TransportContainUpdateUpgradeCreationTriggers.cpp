// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /ICode/GameEngine/Source /D_STLP_USE_STATIC_LIB
// stlport
// Target468045..46824A RET0,517B. WB115D5F0 names TransportContain::UpdateUpgradeCreationTriggers.
// BF1 clean TransportContain createPayload and ZH TransportContain supply containment/factory semantics;
// upgrade-trigger roster is target-specific, absent from those reference bodies.
// Native roster110, owner8, data record lookup467799, count8, factory/upgrade providers and virtual ABI
// independently establish this flow; provisional capacity predicate466D50 is not a recovered body.
#include "ascii_string.h"
#include "Common/GameLogicObjectLookupView.h"
#include <string.h>
#include <vector>
namespace _STL {
// Bind the range erase to the rowed AsciiString-vector worker.
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString *first, AsciiString *last);
}
class Team;class UpgradeTemplate;class ThingTemplate;
struct CreateMask{unsigned words[4];};
enum ObjectID; class ThingFactory{public:const ThingTemplate*findTemplate(const AsciiString&);Object*newObject(const ThingTemplate*,Team*,const CreateMask*,ObjectID);};extern ThingFactory*TheThingFactory;
class UpgradeCenter{public:const UpgradeTemplate*findUpgrade(const AsciiString&)const;};extern UpgradeCenter*TheUpgradeCenter;
struct BfmeStringRecord00466E64{AsciiString upgrade;AsciiString object;unsigned count;};
class Rva00467799{public:BfmeStringRecord00466E64*rva00467799(const StringBase<char>&);};
class Rva00466D50{public:bool rva00466D50(unsigned);};
class TransportBodyView {public:
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s0A();
virtual void s0B();
virtual void s0C();
virtual void s0D();
virtual void s0E();
virtual void s0F();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s1A();
virtual void s1B();
virtual void s1C();
virtual void s1D();
virtual void s1E();
virtual void s1F();
virtual void s20();
virtual void s84(bool);
virtual bool s88();
};
class TransportContainView {public:
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s0A();
virtual void s0B();
virtual void s0C();
virtual void s0D();
virtual void s0E();
virtual void s0F();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s1A();
virtual void s1B();
virtual void s1C();
virtual void s1D();
virtual void s1E();
virtual void*s7C();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual bool s98(Object*,bool,bool);
virtual void s9C(Object*);
};
class Object {public:
 bool hasUpgrade(const UpgradeTemplate*)const;
 char pad00[0x250];TransportContainView*contain;TransportBodyView*body;
 char pad258[0x304-0x258];Team*team;
};
class ThingTemplate {public:char pad00[0x5F1];signed char transportSlots;};
class GlobalData;extern GlobalData*TheWritableGlobalData;
struct TransportGlobalView{char pad00[0xD45];bool flag;};
class AI;extern AI*TheAI;	// 0x009FF0F8 under its converged name; the LOD record view is cast where used
struct TransportLodRecord{char pad00[0xBB];bool flag;};
struct TransportLodView{char pad00[0x18];TransportLodRecord*record;};
extern GameLogic*TheGameLogic;
class TransportContain {public:
 void UpdateUpgradeCreationTriggers();
 char pad00[8];Object*owner;char pad0C[0x20-0xC];TransportContainView iface;
 char pad24[0x110-0x24];_STL::vector<AsciiString,_STL::allocator<AsciiString> >triggers;
};
void TransportContain::UpdateUpgradeCreationTriggers()
{
 _STL::vector<AsciiString,_STL::allocator<AsciiString> >*list=&triggers;
 unsigned count=list->size();Object*obj=owner;
 if(count==0||!obj)return;
 TransportContainView*contain=obj->contain;
 if(!contain)return;
 bool active=false;
 for(unsigned i=0;i<count;++i) {
  if(((const StringBase<char>*)&list->begin()[i])->compare(*(const StringBase<char>*)&AsciiString::TheEmptyString)==0)continue;
  BfmeStringRecord00466E64*record=(list->end() ? (((Rva00467799*)this)->rva00467799(*(StringBase<char>*)&list->begin()[i])) : (((Rva00467799*)this)->rva00467799(*(StringBase<char>*)&list->begin()[i])));
  if(!record)continue;
  active=true;
  const UpgradeTemplate*upgrade=TheUpgradeCenter->findUpgrade(list->begin()[i]);
  if(!upgrade||!obj->hasUpgrade(upgrade))continue;
  ((StringBase<char>*)&list->begin()[i])->clear();
  const ThingTemplate*thingTemplate=TheThingFactory->findTemplate(record->object);
  if(!thingTemplate)continue;
  CreateMask mask;memset(&mask,0,16);
  if(contain->s7C()) {
   if(!((TransportGlobalView*)TheWritableGlobalData)->flag && !(*(unsigned char*)((char*)thingTemplate+0x113)&4) && !(*(unsigned char*)((char*)thingTemplate+0x109)&4) && ((TransportLodView*)TheAI)->record->flag)
    ((unsigned char*)&mask)[6]|=0x80;
  }
  unsigned total=record->count;
  for(unsigned j=0;j<total;++j) {
   if(!((Rva00466D50*)this)->rva00466D50((unsigned)thingTemplate->transportSlots))break;
   Object*created=TheThingFactory->newObject(thingTemplate,(i ? obj->team : obj->team),&mask,(ObjectID)0);
   if(!created)break;
   if(iface.s98(created,false,false)) {
    TransportBodyView*body=obj->body;
    if(body&&body->s88()) {body=created->body;if(body)body->s84(true);}
    contain->s9C(created);
   }else {TheGameLogic->destroyObject(created);break;}
  }
 }
 if(!active)list->erase(list->begin(),list->end());
}
