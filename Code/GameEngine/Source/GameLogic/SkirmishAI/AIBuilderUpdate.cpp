// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// WB136EAF0 names AIBuilder::update; native4ECB19..4ECD9F RET0 full646.
// BF1/ZH lack this BF2 controller. Caller SkirmishAI and existing owner rows
// prove AIBuilder; accessed fields and virtual slots below are target facts.
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "ascii_string.h"
#include <vector>
#include <list>
// Keep vector<void*>::empty inline without emitting this unit's /O1 COMDAT
// copy (retail's out-of-line accessors are the /Od bodies at 0x00023B90-0x00023C20).
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool vector<void*>::empty() const { return this->_M_start == this->_M_finish; }
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::erase(list<int, allocator<int> >::iterator);
}

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
class Player;class Object{public:char pad[0x74];ObjectID id;};
extern GameLogic*TheGameLogic;
#include "../../../Include/Common/Rva004E9378.h"
#include "../../../Include/GameLogic/Rva00506B1B.h"
#include "../../../Include/GameLogic/Rva0055ADD8.h"
#include "../../../Include/Common/AIBuildable.h"
class AIUnitBuilder{public:Object*Rva005982EA(const AsciiString*,_STL::vector<ObjectID>*,bool);};
struct Rva005996FFArg;
#include "../../../../Libraries/Source/WWVegas/WWLib/Rva005996FF.h"
#include "../../../Include/GameLogic/AIDozerManager.h"
// 0x00599870 is rowed as Rva005997CD::rva00599870 (Rva005997CDNearestPick.cpp),
// the nearest-entry pick over the dozer manager; called by that row's name.
struct Vec2;
class Rva005997CD{public:ObjectID rva00599870(const Vec2*,bool);};
// Existing dozer callee pin retains its opaque four-byte return spelling;
// this caller consumes those bits as ObjectID without dereferencing them.
class Rva004ECB19Entry{
public:
 virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
 virtual bool slot04();virtual void slot05();virtual void slot06();virtual void slot07(int);
 virtual void slot08();virtual void slot09();virtual void slot10();virtual bool slot11();
 virtual void slot12();virtual Coord3D slot13();
 float word04;ObjectID producer08;AsciiString name0C;char gap10[0x28-0x10];bool flag28;
};
class AIBuilder{
public:void update();void checkForNewUpgrades();void rva004EC700();void moneySaverUpdate();
 Player*owner00;char gap04[0x130-4];_STL::vector<void*>entries130;_STL::list<int>orders13C;AIDozerManager dozer140;
};
void AIBuilder::update(){
 _STL::list<int>::iterator order=orders13C.begin();
 while(order!=orders13C.end()){
  if(((Rva004E9378*)*order)->rva004E9378())order=orders13C.erase(order);else ++order;
 }
 checkForNewUpgrades();
 ((Rva00506B1B*)((char*)this+4))->rva00506B2F();
 ((Rva00506B1B*)((char*)this+0xE4))->rva00506B2F();
 ((Rva00506B1B*)((char*)this+0x38))->rva00506B2F();
 ((Rva00506B1B*)((char*)this+0x90))->rva00506B2F();
 ((Rva00506B1B*)((char*)this+0xC0))->rva00506B2F();
 ((Rva00506B1B*)((char*)this+0x108))->rva00506B2F();
 ((Rva00506B1B*)((char*)*(void**)((char*)this+0x12C)+0xC))->rva00506B2F();
 _STL::vector<void*>::iterator it=entries130.begin();
 while(it!=entries130.end()){
  Rva004ECB19Entry*entry=(Rva004ECB19Entry*)*it;
  if(((Rva004E9378*)entry)->rva004E9378())it=entries130.erase(it);
  else{entry->slot05();++it;}
 }
 if(!entries130.empty()){
  unsigned dozerCount=((_STL::list<int>*)((char*)&dozer140+4))->size();
  rva004EC700();
  for(it=entries130.begin();it!=entries130.end();++it){
   Rva004ECB19Entry*entry=(Rva004ECB19Entry*)*it;bool assigned=false;
   if(entry->slot11()){
    Object*created=((AIUnitBuilder*)((char*)this+0x38))->Rva005982EA(&entry->name0C,0,false);
    if(created){
    entry->producer08=created->id;assigned=true;}else{if(0){AsciiString unused;}entry->producer08=INVALID_OBJECT_ID;continue;}
   }
   if(entry->slot04()&&entry->flag28){entry->producer08=((Rva005997CD*)&dozer140)->rva00599870((const Vec2*)&entry->slot13(),false);assigned=true;}
   int can=((AIBuildable*)entry)->doCanMake(owner00);
   if(can==0||(can==8&&dozerCount>0)||can==2){
    Rva004ECB19Entry*selected=entry;
    bool success=false;
    if(can==0){
     if(((AIBuildable*)selected)->doBuild(owner00)){
      orders13C.push_back((const int&)selected);selected->slot07(1);
      if(selected->slot04())((Rva005996FF*)&dozer140)->unRegisterDozer((Rva005996FFArg*)TheGameLogic->findObjectByID(selected->producer08),false);
      success=true;
     }else ((Rva0055ADD8*)selected)->failBuild((int)owner00);
     entries130.erase(it);
    }
    if(!success&&assigned)selected->producer08=INVALID_OBJECT_ID;
    break;
   }
   if(assigned)entry->producer08=INVALID_OBJECT_ID;
   if(can==10)((Rva0055ADD8*)entry)->failBuild((int)owner00);
  }
 }
 for(it=entries130.begin();it!=entries130.end();){
  if(((Rva004E9378*)*it)->rva004E9378())it=entries130.erase(it);else ++it;
 }
 dozer140.rva00599EDC();moneySaverUpdate();
}
