// ?update@DetachableRiderUpdateUpdateReceiver@@QAE?AW4UpdateSleepTime@@XZ
// partial score=0.9877346278317153 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// cl: /ICode/GameEngine/Source/Common /ICode/GameEngine/Include/GameLogic
// stlport
#include "ascii_string.h"
#include <vector>
#include "GameLogicObjectLookupView.h"
#include "ContainmentListView.h"
// Native004AEC9B..004AEF05 RET0; DetachableRiderUpdate ctor4AE883
// installs C5545C as the+10 secondary update vtable, whose slot0 is this body.
// ModuleData+8 records have nativeIMUL54/19-word masks/OCL50; data14 names,
// 20 weapon slot and24/25 flags. Flag semantics remain neutral.
// Object condition bit265/status39 and containment child relationships are
// target reads. Borrowed descriptor uses canonical opaque4-byte list element.
// Function and interface method names remain neutral where only slots are known.
class ObjectCreationList {public:void create(void*,void*,void*);};
class Drawable {public:void rva002724FD(const AsciiString&,int,int,float,float);};
enum DisabledType{DISABLED4=4};enum WeaponSlotType{WEAPON0=0};enum WeaponLockType{LOCK2=2};enum ObjectStatusTypes{STATUS39=39};enum CommandSourceType{SOURCE2=2};
enum UpdateSleepTime{FOREVER=0x3fffffff};
class AICommandInterface {public:void aiIdle(CommandSourceType);};
struct RiderAI {char pad[0x20];AICommandInterface commands;};
class BfmeSubBGB {public:bool rva00298893();};
class Rva001E42F2 {public:void rva001E42F2(const int*);};
template<int N>class VGap:public VGap<N-1>{public:virtual void gap(char(*)[N]);};template<>class VGap<0>{};
class RiderInterface:public VGap<14>{public:virtual void release(Object*);};
class RiderContainInterface:public VGap<31>{public:virtual RiderInterface*getRider();virtual void s32();virtual void s33();virtual void s34();virtual void s35();virtual void s36();virtual void s37();virtual void s38();virtual void s39();virtual void s40();virtual void remove(Object*,bool);virtual void s42();virtual void s43();virtual void s44();virtual void s45();virtual void s46();virtual void s47();virtual void s48();virtual void s49();virtual void s50();virtual void s51();virtual void s52();virtual void s53();virtual void s54();virtual void s55();virtual void s56();virtual void s57();virtual void s58();virtual void s59();virtual void s60();virtual void s61();virtual void s62();virtual void s63();virtual void s64();virtual void s65();virtual void s66();virtual void s67();virtual void s68();virtual int getCount(bool);virtual Rva0036AE51ListView getList();};
struct RiderConditionBits {
 unsigned words[19];
 __forceinline unsigned test(int bit)const{return words[bit>>5]&(1u<<(bit&31));}
 __forceinline void set(int bit){words[bit>>5]|=1u<<(bit&31);}
 __forceinline void clear(int bit){words[bit>>5]&=~(1u<<(bit&31));}
};
class Object {
public:
 Drawable*getDrawable()const;bool clearDisabled(DisabledType);bool setWeaponLock(WeaponSlotType,WeaponLockType);void releaseWeaponLock(WeaponLockType);void setStatus(ObjectStatusTypes,bool);bool testStatus(ObjectStatusTypes)const;void rva0028AE6D();
 char pad[0x110];RiderConditionBits conditions;char pad15c[0x250-0x15c];RiderContainInterface*contain;char pad254[4];RiderAI*ai;char pad25c[0x274-0x25c];Object*parent;
 __forceinline RiderInterface*getRider(){RiderContainInterface*c=contain;return c?c->getRider():0;}
};
struct RiderRecord {int mask[19];unsigned opaque4c;ObjectCreationList*creation;};
struct RiderData {char pad[8];_STL::vector<RiderRecord> records;_STL::vector<AsciiString> names;WeaponSlotType weapon;bool flag24;bool flag25;};
struct RiderOwnerHead {void*vtable;const RiderData*data;Object*object;};
class DetachableRiderUpdateUpdateReceiver {
public:UpdateSleepTime update();char pad[0x10];bool active;unsigned char index;
};
extern GameLogic*TheGameLogic;
UpdateSleepTime DetachableRiderUpdateUpdateReceiver::update(){
 const RiderData*data=((RiderOwnerHead*)((char*)this-0x10))->data;
 Object*object=((RiderOwnerHead*)((char*)this-0x10))->object;
 Drawable*draw=object->getDrawable();object->clearDisabled(DISABLED4);
 if(active){
  if(draw)for(unsigned i=0;i<data->names.size();++i)draw->rva002724FD(data->names[i],0,0,0.0f,0.0f);
  ObjectCreationList*creation=data->records[index].creation;
  if(creation)creation->create(object,object,0);
  ((Rva001E42F2*)object)->rva001E42F2(data->records[index].mask);
  object->setWeaponLock(data->weapon,LOCK2);object->setStatus(STATUS39,true);
  if(object->conditions.test(265)==0){object->conditions.set(265);object->rva0028AE6D();}
  if(data->flag25){
   Object*parent=object->parent;
   if(parent){
    RiderInterface*rider=parent->getRider();
    if(rider)rider->release(object);else {RiderContainInterface*c=parent->contain;if(c)c->remove(object,false);}
    if(object->ai)object->ai->commands.aiIdle(SOURCE2);
   }
   TheGameLogic->deselectObject(object,0xfffff,true);
  }else if(data->flag24){
   Object*parent=object->parent;
   if(parent){
    if(parent->getRider()){
     int total=parent->contain->getCount(false);int count=0;
     Rva0036AE51ListView list=parent->contain->getList();
     ContainmentList::iterator i=list.b->begin();ContainmentList::iterator begin=i;ContainmentList::iterator end=list.b->end();
     while(i!=end){Object*child=(Object*)containmentFirstWord(*i);if(child->testStatus(STATUS39))++count;++i;}
     if(count==total && begin!=end)do {Object*child=(Object*)containmentFirstWord(*begin);++begin;((BfmeSubBGB*)child)->rva00298893();}while(begin!=list.b->end());
    }
   }else ((BfmeSubBGB*)object)->rva00298893();
  }
 }else{
  if(draw)for(unsigned i=0;i<data->names.size();++i)draw->rva002724FD(data->names[i],1,0,0.0f,0.0f);
  object->releaseWeaponLock(LOCK2);object->setStatus(STATUS39,false);
  if(object->conditions.test(265)!=0){object->conditions.clear(265);object->rva0028AE6D();}
 }
 return FOREVER;
}
