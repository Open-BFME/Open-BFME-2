// cl: /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT
//
// ?CalcPlayerRemap@Impl@StrategicConflictResults@@QAEXXZ, retail 0x005ebcce, 241 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
// WB15E8D20 names StrategicConflictResults::Impl::CalcPlayerRemap in
// GameClient/Gui/InGame/Strategic/StrategicConflictResults.cpp.
// Native5EBCCE..5EBDBF proves winner-first selector packing (side*10000+army)
// into maps38/44, battle pointer0C, winning side38 and side-vector18/1C
// with28B elements. Existing69B aggregate count corroborates outer stride.
// Full STLport definitions close the earlier spill/induction mismatch;
// declaration-only operator[] loses interprocedural optimization and is not
// a byte match. Complete compiled body241 equals retail with no unresolved
// relocations. Canonical /O1 allocator/layout flags add zero new COMDAT
// variants but the unit still fails link preview with12 conflicting copies
// and8 wrong-selected names. This is banked evidence, not a live recovery.
// Shared tree/allocator provider repair is needed before publication.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <mbstring.h>
#include <stdio.h>
#undef _CRTIMP
#define _CRTIMP
#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
class StrategicConflictResults {public:class Impl;};
class Rva00226883 {public:void rva0022999F();};
struct StrategicBattleSideCountView {char unknown00[28];};

#include "../../../Libraries/Include/Lib/RGBColor.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _Rb_tree_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> > > _Rb_tree<int,pair<int const ,int>,_Select1st<pair<int const ,int> >,less<int>,allocator<pair<int const ,int> > >::insert_unique(_Rb_tree_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> > >,pair<int const ,int> const &); }
// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool>::pair(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > const &, bool const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator++(); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator--(); }
namespace _STL { template <> _Rb_tree_node<pair<int const, int> > * _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_M_create_node(pair<int const, int> const &); }
// bfme link decl-only end
class LivingWorldBattle {public:int rva003F459A();int getSide()const {return side;}int getSideCount()const {return sideEnd-sideBegin;}char unknown00[0x18];StrategicBattleSideCountView *sideBegin,*sideEnd,*sideCapacity;char unknown24[0x14];int side;};
#include "../../Include/Common/Rva003F468D.h"
class StrategicConflictResults::Impl {public:
 void ExternPlayerColor(int,char *,bool);
 void ExternFunc(int,char *,bool);
 void CalcPlayerRemap();
 char unknown00[0xC];LivingWorldBattle *battle;char unknown10[0x28];_STL::map<int,int> players,inverse;
};
void StrategicConflictResults::Impl::CalcPlayerRemap() {
 if(!battle)return;
 reinterpret_cast<Rva00226883 *>(&players)->rva0022999F();
 reinterpret_cast<Rva00226883 *>(&inverse)->rva0022999F();
 int winningSide=battle->getSide();
 int flat=0;
 int count=reinterpret_cast<Rva003F468D *>(battle)->rva003F4DAE(winningSide);
 for(int army=0;army<count;++army){
  int packed=winningSide*10000+army;
  players[flat]=packed;
  inverse[packed]=flat;
  ++flat;
 }
 for(int side=0;side<battle->getSideCount();++side){
  if(side==winningSide)continue;
  count=reinterpret_cast<Rva003F468D *>(battle)->rva003F4DAE(side);
  for(int army=0;army<count;++army){
   int packed=side*10000+army;
   players[flat]=packed;
   inverse[packed]=flat;
   ++flat;
  }
 }
}
