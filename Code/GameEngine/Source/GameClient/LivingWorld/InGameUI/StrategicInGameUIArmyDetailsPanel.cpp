// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
class Rva005E39AE { public: void rva005E3AAA(int); };
class Rva005F22D2 { public: void rva005F2295(int); };
class ArmySummary;
namespace StrategicInGameUI {
class ArmyDetailsPanel {
public:
 class Impl {
 public:
  virtual void OnRemovingEntryFromArmySummary(const ArmySummary &,int);
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
