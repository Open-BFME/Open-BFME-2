// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
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
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Object;
class Rva00576BDDDispute;
class PendingBattleVisitor {
public:
 virtual bool Visit(LivingWorldPendingBattle *) = 0;
 ~PendingBattleVisitor() {}
};
#include "../../../../Include/GameClient/Rva0020E7E8Callback.h"
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
namespace StrategicInGameUI {
}



class Rva00DFE1C8Host;
// g_00DFE1C8 is only an alias of the owned global TheLivingWorldManager (ledger names column); this unit reads the owner through its own view type.
extern class LivingWorldManager *TheLivingWorldManager;
#define g_00DFE1C8 (*(Rva00DFE1C8Host * *)&TheLivingWorldManager)
#include "../../../../Include/Common/Rva00328A83PtrChaseField.h"
struct Rva002B5C5EVal;
// The two native owning state holders share the38-byte reset at575674.
// Distinct typed instantiations preserve the native caller's two EH paths;
// each emitted reset is proved byte-and-relocation identical to the owner.
// Slot0 returns the allocation after flags0 destruction. The original class
// identities remain unresolved; these views only express the witnessed ABI.
template<class T> class ResolveClickHolder { public:
 T *p;
 __declspec(noinline) void reset(T *value) {
  if(value==p) return;
  T *old=p; p=value;
  void *released=old ? old->deleteInstance(0) : 0;
  ::operator delete(released);
 }
};
// 0x0057539C is rowed as Rva00575383's member forwarder (Rva0057539CForwarders.cpp).
class Rva00575383 { public: void rva0057539C(); };
class Rva005CD010 { public: void rva005CD010(); };
#include "../../../../Include/GameClient/Rva005CCEB6.h"
#include "../../../../Include/GameClient/Rva005CD708.h"
class Rva005D14AB { public: void rva005D14AB(); };
#include "../../../../Include/Common/Rva000AD6F4.h"
#include "../../../../Include/Common/Rva002B5EB5.h"
#include "../../../../Include/Common/Rva0042D6AEPtrChaseField.h"
class ResolveUpdateAction {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void Update();
};
struct ResolveUpdateUIHolder { void *unknown00; Rva00328A83PtrChaseField *impl; };
struct ResolveUpdateWorldView { char unknown00[0x98]; void *localPlayer; };
struct ResolveUpdateImplView {
 char unknown00[0x10];
 ResolveUpdateUIHolder *ui;
 void *viewer;
 void *localPlayer;
 ResolveUpdateAction *battleState;
 char phaseEnder[16];
 char statusDisplayer[16];
 Rva005D14AB *ownershipState;
 bool endPhaseRequested;
};
// Native576D0D..576DCD and WB14D0900: update UI, rebuild player-dependent
// checklist/state holders after a player change, then update phase controls.
// The two neutral outer wrappers57539C and5CD010 independently load their
// implementation at+4 and tail-call5750C7 /5CCFD1; the latter clears a list.
// The WB suggestion for5750C7 contradicts its native no-argument body and is
// deliberately not promoted to a semantic name.
void StrategicInGameUI::ResolveBattlesBehavior::Impl::Update()
{
 ResolveUpdateImplView *state=reinterpret_cast<ResolveUpdateImplView *>(this);
 reinterpret_cast<Rva00575383 *>(state->ui)->rva0057539C();
 void *player=reinterpret_cast<ResolveUpdateWorldView *>(TheLivingWorldLogic)->localPlayer;
 if(player!=state->localPlayer) {
  reinterpret_cast<Rva000AD6F4 *>(&state->battleState)->clear();
  reinterpret_cast<Rva000AD6F4 *>(&state->ownershipState)->clear();
  Rva005CD010 *checklist=reinterpret_cast<Rva005CD010 *>(reinterpret_cast<char *>(this)+4);
  checklist->rva005CD010();
  Rva00576753Func(reinterpret_cast<int>(state->localPlayer),reinterpret_cast<int>(checklist),reinterpret_cast<int>(state->viewer));
  CreateResolveRegionOwnershipChecklistItems();
  state->localPlayer=player;
 }
 if(state->ownershipState) state->ownershipState->rva005D14AB();
 if(state->battleState) state->battleState->Update();
 reinterpret_cast<Rva005CCEB6 *>(reinterpret_cast<char *>(this)+4)->rva005CCEB6();
 reinterpret_cast<StrategicInGameUI::ManualPhaseEnder *>(state->phaseEnder)->Update();
 reinterpret_cast<Rva005CD708 *>(state->statusDisplayer)->rva005CD708();
 if(!state->endPhaseRequested && !state->battleState && reinterpret_cast<Rva002B5EB5 *>(TheLivingWorldLogic)->IsLocalPlayerAllowedToEndPhase()) {
  int hud=state->ui->impl->get();
  int button=reinterpret_cast<Rva0042D6AEPtrChaseField *>(hud)->get();
  if(button) {
   reinterpret_cast<ResolveUpdateAction *>(button)->Update();
   state->endPhaseRequested=true;
  }
 }
}
