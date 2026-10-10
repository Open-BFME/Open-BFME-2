// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common /ICode/GameEngine/Include/GameLogic
// stlport
// Native0050AEE4..0050B107 RET8; WB10A8310 same source/containment
// call graph establishes relationship, with different Object offsets and
// target virtual slots. No applicable clean donor was found in BFME1/ZH.
// Queue's WeaponSet signature is refuted: native accepts a source-ID record
// and targetObject. Receiver name remains address-derived; its limit128,
// masks12C/148 and death164 are target reads, not a reconstructed full class.
// Existing BitFlags<116> ABI retains the proven seven-word target mask.
// Native outer and nested containment copies use the canonical opaque4B
// list and owned36AE51/4EC395 helpers. Static HordeContain key and guard are
// local target data; primary module+20 supplies the nested containment view.
#include "GameLogicObjectLookupView.h"
#include "ContainmentListView.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
#include <list>
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
namespace _STL { template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base(); }
enum NameKeyType{INVALIDKEY=0};
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator*TheNameKeyGenerator;
class Rva00294D61 {public:void report(Object*,int);};
enum DamageType{UNRESISTABLE=8};enum DeathType{NORMAL=0};
template<int N>class VGap:public VGap<N-1>{public:virtual void gap(char(*)[N]);};template<>class VGap<0>{};
class Contain:public VGap<4>{public:virtual bool slot4();virtual void slot5();virtual void slot6();virtual bool slot7();virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();virtual void slot16();virtual void slot17();virtual void slot18();virtual void slot19();virtual void slot20();virtual void slot21();virtual void slot22();virtual void slot23();virtual void slot24();virtual void slot25();virtual void slot26();virtual void slot27();virtual void slot28();virtual void slot29();virtual void slot30();virtual void slot31();virtual void slot32();virtual void slot33();virtual void slot34();virtual void slot35();virtual void slot36();virtual void slot37();virtual void slot38();virtual void slot39();virtual void slot40();virtual void slot41();virtual void slot42();virtual void slot43();virtual void slot44();virtual void slot45();virtual void slot46();virtual void slot47();virtual void slot48();virtual void slot49();virtual void slot50();virtual void slot51();virtual void slot52();virtual void slot53();virtual void slot54();virtual void slot55();virtual void slot56();virtual void slot57();virtual void slot58();virtual void slot59();virtual void slot60();virtual void slot61();virtual void slot62();virtual void slot63();virtual void slot64();virtual void slot65();virtual void slot66();virtual void slot67();virtual void slot68();virtual unsigned getCount(bool);virtual Rva0036AE51ListView getList();};
struct TargetTemplate {char pad[0x115];unsigned char bits115;};
extern GameLogic*TheGameLogic;
template<int N>class BitFlags {public:unsigned words[7];};
class Module;
class Thing {public:bool isKindOfMulti(const BitFlags<116>&,const BitFlags<116>&)const;};
class Object:public Thing {protected:Module*findModule(NameKeyType)const;friend class Rva0050AEE4Nugget;public:void kill(DamageType,DeathType);char pad[4];TargetTemplate*data;char pad8[0x250-8];Contain*contain;char pad254[0x438-0x254];unsigned char deadBits;};
struct SourceRecord {char pad[8];ObjectID source;};
class Rva0050AEE4Nugget {public:void rva0050AEE4(SourceRecord*,Object*);char prefix[0x128];int limit;BitFlags<116> mask;BitFlags<116> forbidden;DeathType death;};
void Rva0050AEE4Nugget::rva0050AEE4(SourceRecord*record,Object*target){
 if(!target||!record)return;
 Object*source=TheGameLogic->findObjectByID(record->source);
 if(!source)return;
 Contain*contain=target->contain;
 if(!contain||contain->getCount(false)<=0||!contain->slot4()||contain->slot7())return;
 int processed=0;
 ContainmentList list=contain->getList().rva0036AE51();
 for(ContainmentList::iterator i=list.begin();i!=list.end()&&processed<limit;){
  Object*child=(Object*)containmentFirstWord(*i++);
  if(!child || (child->deadBits&1) || !child->isKindOfMulti(mask,forbidden))continue;
  if(child->data->bits115&0x20){
   static NameKeyType key=(NameKeyType)TheNameKeyGenerator->nameToKey("HordeContain");
   void*module=child->findModule(key);
   if(module){
    ContainmentList nested=((Contain*)((char*)module+0x20))->getList().rva0036AE51();
    for(ContainmentList::iterator j=nested.begin();j!=nested.end()&&processed<limit;){
     Object*child=(Object*)containmentFirstWord(*j++);
     if(child && !(child->deadBits&1) && child->isKindOfMulti(mask,forbidden)){
      ((Rva00294D61*)source)->report(child,1);child->kill(UNRESISTABLE,death);++processed;
     }
    }
   }
  }else{((Rva00294D61*)source)->report(child,1);child->kill(UNRESISTABLE,death);++processed;}
 }
}
