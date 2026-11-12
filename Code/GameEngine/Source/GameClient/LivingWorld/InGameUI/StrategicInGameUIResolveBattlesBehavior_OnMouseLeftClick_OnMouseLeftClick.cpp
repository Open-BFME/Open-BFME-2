// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
// Split from StrategicInGameUIResolveBattlesBehavior_OnMouseLeftClick.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Split from StrategicInGameUIResolveBattlesBehavior.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
void Rva00576753Func(int a, int b, int c);	// defined in StrategicInGameUIResolveBattlesBehavior.cpp
#include <stdlib.h>
//
// StrategicInGameUI::ResolveBattlesBehavior::Impl (WorldBuilder
// StrategicInGameUIResolveBattlesBehavior.cpp names its translateGameMessage, vtable match).
// Target facts for 0x0057667D: offers the message to its ManualPhaseEnder +0x20 and its PlayerStatusDisplayer (0x005CD690) +0x30, consuming it
// (1) when one does, else defers to the base
// UserInputTranslator::translateGameMessage 0x005CBC95 (WorldBuilder name,
// pinned). Member types are the callees' views (inference).

enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

class GameMessage;

#include "../../../../../Libraries/Include/Lib/ICoord2D.h"

// WB calls IRegion2D::width/height on the click region; retail inlines both
// (the region.cpp rows 0x00004D4B/0x00004D51 are the out-of-line copies), so
// the extents are spelled out in the handler rather than defining second
// copies of those members.
#include "../../../../../Libraries/Include/Lib/IRegion2D.h"

// The translator base (WB UserInputTranslator.cpp): translateGameMessage in
// slot 0, a deleting dtor in slot 1, then the input handlers, whose
// defaults are the shared stubs 0x005748B2 (slot 2 and slots 18..25) and
// 0x005748AD (slots 3..17). Only the slots this unit needs are named.
#include "../../../../Include/GameClient/UserInputTranslator.h"

// The translators behind the behavior (ManualPhaseEnder.cpp's and
// PlayerStatusDisplayer.cpp's units).
#include "../../../../Include/GameLogic/ManualPhaseEnder.h"
namespace StrategicInGameUI
{
}
#include "../../../../Include/GameClient/PlayerStatusDisplayer.h"
namespace StrategicInGameUI
{
}

namespace StrategicInGameUI
{
class ResolveBattlesBehavior
{
public:
	class Impl;
};
}

class StrategicInGameUI::ResolveBattlesBehavior::Impl : public UserInputTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	void rva00576AF3();
 void Update();
 void CreateResolveRegionOwnershipChecklistItems();
 virtual int OnMouseLeftClick(const IRegion2D &region, int modifiers);

private:
	char m_pad04[0x20 - 0x04];
	StrategicInGameUI::ManualPhaseEnder m_phaseEnder; // +0x20
	StrategicInGameUI::PlayerStatusDisplayer m_statusDisplayer; // +0x30
};


class LivingWorldPendingBattle;
class PendingBattleVisitor;
class Rva0020E7E8Callback;
#include "../../../../Include/GameLogic/LivingWorldRegionManager.h"
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct ResolveBattleWorldView
{
    char unknown00[0xB0];
    LivingWorldRegionManager *regionManager;
};
class Object;
class Rva00576BDDDispute;
class PendingBattleVisitor {
public:
 virtual bool Visit(LivingWorldPendingBattle *) = 0;
 ~PendingBattleVisitor() {}
};
#include "../../../../Include/GameClient/Rva0020E7E8Callback.h"
class Rva005766B3 : public PendingBattleVisitor {
public:
 Rva005766B3(int,int,int);
 ~Rva005766B3() {}
 virtual bool Visit(LivingWorldPendingBattle *);
private:
 int a,b,c;
};


class LivingWorldBattle { public: bool rva003F48EF(void *); };
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
// The constructor at 0x005D1DCB is rowed as Rva005D1D38(void *, void *).
class Rva005D1D38 {
public:
 Rva005D1D38(void *, void *);
 char storage[24];
};
class Rva005D1DCB : public Rva005D1D38 {};
namespace StrategicInGameUI {
struct ChecklistItemRef {
 Rva005D1DCB *m_ptr;
 ChecklistItemRef(Rva005D1DCB *p) : m_ptr(p) { if(p) ++*(int *)((char *)p+4); }
 ~ChecklistItemRef() { if(m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr); }
};
class Checklist { public: void AddItem(const ChecklistItemRef &); };
}
// Native vtable86E7D0 slot0 reaches5766D3; pending/completed enumerators
// invoke it with one battle pointer and inspect AL. WB14CFA70 confirms the
// filtered checklist allocation and counted reference. Fields4/8/C remain
// opaque pointer words, matching the existing constructor ABI.
bool Rva005766B3::Visit(LivingWorldPendingBattle *battle) {
 if(((LivingWorldBattle *)battle)->rva003F48EF((void *)a)) {
  StrategicInGameUI::ChecklistItemRef item((Rva005D1DCB *)new Rva005D1D38((void *)c,battle));
  ((StrategicInGameUI::Checklist *)b)->AddItem(item);
 }
 return true;
}


