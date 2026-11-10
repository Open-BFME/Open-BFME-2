// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// Native 0x005E52FD..0x005E5424 is the complete 295-byte Populate body.
// WB 0x015F8D00 names ArmyDetailsPanel::Impl::Populate (source lines624..655).
// Preserve the existing Rva005E39AE owner ABI used by its verified122B caller.
// Target army+78 gives the summary; its +40/+44 array has eight-byte entries.
// WB15F7100 and comparator5E4300 establish the four-byte army-context functor.
// The sort family now has that same stateful owner throughout; no alias pins.
// ScienceType reserve/push_back are existing four-byte storage providers,
// as in the verified EntryAdded sibling; no science identity is inferred.
// Retail EH mapD5BDA8 keeps vector[-2C] in state0 and entry[-18] in state1.
// The temporary icon uses its existing provisional SBServer provider ABI.
// Keep the unsigned comparison local: this TU's standalone template copy
// differs from retail's provider; its existing callers inline the comparison.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "ascii_string.h"
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template<> __declspec(dllimport) __forceinline void allocator<int>::deallocate(int *p,size_t) const {if(p)Rva00030830GameFree(p);}
template<> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<int *, int, allocator<int> >::deallocate(int *p, size_t n) { __stl_alloc_rebind(static_cast<allocator<int> &>(*this), (int *)0).deallocate(p, n); }
}
#include "../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct SBServer {
 void *handle;
 SBServer(); SBServer(const SBServer &);
 ~SBServer(){if(handle)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)handle+((int **)handle)[0][1]));}
};
#include "../../../../Include/Common/ArmySummaryEntry.h"
class Rva004F6093Holder {
public:
 Rva004F6093Holder():m_p(0){}
 Rva004F6093Holder(const Rva004F6093Holder &);
 ~Rva004F6093Holder(){if(m_p)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)m_p+0xAC));}
 ArmySummaryEntry *get() const {return m_p;}
private: ArmySummaryEntry *m_p;
};
struct ArmySummaryEntryRef {Rva004F6093Holder m_holder;};
struct ArmyDetailsSummaryRecord {int key;void *entry;};
class ArmySummary {public:ArmySummaryEntryRef GetEntry(int);char pad[0x40];ArmyDetailsSummaryRecord *begin,*end;};
class Rva0040CC0EIndexedField {public:int get(int) const;};
struct ArmyDetailsArmyView {char pad[0x18];AsciiString name;char gap[0x78-0x1C];ArmySummary *summary;};
struct Rva005E4300Context;
#include "../../../../../Libraries/Source/WWVegas/WWLib/Rva005E4300Cmp.h"
namespace _STL {template<class It,class Cmp> void sort(It,It,Cmp);}
struct Rva002BA8F1Listener;
#include "../../../../Include/Common/Rva005A0B4CList.h"
enum ScienceType {SCIENCE_NONE=0};
namespace StrategicInGameUI {class ArmyDetailsPanel {public:class Impl {public:SBServer CreateIcon(int,ArmySummaryEntry*);};};}
class Rva005E39AE {public:
 void rva005E52FD();
 char prefix[0x10];ArmyDetailsArmyView *army;char gap[0x2c-0x14];bool populated;
};
void Rva005E39AE::rva005E52FD() {
 ArmySummary *summary=army->summary;
 if(summary) {
  int entryCount=summary->end-summary->begin;
  _STL::vector<int> entryIDs;
  ((_STL::vector<ScienceType> *)&entryIDs)->reserve(entryCount);
  for(int i=0;i<entryCount;++i) {
   int id=((Rva0040CC0EIndexedField *)summary)->get(i);
   ((_STL::vector<ScienceType> *)&entryIDs)->push_back((const ScienceType &)id);
  }
  _STL::sort(entryIDs.begin(),entryIDs.end(),Rva005E4300Cmp((Rva005E4300Context *)army));
  for(int i=0;i<entryCount;++i) {
   int entryID=entryIDs[i];
   ArmySummaryEntryRef entry=summary->GetEntry(entryID);
   if(entry.m_holder.get()->CarryoverUnit::m_name!=army->name)
    ((StrategicInGameUI::ArmyDetailsPanel::Impl*)this)->CreateIcon(entryID,entry.m_holder.get());
  }
  ((Rva005A0B4CList*)((char*)summary+4))->append((Rva002BA8F1Listener*)this);
 }
 populated=true;
}
