// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// Native 0x005E4E55..0x005E4F6D (RET8), WB015F9790 lines774-802.
// Counted icon creation, entry-ID filtering, partition and slot movement.
// Preserve AsciiString operator!= instead of spelling its compare call:
// its inline Boolean expression controls ESI/EDI allocation through the tail.
// Both vector providers remain visible so the backing pointer stays in ESI.
// The existing ScienceType instantiations are storage-compatible int providers;
// this consumer makes no claim that army entry IDs are science IDs.
#include "../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct SBServer {
 void *handle;
 SBServer():handle(0){}
 SBServer(const SBServer &);
 ~SBServer(){if(handle)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)handle+((int **)handle)[0][1]));}
 SBServer &operator=(const SBServer &);
};
// Keep the already-inlined unsigned growth comparison local; its external
// template copy differs from the retail provider.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{ return a < b ? b : a; }
}
#include <map>
#include <vector>
#include "ascii_string.h"
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template<> __declspec(dllimport) __forceinline void allocator<int>::deallocate(int *p,size_t) const {if(p)Rva00030830GameFree(p);}
// The proxy deallocate is only inlined here; its unreferenced copy differed
// from the first one in link order.
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<int *, int, allocator<int> >::deallocate(int *__p, size_t __n)
{ __stl_alloc_rebind(__STATIC_CAST(_Base&, *this),(int*)0).deallocate(__p, __n); }
}

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
class Rva005F22D2 { public: void rva005F2295(int); };
#include "../../../../Include/Common/ArmySummaryEntry.h"
class Rva004F6093Holder {
public:
 Rva004F6093Holder():m_p(0){}
 Rva004F6093Holder(const Rva004F6093Holder &);
 ~Rva004F6093Holder(){if(m_p)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)m_p+0xAC));}
 ArmySummaryEntry *get() const {return (ArmySummaryEntry *)m_p;}
private: void *m_p;
};
struct ArmySummaryEntryRef {Rva004F6093Holder m_holder;};
struct ArmyDetailsSummaryRecord {int key;void *entry;};
class ArmySummary {public: ArmySummaryEntryRef GetEntry(int);char pad[0x40];ArmyDetailsSummaryRecord *begin,*end;};
#include "../../../../Include/GameLogic/Rva0040CB2CIndexedField.h"
class Rva0040CC0EIndexedField {public:int get(int) const;};
struct ArmyDetailsArmyView {char pad[0x18];AsciiString name;char gap[0x78-0x1C];ArmySummary *summary;};
struct Rva005E4300Context;
#include "../../../../../Libraries/Source/WWVegas/WWLib/Rva005E4300Cmp.h"
int *__cdecl rva005E49FD(int *,int *,Rva005E4300Cmp,int);
class ArmyDetailsIconSlotView {public:virtual void slot0();virtual void slot1();virtual void MoveTo(int);};
struct ArmyDetailsMemberIconView {int *vbtable;char gap[8];ArmyDetailsIconSlotView *slot;};
struct Rva005E4CA3IconRef {
 ~Rva005E4CA3IconRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)ptr+ptr->vbtable[1]));}
 ArmyDetailsMemberIconView *ptr;
};
enum ScienceType {SCIENCE_NONE=0};

namespace StrategicInGameUI {
class ArmyDetailsPanel {
public:
 class Impl {
 public:
  virtual void OnRemovingEntryFromArmySummary(const ArmySummary &,int);
  virtual void OnEntryAddedToArmySummary(const ArmySummary &,int);
  SBServer CreateIcon(int,ArmySummaryEntry *);
 private:
  char prefix[0x10-4]; ArmyDetailsArmyView *army; Rva005F22D2 *selected; char gap[4];
  _STL::map<int,SBServer> icons; int selectedID;
 };
};
}
void StrategicInGameUI::ArmyDetailsPanel::Impl::OnEntryAddedToArmySummary(const ArmySummary &,int entryID) {
 ArmySummary *summary=army->summary;
 SBServer icon=CreateIcon(entryID,summary->GetEntry(entryID).m_holder.get());
 int entryCount=summary->end-summary->begin;
 _STL::vector<int> entryIDs;
 ((_STL::vector<ScienceType> *)&entryIDs)->reserve((unsigned)icons.size());
 for(int i=0;i<entryCount;++i) {
  int rawEntry=((Rva0040CB2CIndexedField *)summary)->get(i);
  if(*(AsciiString *)(rawEntry+4)!=army->name) {
   int id=((Rva0040CC0EIndexedField *)summary)->get(i);
   ((_STL::vector<ScienceType> *)&entryIDs)->push_back((const ScienceType &)id);
  }
 }
 int *it=rva005E49FD(entryIDs.begin(),entryIDs.end(),Rva005E4300Cmp((Rva005E4300Context *)army),entryID);
 ((ArmyDetailsMemberIconView *)icon.handle)->slot->MoveTo(it-entryIDs.begin());
}