#include "../../../../Include/GameClient/Rva002C025AViewer.h"
class Rva00212728 { public: void *rva00212728(void *); };
class Rva00DFE1C8Host;
// g_00DFE1C8 is only an alias of the owned global TheLivingWorldManager (ledger names column); this unit reads the owner through its own view type.
extern class LivingWorldManager *TheLivingWorldManager;
#define g_00DFE1C8 (*(Rva00DFE1C8Host * *)&TheLivingWorldManager)
#include "../../../../Include/Common/Rva00328A83PtrChaseField.h"
#include "../../../../Include/GameClient/Rva0042D6BAPtrChaseField.h"
#include "../../../../Include/Common/Rva0057C22FByteChaseField.h"
struct Rva002B5C5EVal;
class Rva002B5C5E { public: Rva002B5C5EVal *rva002B5C5E(int); };
#include "../../../../Include/GameLogic/RegionAwardDispute.h"
// The two native owning state holders share the38-byte reset at575674.
// Distinct typed instantiations preserve the native caller's two EH paths;
// each emitted reset is proved byte-and-relocation identical to the owner.
// Slot0 returns the allocation after flags0 destruction. The original class
// identities remain unresolved; these views only express the witnessed ABI.
class ResolveClickState { public: virtual void *deleteInstance(int); };
// The constructor at 0x0057647E is rowed as Rva005764F9(Rva005764F9Holder *, int).
struct Rva005764F9Holder;
class Rva005764F9 : public ResolveClickState { public: Rva005764F9(Rva005764F9Holder *,int); char data[8]; };
class Rva0057647E : public Rva005764F9 {};
class Rva005765D1 : public ResolveClickState { public: Rva005765D1(void *,int,int); char data[8]; };
template<class T> class ResolveClickHolder { public:
 T *p;
 __declspec(noinline) void reset(T *value) {
  if(value==p) return;
  T *old=p; p=value;
  void *released=old ? old->deleteInstance(0) : 0;
  ::operator delete(released);
 }
};
struct ResolveClickUI { void *unknown0; Rva00328A83PtrChaseField *impl; };
struct ResolveClickPlayer { char unknown0[0x14]; int id; };
struct ResolveClickObject { char unknown0[0x10]; void *key; };
struct ResolveClickView {
 char unknown0[0x10]; ResolveClickUI *ui; Rva002C025AViewer *viewer;
 ResolveClickPlayer *player; ResolveClickHolder<Rva0057647E> battle; char unknown20[0x20]; ResolveClickHolder<Rva005765D1> ownership;
};
// Native576946..576ACB and WB14D0EE0 (OnMouseLeftClick, asserts at
// StrategicInGameUIResolveBattlesBehavior.cpp:531..561) independently show
// the point-pick, battle lookup and dispute-resolution branches. The handler
// is a virtual: nothing calls it directly, and it fills slot 18 (+0x48) of
// the Impl vftable 0x00C6E7F0, whose slot 0 is this unit's
// translateGameMessage 0x0057667D and which the Impl constructor 0x00576DF1
// and destructor 0x00576C4B (rowed as Rva00576C4B) install. The base UserInputTranslator::translateGameMessage
// 0x005CBC95 (WB name) dispatches slot +0x48 with argument 0's record (the
// pixel region) and argument 1's integer; WB measures the first argument with
// IRegion2D::width/height (pointer or reference: the codegen is the same).
// The second word is unused here. Point temporaries end immediately after
// picking, allowing retail's subsequent allocation reuse.
int StrategicInGameUI::ResolveBattlesBehavior::Impl::OnMouseLeftClick(const IRegion2D &region, int modifiers) {
 ResolveClickView *state=(ResolveClickView *)this;
 if(region.hi.x-region.lo.x>0 || region.hi.y-region.lo.y>0) return 0;
 if(!state->battle.p) {
  ResolveClickObject *object;
  {
   ICoord2D point; point.x=region.lo.x; point.y=region.lo.y;
   object=(ResolveClickObject *)state->viewer->rva002C025A(&point,1,false);
  }
  if(object) {
   int id=(int)((Rva00212728 *)g_00DFE1C8)->rva00212728(object->key);
   if(id>=0) {
    LivingWorldRegionManager *manager=((ResolveBattleWorldView *)TheLivingWorldLogic)->regionManager;
    LivingWorldPendingBattle *battle=manager->rva0020E501(id);
    if(battle) {
     state->battle.reset((Rva0057647E *)new Rva005764F9((Rva005764F9Holder *)this,(int)battle));
     return 1;
    }
   }
  }
 }
 int hud=state->ui->impl->get();
 Rva0057C22FByteChaseField *dialog=(Rva0057C22FByteChaseField *)((Rva0042D6BAPtrChaseField *)hud)->get();
 if(dialog && !dialog->get()) {
  ResolveClickObject *object;
  {
   ICoord2D point; point.x=region.lo.x; point.y=region.lo.y;
   object=(ResolveClickObject *)state->viewer->rva002C025A(&point,2,false);
  }
  if(object) {
   int id=(int)((Rva00212728 *)g_00DFE1C8)->rva00212728(object->key);
   if(id>=0) {
    RegionAwardDispute *dispute=(RegionAwardDispute *)((Rva002B5C5E *)TheLivingWorldLogic)->rva002B5C5E(id);
    if(dispute) {
     int playerId=state->player->id;
     if(dispute->GetResolvableBy()!=playerId) return 0;
     state->ownership.reset(new Rva005765D1(this,(int)dialog,(int)dispute));
     return 1;
    }
   }
  }
 }
 return 0;
}

// 0x0057539C is rowed as Rva00575383's member forwarder (Rva0057539CForwarders.cpp).
class Rva00575383 { public: void rva0057539C(); };
