// cl: /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /O1 /G7 /arch:SSE /DNDEBUG /MD
// Link view first: scalar Vector3 operator* stays inline without emitting a copy that competes with retail's owners (0x00066382, 0x0007DFB3).
#include "../../../../../reference/shims/bfme_vector3_full_link/vector3_full_link.h"
// Retail E1669..E185E, 503B RET8, vtable BCE788 slot141. Target
// independently proves grid3888/width3890/height3894, D4-byte cells and
// cell+0C center/extent box, filter slot130 (208), and 24B output.
// Existing FlatHeightMap.cpp/FlatHeightMapUpdateCenter.cpp rows establish
// the same tile storage/stride/dimensions; this file belongs to that terrain
// subsystem. Original virtual method/receiver names remain address-derived.
// Clean BFME1 cee35b7d8 WWMath aabox.h/vector3.h provide the min/max and
// center/extent arithmetic. Target Is_Empty call uses AL; the owned opaque
// Rva00719800 int-return view is explicitly truncated to preserve that ABI.
// Init_Empty7197D0 and predicate719800 are owned providers; no new pins.
// Wrapping if/else preserves the early shared zero block; staged Vector3
// Update_Min/Update_Max (not Add_Box) and AABox::Init preserve native SIMD
// order. Upper point is Extent+Center to reproduce the last two byte fields.
#include "aabox.h"
class Rva00719800 {public:int rva00719800()const;};
class BoundsFilterView {public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
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
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual void s31();
 virtual void s32();
 virtual void s33();
 virtual void s34();
 virtual void s35();
 virtual void s36();
 virtual void s37();
 virtual void s38();
 virtual void s39();
 virtual void s40();
 virtual void s41();
 virtual void s42();
 virtual void s43();
 virtual void s44();
 virtual void s45();
 virtual void s46();
 virtual void s47();
 virtual void s48();
 virtual void s49();
 virtual void s50();
 virtual void s51();
 virtual void s52();
 virtual void s53();
 virtual void s54();
 virtual void s55();
 virtual void s56();
 virtual void s57();
 virtual void s58();
 virtual void s59();
 virtual void s60();
 virtual void s61();
 virtual void s62();
 virtual void s63();
 virtual void s64();
 virtual void s65();
 virtual void s66();
 virtual void s67();
 virtual void s68();
 virtual void s69();
 virtual void s70();
 virtual void s71();
 virtual void s72();
 virtual void s73();
 virtual void s74();
 virtual void s75();
 virtual void s76();
 virtual void s77();
 virtual void s78();
 virtual void s79();
 virtual void s80();
 virtual void s81();
 virtual void s82();
 virtual void s83();
 virtual void s84();
 virtual void s85();
 virtual void s86();
 virtual void s87();
 virtual void s88();
 virtual void s89();
 virtual void s90();
 virtual void s91();
 virtual void s92();
 virtual void s93();
 virtual void s94();
 virtual void s95();
 virtual void s96();
 virtual void s97();
 virtual void s98();
 virtual void s99();
 virtual void s100();
 virtual void s101();
 virtual void s102();
 virtual void s103();
 virtual void s104();
 virtual void s105();
 virtual void s106();
 virtual void s107();
 virtual void s108();
 virtual void s109();
 virtual void s110();
 virtual void s111();
 virtual void s112();
 virtual void s113();
 virtual void s114();
 virtual void s115();
 virtual void s116();
 virtual void s117();
 virtual void s118();
 virtual void s119();
 virtual void s120();
 virtual void s121();
 virtual void s122();
 virtual void s123();
 virtual void s124();
 virtual void s125();
 virtual void s126();
 virtual void s127();
 virtual void s128();
 virtual void s129();
 virtual bool exclude(const AABoxClass&)const;
};
struct BoundsGridD4 {char prefix[12];AABoxClass box;char tail[0xd4-36];};
class Rva000E3B41 {public:
 virtual void ownerSlot0();
 virtual void ownerSlot1();
 virtual void ownerSlot2();
 virtual void ownerSlot3();
 virtual void ownerSlot4();
 virtual void ownerSlot5();
 virtual void ownerSlot6();
 virtual void ownerSlot7();
 virtual void ownerSlot8();
 virtual void ownerSlot9();
 virtual void ownerSlot10();
 virtual void ownerSlot11();
 virtual void ownerSlot12();
 virtual void ownerSlot13();
 virtual void ownerSlot14();
 virtual void ownerSlot15();
 virtual void ownerSlot16();
 virtual void ownerSlot17();
 virtual void ownerSlot18();
 virtual void ownerSlot19();
 virtual void ownerSlot20();
 virtual void ownerSlot21();
 virtual void ownerSlot22();
 virtual void ownerSlot23();
 virtual void ownerSlot24();
 virtual void ownerSlot25();
 virtual void ownerSlot26();
 virtual void ownerSlot27();
 virtual void ownerSlot28();
 virtual void ownerSlot29();
 virtual void ownerSlot30();
 virtual void ownerSlot31();
 virtual void ownerSlot32();
 virtual void ownerSlot33();
 virtual void ownerSlot34();
 virtual void ownerSlot35();
 virtual void ownerSlot36();
 virtual void ownerSlot37();
 virtual void ownerSlot38();
 virtual void ownerSlot39();
 virtual void ownerSlot40();
 virtual void ownerSlot41();
 virtual void ownerSlot42();
 virtual void ownerSlot43();
 virtual void ownerSlot44();
 virtual void ownerSlot45();
 virtual void ownerSlot46();
 virtual void ownerSlot47();
 virtual void ownerSlot48();
 virtual void ownerSlot49();
 virtual void ownerSlot50();
 virtual void ownerSlot51();
 virtual void ownerSlot52();
 virtual void ownerSlot53();
 virtual void ownerSlot54();
 virtual void ownerSlot55();
 virtual void ownerSlot56();
 virtual void ownerSlot57();
 virtual void ownerSlot58();
 virtual void ownerSlot59();
 virtual void ownerSlot60();
 virtual void ownerSlot61();
 virtual void ownerSlot62();
 virtual void ownerSlot63();
 virtual void ownerSlot64();
 virtual void ownerSlot65();
 virtual void ownerSlot66();
 virtual void ownerSlot67();
 virtual void ownerSlot68();
 virtual void ownerSlot69();
 virtual void ownerSlot70();
 virtual void ownerSlot71();
 virtual void ownerSlot72();
 virtual void ownerSlot73();
 virtual void ownerSlot74();
 virtual void ownerSlot75();
 virtual void ownerSlot76();
 virtual void ownerSlot77();
 virtual void ownerSlot78();
 virtual void ownerSlot79();
 virtual void ownerSlot80();
 virtual void ownerSlot81();
 virtual void ownerSlot82();
 virtual void ownerSlot83();
 virtual void ownerSlot84();
 virtual void ownerSlot85();
 virtual void ownerSlot86();
 virtual void ownerSlot87();
 virtual void ownerSlot88();
 virtual void ownerSlot89();
 virtual void ownerSlot90();
 virtual void ownerSlot91();
 virtual void ownerSlot92();
 virtual void ownerSlot93();
 virtual void ownerSlot94();
 virtual void ownerSlot95();
 virtual void ownerSlot96();
 virtual void ownerSlot97();
 virtual void ownerSlot98();
 virtual void ownerSlot99();
 virtual void ownerSlot100();
 virtual void ownerSlot101();
 virtual void ownerSlot102();
 virtual void ownerSlot103();
 virtual void ownerSlot104();
 virtual void ownerSlot105();
 virtual void ownerSlot106();
 virtual void ownerSlot107();
 virtual void ownerSlot108();
 virtual void ownerSlot109();
 virtual void ownerSlot110();
 virtual void ownerSlot111();
 virtual void ownerSlot112();
 virtual void ownerSlot113();
 virtual void ownerSlot114();
 virtual void ownerSlot115();
 virtual void ownerSlot116();
 virtual void ownerSlot117();
 virtual void ownerSlot118();
 virtual void ownerSlot119();
 virtual void ownerSlot120();
 virtual void ownerSlot121();
 virtual void ownerSlot122();
 virtual void ownerSlot123();
 virtual void ownerSlot124();
 virtual void ownerSlot125();
 virtual void ownerSlot126();
 virtual void ownerSlot127();
 virtual void ownerSlot128();
 virtual void ownerSlot129();
 virtual void ownerSlot130();
 virtual void ownerSlot131();
 virtual void ownerSlot132();
 virtual void ownerSlot133();
 virtual void ownerSlot134();
 virtual void ownerSlot135();
 virtual void ownerSlot136();
 virtual void ownerSlot137();
 virtual void ownerSlot138();
 virtual void ownerSlot139();
 virtual void ownerSlot140();
 char prefix[0x3888-4];BoundsGridD4 *grid;int unknown388C;int width,height;
 virtual void vslot141(const BoundsFilterView*,AABoxClass*);
};
__forceinline void zeroBounds(AABoxClass*out){out->Center.Set(0,0,0);out->Extent.Set(0,0,0);}
// ?vslot141@Rva000E3B41@@UAEXPBVBoundsFilterView@@PAVAABoxClass@@@Z @0x000E1669: slot 141 of retail's table 0x00BCE788.
void Rva000E3B41::vslot141(const BoundsFilterView*filter,AABoxClass*out){
 if(!grid){zeroBounds(out);}
 else {
 MinMaxAABoxClass bounds;bounds.Init_Empty();
 for(int column=0;column<width;++column) {
  for(int row=0;row<height;++row) {
   const AABoxClass &box=grid[row*width+column].box;
   if(filter->exclude(box))continue;
   if(box.Extent.X==0 && box.Extent.Y==0 && box.Extent.Z==0)continue;
   Vector3 low=box.Center-box.Extent;
   bounds.MinCorner.Update_Min(low);
   Vector3 high=box.Extent+box.Center;
   bounds.MaxCorner.Update_Max(high);
  }
 }
 if((unsigned char)((const Rva00719800*)&bounds)->rva00719800()){zeroBounds(out);}
 else {
 out->Init(bounds);
 }
 }
}
