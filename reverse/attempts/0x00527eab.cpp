// ?Update@Impl@InGamePlanningModeInterface@@QAEXXZ
// partial score=0.98 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// Native 0x00527EAB..0x00527F65, 186B RET0; WB 0x013D1610 names
// InGamePlanningModeInterface::Impl::Update at lines104..105.
// Target independently proves local player +10, discriminator +750==2,
// level/prefix/state at +0/+4/+8, Open/Close calls and transitions 1/3.
// The discriminator's application meaning is intentionally unasserted.
// No applicable BFME1 planning-mode unit was present at 9cbfb551fe20d.
// Established sibling APT and singleton providers are retained exactly.
// Trial has the correct186-byte instruction body; its one unresolved REL32
// is rva0010231F@Rva0010225F, whose complete229-byte bank keeps a scheduling
// mismatch. No pin or identity alias was added to conceal that dependency.
#include "ascii_string.h"
class PlayerList;
extern PlayerList *ThePlayerList;
struct PlanningPlayerView { unsigned char before750[0x750]; int kind750; };
struct PlanningPlayerListView { unsigned char before10[0x10]; PlanningPlayerView *local10; };
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00222A8BTarget;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *,void *,const char *,const char *);
class Rva001021F7;
Rva001021F7 *Rva00102215Get();
class Rva0010225F { public: void rva0010231F(); void rva00102284(); };
class InGamePlanningModeInterface { public: class Impl; };
class InGamePlanningModeInterface::Impl {
public: void Update();
private: void *level00; AsciiString prefix04; int kind08;
};
void InGamePlanningModeInterface::Impl::Update() {
 PlanningPlayerView *player=reinterpret_cast<PlanningPlayerListView *>(ThePlayerList)->local10;
 if (player && player->kind750==2) {
  if (kind08!=1 && kind08!=2) {
   Rva00524EF4AptCall(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager),level00,prefix04.str(),"Open");
   Rva001021F7 *p=Rva00102215Get();
   if (p) reinterpret_cast<Rva0010225F *>(p)->rva0010231F();
   kind08=1;
  }
 } else {
  if (kind08==1 || kind08==2) {
   Rva00524EF4AptCall(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager),level00,prefix04.str(),"Close");
   Rva001021F7 *p=Rva00102215Get();
   if (p) reinterpret_cast<Rva0010225F *>(p)->rva00102284();
   kind08=3;
  }
 }
}
