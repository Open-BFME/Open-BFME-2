// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Dedicated TU: NestedRecordLookupRva003F6D35.cpp carries the matched
// 0x3F6D35 row under its own /EHsc /MD flags; this body needs /O1 /G7.
// R1 template visibility: dropping the three explicit vector/find
// specialization declarations restores retail's base-load order. Exact 168B.
// Keep vector growth's unsigned comparison local. Its standalone template
// copy differs from retail; all uses in this unit are already inlined.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
 return a < b ? b : a;
}
}
#include <vector>
#include <algorithm>
// Suppress this TU's non-retail copy of ??$_Construct@UBfmePod104@@U1@@_STL@@YAXPAUBfmePod104@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod104;
namespace _STL { template <> void _Construct<BfmePod104,BfmePod104>(BfmePod104 *,BfmePod104 const &); }
// Suppress this TU's non-retail copy of ?push_back@?$vector@UBfmePod104@@V?$allocator@UBfmePod104@@@_STL@@@_STL@@QAEXABUBfmePod104:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod104;
namespace _STL { template <> void vector<BfmePod104,allocator<BfmePod104> >::push_back(BfmePod104 const &); }
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}
// The overflow body is supplied by StlportVectorInsertOverflowFamily.cpp.
struct BfmePod104;
namespace _STL {
template <> void vector<BfmePod104, allocator<BfmePod104> >::_M_insert_overflow(BfmePod104 *, const BfmePod104 &, const __false_type &, unsigned int, bool);
}

class ModuleData;
class CreateAHeroData;
struct BfmePod104 { int data[26]; };
namespace _STL {



}
struct Rva003F6DF9Child {char pad98[0x98];unsigned field98;char pad9c[0xc];bool flaga8;};
struct Rva003F6DF9Entry {unsigned word;Rva003F6DF9Child *child;};
struct Rva003F6DF9Data {char pad2c[0x2c];unsigned dirty;char pad30[0x10];_STL::vector<Rva003F6DF9Entry> entries;char pad4c[0x1c];};
#include "../../../../GameEngine/Include/GameLogic/LivingWorldBattle.h"
struct Rva002BA8F1Listener;
class Rva005A0B4CList {public:void append(Rva002BA8F1Listener*);private:void*words[3];};
struct Rva003F6DF9Payload {char pad8[8];Rva005A0B4CList listeners;char pad14[0x64];Rva003F6DF9Data *data;};
#include "../../../../GameEngine/Include/GameLogic/Rva0040CB2CIndexedField.h"
struct Rva003F6D35Inner {
 unsigned word;_STL::vector<const ModuleData*> payloads;_STL::vector<BfmePod104> data;unsigned tail[5];
};
class Rva003F6D35Owner { public: Rva003F6D35Inner *findOrCreateRva003F6D35(void *); };
void LivingWorldBattle::AddArmy(int input,void *payload){
 Rva003F6D35Inner *inner=((Rva003F6D35Owner *)this)->findOrCreateRva003F6D35((void *)input);
 Rva003F6DF9Data *data=((Rva003F6DF9Payload *)payload)->data;
 if(data)data->dirty=0;
 input=(int)payload; CreateAHeroData *&search=(CreateAHeroData*&)input;
 if(_STL::find((CreateAHeroData**)inner->payloads.begin(),(CreateAHeroData**)inner->payloads.end(),search)==(CreateAHeroData**)inner->payloads.end()){
  input=(int)payload; const ModuleData *&entry=(const ModuleData*&)input;
  inner->payloads.push_back(entry);
  inner->data.push_back(*(BfmePod104*)data);
  if(data){
   int count=data->entries.size();
   for(int i=0;i<count;++i){
    Rva003F6DF9Child *child=(Rva003F6DF9Child*)((Rva0040CB2CIndexedField*)data)->get(i);
    child->field98=0;child->flaga8=false;
   }
  }
  ((Rva003F6DF9Payload *)payload)->listeners.append((Rva002BA8F1Listener*)static_cast<LivingWorldBattleListener*>(this));
 }
}
