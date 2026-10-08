// ?CalcPlayerRemap@Impl@StrategicConflictResults@@QAEXXZ
// partial score=1.0 date=2026-10-08
// cl: /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT
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
#include <stdio.h>
#undef _CRTIMP
#define _CRTIMP
#include <map>
class StrategicConflictResults {public:class Impl;};
class Rva00226883 {public:void rva0022999F();};
struct StrategicBattleSideCountView {char unknown00[28];};
extern "C" unsigned char *__cdecl _mbscpy(unsigned char *,const unsigned char *);

struct RGBColor { int getAsInt()const;float red,green,blue;};
class LivingWorldBattle {public:int rva003F459A();int getSide()const {return side;}int getSideCount()const {return sideEnd-sideBegin;}char unknown00[0x18];StrategicBattleSideCountView *sideBegin,*sideEnd,*sideCapacity;char unknown24[0x14];int side;};
class Rva003F468D {public:int rva003F468D(int,int);int rva003F4DAE(int);};
struct StrategicPlayerColorView {char unknown00[0x184];RGBColor color;};
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
