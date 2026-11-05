// RousingSpeechUpdate primary vtable slot17 identifies the trigger override.
// The GameLogic receiver of the leader lookup is an equal-arm conditional (late-folded ?:),
// which reproduces retail's register order for findObjectByID (W7-R1 lever).
// WB draft supplies the class/purpose; retail independently establishes data+4,
// owner+8, affected list+88, MD FX+D8/modifiers+E4/levelUp+F0, Object
// condition-word+124, contain+250, XP+264 and leader ID+44C. Model words
// are only the observed seven-word prefix beginning +10C, not a whole class.
// Callable identities are existing owned rows; vector copy BC07E/dtor2CC70,
// lookup49DC5, modifier28EA91, notifier28AE6D, FX B2235, XP39B4EC,
// callback4ACD8E, base45108D and collector4AD176 all resolve.
// 343/345: sole instruction difference at target4AD4B0: ECX receiver is
// coalesced instead of native EBX, omitting MOV ECX,EBX before call+110.
// The retail contain access follows the null guard (and can dereference null).
// cl:  /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <list>
#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
namespace _STL {
template<>vector<AsciiString>::vector(const vector<AsciiString>&);
template<>vector<AsciiString>::~vector();
template<class I,class L,class R>static inline bool operator!=(const _List_iterator<I,L>&a,const _List_iterator<I,R>&b){return a._M_node!=b._M_node;}
}
class Object;
void rva004ACD8E(Object *);
#include "../../../../Include/GameLogic/ExperienceTracker.h"
class SpeechContainedCallView {public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();
 virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();
 virtual void s20();virtual void s21();virtual void s22();virtual void s23();virtual void s24();virtual void s25();virtual void s26();virtual void s27();virtual void s28();virtual void s29();
 virtual void s30();virtual void s31();virtual void s32();virtual void s33();virtual void s34();virtual void s35();virtual void s36();virtual void s37();virtual void s38();virtual void s39();
 virtual void s40();virtual void s41();virtual void s42();virtual void s43();virtual void s44();virtual void s45();virtual void s46();virtual void s47();virtual void s48();virtual void s49();
 virtual void s50();virtual void s51();virtual void s52();virtual void s53();virtual void s54();virtual void s55();virtual void s56();virtual void s57();virtual void s58();virtual void s59();
 virtual void s60();virtual void s61();virtual void s62();virtual void s63();virtual void s64();virtual void s65();virtual void s66();virtual void s67();
 virtual void iterateContained(void (*)(Object*,void*),void*,int);
};
class Object {public:
 bool addAttributeModifierToPool(const AsciiString &,int);
 void rva0028AE6D();
 char unknown00[0x74];ObjectID id;char unknown78[0x10c-0x78];
 struct WordMask {unsigned words[7];__forceinline unsigned test(int n)const{return words[n/32]&(1u<<(n%32));} __forceinline void set(int n){words[n/32]|=1u<<(n%32);}} condition;
 char unknown128[0x250-0x128];SpeechContainedCallView *contained250;
 char unknown254[0x264-0x254];ExperienceTracker *experience264;
 char unknown268[0x44c-0x268];ObjectID leader44c;
};
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};
class RousingSpeechUpdateModuleData {public:
 char unknown00[0xd8];const FXList *followerFX;char unknownDC[8];
 _STL::vector<AsciiString> modifiers;bool levelUp;
};
#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"
class RousingSpeechUpdate:public SpecialAbilityUpdate {public:
 virtual void triggerAbilityEffect();void rva004AD176();
 _STL::list<ObjectID> affected;
};
void RousingSpeechUpdate::triggerAbilityEffect()
{
 const RousingSpeechUpdateModuleData *md=(const RousingSpeechUpdateModuleData *)m_moduleData;
 SpecialAbilityUpdate::triggerAbilityEffect();
 rva004AD176();
 if(!affected.empty()) {
   _STL::vector<AsciiString> names(md->modifiers);
   for(AsciiString *name=names.begin();name!=names.end();++name) {
     for(_STL::list<ObjectID>::iterator id=affected.begin();id!=affected.end();++id) {
       Object *target=TheGameLogic->findObjectByID(*id);
       if(target) {
         target->addAttributeModifierToPool(*name,-1);
         if(!target->condition.test(201)){target->condition.set(201);target->rva0028AE6D();}
         target->leader44c=m_object->id;
         const FXList *fx=md->followerFX;
         if(fx)FXList::doFXObj(fx,target,0);
       }
     }
   }
   bool levelUp = md->levelUp;
   if(levelUp) {
     for(_STL::list<ObjectID>::iterator id=affected.begin();id!=affected.end();++id) {
       Object *target=(TheGameLogic ? TheGameLogic : TheGameLogic)->findObjectByID(*id);
       if(target)target->experience264->rva0039B4EC(1,true,false);
       SpeechContainedCallView *contained=target->contained250;
       if(contained)contained->iterateContained(reinterpret_cast<void(*)(Object*,void*)>(&rva004ACD8E),0,1);
     }
   }
 }
}
