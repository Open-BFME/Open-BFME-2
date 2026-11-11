// cl: /O1 /G7 /arch:SSE /MD /D_CRTIMP= /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native5E4B6F..5E4B9D is the complete46B RET8 callback. WB15F9D40
// independently names ArmyDetailsPanel::Impl::OnRemovingEntryFromArmySummary:
// compare entryID with selected28; invoke same-this existing deselection;
// erase iconMap1C by entryID; remove selected entry through member14.
// Constructor5E4AE2 and CreateIcon5E4CA3 witness the same primary receiver,
// offsets and twelve-byte map. Icon insertion uses the existing four-byte
// refcounted value ABI. Retain that provider's provisional SBServer spelling;
// its actual original handle type remains unknown and no GameSpy role is
// asserted. No handle methods or vtables are defined in this consumer.
// Map key erase is a formally proven whole-body/relocation fold onto5E46A8,
// with its42/33/37/37B bound/distance helpers proved recursively. The provider
// instantiation is emitted here by the vendor definition. Its complete
// body and every recursively called helper are admitted by the fold proof;
// keeping that definition visible preserves retail's cached entryID.
struct SBServer { void *handle; SBServer(); SBServer(const SBServer &); ~SBServer(); SBServer &operator=(const SBServer &); };
#include <map>

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
#include "../../../../Include/Common/Rva005E39AE.h"
#include "../../../../Include/GameClient/Rva005F22D2.h"
class ArmySummary;
namespace StrategicInGameUI {
class ArmyDetailsPanel {
public:
 class Impl {
 public:
  virtual void OnRemovingEntryFromArmySummary(const ArmySummary &,int);
  void OnIconLeftClicked(int);
 private:
  char prefix[0x14-4]; Rva005F22D2 *selected; char gap[4];
  _STL::map<int,SBServer> icons; int selectedID;
 };
};
}
void StrategicInGameUI::ArmyDetailsPanel::Impl::OnRemovingEntryFromArmySummary(const ArmySummary &,int entryID) {
 if(entryID==selectedID) reinterpret_cast<Rva005E39AE *>(this)->rva005E3AAA(entryID);
 icons.erase(entryID);
 selected->rva005F2295(entryID);
}

#include "../../../../Include/GameClient/KeyboardClass.h"
extern Keyboard *TheKeyboard;
#include "../../../../Include/GameClient/Rva005F2278.h"
class Rva005E4DAF { public: void Deselect(int); void Select(int); };
struct ArmySelectionCountView { char unknown[0x14]; unsigned count; };
void StrategicInGameUI::ArmyDetailsPanel::Impl::OnIconLeftClicked(int entryID) {
 Rva005E4DAF *actions=(Rva005E4DAF *)this;
 if(TheKeyboard->isCtrl()) {
  if(((Rva005F2278 *)selected)->rva005F2278(entryID)) actions->Deselect(entryID);
  else actions->Select(entryID);
 } else if(((Rva005F2278 *)selected)->rva005F2278(entryID) && ((ArmySelectionCountView *)selected)->count==1) {
  actions->Deselect(entryID);
 } else {
  _STL::map<int,SBServer>::iterator end=icons.end();
  for(_STL::map<int,SBServer>::iterator it=icons.begin(); it!=end; ++it) {
   int key=it->first;
   if(((Rva005F2278 *)selected)->rva005F2278(key)) actions->Deselect(key);
  }
  actions->Select(entryID);
 }
}

// OnIconLeftClicked: native005E50E1..005E5177 is the complete150B RET4
// callback; WB015F86B0 names the method and this file (lines540..541).
// Native begins PUSH EBP/MOV EBP, not the aggregate-copy instruction named
// in the old false-boundary record. Ctrl toggles the clicked ID. Without
// Ctrl, clicking the sole selected ID deselects it; otherwise walk the
// complete icon map and deselect selected IDs before selecting the click.
// The map header is captured before callbacks; the selected collection at
// +14 carries its native count at+14. Existing setters and contains-test
// retain their provider ABI names; the four-byte icon handle stays provisional.
// Every byte including the loop and all direct call sites is exact.
